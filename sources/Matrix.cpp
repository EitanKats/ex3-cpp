//
// Created by Eitan Kats on 02/04/2022.
//

#include "Matrix.hpp"

#include <utility>
#include "vector"
#include <cmath>
#include <ctype.h>
#include "string"
#include <regex>


using std::signbit;
namespace zich {

    Matrix::Matrix(vector<double> &matrix, int rowsNum, int colsNum) :
            _flatMatrix(matrix), _rowsNum(rowsNum), _columnsNum(colsNum) {
        if (rowsNum <= 0 || colsNum <= 0) {
            throw std::invalid_argument("bad dimensions");
        }
        if (rowsNum * colsNum != _flatMatrix.size()) {
            throw std::invalid_argument("bad dimensions");
        }
    }

    Matrix::Matrix(const vector<double> &matrix, int rowsNum, int colsNum) :
            _flatMatrix(matrix), _rowsNum(rowsNum), _columnsNum(colsNum) {
        if (rowsNum <= 0 || colsNum <= 0) {
            throw std::invalid_argument("bad dimensions");
        }
        if (rowsNum * colsNum != _flatMatrix.size()) {
            throw std::invalid_argument("bad dimensions");
        }
    }

    void Matrix::validateDimensionsNaively(const Matrix &m) const {
        if (this->_columnsNum != m._columnsNum || this->_rowsNum != m._rowsNum) {
            throw std::invalid_argument("cannot compare matrices with different dimensions");
        }

    }

    void Matrix::validateDimensionsForMultiplication(const Matrix &m) const {
        //the column condition is important because modulus is used in the function and it relies on division in cpp
        if (this->_columnsNum != m._rowsNum || m._columnsNum == 0) {
            throw std::invalid_argument("cannot multiply matrices with those dimensions");
        };
    }

    double Matrix::calculateSum() const {
        double sum = 0;
        for (const double &num: this->_flatMatrix) {
            sum += num;
        }
        return sum;
    }

    void Matrix::multiplyMats(const Matrix &other_m, std::vector<double> &multipliedMatVect) const {

        vector<double> &newVect = multipliedMatVect;
        int rowCtr = 0;
        int currRow = 0;
        for (int i = 0; i < multipliedMatVect.size(); ++i) {
            if (rowCtr == other_m._columnsNum) {
                currRow += _columnsNum;
                rowCtr = 0;
            }
            for (int j = 0; j < other_m._rowsNum; ++j) {
                // j* other_m._columnsNum loops over the first column indexes
                //the modulus is used to add an offset so that it lands of the column
                int nextMatIdx = (j * other_m._columnsNum) + (i % other_m._columnsNum);
                int currMatIdx = currRow + j;
                double fromOther = other_m._flatMatrix[(unsigned int) nextMatIdx];
                double fromCurrent = _flatMatrix[(unsigned int) currMatIdx];
                newVect[(unsigned int) i] += fromCurrent * fromOther;
            }
            rowCtr++;
        }
    }

    void validateRowFromInput(std::string &row) {
        if (row.at(0) != '[' || row.at(row.size() - 1) != ']') throw std::runtime_error("bad matrix as input");
        bool isRowOpen = false;
        bool isNumberParsing = false;
        int openBracketCtr = 0;
        int closingBracketCtr = 0;
        int bracketAmountLimit = 1;
        int dotsInNumLimit = 1;
        int numberOfDotsInNum = 0;
        std::string currNum;
        for (size_t i = 0; i < row.length(); ++i) {
            bool is_valid_char = isdigit(row[i]) || row[i] == '.' || row[i] == ' ' || row[i] == '[' || row[i] == ']' ||
                                 row[i] == '-';

            if (row[i] == '[' and isRowOpen) throw std::runtime_error("bad matrix as input");
            if (row[i] == ']' and !isRowOpen) throw std::runtime_error("bad matrix as input");
            if (row[i] == ']' and isRowOpen) closingBracketCtr++;
            if (isNumberParsing and row[i] == ' ') {
                isNumberParsing = false;
                numberOfDotsInNum = 0;
            }

            if (row[i] == '[') {
                isRowOpen = true;
                ++openBracketCtr;
            }

            if (!is_valid_char) throw std::runtime_error("bad matrix as input");
            if (closingBracketCtr > bracketAmountLimit || openBracketCtr > bracketAmountLimit)
                throw std::runtime_error("bad matrix as input");
            if ((row[i] == '.' || row[i] == '-') && !isNumberParsing) throw std::runtime_error("bad matrix as input");
            if ((isdigit(row[i]) || row[i] == '.') && isNumberParsing) {
                if (row[i] == '.' && numberOfDotsInNum == dotsInNumLimit) {
                    throw std::runtime_error("bad matrix as input");
                }
                if (row[i] == '.' and numberOfDotsInNum < dotsInNumLimit) {
                    numberOfDotsInNum++;
                }
            }
            currNum.append(1, row[i]);
            if ((isdigit(row[i]) || row[i] == '-' && isdigit(row[i + 1]) && !isNumberParsing)) {
                //starts new number
                currNum = row[i];
                isNumberParsing = true;
            }

        }
    }

