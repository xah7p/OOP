#include "Matrix.h"

template <std::convertible_to<double> T>
Matrix<T>::Matrix(size_t rowCount, size_t colsCount):
    matrix(rowCount, std::vector<T>(colsCount, T{})), rowCount(rowCount), colsCount(colsCount)
{ }

template <std::convertible_to<double> T>
Matrix<T>::Matrix(size_t rowCount, size_t colsCount, const T& filler):
    matrix(rowCount, std::vector<T>(colsCount, filler)), rowCount(rowCount), colsCount(colsCount)
{ }

template <std::convertible_to<double> T>
Matrix<T>::Matrix(const Matrix<T>& other) = default;

template <std::convertible_to<double> T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept = default;

template <std::convertible_to<double> T>
size_t Matrix<T>::getColsCount() const noexcept
{
    return colsCount;
}

template <std::convertible_to<double> T>
size_t Matrix<T>::getRowsCount() const noexcept
{
    return rowCount;
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) = default;

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept = default;

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> ilist)
{
    rowCount = ilist.size();
    colsCount = ilist.begin()->size();
    matrix.assign(rowCount, std::vector<T>(colsCount, T{}));
    size_t r = 0;
    for (const auto& row : ilist)
    {
        size_t c = 0;
        for (const auto& el : row)
            matrix[r][c++] = el;
        ++r;
    }
    return *this;
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::make_sum(const Matrix<T>& other) const
{
    Matrix<T> out(*this);
    return out.add(other);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    return make_sum(other);
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::add(const Matrix<T>& other)
{
    if (rowCount != other.rowCount || colsCount != other.colsCount)
        throw std::runtime_error("Matrix dimensions mismatch");
    for (size_t i = 0; i < rowCount; ++i)
        for (size_t j = 0; j < colsCount; ++j)
            matrix[i][j] += other.matrix[i][j];
    return *this;
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
    return add(other);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::make_diff(const Matrix<T>& other) const
{
    Matrix<T> out(*this);
    return out.subtract(other);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
    return make_diff(other);
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::subtract(const Matrix<T>& other)
{
    if (rowCount != other.rowCount || colsCount != other.colsCount)
        throw std::runtime_error("Matrix dimensions mismatch");
    for (size_t i = 0; i < rowCount; ++i)
        for (size_t j = 0; j < colsCount; ++j)
            matrix[i][j] -= other.matrix[i][j];
    return *this;
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
    return subtract(other);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::make_product(const Matrix<T>& other) const
{
    if (colsCount != other.rowCount)
        throw std::runtime_error("Matrix dimensions mismatch");
    Matrix<T> out(rowCount, other.colsCount, T{});
    for (size_t i = 0; i < rowCount; ++i)
        for (size_t k = 0; k < colsCount; ++k)
            for (size_t j = 0; j < other.colsCount; ++j)
                out[i][j] += matrix[i][k] * other.matrix[k][j];
    return out;
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
    return make_product(other);
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::multiply(const Matrix<T>& other)
{
    *this = make_product(other);
    return *this;
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
{
    return multiply(other);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::make_product(const T& elem) const
{
    Matrix<T> out(*this);
    return out.multiply(elem);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::operator*(const T& elem) const
{
    return make_product(elem);
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::multiply(const T& elem) noexcept
{
    for (size_t i = 0; i < rowCount; ++i)
        for (size_t j = 0; j < colsCount; ++j)
            matrix[i][j] *= elem;
    return *this;
}

template <std::convertible_to<double> T>
Matrix<T>& Matrix<T>::operator*=(const T& elem) noexcept
{
    return multiply(elem);
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::negate() const
{
    Matrix<T> out(*this);
    return out.multiply(static_cast<T>(-1));
}

template <std::convertible_to<double> T>
Matrix<T> Matrix<T>::operator-() const
{
    return negate();
}

template <std::convertible_to<double> T>
std::vector<T>& Matrix<T>::operator[](size_t row)
{
    return matrix[row];
}

template <std::convertible_to<double> T>
const std::vector<T>& Matrix<T>::operator[](size_t row) const
{
    return matrix[row];
}

template class Matrix<double>;