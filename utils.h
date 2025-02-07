#pragma once
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>

using namespace std;
using namespace c7x;

void validate(int iteration,int iteration2);
void validate_2d_int16_t(int row,int col,int16_t *res1Idx,int16_t *res2Idx);
void get_random_value_for_2d_int16_t(int row,int col,int16_t *mIdx);