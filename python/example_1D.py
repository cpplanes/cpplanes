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
import numpy as np

from pyplanes.mesh import Mesh1D
from pyplanes.bc import RigidWall, UnitVelocity
from pyplanes.interp import LinearLagrangeInterpolator
from pyplanes.materials import Fluid
from pyplanes.domain import FEMDomain



f = 200;


mesh = Mesh1D(1, N=40)
air = Fluid(rho=1.241, c=343)
left_exc = UnitVelocity(edges=mesh.get_edge([0]), material=air)
right_wall = RigidWall(edges=mesh.get_edge([-1]), material=air)

interp = LinearLagrangeInterpolator(dim=1)

domain = FEMDomain(mesh=mesh, interp=interp, material=air,
        boundary_conditions=[left_exc, right_wall])

domain.solve(f=f)

node_coords = np.array(mesh.nodes)

plt.figure()
plt.plot(node_coords[:,0], np.absolute(domain.solution), marker='+', linestyle='None')
plt.show()

