#ifndef MATMATH_HPP
#define MATMATH_HPP

#include "Matrix.hpp"

Matrix matAdd(Matrix, Matrix);
Matrix matSub(Matrix, Matrix);
Matrix matScale(Matrix, double);
Matrix matTrans(Matrix);
Matrix matDot(Matrix, Matrix);
Matrix matMult(Matrix, Matrix);
Matrix matAddScale(Matrix, double);
Matrix matSig(Matrix);


#endif

