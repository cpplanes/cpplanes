/*
 * base_mesh.h
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

#include "edge.h"
#include "element.h"
#include "mesh.h"

namespace cpplanes {

	template <typename _ElementT, typename _EdgeT>
	class BaseMesh : MeshRoot {
	protected:
		/* Storage */
		std::vector<std::vector<int>> elements;
		std::vector<std::vector<int>> edges;
		std::vector<std::vector<real_t>> nodes;

		const MeshConfig config = {
			_ElementT::dimension,
			_ElementT::nb_nodes
		};

	public:
		_ElementT get_element(int id);
		_EdgeT get_edge(int id);

		typedef _ElementT ElementT;
		typedef _EdgeT EdgeT;

		inline int get_nb_elements() { return elements.size(); };
	};

}
