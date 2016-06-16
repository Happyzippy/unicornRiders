/***
	Walker Robot configuration file

	DO NOT EDIT, THIS FILE IS CODE GENERATED
***/

#include "walker_conf.h"
#include <stdint.h>

#define WALKCYCLE_LUT_TABLE_SIZE 30

int hipCycle(int index, float phase)
{
	static const int16_t lookup[WALKCYCLE_LUT_TABLE_SIZE] = {66,59,50,41,32,23,14,5,-5,-14,-23,-32,-41,-50,-59,-65,-65,-61,-53,-35,-13,8,24,38,49,57,63,67,68,68};
	index = (index + ((int)(phase*WALKCYCLE_LUT_TABLE_SIZE))) % WALKCYCLE_LUT_TABLE_SIZE;
	return lookup[index];
}

int kneeCycle(int index, float phase)
{
	static const int16_t lookup[WALKCYCLE_LUT_TABLE_SIZE] = {155,150,146,142,140,138,137,137,137,137,138,140,142,146,150,155,165,176,187,197,206,212,210,206,201,195,188,180,172,163};
	index = (index + ((int)(phase*WALKCYCLE_LUT_TABLE_SIZE))) % WALKCYCLE_LUT_TABLE_SIZE;
	return lookup[index];
}

