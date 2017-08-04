#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# system.py
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

import scipy.sparse as sparse


class System:

    def __init__(self, domains=None):

        self.domains = domains if domains is not None else []

        self.interfaces = self.find_interfaces()
        self.materials = self.gather_material_references()

        self.A = None
        self.b = None

    def gather_material_references(self):
        material_references = set()
        for d in self.domains:
            material_references.add(d.material)

        return material_references

    def find_interfaces(self):
        """ Iterate over the list of domains to find and qualify the interfaces
        """
        pass

    def assemble(self, f):
        """ Assemble each domain separately (so it can be parallelized) and interfaces """

        # update materials with the new frequency
        # a caching system should be implemented in Material
        for m in self.materials:
            m.update(f)

        self.total_size = 0
        self.domain_sizes = {}
        for i_d, d in enumerate(self.domain):
            needed_size = d.assemble(f)
            self.total_size += needed_size
            self.domain_sizes[i_d] = needed_size

        self.A = sparse.coomatrix((self.total_size,self.total_size))
        self.b = sparse.coomatrix((self.total_size,))
        # + manage a domain->global DOF map

        for i in self.interfaces:
            i.assemble(f)
            # + place using the maps for the domains devised before

    def solve(self, f):
        self.assemble(f)
        self.x = sparse.linalg.spsolve(self.A, self.b)
