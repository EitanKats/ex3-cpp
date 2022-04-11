//
// Created by Eitan Kats on 02/04/2022.
//

#include <vector>
#include <iostream>
#include <stdexcept>


#ifndef EX3_CPP_MATRIX_HPP
#define EX3_CPP_MATRIX_HPP

using std::vector;
using std::ostream;
using std::istream;
namespace zich {
    class Matrix {
    private:
        vector<double> _flatMatrix;
        int _rowsNum;
        int _columnsNum;

        double calculateSum() const;

        void validateDimensionsNaively(const Matrix &m) const;

        void validateDimensionsForMultiplication(const Matrix &m) const;

        void multiplyMats(const Matrix &other_m, std::vector<double> &multipliedMatVect) const;

    public:
        Matrix(vector<double> &matrix, int rowsNum, int colsNum);

        Matrix(const vector<double> &matrix, int rowsNum, int colsNum);

        friend ostream &operator<<(ostream &output, const Matrix &m);

        friend istream &operator>>(istream &input, Matrix &m);

        //region equality operators
        bool operator<(const Matrix &m) const;

        bool operator<=(const Matrix &m) const;

        bool operator>(const Matrix &m) const;

        bool operator>=(const Matrix &m) const;

        bool operator==(const Matrix &m) const;

        bool operator!=(const Matrix &m) const;
        //endregion


        Matrix operator-() const;

        Matrix operator+() const;


        //increments
        Matrix &operator++();

        Matrix operator++(int postfix);

        //decrement

        Matrix &operator--();

        Matrix operator--(int postfix);

        // between two matrices
        Matrix operator*(const Matrix &other_m) const;

        Matrix operator*=(const Matrix &other_m);

        Matrix operator+(const Matrix &other_m) const;

        Matrix operator-(const Matrix &other_m) const;

        Matrix &operator+=(const Matrix &other_m);

        Matrix &operator-=(const Matrix &other_m);

        Matrix &operator*=(const double scalar);

        Matrix operator*(double scalar);

        friend Matrix operator*(double scalar, const Matrix &m);
    };

}


#endif //EX3_CPP_MATRIX_HPP

