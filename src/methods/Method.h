/*
 * Method.h
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

#ifndef __Method_h__
#define __Method_h__

#include <Eigen/Sparse>
#include <Eigen/Dense>
#include "../config.h"
#include "../utils.h"
#include "../Mesh.h"

using namespace Eigen;
using namespace cpplanes;

namespace method {

class Method {
public:
	Matrix<real_t, Dynamic, Dynamic> get_H(std::array<mesh::Node, MAX_NODES_PER_ELEMENT> nodes);
	Matrix<real_t, Dynamic, Dynamic> get_Q(std::array<mesh::Node, MAX_NODES_PER_ELEMENT> nodes);

	SparseMatrix<cplx_t> assemble(cplx_t frequency, int linsys_size, mesh::Mesh mesh);

	// virtual void adapt_mesh(mesh::Mesh mesh);
	// virtual get_M()
	// virtual get_K1()
	// virtual get_K1()
};

}

#endif /* !__Method_h__ */

