/*
 * air.h
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

#include "fluid.h"

namespace cpplanes {
	namespace medium {

		class Air: public Fluid {
		private:
			real_t T;  ///< reference temperature [K]
			real_t P;  ///< atmospheric Pressure [Pa]
			real_t gamma;  ///< polytropic coefficient []
			real_t lambda;  ///< thermal conductivity [W.m^-1.K^-1]
			real_t mu;  ///< dynamic viscosity [kg.m^-1.s^-1]
			real_t Pr;  ///< Prandtl's number []
			real_t molar_mass;  ///< molar mass [kg.mol^-1]
			real_t rho;  ///< density [kg.m^-3]
			real_t C_p;  ///< (mass) specific heat capacity as constant pressure [J.K^-1]

			real_t K;  ///< adiabatic bulk modulus
			real_t c;  ///< adiabatic sound speed
			real_t Z;  ///< characteristic impedance
			real_t C_v;  ///< (mass) specific heat capacity as constant volume [J.K^-1]
			real_t nu;  ///< kinematic viscosity
			real_t nu_prime;


		public:
			Air(real_t T = 293.15,
				real_t P = 1.01325e5,
				real_t gamma = 1.400,
				real_t lambda = 0.0262,
				real_t mu = 0.1839e-4,
				real_t Pr = 0.710,
				real_t molar_mass = 0.29e-1,
				real_t rho = 1.213,
				real_t C_p = 1006);

			virtual cplx_t get_Pwn(cplx_t frequency) const override;
		};

	}
}

