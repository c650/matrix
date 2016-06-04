/*
    matrix.h

    Purpose: A Matrix implementation to ease future problems that
    could more efficiently be solved with Matrix abstraction.

    @author c650
    @version 0.2 06/04/16

    The MIT License (MIT)

    Copyright (c) 2016 c650

*/
#include <iostream>
#include <vector>
#include <cstdlib>

template <typename T>
class Matrix {
    /*
        `elements` is a 2D array that is
         a vector of the rows of the matrix.
    */
    std::vector< std::vector<T> > elements;

  public:
    Matrix(std::vector< std::vector<T> >& elem)
        : elements(elem) {}
    Matrix(std::vector< std::vector<T> >&& elem)
        : elements(std::move(elem)) {}

    /*
        COPY and MOVE constructors
    */
    Matrix(Matrix& m)
        : elements(m.elements) {}
    Matrix(Matrix&& m)
        : elements(std::move(m.elements)) {}
    
    /*
        BAREBONES constructor
    */
    Matrix(const int rows, const int cols) 
        : elements(std::vector< std::vector<T> >(rows, std::vector<T>(cols))) {}

    /*
        DEFAULT destructor, nothing to do.
    */
    ~Matrix() {}

    /*
        BEGIN FUNCTION PROTOTYPES
    */
    void operator=(Matrix<T>& other);
    void operator=(Matrix<T>&& other);
    
    // column/row num getters
    int num_cols();
    int num_rows();

    // get all elements
    const std::vector< std::vector<T> >& get_elements();

    // subscript operator,
    // @param rhs [int] an 0 <= index < num_cols
    // @return a vector
    std::vector<T>& operator[](const int &rhs);
    /*
        Matrix Arithmetic Methods
    */

    
    // ADDITION:

    // Binary operator to add two matrices together.
    // Does not modify either matrix.

    // @param other the Matrix on the right side of +

    // @return a Matrix, whose elements are the sums of
    // the corresponding elements of `this` and `other`
    
    Matrix<T> operator+(Matrix<T> &other);

    // SUBTRACTION:

    // Binary operator to subtract two matrices.
    // Does not modify either matrix.

    // @param other the Matrix on the right side of -

    // @return a Matrix, whose elements are the differences of
    // the corresponding elements of `this` and `other`

    Matrix<T> operator-(Matrix<T> &other);

    // MATRIX*MATRIX MULTIPLICATION

    // Binary operator to multiple two matrices.
    // Does not modify either matrix.

    // @param other the Matrix on the right side of *

    // @return a Matrix, whose elements are the products of
    // the corresponding elements of `this` and `other`, following
    // the accepted way of multiplying matrices.

    Matrix<T> operator*(Matrix<T> &other);

    // MATRIX*SCALAR MULTIPLICATION

    // Multiplies a Matrix by a scalar value.

    // @param other the scalar value

    // @return the result of scaling `this` by `other`

    Matrix<T> operator*(const T& other);

    // Matrix Power Method
    // Powers >= 1 only!

    // @param p an unsigned integer >= 1 to which the Matrix will
    // be raised.

    // @return the Matrix raised to the `p` power

    Matrix<T> power(const unsigned int &p);

    // I/O functions
    template <typename T1>
    friend std::istream& operator>>(std::istream& in, Matrix<T1>& matrix);

    template <typename T1>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<T1>& matrix);
};