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
from ..integration.gauss_legendre import GaussLegendreTriangle

class LinearLagrangeInterpolator(Interpolator):
    """ Linear interpolator using a set of Lagrange shape functions
    and Gauss-Legendre as integration strategy.


    Q : Phi*Phi
    H : Phi'*Phi'
    """

    def __init__(self, dim=1, integration_scheme=GaussLegendreTriangle):

        super().__init__()
        self.dim = dim
        self.__integration_scheme = integration_scheme

        if self.dim==1:
            self.__Q = 1/6*np.matrix([[2, 1], [1, 2]])
            self.__H = np.matrix([[1, -1], [-1, 1]])
            self.__last_h = None

    def interpolate_over(self, element):
        """ Dimension-based dispatcher """
        if self.dim==1:
            return self.__1dinterp(element)
        if self.dim==2:
            return self.__2dinterp(element)

    def __1dinterp(self, element):
        """ 1D (line) interpolation

        This is almost entirely precomputed
        The function implements a naive caching strategy for
        fun and later use... may be.
        """
        h = np.abs(element.nodes[1][0]-element.nodes[0][0])
        if self.__last_h!=h:
            self.__last_h = h
            self.__interpolated_tuple = (
                    h*self.__Q,
                    1/h*self.__H
                    )
        return self.__interpolated_tuple

    def __2dinterp(self, element):
        """ 2D (triangle) interpolation

        (no caching this time)

        To do :
        - make clear the "triangle" part (or better, find an implementation for any
          n-sided flat convex polygon and let the element type govern)
        """
        # prepare nodes for multiplication
        nodes = np.array(element.nodes, dtype=np.float64)
        GP = self.__integration_scheme.get_order(4)

        x0 = GP['x_i'][0]
        x1 = GP['x_i'][1]
        w0 = GP['w_i'][0]
        w1 = GP['w_i'][1]

        ksi_eta_map = np.array([
            [x0, x0],
            [1-2*x0, x0],
            [x0, 1-2*x0],
            [x1, x1],
            [1-2*x1, x1],
            [x1, 1-2*x1]
        ])

        weights = 3*[w0]+3*[w1]

        H = np.zeros((3,3))
        Q = np.zeros((3,3))

        interp_fun_deriv = np.array([
            [-1, 1, 0],
            [-1, 0, 1]
        ], dtype=np.float64)
        for i_pg in range(GP['nb_interp_points']):
            ksi = ksi_eta_map[i_pg, 0]
            eta = ksi_eta_map[i_pg, 1]

            interp_fun = np.array([1-ksi-eta, ksi, eta])

            J = np.dot(interp_fun_deriv, nodes)
            w = weights[i_pg]*np.linalg.det(J)

            JinvInterpDeriv = np.dot(np.linalg.inv(J), interp_fun_deriv)
            H += w*np.dot(JinvInterpDeriv.T, JinvInterpDeriv)

            Q += w*np.outer(interp_fun, interp_fun)

        return (Q, H)
