/*
 * Mesh.h
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

#ifndef __Mesh_h__
#define __Mesh_h__

#include "config.h"

#include <array>
#include <vector>

namespace mesh {

class Element {
public:
	std::array<int, MAX_NODES_PER_ELEMENT> nodes = {-1};
	int nb_nodes;
};

class Edge {
public:
	std::array<int, MAX_NODES_PER_EDGE> nodes = {-1};
	std::array<int, MAX_ELEMENTS_PER_EDGE> elements = {-1};
	// linsys::BC type;
};

class Node {
public:
	int index;
	std::array<int, MAX_COORDS_PER_NODE> coords = {-1};
};

class Mesh {
	/*
	 * A mesh stores the geometrical features (nodes and positions, edges, connectivity
	 * tables and elements).
	 *
	 */

private:
protected:
public:
	std::vector<Element> elements;
	std::vector<Edge> edges;
	std::vector<Node> nodes;
	Mesh slice(std::vector<Node> nodes);
};

}

#endif /* !__Mesh_h__ */

