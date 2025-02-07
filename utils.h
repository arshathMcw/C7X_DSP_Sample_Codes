#pragma once
#include <iostream>
#include <c7x.h>
#include <c7x_scalable.h>

using namespace std;
using namespace c7x;

void validate(int iteration,int iteration2);
void validate_2d_int16_t(int row,int col,vector<vector<int16_t>> mat1,vector<vector<int16_t>> mat2);
void get_random_value_for_2d_int16_t(int row,int col,vector<vector<int16_t>>& mat);