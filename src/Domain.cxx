/*
 * Domain.cxx
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

#include "Domain.h"

namespace domain {

int Domain::get_nbdof () {

	if (nbdof > -1) {
		return nbdof;
		// TODO warning
	}

	// Let the method add nodes it requires for interpolation
	// method.adapt_mesh(mesh);

	int nbdof = mesh.nodes.size()*model.nbdof_fem_by_node;
	// TODO: implement Dirichlet BC
	return nbdof;
}

matrix<cplx_t> Domain::assemble(cplx_t frequency, int linsys_size) {
	matrix<cplx_t> t =  method.assemble(frequency, linsys_size, mesh);
	return t;
}

}


