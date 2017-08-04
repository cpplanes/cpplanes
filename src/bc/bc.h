/*
 * bc.h
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

#include <Eigen/Sparse>
#include <Eigen/Dense>

#include "../types.h"

using namespace Eigen;

namespace cpplanes {

	class BCBase {
	public:
		virtual void evaluate(cplx_t frequency);

		int nb_added_coefs;
		std::vector<Triplet<cplx_t>> A;
		std::vector<std::vector<cplx_t>> b;
		std::vector<int> remove_nodes;
	};
}

