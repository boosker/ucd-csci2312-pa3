#include "Exceptions.h"

namespace Clustering {

    // OutOfBoundsEx Functions

    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r) : __current(c), __rhs(r) {
        __name = "Out Of Bounds";
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
        return os;
    }

    // DimensionalityMismatchEx Functions

    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r) : __current(c), __rhs(r) {
        __name = "Dimensionality Mismatch";
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
        return os;
    }

    // ZeroClustersEx Functions

    ZeroClustersEx::ZeroClustersEx() {
        __name = "Zero Clusters";
    }

    std::string ZeroClustersEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex) {
        return os;
    }

    // DataFileOpenEx Functions

    DataFileOpenEx::DataFileOpenEx(std::string filename) : __filename(filename) {
        __name = "Data File Open";
    }

    std::string DataFileOpenEx::getFilename() const {
        return __filename;
    }

    std::string DataFileOpenEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex) {
        return os;
    }

    // ZeroDimensionsEx Functions

    ZeroDimensionsEx::ZeroDimensionsEx() {
        __name = "Zero Dimensions";
    }

    std::string ZeroDimensionsEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex) {
        return os;
    }

    // EmptyClusterEx Functions

    EmptyClusterEx::EmptyClusterEx() {
        __name = "Empty Cluster";
    }

    std::string EmptyClusterEx::getName() const {
        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex) {
        return os;
    }
}

