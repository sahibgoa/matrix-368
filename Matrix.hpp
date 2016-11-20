#include <algorithm>
#include <vector>
#include <cassert>

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
     * @brief Overloading the addition operator for Matrix class
     *
     * @param m : the matrix to be added to the calling object
     * @return the sum of the calling Matrix object and m
     */
    const Matrix<T> operator+(const Matrix &m) const;

    /**
     * @brief Overloading the subtraction operator for Matrix class
     *
     * @param m : the matrix to be subtracted from the calling object
     * @return the difference between the calling Matrix object and m
     */
    const Matrix<T> operator-(const Matrix &m) const;

    /**
     * @brief Overloading the multiplication operator for Matrix class
     *
     * @param m : the matrix to be multiplied to the calling object
     * @return the product of the calling Matrix object and m
     */
    const Matrix<T> operator*(const Matrix &m) const;

    /**
     * @brief Overloading the addition assignment operator for Matrix class
     *
     * @param m : the matrix to be added to the calling object
     * @return reference to the calling object after m has been added to it
     */
    Matrix<T> &operator+=(const Matrix &m);

    /**
     * @brief Overloading the subtraction assignment operator for Matrix class
     *
     * @param m : the matrix to be subtracted from the calling object
     * @return reference to the calling object after m has been subtracted from
     *         it
     */
    Matrix<T> &operator-=(const Matrix &m);

    /**
     * @brief Overloading the multiplication assignment operator for Matrix
     *        class
     *
     * @param m : the matrix to be multiplied to the calling object
     * @return reference to the calling object after m has been multiplied to it
     */
    Matrix<T> &operator*=(const Matrix &m);

    /**
     * @brief Overloading the equality check operator for Matrix class
     *
     * @param m : the matrix to be compared to the calling object
     * @return true if the matrices are equal, false otherwise
     */
    bool operator==(const Matrix &m) const;

    /**
     * @brief Overloading the not-equal check operator for Matrix class
     *
     * @param m : the matrix to be compared to the calling object
     * @return true if the matrices not equal false otherwise
     */
    bool operator!=(const Matrix &m) const;

    /**
     * @brief Overloading the multiplication operator (with scalars) for Matrix
     *        class
     *
     * @param m : the matrix to be multiplied with the scalar
     * @param c : the scalar to be multiplied with the matrix
     * @return the product of the matrix and the scalar
     */
    template <typename L>
    friend const Matrix<T> operator*(const Matrix<T> &m, T c);

    /**
     * @brief Overloading the multiplication operator (with scalars) for Matrix
     *        class
     *
     * @param c : the scalar to be multiplied with the matrix
     * @param m : the matrix to be multiplied with the scalar
     * @return the product of the matrix and the scalar
     */
    template <typename L>
    friend const Matrix<T> operator*(T c, const Matrix<T> &m);

    /**
     * @brief Overloading the multiplication assignment operator (with scalars)
     *        for Matrix class
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
    assert(r >= 0 && c >= 0);
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
    assert(index >= 0);
    return data[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](const int index) const {
    assert(index >= 0);
    return data[index];
}

template <typename T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const {
    assert(this->row == m.getRows() && this->col == m.getCols());
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
    assert(this->row == m.getRows() && this->col == m.getCols());
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
    assert(this->col == m.getRows());
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
