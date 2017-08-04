/*
 * FEM.h
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

#pragma once

#include <vector>
#include <memory>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include "../medium/medium.h"
#include "../bc/bc.h"
#include "../method.h"
#include "../types.h"

using namespace Eigen;

namespace cpplanes {

	template <typename _MeshT, class _Interp>
	class FEM : public Method {
	private:
		const PhysicalModel& medium;
		const _MeshT& mesh;
		const _Interp& interp;
		const std::vector<std::shared_ptr<BCBase>> boundary_conditions;

		real_t assembled_frequency;
		std::vector<int> map_dof_node;
		std::vector<int> removed_nodes;

		std::vector<Triplet<real_t>> A_triplets;

		SparseMatrix<cplx_t> A;
		VectorXc b;
		VectorXc x;
		VectorXc solution;

	protected:
		// Protected constructor, this class should not
		// be instanciated without being subclassed
		FEM(
			const PhysicalModel& medium,
			const _MeshT& mesh,
			const _Interp& interp,
			const std::vector<std::shared_ptr<BCBase>> boundary_conditions
		);

		void assemble(cplx_t frequency);
		void solve(cplx_t frequency);

	public:
		typedef _MeshT MeshT;
		typedef typename MeshT::ElementT ElementT;
		typedef typename _Interp::MatrixT MatrixT;
	};

}

