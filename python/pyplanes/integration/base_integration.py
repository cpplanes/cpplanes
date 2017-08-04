#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# base_integration.py
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

class IntegrationScheme:
    """ Integration Scheme are represented through storage-like
    classes containing pre-computed coefficients for often used orders
    and a class method to compute on the fly the others"""

    Order = {}

    @classmethod
    def get_order(cls, n):
        """ Operate the lookup in Order and return either the
        found spec or a version computed on-the-fly """

        precomputed = cls.Order.get(n)
        if precomputed is None:
            return cls.compute_order(n)
        else:
            return precomputed

    @classmethod
    def compute_order(cls, n):
        """ Compute coefficient for order n """
        raise NotImplementedError('This function must be overrided by subclasses')
