/*
    matrix.cpp

    Purpose: A Matrix implementation to ease future problems that
    could more efficiently be solved with Matrix abstraction.

    @author c650
    @version 0.1 1/10/16

    The MIT License (MIT)

    Copyright (c) 2016 c650

*/
#include <iostream>
#include <vector>
#include <cstdlib>

/*
    Begin the Matrix class:
*/
template <typename T> class Matrix {
    /*
        `elements` is a 2D array that is
         a vector of the rows of the matrix.
    */
    std::vector< std::vector<T> > elements;

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
    Matrix(std::vector< std::vector<T> >&& elem) : elements(elem) {}
    /*
        Makes a new instance of Matrix

        @param m another instance of Matrix to copy
        using func get_all_elements()

        @return a new instance of Matrix
    */
    Matrix(Matrix& m) : elements(m.elements) {}
    /*
        New instance of Matrix from old Matrix, move
    */
    Matrix(Matrix&& m) : elements(std::move(m.elements)) {}
    /*
        Makes a new, empty instance of Matrix

        @param rows the number of rows desired
        @param cols the number of columns desired

        @return a new instance of Matrix
    */
    Matrix(const int &rows, const int &cols) {
        elements = std::vector<T>(rows, std::vector<T>(cols));
    }
    
    //     ASSIGNMENT (=) OPERATOR
    //     COPY

    //     @param other a matrix to copy from
    //     @return modified Matrix<T>
    
    // Matrix<T>& operator=(Matrix<T>& other) {

    //     elements = other.elements;
    //     return *this;
    // }
    /*
        ASSIGNMENT (=) OPERATOR
        MOVE

        @param other a matrix to move into
        @return modified Matrix<T>
    */
    Matrix<T>& operator=(Matrix<T>&& other) {
        std::swap(elements, other.elements);
        return *this;
    }
    /*
        REMEMBER THE DESTRUCTOR
    */
    ~Matrix();

    /*
        Column and Row Size Getters:
    */
    /*
        Returns the number of columns in an instance
        of Matrix

        @return the number of columns
    */
    int num_cols() {
        return elements[0].size();
    }
    /*
        Returns the number of rows for an instance of
        Matrix

        @return the number of columns
    */
    int num_rows() {
        return elements.size();
    }

    /*
        Returns a vector representing a row in the Matrix

    */
    std::vector<T> operator[](const int &rhs) {
        if (abs(rhs) > num_rows()) {
            throw std::invalid_argument("operator[] in Matrix out of bounds");
        }

        if (rhs >= 0) {
            return elements[rhs];
        } else {
            return elements[num_rows() + rhs];
        }

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
    void set(const int &row, const int &col, T const &val) {
        if (this->num_cols() > col && this->num_rows() > row)
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
    T get(const int &row, const int &col) {
        if (this->num_cols() > col && this->num_rows() > row)
            return elements[row][col];
        else
            return 0;
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
    Matrix<T> operator+(Matrix<T> &other) {
        // Matrices must be same dimensions to
        // be addable
        if (this->num_rows() != other.num_rows() || this->num_cols() != other.num_cols())
            throw std::invalid_argument("these Matrices cannot be added/subtracted");

        // make matrix based on `this`
        Matrix<T> resultant(*this);

        for (int i = 0, n = this->num_rows(); i < n; i++) {
            for (int j = 0, o = this->num_cols(); j < o; j++) {
                // set each value in the resultant equal
                // to the sum of the corresponding values
                // in `this` and `other`
                resultant.set(i, j, this->get(i, j) + other.get(i, j));
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
    Matrix<T> operator-(Matrix<T> &other) {
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
    Matrix<T> operator*(Matrix<T> &other) {
        Matrix<T> resultant(this->num_rows(), other.num_cols());

        if (this->num_cols() != other.num_rows())
            throw std::invalid_argument("these Matrices cannot be multiplied");

        // go through all rows of the left Matrix
        for (int i = 0, n = this->num_rows(); i < n; i++) {

            // go through all columns of right Matrix for each row
            // of the left Matrix

            for (int j = 0, o = other.num_cols(); j < o; j++) {

                T tmp = 0;

                int x = 0;
                while (x < n) {
                    tmp += (this->get(i, x) * other.get(x, j));
                    x++;
                }

                resultant.set(i, j, tmp); // put the tmp into the resultant
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
    Matrix<T> operator*(T &other) {
        Matrix<T> resultant(*this);

        for (int i = 0, n = this->num_rows(); i < n; i++) {
            for (int j = 0, o = this->num_cols(); j < o; j++) {
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
    Matrix power(const unsigned int &p) {
        if (p == 1)
            return *this;
        else if (p <= 0) // use length error
            throw std::length_error{};

        Matrix m(*this);

        m = m.power(p / 2);
        m = m * m;

        if (p % 2 == 1)
            m = m * (*this);

        return m;
    }
    /*
        Matrix Printer
        Formats the Matrix for STDOUT
    */
    std::ostream& operator<<(std::ostream& out) {
        for (const std::vector<T>& a : elements) {
            
            out << "| ";

            for (const T& b : a)
                out << b << " ";

            out << "|" << std::endl;
        }

        return out;
    }
};

int main() {
    return 0;
}