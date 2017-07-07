#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# freefem.py
#
# This file is part of cpplanes, a software distributed under the MIT license.
# For any question, please contact one of the authors cited below.
#
# Copyright (c) 2017
# 	Olivier Dazel <olivier.dazel@univ-lemans.fr>
# 	Mathieu Gaborit <gaborit@kth.se>
# 	Peter Göransson <pege@kth.se>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#

from ..base_mesh import Mesh

def freefem_read(filename):

    with open(filename, 'r') as fh:

        # the first line gives the number of nodes, elements and edges
        l = fh.readline()
        Nnodes, Nelements, Nedges = map(int, l.split(' '))

        remaining = fh.readlines()

    node_related_lines = remaining[:Nnodes-1]
    remaining = remaining[Nnodes:]
    element_related_lines = remaining[:Nelements-1]
    remaining = remaining[Nelements:]
    edge_related_lines = remaining[:Nedges-1]
    remaining = remaining[Nedges:]

    if len(remaining)!=0:
        print('May be an issue while reading the mesh')

    # insert into a mesh object
    mesh = Mesh()

    cleaner = lambda _: map(float, _.split(' '))
    nodes_raw = map(
        cleaner,
        node_related_lines
    )

    for e in nodes_raw:
        e = list(e)
        mesh.nodes.append((e[0], e[1]))
        mesh.nodes_labels.append(e[2])

    del nodes_raw
    del node_related_lines

    elements_raw = map(
        cleaner,
        element_related_lines
    )

    for e in elements_raw:
        e = list(e)
        mesh.elements.append((e[0], e[1], e[2]))
        mesh.elements_labels.append(e[3])

    del elements_raw
    del element_related_lines

    edges_raw = map(
        cleaner,
        edge_related_lines
    )

    for e in edges_raw:
        e = list(e)
        mesh.edges.append((e[0], e[1]))
        mesh.edges_labels.append(e[2])

    del edges_raw
    del edge_related_lines

    return mesh
