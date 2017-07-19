#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# test2.py
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

from matplotlib import pyplot as plt
import numpy as np

from pyplanes.mesh.readers import freefem_read
from pyplanes.bc import RigidWall, UnitVelocity
from pyplanes.interp import LinearLagrangeInterpolator
from pyplanes.integration import GaussLegendre
from pyplanes.materials import Fluid
from pyplanes.domain import FEMDomain


f = 1000;


mesh = freefem_read('square.msh')

edges_bc_rigid = []
edges_bc_unit = []
for i in range(len(mesh.edges_labels)):
    if mesh.edges_labels[i]==0:
        edges_bc_rigid.append(i)
    elif mesh.edges_labels[i]==1:
        edges_bc_unit.append(i)

air = Fluid(rho=1.213, c=343)

bc_rigid= RigidWall(edges=list(map(mesh.get_edge, edges_bc_rigid)), material=air)
bc_unit = UnitVelocity(edges=list(map(mesh.get_edge, edges_bc_unit)), material=air)

interp = LinearLagrangeInterpolator(dim=2, integration_scheme=GaussLegendre)

domain = FEMDomain(mesh=mesh, material=air, boundary_conditions=[bc_unit, bc_rigid], interp=interp)

domain.solve(f=f)

plt.figure()
node_coords = np.array(mesh.nodes)
plt.plot(node_coords[:,0], np.absolute(domain.solution), marker='+', linestyle='None')

plt.figure()
plt.tricontourf(node_coords[:,0], node_coords[:,1], mesh.elements, np.absolute(domain.solution))
plt.axis('equal')
plt.colorbar()

plt.show()
# plt.figure()
# plt.plot(mesh.nodes[:-1], x)
# plt.show()


