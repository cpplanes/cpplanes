/*
 * edge.cpp
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

#include "edge.h"

#include "../mathutils.h"

using cpplanes::VectorXr;

namespace cpplanes {

	template<int _DIM, int _NB_N>
	Edge<_DIM, _NB_N>::Edge(
		std::vector<int> nodes_id,
		std::vector<std::vector<real_t>> nodes_coords
	): nodes_id(nodes_id), nodes_coords(nodes_coords), dimension(dimension) {}

	template<int _DIM, int _NB_N>
	real_t Edge<_DIM, _NB_N>::get_length() {
		if (length < 0) {
			real_t max_sqdlength = 0, current_sqdlength;
			VectorXr v1, v2, v_difference;

			int vectors_size = nodes_coords[0].size();
			for (std::vector<real_t> coords1 : nodes_coords) {
				v1 = VectorXr::Map(coords1.data(), vectors_size);

				for (std::vector<real_t> coords2 : nodes_coords) {
					v2 = VectorXr::Map(coords2.data(), vectors_size);

					v_difference = v1 - v2;
					current_sqdlength = v_difference.squaredNorm();
					if (current_sqdlength > max_sqdlength) {
						max_sqdlength = current_sqdlength;
					}
				}
			}
			length = std::sqrt(max_sqdlength);
		}
		return length;
	}

}

