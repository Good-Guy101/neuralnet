#include "matmath.hpp"
#include "Matrix.hpp"

#include <iostream>
#include <math.h>

bool checkDims(Matrix m1, Matrix m2){
	if(m1.rows == m2.rows && m1.col == m2.col)
		return true;
	return false;
}

Matrix matAdd(Matrix m1, Matrix m2){
	if(!checkDims(m1, m2)){
		std::cout<<"\033[31m"<<"[Error] Matrices must be of the same dimentions for addition"<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}
	Matrix m = Matrix(m1.rows, m2.col);
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			m.entries[i][j] = m1.entries[i][j] + m2.entries[i][j];
		}
	}
	return m;
}

Matrix matSub(Matrix m1, Matrix m2){
	if(!checkDims(m1, m2)){
		std::cout<<"\033[31m"<<"[Error] Matrices must be of the same dimentions for subtraction"<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}
	Matrix m = Matrix(m1.rows, m2.col);
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			m.entries[i][j] = m1.entries[i][j] - m2.entries[i][j];
		}
	}
	return m;
}

Matrix matScale(Matrix m1, double scale){
	Matrix m = m1;
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			m.entries[i][j] *= scale;
		}
	}
	return m;
}

Matrix matTrans(Matrix m1){
	Matrix m = Matrix(m1.col, m1.rows);
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			m.entries[i][j] = m1.entries[j][i];
		}
	}
	return m;
}

Matrix matDot(Matrix m1, Matrix m2){
	if(!(m1.col == m2.rows)){
		std::cout<<"\033[31m"<<"[Error] Matrices must be in the form m x n  n x p for dot product"<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}
	Matrix m = Matrix(m1.rows, m2.col);
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			double sum = 0;
			for(int x = 0; x < m2.rows; x++){
				sum += m1.entries[i][x] * m2.entries[x][j];
			}
			m.entries[i][j] = sum;
		}
	}
	return m;
}

Matrix matMult(Matrix m1, Matrix m2){
	if(!checkDims(m1, m2)){
		std::cout<<"\033[31m"<<"[Error] Matrices must be of the same dimentions for element multiplication"<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}
	Matrix m = Matrix.
}

Matrix matAddScale(Matrix m1, double num){
	Matrix m = m1;
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			m.entries[i][j] += num;
		}
	}
	return m;
}

Matrix matPow(Matrix m1, double num){
	Matrix m = m1;
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			pow(m.entries[i][j], num);
		}
	}
	return m;
}


Matrix matSig(Matrix m1){
	Matrix m = m1;
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.col; j++){
			m.entries[i][j] =  (((m.entries[i][j] / (1 + std::abs(m.entries[i][j]))) + 1) * 0.5);
		}
	}
	return m;
}
