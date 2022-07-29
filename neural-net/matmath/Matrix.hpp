#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <math.h>

class Matrix{
public:
	double** entries;
	int rows;
	int col;

	Matrix();
	Matrix(int, int);
	void fill(double);
	void print();
	Matrix copy();
	void save(char*);
	Matrix load(char*);
	void randomize();
	int max();
	Matrix flat(int);
	double length();
};

Matrix matAdd(Matrix, Matrix);
Matrix matSub(Matrix, Matrix);
Matrix matScale(Matrix, double);
Matrix matTrans(Matrix);
Matrix matDot(Matrix, Matrix);
Matrix matMult(Matrix, Matrix);
Matrix matAddScale(Matrix, double);
Matrix matPow(Matrix, double);
Matrix matSig(Matrix);
Matrix matdSig(Matrix);

#endif 