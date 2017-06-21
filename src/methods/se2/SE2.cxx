/*
 * SE2.cpp
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

#include "SE2.h"
#include "../../Model.h"
#include <cmath>
#include <Eigen/Sparse>
#include <Eigen/Dense>

namespace se2 {
using namespace Eigen;

Matrix<double, 2, 2> SE2::get_H(std::array<Node, 2> nodes) {
	double h = std::abs(nodes[0].coords[0]-nodes[1].coords[0]);
	matrix<double> H(2,2);
	H(0,0) = 1/h;
	H(0,1) = -1/h;
	H(1,0) = -1/h;
	H(1,1) = 1/h;
	return H
}

Matrix<double, 2, 2> SE2::get_Q(std::array<Node, 2> nodes) {
	double h = std::abs(nodes[0].coords[0]-nodes[1].coords[0]);
	matrix<double> H(2,2);
	H(0,0) = 2*h/6;
	H(0,1) = h/6;
	H(1,0) = h/6;
	H(1,1) = 2*h/6;
	return H
}

SparseMatrix<cplx_t> SE2::assemble(cplx_t frequency, int linsys_size,  mesh::Mesh mesh) {
	SparseMatrix<cplx_t> A_domain(linsys_size, linsys_size);
	Matrix<cplx_t, 2, 2> A_elem(2, 2);

	for (auto element : mesh.elements) {
		int ni = element.nodes[0].index;
		// TODO: Generalize this !
		A_domain(range(ni,ni+1), range(ni,ni+1)) = get_H(element.nodes);
	}

	return A_domain;
}

}

