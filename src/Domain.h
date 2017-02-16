/*
 * Domain.h
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

#ifndef __Domain_h__
#define __Domain_h__

#include "Mesh.h"
#include "Medium.h"
#include "utils.h"
#include "methods/Method.h"
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;
using namespace cpplanes;

namespace domain {

class Domain {
	/*
	 * A domain assigns a method, a physical model to a given Mesh object
	 * (which defines geometrical properties).
	 *
	 */
private:
	mesh::Mesh mesh;
	medium::Id material_id;
	medium::PhysicalModel model;
	method::Method method;
	int nbdof = {-1};
public:
	int get_nbdof();
	matrix<cplx_t> assemble(cplx_t frequency, int linsys_size);
};

}

#endif /* !__Domain_h__ */

