/*
 * air.cpp
 *
 * Copyright (C) 2017 Mathieu Gaborit (matael) <mathieu@matael.org>
 *
 * Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
 * Mathieu (matael) Gaborit wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer or coffee in return
 *
 */

#include "air.h"

#include <cmath>

#include "../mathutils.h"

namespace cpplanes {
	namespace medium {
		using cpplanes::math::PI;

		Air::Air(real_t T, real_t P, real_t gamma, real_t lambda, real_t mu,
			real_t Pr, real_t molar_mass, real_t rho, real_t C_p):
			T(T), P(P), gamma(gamma), lambda(lambda), mu(mu),
			Pr(Pr), molar_mass(molar_mass), rho(rho), C_p(C_p) {
			K = gamma * P;
			c = std::sqrt(K / rho);
			Z = rho * c;
			C_v = C_p / gamma;
			nu = mu / rho;
			nu_prime = nu / Pr;
		}

		cplx_t Air::get_Pwn(cplx_t frequency) const {
			return 2.0 * PI * frequency / c;
		}
	}
}


