/*
 * Medium.h
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

#ifndef __Medium_h__
#define __Medium_h__

namespace medium {
/*
 * To be implemented:
 * - Elastic,
 * - EquivalentFluid,
 * - Limp,
 * - Biot98,
 * - Biot01,
 * - PML
 */

typedef unsigned int Id;

class PhysicalModel {
private:
public:
	const int state_vector_size = {-1};
	const int nbdof_fem_by_node = {-1};
};

class Air: public PhysicalModel {
public:
	const int state_vector_size = 3;
	const int nbdof_fem_by_node = 1;
};

}

#endif /* !__Medium_h__ */

