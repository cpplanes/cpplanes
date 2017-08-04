/*
 * element.cpp
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

#include "element.h"

#include <cmath>

namespace cpplanes {

	template<int _DIM, int _NB_N>
	Element<_DIM, _NB_N>::Element(std::vector<int> nodes_id,
		std::vector<std::vector<real_t>> nodes_coords):
		nodes_id(nodes_id), nodes_coords(nodes_coords) {}

	Element1D::Element1D(
		std::vector<int> nodes_id,
		std::vector<std::vector<real_t>> nodes_coords
	): Element(nodes_id, nodes_coords) {
		// TODO: check vectors' size
	}

	real_t Element1D::get_length() {
		return static_cast<real_t>(
				std::abs(nodes_coords[0][0] - nodes_coords[1][0])
			);
	}

}

