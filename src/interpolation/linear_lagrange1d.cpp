/*
 * linear_lagrange1d.cpp
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

#include "linear_lagrange1d.h"

#include <vector>

using namespace Eigen;
using cpplanes::Matrix2r;
using cpplanes::Vector2r;

namespace cpplanes {

	LinearLagrange1D::LinearLagrange1D(
		integration::IntegrationScheme integration_scheme,
		int integration_order
	): LinearLagrange(integration_scheme, 1), integration_order(integration_order) {
		unit_Q << 2 / 6, 1 / 6, 1 / 6, 2 / 6;
		unit_H << 1, -1, -1, 1;
	}

	void LinearLagrange1D::get_Q(Element1D const& element, Matrix2r const& Q_) {
		Map<Vector2r>
		n0(static_cast<std::vector<real_t>>(element.nodes_coords.at(0)).data()),
		n1(static_cast<std::vector<real_t>>(element.nodes_coords.at(1)).data());
		real_t length = (n0 - n1).norm();
		Matrix2r& Q = const_cast<Matrix2r&>(Q_);
		Q = length * unit_Q;
	}

	void LinearLagrange1D::get_H(Element1D const& element, Matrix2r const& H_) {
		Map<Vector2r>
		n0(static_cast<std::vector<real_t>>(element.nodes_coords.at(0)).data()),
		n1(static_cast<std::vector<real_t>>(element.nodes_coords.at(1)).data());
		real_t length = (n0 - n1).norm();
		Matrix2r& Q = const_cast<Matrix2r&>(H_);
		Q = 1 / length * unit_Q;
	}

}

