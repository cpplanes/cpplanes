#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# base_mesh.py
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
# Basic mesh routines & classes
#

import numpy as np
import itertools

class MeshError(Exception):
    """ Local exception for debug purposes """
    pass

class Element:
    """ Represent an element
    and store the nodes ids & coords (1 lookup instead of 2).

    To do:
    - add the label
    """

    def __init__(self, nodes, node_ids, dimension=-1):
        self.nodes = nodes
        self.node_ids = node_ids
        self.dimension = dimension

class Edge:
    """ Represent an edge
    and store the nodes ids & coords (1 lookup instead of 2).
    Ideally should also embed a list of elements which it's linked to.

    To do:
    - add the label
    - add references to nearby elements
    """

    def __init__(self, nodes, node_ids, dimension=-1):
        self.nodes = nodes
        self.node_ids = node_ids
        self.dimension = dimension
        self.__length = None

    def get_length(self):
        if self.__length is None:
            distance = lambda n0, n1: np.linalg.norm(np.array(n0)-np.array(n1))
            if self.dimension==1:
                self.__length = distance(self.nodes[0], self.nodes[1])
            elif self.dimension==2:
                self.__length = 0
                for n_pair in itertools.product(self.nodes, self.nodes):
                    current_length = distance(n_pair[0],n_pair[1])
                    if current_length>self.__length:
                        self.__length = current_length
            else:
                raise MeshError(f'Unable to compute length of an edge in dimension {self.dimension}')
        return self.__length

class Mesh:
    """ Stores the mesh

    nodes are stored as a list of vectors (1, 2 or 3D) with the coordinates
    edges are stored as a list of vectors containing references to the linked nodes
    elements are stored as a list of vector containing the nodes

    labels for each are stored in separate vectors

    ids for elements, nodes and edges are the indices in these vectors

    strictly speaking, the vectors should be private and accessors deployed to annotate
    data on-the-fly
    """

    def __init__(self, dimension=-1):

        self.dimension = dimension

        self.nodes = []
        self.elements = []
        self.edges = []
        self.nodes_labels = []
        self.elements_labels = []
        self.edges_labels = []

    def get_element(self, element_ids):
        """ Accessor function for elements returning a (list of) Element object
        corresponding to the given (list of) ids"""
        if type(element_ids)!=list:
            return Element(
                    nodes = [self.nodes[_] for _ in self.elements[element_ids]],
                    node_ids = self.elements[element_ids],
                    dimension = self.dimension
                    )
        else:
            return [
                    Element(
                        nodes = [self.nodes[_] for _ in self.elements[eid]],
                        node_ids = self.elements[eid],
                        dimension = self.dimension
                    ) for eid in element_ids]

    def get_edge(self, edge_ids):
        """ Accessor function for elements returning a (list of) Element object
        corresponding to the given (list of) ids"""
        if type(edge_ids)!=list:

            return Edge(
                    nodes = [self.nodes[_] for _ in self.edges[edge_ids]],
                    node_ids = self.edges[edge_ids],
                    dimension = self.dimension
                    )
        else:
            return [
                    Edge(
                        nodes = [self.nodes[_] for _ in self.edges[eid]],
                        node_ids = self.edges[eid],
                        dimension = self.dimension
                    ) for eid in edge_ids]

    def check_normals(self):
        """ Sanity check for meshs, returns a list of badly oriented triangles
        To be moved to a subclass for triangles (templates ?)
        """

        if len(self.elements[0])!=3:
            raise MeshError('Not applicable to geometries < 2D')

        badly_oriented_elements = []
        for ii in range(len(self.elements)):
            e = self.get_element(ii)

            P1 = np.array(e.nodes[0])
            P2 = np.array(e.nodes[1])
            P3 = np.array(e.nodes[2])

            normal = np.cross(P2-P1, P3-P1)

            if normal<0:
                badly_oriented_elements.append(ii)

        return badly_oriented_elements


