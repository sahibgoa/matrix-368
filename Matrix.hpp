///////////////////////////////////////////////////////////////////////////////
// File Name:      Matrix.hpp
//
// Author:         Sahib Pandori and Haylee Monteiro
// CS email:       sahib@cs.wisc.edu and haylee@cs.wisc.edu
//
// Description:    This file contains all the templated methods and definition
//                 for the Matrix objects
///////////////////////////////////////////////////////////////////////////////
#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <vector>
#include <cassert>
#include <exception>

class InvalidDimension : public std::exception {
private:
    int row;
    int col;
public:
    InvalidDimension(int r, int c) {
        this->row = r;
        this->col = c;
    }
    virtual const char* what() const throw() {
        std::string exception = "Invalid Dimension Exception: ";
        if (row < 0 && col < 0) {
            exception += std::to_string(row) + " and " + std::to_string(col)
                         + " are invalid dimensions for rows and columns "
                         + "respectively\n";
        } else if (row < 0) {
            exception += std::to_string(row) + " is an invalid dimension for "
                         + "rows\n";
        } else if (col < 0) {
            exception += std::to_string(col) + " is an invalid dimension for "
                         + "columns\n";
        } else {
            exception += "Exception thrown at the wrong time\n";
        }
        return exception.c_str();
    }
};

class IndexOutOfBounds : public std::exception {
private:
    int index;
public:
    IndexOutOfBounds(const int i) {
        this->index = i;
    }

    virtual const char* what() const throw() {
        std::string exception = "Index Out Of Bounds Exception: "
                                + std::to_string(index)
                                + " is an invalid index for rows\n";
        return exception.c_str();
    }
};

class IncompatibleMatrices : public std::exception {
private:
    char op;
    int lhs_row;
    int lhs_col;
    int rhs_row;
    int rhs_col;
public:
    IncompatibleMatrices(char op, int lrow, int lcol, int rrow, int rcol) {
        this->op = op;
        this->lhs_row = lrow;
        this->lhs_col = lcol;
        this->rhs_row = rrow;
        this->rhs_col = rcol;
    }
    virtual const char* what() const throw() {
        std::string exception =  "Incompatible Matrices Exception: ";
        switch (op) {
            case '+':
                exception += "Addition ";
                break;
            case '-':
                exception += "Subtraction ";
                break;
            case '*':
                exception += "Multiplication ";
                break;
            default:
                exception += "Undefined operation ";
                break;
        }
        exception += "of LHS matrix with dimensions " + std::to_string(lhs_row)
                     + " x " + std::to_string(lhs_col) + " and RHS matrix with"
                     + " dimensions " + std::to_string(rhs_row) + " x "
                     + std::to_string(rhs_col) + " is undefined\n";

        return exception.c_str();
    }
};



template<typename T>
class Matrix {
private:
    // Number of rows in the matrix
    int row;
    // Number of columns in the matrix
    int col;
    // Data structure that holds all the values of the matrix
    std::vector<std::vector<T>> data;
public:
    /**
     * @brief Constructor to initialize the matrix with r rows and c columns
     *
     * @param r : number of rows
     * @param c : number of columns
     */
    Matrix(int r, int c);

    /**
     * @brief Returns the numbner of rows in the matrix
     *
     * @return number of rows
     */
    const int getRows() const;

    /**
     * @brief Returns the numbner of columns in the matrix
     *
     * @return number of columns
     */
    const int getCols() const;

    /**
     * @brief Overloading non-const array (vector) index operator
     *
     * @param index : the row to be accessed
     * @return the entire row vector
     */
    std::vector<T> &operator[](const int index);

    /**
     * @brief Overloading the const array (vector) index operator
     *
     * @param index : the row to be accessed
     * @return the entire row vector
     */
    const std::vector<T> &operator[](const int index) const;

    /**
     * @brief Overloading the addition operator for Matrix
     *
     * @param m : the matrix to be added to the calling object
     * @return the sum of the calling Matrix object and m
     */
    const Matrix<T> operator+(const Matrix &m) const;

    /**
     * @brief Overloading the subtraction operator for Matrix
     *
     * @param m : the matrix to be subtracted from the calling object
     * @return the difference between the calling Matrix object and m
     */
    const Matrix<T> operator-(const Matrix &m) const;

    /**
     * @brief Overloading the multiplication operator for Matrix
     *
     * @param m : the matrix to be multiplied to the calling object
     * @return the product of the calling Matrix object and m
     */
    const Matrix<T> operator*(const Matrix &m) const;

    /**
     * @brief Overloading the addition assignment operator for Matrix
     *
     * @param m : the matrix to be added to the calling object
     * @return reference to the calling object after m has been added to it
     */
    Matrix<T> &operator+=(const Matrix &m);

    /**
     * @brief Overloading the subtraction assignment operator for Matrix
     *
     * @param m : the matrix to be subtracted from the calling object
     * @return reference to the calling object after m has been subtracted from
     *         it
     */
    Matrix<T> &operator-=(const Matrix &m);

    /**
     * @brief Overloading the multiplication assignment operator for Matrix
     *
     * @param m : the matrix to be multiplied to the calling object
     * @return reference to the calling object after m has been multiplied to it
     */
    Matrix<T> &operator*=(const Matrix &m);