    std::vector<std::string> splitText(const std::string &input, const std::string &regex) {
        // passing -1 as the submatch index parameter performs splitting
        std::regex re(regex);
        std::sregex_token_iterator
                first{input.begin(), input.end(), re, -1},
                last;
        return {first, last};
    }

    istream &operator>>(istream &input, Matrix &m) {
        std::string line;
        bool isRowOpen = false;
        int numCtr = 0;
        int rowCtr = 0;
        unsigned int currNumber = 0;
        getline(input, line);
        //the next 3 lines are used to split the lines by ", " https://stackoverflow.com/a/9437426/6569084
        // passing -1 as the submatch index parameter performs splitting
        std::string rowRegex = ", ";
        std::string numberSplitRegex = " ";
        std::string extractNumbersRegex = "\\[([^\\][]*)]";
        std::vector<std::string> columnsSplit = splitText(line, ", ");
        if (columnsSplit.empty()) throw std::runtime_error("bad matrix as input");

        unsigned int numsPerRow = 0;
        for (int i = 0; i < columnsSplit.size(); ++i) {
            std::string &currRow = columnsSplit.at((unsigned int) i);
            validateRowFromInput(currRow);
            std::vector<std::string> numbersSplit = splitText(currRow, extractNumbersRegex);
            if (i > 1 && numbersSplit.size() != numsPerRow) throw std::runtime_error("bad matrix as input");
            numsPerRow = numbersSplit.size();
        }

        return input;
    };

    ostream &operator<<(ostream &output, const Matrix &m) {

        for (int row = 0; row < m._rowsNum; ++row) {
            output << '[';
            for (int col = row * m._columnsNum; col < (row + 1) * m._columnsNum; ++col) {
                if (col % m._columnsNum == 0) {
                    output << m._flatMatrix[(unsigned int) col];
                } else {
                    output << ' ' << m._flatMatrix[(unsigned int) col];
                }
            }
            if (row < m._rowsNum - 1) {
                output << "]\n";
            } else {
                output << "]";
            }
        }
        return output;
    }

