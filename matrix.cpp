/*
    matrix.cpp

    Purpose: A Matrix implementation to ease future problems that
    could more efficiently be solved with Matrix abstraction.

    @author c650
    @version 0.2 06/04/16

    The MIT License (MIT)

    Copyright (c) 2016 c650

*/
#include "./matrix.h"
template <typename T>
void Matrix<T>::operator=(Matrix<T>& other) {
    elements = other.elements;
}

template <typename T>
void Matrix<T>::operator=(Matrix<T>&& other) {
    elements = std::move(other.elements);
}

template <typename T>
int Matrix<T>::num_cols() {
    return elements[0].size();
}

template <typename T>
int Matrix<T>::num_rows() {
    return elements.size();
}

template <typename T>
const std::vector< std::vector<T> >& Matrix<T>::get_elements() {
    return elements;
}

template <typename T>  
std::vector<T>& Matrix<T>::operator[](const int &rhs) {
    if (abs(rhs) > num_rows()) {
        throw std::invalid_argument("operator[] in Matrix out of bounds");
    }

    if (rhs >= 0) {
        return elements[rhs];
    } else {
        return elements[num_rows() + rhs];
    }

}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> &other) {
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
            resultant[i][j] = (*this)[i][j] + other[i][j];
        }
    }
    return resultant;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &other) {
    if (this->num_rows() != other.num_rows() || this->num_cols() != other.num_cols())
        throw std::invalid_argument("these Matrices cannot be added/subtracted");

    Matrix<T> resultant(*this);

    for (int i = 0, n = this->num_rows(); i < n; i++) {
        for (int j = 0, o = this->num_cols(); j < o; j++) {
            resultant[i][j] = (*this)[i][j] - other[i][j];
        }
    }
    return resultant;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &other) {
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
                tmp += ( (*this)[i][x] * other[x][j]);
                x++;
            }

            resultant[i][j] = tmp; // put the tmp into the resultant
        }
    }
    return resultant;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& other) {
    Matrix<T> resultant(*this);

    for (int i = 0, n = this->num_rows(); i < n; i++) {
        for (int j = 0, o = this->num_cols(); j < o; j++) {
            resultant.elements[i][j] *= other;
        }
    }

    return resultant;
}

template <typename T>
Matrix<T> Matrix<T>::power(const unsigned int &p) {
    if (p == 1)
        return *this;
    else if (p <= 0)
        throw std::out_of_range("can't raise to a negative power right now");

    Matrix m(*this);

    m = m.power(p / 2);
    m = m * m;

    if (p % 2 == 1)
        m = m * (*this);

    return m;
}

template <typename T1>
std::istream& operator>>(std::istream& in, Matrix<T1>& matrix) {
    for (auto& row : matrix.elements) {
        for (auto& elem : row) {
            in >> elem;
        }
    }
    return in;
}

template <typename T1>
std::ostream& operator<<(std::ostream& out, const Matrix<T1>& matrix) {
    for (const auto& row : matrix.elements) {
        
        out << "| ";

        for (const auto& elem : row)
            out << elem << " ";

        out << "|" << std::endl;
    }

    return out;
}