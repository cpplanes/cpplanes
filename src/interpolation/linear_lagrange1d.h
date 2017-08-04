/*
 * linear_lagrange1d.h
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

#include <Eigen/Dense>

#include "linear_lagrange.h"
#include "../types.h"

using namespace Eigen;
using cpplanes::Matrix2r;

namespace cpplanes {

	class LinearLagrange1D : LinearLagrange<Element1D, Matrix2r> {
	private:
		int integration_order;
		Matrix2r unit_H, unit_Q;

	public:
		LinearLagrange1D(
			integration::IntegrationScheme integration_scheme,
			int integration_order
		);

		virtual void get_H(Element1D const& element, Matrix2r const& H_);
		virtual void get_Q(Element1D const& element, Matrix2r const& Q_);
	};

}
