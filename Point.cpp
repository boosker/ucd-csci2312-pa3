// File: Point.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

#include "Point.h"

using namespace std;

namespace Clustering {

    // ID Generator
    unsigned int Point::__idGen = 0;

    static const char POINT_VALUE_DELIM = ',';

    // Constructors

    Point::Point(unsigned int d) : __id(__idGen++), __dim(d), __values(new double[__dim]) {
        if (d == 0)
            throw ZeroDimensionsEx();

        for (int i = 0; i < __dim; i++)
            __values[i] = double();
    }

    Point::Point(unsigned int d, double *pDouble) : __id(__idGen++), __dim(d), __values(new double[__dim])  {
        if (d == 0)
            throw ZeroDimensionsEx();

        for (int i = 0; i < __dim; i++)
            __values[i] = pDouble[i];
    }

    // RewindID Function
    void Point::rewindIdGen() {
        __idGen--;
    }

    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point &p) {
        __id = p.__id;
        __dim = p.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
            __values[i] = p.__values[i];
    }

    Point &Point::operator=(const Point &p) {
        if (p.__dim != __dim)
            throw DimensionalityMismatchEx(__dim, p.__dim);

        __id = p.__id;
        __dim = p.__dim;
        for (int i = 0; i < __dim; i++)
            __values[i] = p.__values[i];

        return *this;
    }

    Point::~Point() {
        delete [] __values;
    }

    // Accessor Functions
    int Point::getId() const { return __id; }
    unsigned int Point::getDims() const { return __dim; }

    void Point::setValue(unsigned int i, double d) {
        if (i >= __dim)
            throw OutOfBoundsEx(i, __dim);

        __values[i] = d;
    }

    double Point::getValue(unsigned int i) const {
        if (i >= __dim)
            throw OutOfBoundsEx(i, __dim);

        return __values[i];
    }

    // Functions
    double Point::distanceTo(const Point &p) const {
        double add = 0;
        double distance;

        if (p.__dim != __dim)
            throw DimensionalityMismatchEx(__dim, p.__dim);

        for (int i = 0; i < __dim; i++)
            add = add + pow(__values[i] - p.__values[i], 2);
        distance = sqrt(add);

        return distance;

    }

    // OVERLOADED OPERATORS

    // Members
    Point &Point::operator*=(double d) {
        for (int i = 0; i < __dim; i++)
            __values[i] = __values[i] * d;

        return *this;
    }

    Point &Point::operator/=(double d) {
        for (int i = 0; i < __dim; i++)
            __values[i] = __values[i] / d;

        return *this;
    }

    const Point Point::operator*(double d) const {
        Point p(__dim, __values);

        for (int i = 0; i < p.__dim; i++)
            p.__values[i] = p.__values[i] * d;

        return p;
    }

    const Point Point::operator/(double d) const {
        Point p(__dim, __values);

        for (int i = 0; i < p.__dim; i++)
            p.__values[i] = p.__values[i] / d;

        return p;
    }

    double &Point::operator[](unsigned int index) {
        if (index >= __dim)
            throw OutOfBoundsEx(__dim, index);

        return __values[index];
    }

    const double &Point::operator[](unsigned int index) const {
        if (index >= __dim)
            throw OutOfBoundsEx(index, __dim);

        return __values[index];
    }

    Point &operator+=(Point &lhs, const Point &rhs) {
        if (rhs.__dim != lhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim, rhs.__dim);

        for (int i = 0; i < lhs.__dim; i++)
            lhs.__values[i] = lhs.__values[i] + rhs.__values[i];

        return lhs;
    }

    Point &operator-=(Point &lhs, const Point &rhs) {
        if (rhs.__dim != lhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim, rhs.__dim);

        for (int i = 0; i < lhs.__dim; i++)
            lhs.__values[i] = lhs.__values[i] - rhs.__values[i];

        return lhs;
    }

    const Point operator+(const Point &lhs, const Point &rhs) {
        Point p(lhs);

        p += rhs;

        return p;
    }

    const Point operator-(const Point &lhs, const Point &rhs) {
        Point p(lhs);

        p -= rhs;

        return p;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        if (rhs.__dim != lhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim, rhs.__dim);

        if (lhs.__id != rhs.__id) {
            return false;
        }
        if (lhs.__dim != rhs.__dim) {
            return false;
        }
        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] != rhs.__values[i]) {
                return false;
            }
        }

        return true;
    }


    bool operator!=(const Point &lhs, const Point &rhs) {
        return !(lhs == rhs);
    }

    bool operator<(const Point &lhs, const Point &rhs) {
        if (rhs.__dim != lhs.__dim)
            throw DimensionalityMismatchEx(lhs.__dim, rhs.__dim);

        for (int i = 0; i < lhs.__dim; i++) {
            if (lhs.__values[i] < rhs.__values[i]) {
                return true;
            }
        }

        return false;
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        return (rhs < lhs);
    }

    bool operator<=(const Point &lhs, const Point &rhs) {
        return !(lhs > rhs);
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        return !(lhs < rhs);
    }

    std::ostream &operator<<(ostream &os, const Point &p) {
        for (int i = 0; i < p.__dim - 1; i++)
            os << p.__values[i] << ",";
        os << p.__values[p.__dim - 1];
        os << " ; ";

        return os;
    }


    std::istream &operator>>(istream &in, Point &p) {
        std::string line;
        unsigned long int commas;

        std::getline(in, line, '\n');

        commas = (unsigned) (count(line.begin(), line.end(), POINT_VALUE_DELIM));
        commas += 1;

        if (commas != p.getDims()) {
            p.rewindIdGen();
            throw Clustering::DimensionalityMismatchEx(p.getDims(), commas);
        }

        std::stringstream lineStr(line);

        for (int i = 1; i <= p.getDims(); i++) {
            std::string value;
            std::getline(lineStr, value, POINT_VALUE_DELIM);
            double val = atof(value.c_str());

            try {
                p.setValue(i, val);
            }
            catch (Clustering::OutOfBoundsEx e) {
                std::cout << "In Point extraction operator - " << e << std::endl;
            }
        }
        return in;
    }
}