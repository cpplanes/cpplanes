#! /usr/bin/env python
# -*- coding:utf8 -*-
#
# test.py
#
# Copyright © 2017 Mathieu Gaborit (matael) <mathieu@matael.org>
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Mathieu (matael) Gaborit wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and you
# think this stuff is worth it, you can buy me a beer or coffee in return
#

# from functools import reduce
from matplotlib import pyplot as plt

from pyplanes.mesh import Mesh1D
from pyplanes.bc import RigidWall, UnitPressure
from pyplanes.interp import LinearLagrangeInterpolator
from pyplanes.materials import Fluid
from pyplanes.domain import Domain
from pyplanes.FEM import FEM



f = 200;


mesh = Mesh1D(1, N=40)
air = Fluid(rho=1.241, c=343)
left_exc = UnitPressure(edges=mesh.get_edge([0]))
right_wall = RigidWall(edges=mesh.get_edge([-1]))

domain = Domain(mesh=mesh, material=air, boundary_conditions=[left_exc, right_wall])

interp = LinearLagrangeInterpolator(dim=1)

FE_system = FEM(domain=domain, interp=interp)
# FE_system.assemble(f=f)

# A = csr_matrix(FE_system.A)
# A = A[:-1,:]
# A = csc_matrix(A)
# A = A[:,:-1]
#
# b = FE_system.b
# b[0] = 1
# b = b[:-1]

x = FE_system.solve(f=f)

plt.figure()
plt.plot(mesh.nodes[:-1], x)
plt.show()