    /**
     * @brief Overloading the equality check operator for Matrix
     *
     * @param m : the matrix to be compared to the calling object
     * @return true if the matrices are equal, false otherwise
     */
    bool operator==(const Matrix &m) const;

    /**
     * @brief Overloading the not-equal check operator for Matrix
     *
     * @param m : the matrix to be compared to the calling object
     * @return true if the matrices not equal false otherwise
     */
    bool operator!=(const Matrix &m) const;

    /**
     * @brief Overloading the multiplication operator (with scalars) for Matrix
     *
     * @param m : the matrix to be multiplied with the scalar
     * @param c : the scalar to be multiplied with the matrix
     * @return the product of the matrix and the scalar
     */
    template <typename L>
    friend const Matrix<T> operator*(const Matrix<T> &m, T c);

    /**
     * @brief Overloading the multiplication operator (with scalars) for Matrix
     *
     * @param c : the scalar to be multiplied with the matrix
     * @param m : the matrix to be multiplied with the scalar
     * @return the product of the matrix and the scalar
     */
    template <typename L>
    friend const Matrix<T> operator*(T c, const Matrix<T> &m);

    /**
     * @brief Overloading the multiplication assignment operator (with scalars)
     *        for Matrix
     *
     * @param m : the matrix to be multiplied with the scalar
     * @param c : the scalar to be multiplied with the matrix
     * @return the matrix m after the scalar has been multiplied to it
     */
    template <typename L>
    friend Matrix<T> &operator*=(Matrix<T> &m, T c);

    /**
     * @brief Overloading the stream extraction operator to print Matrix object
     *
     * @param o : the output stream to print the output to
     * @param m : the matrix to be printed
     * @return reference to the output stream after the matrix has been printed
     */
    template <typename L>
    friend std::ostream &operator<<(std::ostream &o, const Matrix<T> &m);
};

template <typename T>
Matrix<T>::Matrix(int r, int c) {
    if (r < 0 || c < 0) {
        throw InvalidDimension(r, c);
    }
    Matrix::row = r;
    Matrix::col = c;
    // Resize the vector to fit r rows and c columns
    data.resize((unsigned) r, std::vector<T>((unsigned) c));
}

template <typename T>
const int Matrix<T>::getRows() const {
    return this->row;
}

template <typename T>
const int Matrix<T>::getCols() const {
    return this->col;
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](const int index) {
    if (index < 0 || index >= this->row) {
        throw IndexOutOfBounds(index);
    }
    return data[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](const int index) const {
    if (index < 0 || index >= this->row) {
        throw IndexOutOfBounds(index);
    }
    return data[index];
}

template <typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const {
    if (this->row != m.getRows() || this->col != m.getCols()) {
        throw IncompatibleMatrices('+', this->row, this->col, m.getRows(),
                                   m.getCols());
    }
    Matrix<T> ret(this->row, this->col);
    for(int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            ret[i][j] = this->data[i][j] + m[i][j];
        }
    }
    return ret;
}

template <typename T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) const {
    if (this->row != m.getRows() || this->col != m.getCols()) {
        throw IncompatibleMatrices('-', this->row, this->col, m.getRows(),
                                   m.getCols());
    }
    Matrix<T> ret(this->row, this->col);
    for(int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            ret[i][j] = this->data[i][j] - m[i][j];
        }
    }
    return ret;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &m) {
    *this = this->operator+(m);
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &m) {
    *this = *this - m;
    return *this;
}

template <typename T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T> &m) const {
    if (this->col != m.getRows()) {
        throw IncompatibleMatrices('*', this->row, this->col, m.getRows(),
                                   m.getCols());
    }
    Matrix<T> ret(this->row, m.getCols());
    for(int i = 0; i < this->row; ++i) {
        for(int j = 0; j < m.getCols(); ++j) {
            for(int k = 0; k < this->col; ++k) {
                ret[i][j] += this->data[i][k] * m[k][j];
            }
        }
    }
    return ret;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &m) {
    *this = *this * m;
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &m) const {
    if (this->row != m.getRows() || this->col != m.getCols()) {
        return false;
    }
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (this->data[i][j] != m[i][j])
                return false;
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T> &m) const {
    return !(*this == m);
}

template <typename T>
Matrix<T> const operator*(const Matrix<T> &m, T c) {
    Matrix<T> ret(m.getRows(), m.getCols());
    for(int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            ret[i][j] = m[i][j] * c;
        }
    }
    return ret;
}

template <typename T>
Matrix<T> const operator*(T c, const Matrix<T> &m) {
    return m * c;
}

template <typename T>
Matrix<T> &operator*=(Matrix<T> &m, T c) {
    m = m * c;
    return m;
}

template <typename T>
std::ostream &operator<<(std::ostream &o, const Matrix<T> &m) {
    for(int i = 0; i < m.getRows(); ++i) {
        for(int j = 0; j < m.getCols(); ++j) {
            /* Print the element at row i column j with a space
               (unless it's the last element) */
            (j == m.getCols() - 1) ? o << m[i][j] : o << m[i][j] << " ";
        }
        o << std::endl;
    }
    return o;
}

#endif
