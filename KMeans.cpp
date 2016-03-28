
#include "KMeans.h"

namespace Clustering {

    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) {

    }

    KMeans::~KMeans() {

    }

    unsigned int KMeans::getMaxIter() {
        return __maxIter;
    }

    unsigned int KMeans::getNumIters() {
        return __numIter;
    }

    unsigned int KMeans::getNumNonemptyClusters() {
        return __numNonempty;
    }

    unsigned int KMeans::getNumMovesLastIter() {
        return __numMovesLastIter;
    }

    Cluster &KMeans::operator[](unsigned int u) {
        //return <#initializer#>;
    }

    const Cluster &KMeans::operator[](unsigned int u) const {
        //return <#initializer#>;
    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans) {
        return os;
    }

    void KMeans::run() {

    }
}

