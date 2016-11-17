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
    int getRows();
    int getCols();
    std::vector<T> &operator[](const int index);
    const std::vector<T> &operator[](const int index) const;
    Matrix<T> operator+(Matrix m);
    Matrix<T> operator-(Matrix m);
    Matrix<T> operator*(Matrix m);
    Matrix<T> operator+=(Matrix m);
    Matrix<T> operator-=(Matrix m);
    Matrix<T> operator*=(Matrix m);
    bool operator==(Matrix m) const;
    bool operator!=(Matrix m) const;

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
    Matrix::row = r;
    Matrix::col = c;
    data.resize((unsigned) c, std::vector<T>((unsigned) r));
    //std::for_each(data.begin(), data.end(), [c](std::vector<T> d){d.resize((unsigned) c);});
}

template <typename T>
int Matrix<T>::getRows() {
    return this->row;
}

template <typename T>
int Matrix<T>::getCols() {
    return this->col;
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](const int index) {
    return data[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](const int index) const {
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
bool Matrix<T>::operator==(Matrix<T> m) const {
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            if (this->data[i][j] != m[i][j])
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
            o << m[i][j];
        }
        o << std::endl;
    }
    return o;
}
