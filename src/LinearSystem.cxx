/*
 * LinearSystem.cpp
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

#include "LinearSystem.h"
#include "utils.h"

namespace linsys {

int LinearSystem::get_linsys_size() {
	if (linsys_size > -1) {
		return linsys_size;
	}

	linsys_size = 0;
	for (auto d : domains) {
		linsys_size += d.get_nbdof();
	}

	return linsys_size;
}

bool LinearSystem::assemble(cplx_t frequency) {
	int linsys_size = get_linsys_size();

	matrix<cplx_t> A(linsys_size, linsys_size);
	for (auto d : domains) {
		d.assemble(frequency, linsys_size);
	}

	return true;
}

}


