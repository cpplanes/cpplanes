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
import scipy.sparse.linalg as splinalg


class FEM:
    """ Finite Element procedure

    I tried to keep it applicable to most geometries

    To do:
    - Make this class inherit from a Method super class for easier handling in C++
    - May be use multiple inheritance to inherit from Domain (which is finally a simple
      storage)
    - Method to Method hybrids have to be thought though... would it be easier to iterate
    """

    def __init__(self, interp, *args, **kwargs):
        """ Store domain and interpolation technique """
        super(FEM, self).__init__(*args, **kwargs)
        self.interp = interp

        self.__assembled_frequency = None

        self.map_dof_node = list(range(len(self.mesh.nodes)))
        self.removed_nodes = []
        self.A = None
        self.b = None

    def assemble(self, f=1000):

        k = self.material.get_wavenumber(f)

        self.__assembled_frequency = f
        self.__assembled_wavenumber = k

        A_r, A_c, A_v = [], [], []
        b_r, b_c, b_v = [], [], []

        for element in (self.mesh.get_element(_) for _ in range(len(self.mesh.elements))):

            (Qe, He) = self.interp.interpolate_over(element)
            elem_matrix = He-k**2*Qe

            for i_n1, n1 in enumerate(element.node_ids):
                for i_n2, n2 in enumerate(element.node_ids):
                    A_r.append(self.map_dof_node[n1])
                    A_c.append(self.map_dof_node[n2])
                    A_v.append(elem_matrix[i_n1, i_n2])

        for bc in self.boundary_conditions:
            bc.evaluate(f=f)
            A_r += bc.A_r
            A_c += bc.A_c
            A_v += bc.A_v
            b_r += bc.b_r
            b_c += bc.b_c
            b_v += bc.b_v
            self.removed_nodes += bc.null_nodes

        for n in self.removed_nodes:
            self.map_dof_node.remove(n)

        self.A = sparse.coo_matrix((A_v, (A_r, A_c)), dtype=np.complex128).tocsr()
        self.b = sparse.coo_matrix((b_v, (b_r, b_c)), shape=(self.A.shape[0], 1), dtype=np.complex128)
        self.b = self.b.toarray()

        deleted_rows = self.removed_nodes
        rows_mask = np.ones(self.A.shape[0], dtype=bool)
        rows_mask[deleted_rows] = False
        self.A = self.A[rows_mask]

        deleted_cols = self.removed_nodes
        self.A = self.A.tocsc()
        all_cols = np.arange(self.A.shape[1])
        cols_to_keep = np.where(np.logical_not(np.in1d(all_cols, deleted_cols)))[0]
        self.A = self.A[:, cols_to_keep]

        self.b = self.b[rows_mask]

    def solve(self, f=1000):
        if self.__assembled_frequency != f:
            self.assemble(f=f)
        if self.A is None or self.b is None:
            raise ValueError('System flagged as assembled but no value found.')

        self.x = splinalg.spsolve(self.A, self.b)

        self.solution = np.zeros((len(self.mesh.nodes),), dtype=np.complex128)
        self.solution[np.r_[self.map_dof_node]] = self.x
        return self.solution
