#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# lagrange.py
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

from .base_interp import Interpolator

class LinearLagrangeInterpolator(Interpolator):

    def __init__(self, dim=1):

        super().__init__()
        self.dim = dim

        if self.dim==1:
            self.__PhiPhi = 1/6*np.matrix([[2, 1], [1, 2]])
            self.__PhipPhip = np.matrix([[1, -1], [-1, 1]])
            self.__last_h = None

    def interpolate_over(self, element):
        if self.dim==1:
            return self.__1dinterp(element)

    def __1dinterp(self, element):
        h = np.abs(element.nodes[1][0]-element.nodes[0][0])
        if self.__last_h!=h:
            self.__last_h = h
            self.__interpolated_tuple = (
                    h*self.__PhiPhi,
                    1/h*self.__PhipPhip
                    )
        return self.__interpolated_tuple



