/*
	A Matrix implementation to ease future problems that
	could more efficiently be solved with Matrix abstraction.

	by: Charles Bailey
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
		Constructors
  	*/
  	Matrix (vector< vector<T> > e) : elements(e) {}
  	
  	Matrix (Matrix& m) : elements(m.get_all_elements()) {}
  	
  	Matrix (const int& rows, const int& cols) {
  		for (int i = 0; i < rows; i++) {
  			vector<T> tmp(cols);
  			elements.push_back(tmp);
  		}
  	}

  	/*
		Column and Row Size Getters:
  	*/

	int getcol() {
		return elements[0].size();
	}

	int getrow() {
		return elements.size();
	}
	/*
		Element Getter and Setter:
	*/

	void set(const int& row, const int& col, T const& val) {
		if (this->getcol() > col && this->getrow() > row)
			elements[row][col] = val;
	}

	T get(const int& row, const int& col) {
		if (this->getcol() > col && this->getrow() > row)
			return elements[row][col];
		else
			return 0;
	}

	vector< vector<T> > get_all_elements() {
		// make temp vector
		vector< vector<T> > tmp;
		
		tmp = this->elements;

		return tmp;
	}

  	/*
		Implement Matrix Multiplication
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
		Matrix Power Operator

		NOTE: This needs to be optimized!!!

		Powers >= 1 only!
	*/
	Matrix power(const unsigned int& p) {
		if (p == 1)
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