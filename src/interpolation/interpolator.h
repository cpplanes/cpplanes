/*
 * interpolator.h
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

#include <Eigen/Core>

#include "../mesh/element.h"

using namespace Eigen;

namespace cpplanes {

	template <typename _MatrixT, typename _ElementT>
	class Interpolator {
	protected:
		int dimension;

	public:
		Interpolator(int dimension = -1);

		typedef _MatrixT MatrixT;
		typedef _ElementT ElementT;

		virtual void get_Q(_ElementT const& element, _MatrixT const& Q_) const;
		virtual void get_H(_ElementT const& element, _MatrixT const& H_) const;
	};

}

