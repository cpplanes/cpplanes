#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# FEM.py
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
import scipy.sparse as sparse
from scipy.sparse.linalg import spsolve

class FEM:

    def __init__(self, domain, interp):
        self.domain = domain
        self.material = self.domain.material
        self.mesh = self.domain.mesh
        self.interp = interp

        self.__assembled_frequency = None

        self.A = None
        self.b = None

    def assemble(self, f=1000):

        k = self.material.get_wavenumber(f)

        self.__assembled_frequency = f
        self.__assembled_wavenumber = k

        A_r, A_c, A_v = [], [], []
        b_r, b_c, b_v = [], [], []
        l_r = [0, 0, 1, 1]
        l_c = [0, 1, 0, 1]

        for element in (self.mesh.get_element(_) for _ in range(len(self.mesh.elements))):

            (Me, Ke) = self.interp.interpolate_over(element)
            elem_matrix = Ke-k**2*Me
            _r = [element.node_ids[_] for _ in l_r]
            _c = [element.node_ids[_] for _ in l_c]
            _v = [elem_matrix[l_r[_], l_c[_]] for _ in range(len(_r))]

            A_r += _r
            A_c += _c
            A_v += _v

        deleted_rows = []
        deleted_cols = []
        for bc in self.domain.boundary_conditions:
            bc.evaluate(f=f)
            A_r += bc.A_r
            A_c += bc.A_c
            A_v += bc.A_v
            b_r += bc.b_r
            b_c += bc.b_c
            b_v += bc.b_v
            deleted_rows += bc.deleted_rows
            deleted_cols += bc.deleted_cols

        self.A = sparse.csr_matrix((A_v, (A_r, A_c)),
                shape=(len(self.mesh.nodes),len(self.mesh.nodes)))
        self.b = sparse.csr_matrix((b_v, (b_r, b_c)), shape=(len(self.mesh.nodes),1))
        self.b = self.b.toarray()

        rows_mask = np.ones(self.A.shape[0], dtype=bool)
        rows_mask[deleted_rows] = False
        self.A = self.A[rows_mask]

        self.A = self.A.tocsc()
        all_cols = np.arange(self.A.shape[1])
        cols_to_keep = np.where(np.logical_not(np.in1d(all_cols, deleted_cols)))[0]
        self.A = self.A[:, cols_to_keep]

        self.b = self.b[rows_mask]

    def solve(self, f=1000):
        if self.__assembled_frequency!=f:
            self.assemble(f=f)
        if self.A is None or self.b is None:
            raise ValueError('System flagged as assembled but no value found.')

        self.x = sparse.linalg.spsolve(self.A, self.b)
        return self.x

