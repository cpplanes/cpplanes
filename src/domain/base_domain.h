/*
 * base_domain.h
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

#include <memory>
#include <vector>

#include "../mesh/base_mesh.h"
#include "../medium/medium.h"
#include "../bc/bc.h"

namespace cpplanes {

	template <typename _MeshT>
	class BaseDomain {
		/**
		 * Base class for domain handling
		 *
		 * To be subclassed and templated for the different use cases
		 */
	private:
		_MeshT mesh;
		PhysicalModel& medium;
		std::vector<std::shared_ptr<BCBase>> boundary_conditions;
		// TODO: replace !

	public:
		BaseDomain(
			_MeshT mesh,
			PhysicalModel& medium,
			std::vector<std::shared_ptr<BCBase>> boundary_conditions);
	};

}

