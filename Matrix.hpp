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
    const int getRows() const;
    const int getCols() const;
    std::vector<T> &operator[](const int index);
    const std::vector<T> &operator[](const int index) const;
    Matrix<T> operator+(Matrix m);
    Matrix<T> operator-(Matrix m);
    Matrix<T> operator*(Matrix m);
    Matrix<T> operator+=(Matrix m);
    Matrix<T> operator-=(Matrix m);
    Matrix<T> operator*=(Matrix m);
    bool operator==(const Matrix m) const;
    bool operator!=(const Matrix m) const;

    template <typename L>
    friend Matrix<T> operator*(Matrix<T> m, T c);
    template <typename L>
    friend Matrix<T> operator*(T c, Matrix<T> m);
    template <typename L>
    friend Matrix<T> operator*=(Matrix<T> m, T c);
    template <typename L>
    friend std::ostream &operator<<(std::ostream &o, Matrix<T> m);
};

template <typename T>
Matrix<T>::Matrix() {
    Matrix::row = 0;
    Matrix::col = 0;
}

template <typename T>
Matrix<T>::Matrix(int r, int c) {
    if (r < 0 || c < 0) {
        exit(1);
    }
    Matrix::row = r;
    Matrix::col = c;
    data.resize((unsigned) c, std::vector<T>((unsigned) r));
    //std::for_each(data.begin(), data.end(), [c](std::vector<T> d){d.resize((unsigned) c);});
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
    if (index < 0) {
        exit(1);
    }
    return data[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](const int index) const {
    if (index < 0) {
        exit(1);
    }
    return data[index];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> m) {
    if (this->row != m.getRows() || this->col != m.getCols()) {
        exit(1);
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
Matrix<T> Matrix<T>::operator-(Matrix<T> m) {
    if (this->row != m.getRows() || this->col != m.getCols()) {
        exit(1);
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
    if (this->col != m.getRows()) {
        exit(1);
    }
    Matrix<T> ret(this->row, m.getCols());
    for(int i = 0; i < this->row; ++i) {
        for(int j = 0; j < m.getCols(); ++j) {
            // ret[i][j] = 0;
            for(int k = 0; k < this->col; ++k) {
                ret[i][j] += this->data[i][k] * m[k][j];
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
bool Matrix<T>::operator==(const Matrix<T> m) const {
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
bool Matrix<T>::operator!=(const Matrix<T> m) const {
    //return !(*this == m);
    if (this->row != m.getRows() || this->col != m.getCols()) {
        return true;
    }
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (this->data[i][j] != m[i][j])
                return true;
        }
    }
    return false;
}

template <typename T>
Matrix<T> operator*(Matrix<T> m, T c) {
    Matrix<T> ret(m.getRows(), m.getCols());
    for(int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            ret[i][j] = m[i][j] * c;
        }
    }
    return ret;
}

template <typename T>
Matrix<T> operator*(T c, Matrix<T> m) {
    return m * c;
}

template <typename T>
Matrix<T> operator*=(Matrix<T> m, T c) {
    m = m * c;
    return m;
}

template <typename T>
std::ostream &operator<<(std::ostream &o, Matrix<T> m) {
    for(int i = 0; i < m.getRows(); ++i) {
        for(int j = 0; j < m.getCols(); ++j) {
            (j == m.getCols() - 1) ? o << m[i][j] : o << m[i][j] << " ";
        }
        o << std::endl;
    }
    return o;
}
