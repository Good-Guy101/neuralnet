#include "Matrix.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <math.h>

Matrix::Matrix(){
	this->rows = 1;
	this->col = 1;
	this->entries = new double*[1];
	entries[0] = new double[1];
	this->fill(0);
}

Matrix::Matrix(int _rows, int _col){
	this->rows = _rows;
	this->col = _col;
	this->entries = new double*[this->rows];

	for(int i = 0; i < this->rows; i++){
		entries[i] = new double[this->col];
	}

	this->fill(0);
}

void Matrix::fill(double num){
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->col; j++){
			entries[i][j] = num;
		}
	}
}

void Matrix::print(){
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->col; j++){
			std::cout<<"["<<entries[i][j]<<"]";
		}
		std::cout<<'\n';
	}
}

Matrix Matrix::copy(){
	Matrix m(this->rows, this->col);
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->col; j++){
			m.entries[i][j] = this->entries[i][j];
		}
	}
	return m;
}

void Matrix::save(char* name){
	std::ofstream outFile(name);

	outFile<<this->rows<<" "<<this->col<<'\n';

	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->col; j++){
			outFile<<entries[i][j]<<" ";
		}
		outFile<<'\n';
	}
	outFile.close();
}

Matrix Matrix::load(char* name){
	std::ifstream inFile(name);
	if(!inFile.is_open()){
		std::cout<<"\033[31m"<<"[Error] Error opening file, file "<<name<<" wasn't opened."<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}
	int r;
	int c;

	inFile >> r >> c;
	Matrix m = Matrix(r,c);

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			inFile >> m.entries[i][j];
		}
	}
	inFile.close();
	return m;
}

void Matrix::randomize(){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->col; j++){
			this->entries[i][j] = dis(gen);
		}
	}
}

int Matrix::max(){
	if(this->col > 1){
		std::cout<<"\033[31m"<<"[Error] Invalid sized matrix (max requires Mx1 sized matrix)"<<"\033[0m\n";
	    exit(EXIT_FAILURE);
	}
	double curMax = 0;
	int maxLoc;

	for(int i = 0; i < this->rows; i++){
		if(entries[i][0] > curMax){
			curMax = entries[i][0];
			maxLoc = i;
		}
	}
	return maxLoc;
}

Matrix Matrix::flat(int axis){
	//axis = 0 : col
	//axis = 1 : row
	Matrix m(0,0);
	if(axis == 0){
		m = Matrix(this->rows * this->col, 1);
	}else if(axis == 1){
		m = Matrix(1, this->rows * this->col);
	} else {
		std::cout<<"\033[31m"<<"[Error] Invalid paramater in Matrix::flat, must be 0 or 1"<<"\033[0m\n";
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->col; j++){
			if(axis == 0)
				m.entries[i * this->col + j][0] = this->entries[i][j];
			else if(axis == 1)
				m.entries[0][i * this->col + j] = this->entries[i][j];
		}
	}
	return m;
}

double Matrix::length(){
	double sum = 0.0;
	for(int i = 0; i < this->col; i++){
		sum += std::pow(entries[0][i], 2);
	}
	return std::sqrt(sum);
}

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
	Matrix m = Matrix(m1.rows, m1.col);
	for(int i = 0; i < m1.rows; i++){
		for(int j = 0; j < m1.col; j++)
			m.entries[i][j] = m1.entries[i][j] * m2.entries[i][j];
	}
	return m;
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

Matrix matdSig(Matrix m1){
	Matrix m = m1;
	m = matMult(m, matAddScale(m, -1));
	return m;
}
