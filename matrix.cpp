/*
	matrix.cpp

	Purpose: A Matrix implementation to ease future problems that
	could more efficiently be solved with Matrix abstraction.

	@author c650
	@version 0.1 1/10/16
	
	The MIT License (MIT)

	Copyright (c) 2016 c650
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.	
*/
#include <vector>
#include <iostream>
using namespace std;

/*
	Begin the Matrix class:
*/
template <class T>
class Matrix {
	/*
		`elements` is a 2D array that is
		a vector of the rows of the matrix.
	*/
	vector< vector<T> > elements;

  public:
/*
	Constructors:
*/
	/*
		Makes a new instance of Matrix

		@param elem a 2D vector that represents what a
		Matrix actually is.

		@return a new instance of Matrix
	*/
  	Matrix (vector< vector<T> > elem) : elements(elem) {}
  	/*
		Makes a new instance of Matrix

		@param m another instance of Matrix to copy
		using func get_all_elements()

		@return a new instance of Matrix
	*/
  	Matrix (Matrix& m) : elements(m.get_all_elements()) {}
  	/*
		Makes a new, empty instance of Matrix

		@param rows the number of rows desired
		@param cols the number of columns desired

		@return a new instance of Matrix
	*/
  	Matrix (const int& rows, const int& cols) {
  		vector< vector<T> > _elem(rows,vector<T>(cols));
  		elements = _elem;
  	}

/*
	Column and Row Size Getters:
*/
	/*
		Returns the number of columns in an instance
		of Matrix

		@return the number of columns
	*/
	int getcol() {
		return elements[0].size();
	}
	/*
		Returns the number of rows for an instance of
		Matrix

		@return the number of columns
	*/
	int getrow() {
		return elements.size();
	}

/*
	Element Getter and Setter:
*/
	/*
		Changes the value of a given position in
		the Matrix.

		@param row the row that holds the value to change
		@param col the column of the value to change
		@param val the value to set
	*/
	void set(const int& row, const int& col, T const& val) {
		if (this->getcol() > col && this->getrow() > row)
			elements[row][col] = val;
	}
	/*
		Gets the value held at a certain position in
		the Matrix.

		@param row the row to read from
		@param col the column to read from
		
		@return the value of type T held at the positon
		row,col in the Matrix
	*/
	T get(const int& row, const int& col) {
		if (this->getcol() > col && this->getrow() > row)
			return elements[row][col];
		else
			return 0;
	}
	/*
		Helper method for the second Matrix constructor.

		@return a copy of a Matrix's `elements` attribute
	*/
	vector< vector<T> > get_all_elements() {
		// make temp vector
		vector< vector<T> > tmp;
		
		tmp = this->elements;

		return tmp;
	}
/*
	Matrix Arithmetic Methods
*/
	/*
		ADDITION:

		Binary operator to add two matrices together.
		Does not modify either matrix.

		@param other the Matrix on the right side of +

		@return a Matrix, whose elements are the sums of
		the corresponding elements of `this` and `other`
	*/
	Matrix<T> operator+(Matrix<T>& other) {
		// Matrices must be same dimensions to
		// be addable
		if (this->getrow() != other.getrow() 
			|| this->getcol() != other.getcol())
			return *this;

		// make matrix based on `this`
		Matrix<T> resultant(*this);

		for (int i = 0, n = this->getrow(); i < n; i++) {
			for (int j = 0, o = this->getcol(); j < o; j++) {
				// set each value in the resultant equal
				// to the sum of the corresponding values
				// in `this` and `other`
				resultant.set(i,j,this->get(i,j) + other.get(i,j));
			}
		}

		return resultant;
	}
	/*
		SUBTRACTION:

		Binary operator to subtract two matrices.
		Does not modify either matrix.

		@param other the Matrix on the right side of -

		@return a Matrix, whose elements are the differences of
		the corresponding elements of `this` and `other`
	*/
	Matrix<T> operator-(Matrix<T>& other) {
		return (*this) + (other * -1);
	}
  	/*
		MATRIX*MATRIX MULTIPLICATION

		Binary operator to multiple two matrices.
		Does not modify either matrix.

		@param other the Matrix on the right side of *

		@return a Matrix, whose elements are the products of
		the corresponding elements of `this` and `other`, following
		the accepted way of multiplying matrices.
  	*/
	Matrix<T> operator*(Matrix<T>& other) {
		Matrix<T> resultant(this->getrow(), other.getcol());

		if (this->getcol() != other.getrow())
			return *this;
		
		// go through all rows of the left Matrix
		for (int i = 0, n = this->getrow(); i < n; i++) {

			// go through all columns of right Matrix for each row
			// of the left Matrix
			
			for (int j = 0, o = other.getcol(); j < o; j++) {

				T tmp = 0;
				
				int x = 0;
				while(x < n) {
					tmp+= (this->get(i,x) * other.get(x,j));
					x++;
				}

				resultant.set(i,j,tmp); // put the tmp into the resultant

			}

		}
		return resultant;
	}
	/*
		MATRIX*SCALAR MULTIPLICATION

		Multiplies a Matrix by a scalar value.

		@param other the scalar value

		@return the result of scaling `this` by `other`
	*/
	Matrix<T> operator*(T& other) {
		Matrix<T> resultant(*this);

		for (int i = 0, n = this->getrow(); i < n; i++) {
			for (int j = 0, o = this->getcol(); j < o; j++) {
				resultant.elements[i][j] *= other;
			}
		}

		return resultant;
	}
	/*
		Matrix Power Method
		Powers >= 1 only!

		@param p an unsigned integer >= 1 to which the Matrix will
		be raised.

		@return the Matrix raised to the `p` power
	*/
	Matrix power(const unsigned int& p) {
		if (p == 1)
			return *this;
		else if (p <= 0) // set for now to keep it safe
			return *this;

		Matrix m(*this);

		m = m.power(p/2);
		m = m * m;

		if (p % 2 == 1)
			m = m * (*this);
		return m;
	}
	/*
		Matrix Printer
		Formats the Matrix for STDOUT
	*/
	void print() {
		for (int i = 0, n = this->getrow(); i < n; i++) {
			cout << "| ";
			for (int j = 0, o = this->getcol(); j < o; j++) {
				cout << elements[i][j] << " ";
			}
			cout << "|" << endl;
		}
	}
};

int main() {
	return 0;
}
