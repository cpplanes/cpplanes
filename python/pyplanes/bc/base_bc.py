#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# base_bc.py
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

from functools import reduce

class BoundaryCondition:
    """
    Base class for boundary conditions

    Boundary conditions are evaluated by calling BC.evaluate(frequency). The alterations
    on A and b are stored in COO format right in the BC instantiated object.
    Nodes to be removed from the linear system are not deleted right away but marked
    for deletion, allowing to evaluation BC in any order (parallelization in mind!)


    Improvement:
    We could drop b's column index vector since b is a column vector itself.
    """

    def __init__(self, edges, material):
        """ Constructor
        edges -- edges on which the BC is applied
        material -- material in the domain (to be modified & passed by evaluate() )
        """
        self.edges = edges
        self.material = material

        # maintain a list of affected nodes for easy access
        self.all_node_ids = list(set(
            reduce(
                lambda acc, b: acc+b.node_ids,
                self.edges,
                []
            )
        ))

        # prepare storage of end-value
        self.A_r = []
        self.A_c = []
        self.A_v = []
        self.b_r = []
        self.b_c = []
        self.b_v = []
        self.null_nodes = []

    def evaluate(self, f):
        """
        Evaluate the boundary condition & return True if successful
        """
        return False
