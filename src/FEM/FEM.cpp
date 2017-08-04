/*
 * FEM.cpp
 *
 * This file is part of cpplanes, a software distributed under the MIT license.
 * For any question, please contact one of the authors cited below.
 *
 * Copyright (c) 2017
 * 	Olivier Dazel <olivier.dazel@univ-lemans.fr>
 * 	Mathieu Gaborit <gaborit@kth.se>
 * 	Peter Göransson <pege@kth.se>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 */

#include <numeric>

#include "FEM.h"

using namespace Eigen;

namespace cpplanes {

	template <typename _MeshT, class _Interp>
	FEM<_MeshT, _Interp>::FEM(
		const PhysicalModel& medium,
		const _MeshT& mesh,
		const _Interp& interp,
		const std::vector<std::shared_ptr<BCBase>> boundary_conditions
	):
		medium{medium}, mesh{mesh},
		interp{interp}, boundary_conditions{boundary_conditions} {

		map_dof_node.resize(mesh.element.size()*ElementT::nb_nodes);
		std::iota(map_dof_node.begin(), map_dof_node.end(), 0);

	}

	template <typename _MeshT, class _Interp>
	void FEM<_MeshT, _Interp>::assemble(cplx_t f) {
		cplx_t k = medium.get_Pwn(f);

		// Empty and resize the triplets' vector
		A_triplets.erase(A_triplets.begin(), A_triplets.end());
		A_triplets.resize(mesh.config.nodes_per_element^2*mesh.get_nb_elements());

		// Main assembly
		int list_position = 0;
		ElementT element;
		MatrixT Qe, He, elem_matrix;
		int i_n0, i_n1, n0, n1;
		for (int element_id = 0; element_id < mesh.elements.size(); ++element_id) {
			element = mesh.get_element(element_id);

			interp.get_Q(element, Qe);
			interp.get_H(element, He);

			elem_matrix = He-k^2*Qe;

			for (i_n0 = 0; i_n0 < ElementT::nb_nodes; ++i_n0) {
				for (i_n1 = 0; i_n1 < ElementT::nb_nodes; ++i_n1) {
					n0 = element.nodes_id(i_n0);
					n1 = element.nodes_id(i_n1);

					A_triplets.at(list_position) = {{
							map_dof_node.at(n0),
							map_dof_node.at(n1),
							elem_matrix(i_n0, i_n1)
						}
					};
				}
			}
			++list_position;
		}

		// Boundary conditions
		int nb_added_coefs = 0;
		for (auto bc : boundary_conditions ) {
			bc->evaluate(f);
			nb_added_coefs += bc->nb_added_coefs;
		}

		A_triplets.resize(A_triplets.size()+nb_added_coefs);
		b.resize(mesh.get_nb_elements()*ElementT::nb_nodes);

		// TODO: manage resizes
		for (auto bc : boundary_conditions ) {
			for (auto a_mod : bc->A) {
				A_triplets.at(list_position) = {{
						map_dof_node.at(int(a_mod.row())),
						map_dof_node.at(int(a_mod.col())),
						a_mod.value()
					}
				};
			}
			for (auto b_mod : bc->b) {
				b(map_dof_node.at(int(b_mod.at(0)))) += b_mod.at(1);
			}
		}

		A.resize(mesh.get_nb_elements()*ElementT::nb_nodes);
		A.setFromTriplets(A_triplets.begin(), A_triplets.end());


		assembled_frequency = f;
	}


	template <typename _MeshT, class _Interp>
	void FEM<_MeshT, _Interp>::solve(cplx_t f) {
		if (assembled_frequency != f) {
			assemble(f);
		}

		SparseLU<SparseMatrix<cplx_t, ColMajor>, COLAMDOrdering<Index> > solver;
		solver.analyzePattern(A);
		solver.factorize(A);

		x = solver.solve(b);
	}

}

