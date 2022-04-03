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
namespace zich {
    class Matrix {
    private:
        vector<double> _flatMatrix;
        int _rowsNum;
        int _columnsNum;

    public:
        Matrix(vector<double> &matrix, int rowsNum, int colsNum);

        friend ostream &operator<<(ostream &output, const Matrix &m);

        bool operator<(const Matrix &m) const;

        bool operator<=(const Matrix &m) const;

        bool operator>(const Matrix &m) const;

        bool operator>=(const Matrix &m) const;

        bool operator==(const Matrix &m) const;

        bool operator!=(const Matrix &m) const;


        Matrix operator-() const {
            vector<double> minusVect(this->_flatMatrix);
            for (size_t i = 0; i < minusVect.size(); ++i) {
                minusVect[i] = -minusVect[i];
            }
            Matrix minusMat{minusVect, this->_rowsNum, this->_columnsNum};
            return minusMat;
        };


        //increments
        Matrix &operator++();

        Matrix operator++(int postfix);

        //decrement

        Matrix &operator--();

        Matrix operator--(int postfix);

        // between two matrices
        Matrix operator*(const Matrix &other_m) const;

        Matrix operator+(const Matrix &other_m) const;

        Matrix operator-(const Matrix &other_m) const;


        Matrix& operator*=(const double scalar);

        friend Matrix operator*(double scalar, const Matrix &m);

        friend Matrix operator*(const Matrix &m, double scalar);
    };

}


#endif //EX3_CPP_MATRIX_HPP

