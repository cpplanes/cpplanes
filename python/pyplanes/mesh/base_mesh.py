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

class Element:

    def __init__(self, nodes, node_ids):
        self.nodes = nodes
        self.node_ids = node_ids

class Edge:

    def __init__(self, nodes, node_ids):
        self.nodes = nodes
        self.node_ids = node_ids


class Mesh:

    def __init__(self):

        self.nodes = []
        self.elements = []
        self.edges = []
        self.nodes_labels = []
        self.elements_labels = []
        self.edges_labels = []

