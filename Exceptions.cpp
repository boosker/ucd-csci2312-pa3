#include "Exceptions.h"

using namespace std;

namespace Clustering {

    // OutOfBoundsEx Functions

    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r) : __current(c), __rhs(r) {
        __name = "OutOfBoundsEx";
    }

    unsigned int OutOfBoundsEx::getCurrent() const {
        return __current;
    }

    int OutOfBoundsEx::getRhs() const {
        return __rhs;
    }

    std::string OutOfBoundsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex) {
        os << ex.getName() << ": Index out of bounds!";
        return os;
    }

    // DimensionalityMismatchEx Functions

    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r) : __current(c), __rhs(r) {
        __name = "DimensionalityMismatchEx";
    }

    unsigned int DimensionalityMismatchEx::getCurrent() const {
        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const {
        return __rhs;
    }

    std::string DimensionalityMismatchEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex) {
        os << ex.getName() << ": Dimensions don't match!";
        return os;
    }

    // ZeroClustersEx Functions

    ZeroClustersEx::ZeroClustersEx() {
        __name = "ZeroClustersEx";
    }

    std::string ZeroClustersEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex) {
        os << ex.getName() << ": No clusters listed!";
        return os;
    }

    // DataFileOpenEx Functions

    DataFileOpenEx::DataFileOpenEx(std::string filename) : __filename(filename) {
        __name = "DataFileOpenEx";
    }

    std::string DataFileOpenEx::getFilename() const {
        return __filename;
    }

    std::string DataFileOpenEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex) {
        os << ex.getName() << ": Data file open!";
        return os;
    }

    // ZeroDimensionsEx Functions

    ZeroDimensionsEx::ZeroDimensionsEx() {
        __name = "ZeroDimensionsEx";
    }

    std::string ZeroDimensionsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex) {
        os << ex.getName() << ": No dimensions listed!";
        return os;
    }

    // EmptyClusterEx Functions

    EmptyClusterEx::EmptyClusterEx() {
        __name = "EmptyClusterEx";
    }

    std::string EmptyClusterEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex) {
        os << ex.getName() << ": Cluster is empty!";
        return os;
    }
}

