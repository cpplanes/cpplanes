#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# fluid.py
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

from .base_material import Material

class Fluid(Material):
    """ Fluid medium class

    To do:
    - use the right parameters (not only rho and c)
    - implement a refresh() function to recompute the
      frequency dependent variables
    """

    def __init__(self, rho, c):
        super().__init__()
        self.rho = rho
        self.c = c

    def get_wavenumber(self, f):
        return 2*np.pi*f/self.c
