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

import numpy as np

from .base_bc import BoundaryCondition
from ..materials import Fluid
from ..integration import GaussLegendre


class UnitVelocity(BoundaryCondition):
    """
    Forces a unit velocity on the desired nodes
    """

    def __init__(self, edges, material):
        super().__init__(edges=edges, material=material)

    def evaluate(self, f):
        if isinstance(self.material, Fluid):
            """ Unit velocity for fluids

            grad(p) = j rho omega v

            The alteration is done in b only, A is left untouched.
            """
            omega = 2*np.pi*f

            if self.edges[0].dimension == 1:
                self.b_r = self.get_all_node_ids()
                self.b_c = [0]*len(self.b_r)
                self.b_v = [1j*self.material.rho*omega]*len(self.b_r)

            elif self.edges[0].dimension == 2:
                for e in self.edges:

                    current_b_v = np.array([0,0], dtype=np.complex128)

                    GP = GaussLegendre.get_order(4)
                    for i in range(GP['nb_interp_points']):
                        x_i = GP['x_i'][i]
                        w_i = GP['w_i'][i]
                        current_b_v += np.array([
                            (1-x_i)/2,
                            (1+x_i)/2
                        ], dtype=np.complex128)*w_i
                    current_b_v *= (e.get_length()/2)*(1j*self.material.rho*omega)

                    self.b_v += current_b_v.tolist()
                    self.b_c += [0]*len(e.nodes)
                    self.b_r += e.node_ids
            else:
                return False
        else:
            return False
        return True
