/*
 * base_mesh.cpp
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

#include "base_mesh.h"

namespace cpplanes {

	template <typename _ElementT, typename _EdT>
	_ElementT BaseMesh<_ElementT, _EdT>::get_element(int id) {
		// TODO : bound testing & custom exception
		std::vector<int> nodes_id = elements.at(id);
		std::vector<std::vector<real_t>> nodes_coords(nodes_id.size());
		for (auto n_id : nodes_id) {
			nodes_coords.push_back(nodes.at(n_id));
		}

		return _ElementT(nodes_id, nodes_coords, config.dimension);
	}

	template <typename _ElT, typename _EdgeT>
	_EdgeT BaseMesh<_ElT, _EdgeT>::get_edge(int id) {
		// TODO : bound testing & custom exception
		std::vector<int> nodes_id = edges.at(id);
		std::vector<std::vector<real_t>> nodes_coords(nodes_id.size());
		for (auto n_id : nodes_id) {
			nodes_coords.push_back(nodes.at(n_id));
		}

		return _EdgeT(nodes_id, nodes_coords, config.dimension);
	}
}

