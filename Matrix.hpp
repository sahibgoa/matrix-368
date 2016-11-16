// #include

#include <algorithm>
#include <vector>

template<typename T>
class Matrix {
private:
    int row;
    int col;
    std::vector<std::vector<T>> data;
public:
    Matrix();
    Matrix(int r, int c);
    int getNumRows();
    int getNumColumns();
    T getData(int i, int j) const;
    std::vector<T> &operator[](int index);
    Matrix<T> operator+(Matrix m);
    Matrix<T> operator-(Matrix m);
    Matrix<T> operator*(Matrix m);
    Matrix<T> operator+=(Matrix m);
    Matrix<T> operator-=(Matrix m);
    Matrix<T> operator*=(Matrix m);
    bool operator==(Matrix m) const;
    bool operator!=(Matrix m) const;

    friend Matrix<T> operator*(Matrix<T> m, int c);
    friend Matrix<T> operator*(int c, Matrix<T> m);
    friend Matrix<T> operator*=(Matrix<T> m, int c);
    friend std::ostream &operator<<(std::ostream &o, Matrix<T> m) const;
};

template <typename T>
Matrix<T>::Matrix() {
    Matrix::row = 0;
    Matrix::col = 0;
}

template <typename T>
Matrix<T>::Matrix(int r, int c) {
    Matrix::row = r;
    Matrix::col = c;
    data.resize((unsigned) r);
    std::for_each(data.begin(), data.end(), [](std::vector<T> d){d.resize((unsigned) c);});
}

template <typename T>
int Matrix<T>::getNumRows() {
    return this->row;
}

template <typename T>
int Matrix<T>::getNumColumns() {
    return this->col;
}

template <typename T>
T Matrix<T>::getData(int i, int j) const {
    return this->data[i][j];
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](int index) {
    return data[index];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> m) {
    if (this->row != m.row || this->col != m.col) {
        exit(1);
    }
    Matrix<T> ret(this->row, this->col);
    for(int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            ret[i][j] = this[i][j] + m[i][j];
        }
    }
    return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> m) {
    if (this->row != m.row || this->col != m.col) {
        exit(1);
    }
    Matrix<T> ret(this->row, this->col);
    for(int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            ret[i][j] = this[i][j] - m[i][j];
        }
    }
    return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator+=(Matrix<T> m) {
    *this = *this + m;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-=(Matrix<T> m) {
    *this = *this - m;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> m) {
    Matrix<T> ret(this->row, m.getNumColumns());
    for(int i = 0; i < this->row; ++i) {
        for(int j = 0; j < m.getNumColumns(); ++j) {
            // ret[i][j] = 0;
            for(int k = 0; k < this->col; ++k) {
                ret[i][j] += this[i][k]*m[k][j];
            }
        }
    }
    return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator*=(Matrix<T> m) {
    *this = *this * m;
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(Matrix<T> m) const {
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (this->getData(i, j) != m.getData(i, j))
                return false;
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(Matrix<T> m) const {
    return !(*this == m);
}

template <typename T>
Matrix<T> operator*(Matrix<T> m, int c) {
    Matrix<T> ret(m.row, m.col);
    for(int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; ++j) {
            ret[i][j] = m[i][j] * c;
        }
    }
    return ret;
}

template <typename T>
Matrix<T> operator*(int c, Matrix<T> m) {
    return m * c;
}

template <typename T>
Matrix<T> operator*=(Matrix<T> m, int c) {
    m = m * c;
    return m;
}

template <typename T>
std::ostream &operator<<(std::ostream &o, Matrix<T> m) const {
    for(int i = 0; i < m.getNumRows(); ++i) {
        for(int j = 0; j < m.getNumColumns(); ++j) {
            o << m.getData(i, j);
        }
        o << std::endl;
    }
    return o;
}
