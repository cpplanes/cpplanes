/*
 * LinearSystem.h
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

#ifndef __LinearSystem_h__
#define __LinearSystem_h__

#include <boost/numeric/ublas/matrix.hpp>
#include "Domain.h"
#include "utils.h"

using namespace cpplanes;
using namespace boost::numeric::ublas;
using namespace domain;

namespace linsys {

enum class BC {
	Rigid,
	NormalVelocity,
	TangentialVelocity,
	Sliding,
	Bonded,
	IncidentPW,
	TransmittedPW,
	DtNPlate,
	DispersionAnalysis
};

class LinearSystem {
private:
	int get_linsys_size();

	matrix<cplx_t> A;
	int linsys_size = {-1};
	std::vector<Domain> domains;
public:
	bool assemble(cplx_t frequency);
};

}

#endif /* !__LinearSystem_h__ */

