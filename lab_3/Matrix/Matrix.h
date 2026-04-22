#pragma once
#include <initializer_list>

#include <cstddef>
#include <vector>
#include <concepts>
#include <stdexcept>

template <std::convertible_to<double> T>
class Matrix
{
private:
    std::vector<std::vector<T>> matrix;
    size_t rowCount, colsCount;
public:
    Matrix() = delete;
    Matrix(size_t rowCount, size_t colsCount);
    Matrix(size_t rowCount, size_t colsCount, const T& filler);

    Matrix(const Matrix<T>& other);
    Matrix(Matrix<T>&& other) noexcept;

    ~Matrix() = default;

    size_t getColsCount() const noexcept;
    size_t getRowsCount() const noexcept;

    Matrix<T>& operator=(const Matrix<T>& other);
    Matrix<T>& operator=(Matrix<T>&& other) noexcept;
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> ilist);

    Matrix<T> make_sum(const Matrix<T>& other) const;
    Matrix<T> operator+(const Matrix<T>& other) const;

    Matrix<T>& add(const Matrix<T>& other);
    Matrix<T>& operator+=(const Matrix<T>& other);

    Matrix<T> make_diff(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;

    Matrix<T>& subtract(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);

    Matrix<T> make_product(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;

    Matrix<T>& multiply(const Matrix<T>& other);
    Matrix<T>& operator*=(const Matrix<T>& other);

    Matrix<T> make_product(const T& elem) const;
    Matrix<T> operator*(const T& elem) const;
    
    Matrix<T>& multiply(const T& elem) noexcept;
    Matrix<T>& operator*=(const T& elem) noexcept;

    Matrix<T> negate() const;
    Matrix<T> operator-() const;

    std::vector<T>& operator[](size_t row);
    const std::vector<T>& operator[](size_t row) const;
};

