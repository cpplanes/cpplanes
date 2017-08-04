/*
 * edge.h
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

#include "../types.h"

namespace cpplanes {

	template <int _DIMENSION, int _NB_NODES>
	class Edge {
	private:
		real_t length;

	protected:
		const std::vector<int> nodes_id;
		const std::vector<std::vector<real_t>> nodes_coords;
		const int dimension = _DIMENSION;
		const int nb_nodes = _NB_NODES;

	public:
		Edge(
			std::vector<int> nodes_id,
			std::vector<std::vector<real_t>> nodes_coords
		);

		virtual real_t get_length();
	};


	class Edge1D: public Edge<1, 1> {
	public:
		Edge1D(
			std::vector<int> nodes_id,
			std::vector<std::vector<real_t>> nodes_coords
		);

		inline virtual real_t get_length() override { return 0; }
	};

}

