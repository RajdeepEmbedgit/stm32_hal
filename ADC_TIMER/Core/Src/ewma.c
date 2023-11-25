/*
 * ewma.c
 *
 *  Created on: 23-Jun-2022
 *      Author: LENOVO
 */

#include "reg.h"

#define ALPHA_1					0.875
#define ALPHA_2					0.995

float rsm_1 = 0.0;
float rsm_2 = 0.0;

float ewma (float res)
{
	if (!FLAG_IS_EWMA)
	{
		FLAG_EWMA_SET;
		rsm_1 = res;
		rsm_2 = rsm_1;
	}

	rsm_1 = ((ALPHA_1 * rsm_1) + ((1 - ALPHA_1) * res));
	rsm_2 = ((ALPHA_2 * rsm_2) + ((1 - ALPHA_2) * rsm_1));
	return rsm_2;
}