    Matrix &Matrix::operator*=(const double scalar) {
        for (double &i: this->_flatMatrix) {
            i = i == 0 ? i : i * scalar;
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other_m) const {
        this->validateDimensionsForMultiplication(other_m);
        int newMatSize = _rowsNum * other_m._columnsNum;
        std::vector<double> newVect((unsigned int) newMatSize, 0);
        multiplyMats(other_m, newVect);
        return Matrix{newVect, this->_rowsNum, other_m._columnsNum};
    }

    Matrix Matrix::operator*=(const Matrix &other_m) {
        this->validateDimensionsForMultiplication(other_m);
        int newMatSize = _rowsNum * other_m._columnsNum;
        std::vector<double> newVect((unsigned int) newMatSize, 0);
        multiplyMats(other_m, newVect);
        this->_columnsNum = other_m._columnsNum;
        this->_flatMatrix.swap(newVect);
        return *this;

    }

    Matrix Matrix::operator+(const Matrix &other_m) const {
        this->validateDimensionsNaively(other_m);
        std::vector<double> newVect(this->_flatMatrix);
        for (size_t i = 0; i < this->_flatMatrix.size(); ++i) {
            newVect[i] += other_m._flatMatrix[i];
        }
        return Matrix{newVect, this->_rowsNum, this->_columnsNum};
    }

    Matrix &Matrix::operator+=(const Matrix &other_m) {
        this->validateDimensionsNaively(other_m);
        for (size_t i = 0; i < other_m._flatMatrix.size(); ++i) {
            this->_flatMatrix[i] = this->_flatMatrix[i] + other_m._flatMatrix[i];
        }
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &other_m) {
        this->validateDimensionsNaively(other_m);
        for (size_t i = 0; i < other_m._flatMatrix.size(); ++i) {
            this->_flatMatrix[i] = this->_flatMatrix[i] - other_m._flatMatrix[i];
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other_m) const {
        this->validateDimensionsNaively(other_m);
        std::vector<double> newVect(this->_flatMatrix);
        for (size_t i = 0; i < this->_flatMatrix.size(); ++i) {
            newVect[i] -= other_m._flatMatrix[i];
        }
        return Matrix{newVect, this->_rowsNum, this->_columnsNum};
    }

    Matrix operator*(double scalar, const Matrix &m) {
        std::vector<double> newMatVect(m._flatMatrix.size());
        for (size_t i = 0; i < m._flatMatrix.size(); ++i) {
            newMatVect[i] = m._flatMatrix[i] == 0 ? m._flatMatrix[i] : m._flatMatrix[i] * scalar;
        }
        return Matrix{newMatVect, m._rowsNum, m._columnsNum};
    }

    Matrix Matrix::operator-() const {
        vector<double> minusVect(this->_flatMatrix);
        for (double &i: minusVect) {
            i = i == 0 ? 0 : -i;
        }
        Matrix minusMat{minusVect, this->_rowsNum, this->_columnsNum};
        return minusMat;
    }

    //region equality operators
    bool Matrix::operator!=(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return !this->operator==(m);
    }

    bool Matrix::operator==(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        for (size_t i = 0; i < m._flatMatrix.size(); ++i) {
            double myNum = this->_flatMatrix[i];
            double otherMatNum = m._flatMatrix[i];
            if ((myNum == 0 || otherMatNum == 0) && ((bool) signbit(myNum) != (bool) signbit(otherMatNum))) {
                return false;
            }
            if (myNum != otherMatNum) {
                return false;
            }
        }

        return true;
    }

    bool Matrix::operator<=(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->operator==(m) || this->operator<(m);
    }

    bool Matrix::operator>=(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->operator==(m) || this->operator>(m);
    }

    bool Matrix::operator>(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->calculateSum() > m.calculateSum();
    }

    bool Matrix::operator<(const Matrix &m) const {
        this->validateDimensionsNaively(m);
        return this->calculateSum() < m.calculateSum();
    }
    //endregion

    Matrix Matrix::operator+() const {
        std::vector<double> cpyVect(this->_flatMatrix);
        Matrix matCpy{cpyVect, this->_rowsNum, this->_columnsNum};
        return matCpy;
    }

    Matrix Matrix::operator*(double scalar) {
        std::vector<double> cpyVect(this->_flatMatrix);
        for (double &i: cpyVect) {
            i = i == 0 ? i : i * scalar;
        }

        return Matrix{cpyVect, this->_rowsNum, this->_columnsNum};
    }


    //region postfix and prefix operators
    Matrix &Matrix::operator++() {
        for (double &i: this->_flatMatrix) {
            ++i;
        }
        return *this;
    }

    Matrix Matrix::operator++(int postfix) {
        std::vector<double> cpyVect(this->_flatMatrix);
        Matrix matCpy{cpyVect, this->_rowsNum, this->_columnsNum};
        ++(*this);
        return matCpy;
    }

    Matrix &Matrix::operator--() {
        for (double &i: this->_flatMatrix) {
            --i;
        }
        return *this;
    }

    Matrix Matrix::operator--(int postfix) {
        std::vector<double> cpyVect(this->_flatMatrix);
        Matrix matCpy{cpyVect, this->_rowsNum, this->_columnsNum};
        --(*this);
        return matCpy;
    }
    //endregion
}