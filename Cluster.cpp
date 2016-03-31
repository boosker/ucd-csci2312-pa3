// File: Cluster.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#include "Cluster.h"
#include "Exceptions.h"

using namespace std;

namespace Clustering {
    static constexpr char POINT_VALUE_DELIM = ',';

    unsigned int Cluster::__idGenerator = 0;

    // LNode Constructor
    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n) {}

    // Cluster Constructor
    Cluster::Cluster(unsigned int d) : __id(__idGenerator++),
                                       __size(0), __points(nullptr),
                                       __dimensionality(d),
                                       centroid(__dimensionality, *this)
    {
        centroid.setValid(false);
    }

    unsigned int Cluster::getDimensionality() const {
        return __dimensionality;
    }

    unsigned int Cluster::getId() const {
        return __id;
    }

    // CENTROID CLASS FUNCTIONS

    Cluster::Centroid::Centroid(unsigned int d, const Cluster &c) : __dimensions(d),
                                                                    __p(d), __c(c)
    { }

    // Getters / Setters
    const Point Cluster::Centroid::get() const {
        return __p;
    }
    void Cluster::Centroid::set(const Point &p) {
        __valid = true;
        __p = p;
    }
    bool Cluster::Centroid::isValid() const {
        return __valid;
    }
    void Cluster::Centroid::setValid(bool valid) {
        __valid = valid;
    }

    // Functions
    void Cluster::Centroid::compute() {
        unsigned int dim = __c.__dimensionality;
        Point newPoint(dim);
        Point addend(dim);
        LNodePtr curr = __c.__points;

        for(std::size_t i = 0; i < __c.__size; i++){
            addend = curr->point;
            addend /= __c.__size;
            newPoint += addend;
            curr = curr->next;
        }
        __p = newPoint;
    }
    bool Cluster::Centroid::equal(const Point &p) const {
        return (p == __p);
    }
    void Cluster::Centroid::toInfinity() {
        for(int i = 0; i < __p.getDims(); i++)
            __p[i] = std::numeric_limits<double>::max();
    }

    // MOVE CLASS FUNCTIONS

    Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to) : __p(p),
                                                                      __from(from),
                                                                      __to(to)
    { }

    void Cluster::Move::perform() {
        __to.add(__p);
        __from.remove(__p);
        __from.centroid.setValid(false);
        __to.centroid.setValid(false);
    }

    // THE BIG THREE:

    // Copy Constructor
    Cluster::Cluster(const Cluster &c) : __dimensionality(c.__dimensionality),
                                         centroid(__dimensionality, c),
                                         __size(0), __points(nullptr), __id(c.__id)
    {
        centroid.setValid(false);
        LNodePtr temp = c.__points;

        while (temp != nullptr) {
                add(temp->point);
                temp = temp->next;
        }
    }

    // Assignment Operator
    Cluster &Cluster::operator=(const Cluster &c) {
        LNodePtr temp = c.__points;

        if (*this == c) {
            return *this;
        }
        else {
            __size = 0;
            __dimensionality = c.__dimensionality;
            __id = c.__id;
            centroid.setValid(false);

            while (temp != nullptr) {
                add(temp->point);
                temp = temp->next;
            }

            return *this;
        }
    }

    // Destructor
    Cluster::~Cluster() {
        LNodePtr current = __points;

        while (current != nullptr) {
            LNodePtr next = current->next;
            delete current;
            current = next;
        }
        __points = nullptr;
    }

    // Size Accessor
    unsigned int Cluster::getSize() const {
        return __size;
    }

    // SET FUNCTIONS:

    // Add Point Function
    void Cluster::add(const Point &point) {
        if (point.getDims() != __dimensionality)
            throw DimensionalityMismatchEx(__dimensionality, point.getDims());

        LNodePtr newNode = new LNode(point ,nullptr);

        if (__points == nullptr) {
            __points = newNode;
            newNode->next = nullptr;
        }
        else if (__points->point > point){
            newNode->next = __points;
            __points = newNode;
        }
        else {
            LNodePtr previous = __points, current = __points->next;

            while (true) {
                if (current == nullptr || current->point > point) {
                    previous->next = newNode;
                    newNode->next = current;
                    break;
                }
                previous = current;
                current = current->next;
            }
        }
        centroid.setValid(false);
        __size++;
    }

    // Remove Point Function
    const Point &Cluster::remove(const Point &point) {
        if (point.getDims() != __dimensionality)
            throw DimensionalityMismatchEx(__dimensionality, point.getDims());

        LNodePtr temp;
        LNodePtr previous = __points;

        if (__points == nullptr)
            return point;

        if (__points->point == point) {
            temp = __points->next;
            delete __points;
            __points = temp;
        } else {
            temp = __points;
            while ((temp != nullptr) && (temp->point != point)) {
                previous = temp;
                temp = temp->next;
            }
            if (temp) {
                previous->next = temp->next;
                delete temp;
            }
        }
        __size--;

        centroid.setValid(false);
        return point;
    }

    // Contains Function to tell if the point exists in *this
    bool Cluster::contains(const Point &point) const {
        LNodePtr temp = __points;

        while (temp != nullptr) {
            if (temp->point == point) {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    // PickCentroid Function
    void Cluster::pickCentroids(unsigned int k, Point **pointArray) {
        if (__size == 0) {
            return;
        }
        int step = __size / k;
        LNodePtr current = __points;
        *pointArray[0] = current->point;

        for (int i = 1; i < k; i++){
            int j = 0;
            while (current != nullptr && j < step){
                current = current->next;
                j++;
            }
            *pointArray[i] = current->point;
        }
    }

    // OVERLOADED OPERATORS:

    // MEMBER FUNCTIONS:
    // Subscript Operator
    const Point &Cluster::operator[](unsigned int index) const {
        if (__size == 0)
            throw EmptyClusterEx();
        if (index >= __size)
            throw OutOfBoundsEx(__size, index);

        LNodePtr temp = __points;

        for (int i = 0; i < index; i++)
            temp = temp->next;

        return temp->point;
    }

    // Compound Assignment += Point Argument
    Cluster &Cluster::operator+=(const Point &p) {
        add(p);

        return *this;
    }
    // Compound assignment -= Point Argument
    Cluster &Cluster::operator-=(const Point &p) {
        remove(p);

        return *this;
    }

    // Compound Assignment: Union Operator
    Cluster &Cluster::operator+=(const Cluster &c) {
        LNodePtr temp = c.__points;

        while (temp != nullptr) {
            if (!contains(temp->point))
                add(temp->point);
            temp = temp->next;
        }

        return *this;
    }

    // Compound Assignment: Asymetric Difference Operator
    Cluster &Cluster::operator-=(const Cluster &c) {
        LNodePtr temp = c.__points;

        while (temp != nullptr) {
            if (contains(temp->point))
                remove(temp->point);
            temp = temp->next;
        }

        return *this;
    }

    // FRIEND FUNCTIONS:

    // Output Operator
    std::ostream &operator<<(ostream &os, const Cluster &c) {
        LNodePtr temp = c.__points;

        if ((c.__points == nullptr))
            os << "The list is empty." << endl;
        else {
            while (temp != nullptr) {
                for (int i = 0; i < c.__size; i++) {
                    os << temp->point;
                    temp = temp->next;
                }
            }
            os << " : " << c.__id;
            return os;
        }
    }

    // Input Operator
    std::istream &operator>>(istream &in, Cluster &c) {
        std::string line;

        while (std::getline(in, line, ',')) {
            Point pt(1);
            std::stringstream lineStr(line);

            try {
                lineStr >> pt;
                c.add(pt);
            }
            catch (DimensionalityMismatchEx ex) {
                std::cerr << ex << std::endl;
            }
        }
        return in;
    }

    // Equality Comparison Operator
    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        if (rhs.__dimensionality != lhs.__dimensionality)
            throw DimensionalityMismatchEx(lhs.__dimensionality, rhs.__dimensionality);

        LNodePtr temp1 = lhs.__points;
        LNodePtr temp2 = rhs.__points;

        while (true) {
            if ((temp1 == nullptr) && (temp2 == nullptr))
                return true;

            if ((temp1 == nullptr) || (temp2 == nullptr))
                return false;

            if ((temp1->point) != (temp2->point))
                return false;

            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    // Inequality Comparison Operator
    bool operator!=(const Cluster &lhs, const Cluster &rhs) {
        return !(lhs == rhs);
    }

    // Arithmetic Operator: +, Cluster & Point
    const Cluster operator+(const Cluster &c, const Point &p) {
        Cluster temp = c;

        temp.add(p);

        return temp;
    }

    // Arithmetic Operator: -, Cluster & Point
    const Cluster operator-(const Cluster &c, const Point &p) {
        Cluster temp = c;

        temp.remove(p);

        return temp;
    }

    // Arithmetic Operator: +, Cluster & Cluster
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster temp(lhs);

        temp += rhs;

        return temp;
    }

    // Arithmetic Operator: +, Cluster & Cluster
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster temp(lhs);

        temp -= rhs;

        return temp;
    }
}
