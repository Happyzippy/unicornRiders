/***
	Walker Robot configuration file

	DO NOT EDIT, THIS FILE IS CODE GENERATED
***/

#include "walker_conf.h"
#include <stdint.h>

#define WALKCYCLE_LUT_TABLE_SIZE 50
#define WALKCYCLE_LUT_TABLE_MOD WALKCYCLE_LUT_TABLE_SIZE+1

int hipCycle(int index, float phase)
{
	static const int8_t lookup[WALKCYCLE_LUT_TABLE_SIZE] = {66,62,57,52,46,41,35,30,25,19,14,8,3,-3,-8,-14,-19,-25,-30,-35,-41,-46,-52,-57,-62,-65,-66,-64,-62,-59,-53,-43,-31,-17,-4,8,18,27,35,43,49,54,58,61,65,67,68,68,68,68};
	index = (index + ((int)(phase*WALKCYCLE_LUT_TABLE_SIZE))) % WALKCYCLE_LUT_TABLE_MOD;
	return lookup[index];
}

int kneeCycle(int index, float phase)
{
	static const int8_t lookup[WALKCYCLE_LUT_TABLE_SIZE] = {155,152,149,146,144,142,141,140,139,138,137,137,137,137,137,137,138,139,140,141,142,144,146,149,152,156,161,167,174,181,187,193,199,204,209,211,212,210,207,204,201,197,193,189,185,180,175,170,165,159};
	index = (index + ((int)(phase*WALKCYCLE_LUT_TABLE_SIZE))) % WALKCYCLE_LUT_TABLE_MOD;
	return lookup[index];
}

