/*
 * fem_domain.h
 *
 * This file is part of cpplanes, a software distributed under the MIT license.
 * For any question, please contact one of the authors cited below.
 *
 * Copyright (c) 2017
 * 	Olivier Dazel <olivier.dazel@univ-lemans.fr>
 * 	Mathieu Gaborit <gaborit@kth.se>
 * 	Peter Göransson <pege@kth.se>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 */

#pragma once

#include <vector>

#include "base_domain.h"
#include "../FEM/FEM.h"
#include "../mesh/base_mesh.h"
#include "../medium/medium.h"
#include "../bc/boundary_condition.h"
#include "../interpolation/interpolator.h"

namespace cpplanes {

	template <typename T>
	class FEMDomain: public BaseDomain, public FEM {

	public:
		FEMDomain(
			BaseMesh mesh,
			PhysicalModel medium,
			std::vector<BoundaryCondition> boundary_conditions,
			Interpolator<T> Interpolator
		);

	};

}

