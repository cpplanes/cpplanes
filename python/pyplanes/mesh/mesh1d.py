#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# mesh1d.py
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

from .base_mesh import Mesh


class Mesh1D(Mesh):

    def __init__(self, length, start=0, N=10):
        """
        length: length of the domain
        start: start coordinate
        N: number of elements
        """
        super().__init__(dimension=1)

        self.start = start
        self.end = start+length
        self.N = N

        self.node_spacing = (self.end-self.start)/self.N

        self.nodes = [(_*self.node_spacing,) for _ in range(self.N+1)]
        self.elements = [(_, _+1) for _ in range(len(self.nodes)-1)]
        self.edges = [[_] for _ in range(len(self.nodes))]
