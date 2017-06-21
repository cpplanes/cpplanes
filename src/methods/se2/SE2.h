/*
 * SE2.h
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

#ifndef __SE2_h__
#define __SE2_h__

#include "../Method.h"
#include "../../Mesh.h"
#include "../../Medium.h"
#include "../../utils.h"
#include <Eigen/Sparse>

using namespace Eigen;
using namespace cpplanes;

namespace se2 {

class SE2: public method::Method {
public:
	int size();
	SparseMatrix<cplx_t> assemble(cplx_t frequency, int linsys_size,  mesh::Mesh mesh);
};

}

#endif /* !__SE2_h__ */

