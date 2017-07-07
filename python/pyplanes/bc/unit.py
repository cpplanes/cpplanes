#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# unit.py
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

from .base_bc import BoundaryCondition

class UnitPressure(BoundaryCondition):
    """
    Apply a unit pressure on the desired nodes
    """

    def __init__(self, edges):
        super().__init__(edges=edges)

    def evaluate(self, f):
        self.A_r = []
        self.A_c = []
        self.A_v = []
        self.b_r = self.all_node_ids
        self.b_c = [0]*len(self.all_node_ids)
        self.b_v = [1]*len(self.all_node_ids)
        self.deleted_rows = []
        self.deleted_cols = []

        return True



