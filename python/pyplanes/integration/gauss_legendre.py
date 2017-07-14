#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# gauss_legendre.py
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

from .base_integration import IntegrationScheme


class GaussLegendre(IntegrationScheme):
    """
    Storage class for Gauss-Legendre coefficients and easy access later
    """

    Order = {
        4: {
            'nb_interp_points': 6,
            'x_i': [0.445948490915965, 0.091576213509771],
            'w_i': [0.111690794839005, 0.054975871827661]
        }
    }

    # TODO: should override compute_order()
