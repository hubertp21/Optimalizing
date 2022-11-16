#pragma once

#include"ode_solver.h"

matrix df1(double t, matrix Y, matrix ud1, matrix ud2);
matrix ff1R(matrix x, matrix ud1, matrix ud2);
matrix func_lab_12(matrix x, matrix ud1, matrix ud2);
matrix ff2T(matrix x, matrix ud1, matrix ud2);
