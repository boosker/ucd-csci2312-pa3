// File: Cluster.cpp
// Name: Jacob Jolly
// Class: CSCI 2312
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#include "Cluster.h"

using namespace std;

namespace Clustering {
    static constexpr char POINT_VALUE_DELIM = ',';

    unsigned int Cluster::__idGenerator = 0;

    // LNode Constructor
    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n) {}

    // Cluster Default Constructor
    //Cluster::Cluster() : __size(0), __points(nullptr) {}

    // THE BIG THREE:

    // Copy Constructor
    /*Cluster::Cluster(const Cluster &c) {
        LNodePtr temp = c.__points;

        if (*this == c) {
            return;
        }
        else {

            __points = nullptr;
            __size = 0;

            while (temp != nullptr) {
                add(temp->point);
                temp = temp->next;
            }
        }
    } */

    // Assignment Operator
    Cluster &Cluster::operator=(const Cluster &c) {
        LNodePtr temp = c.__points;

        if (*this == c) {
            return *this;
        }
        else {
            __points = nullptr;
            __size = 0;

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
        __size++;
    }

    // Remove Point Function
    const Point &Cluster::remove(const Point &point) {
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

    // OVERLOADED OPERATORS:

    // MEMBER FUNCTIONS:
    // Subscript Operator
    const Point &Cluster::operator[](unsigned int index) const {
        LNodePtr temp = __points;

        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

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
            return os;
        }
    }

    // Input Operator
    std::istream &operator>>(istream &in, Cluster &c) {
        std::string line;
        while (getline(in,line)) {
            int d = (int) std::count(line.begin(),
                                     line.end(), Clustering::POINT_VALUE_DELIM);

            Point p(d + 1);// = new Clustering::Point(d + 1);
            std::stringstream lineStream(line);

            lineStream >> p;

            c.add(p);
        }

        return in;
    }

    // Equality Comparison Operator
    bool operator==(const Cluster &lhs, const Cluster &rhs) {
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
