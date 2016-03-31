#include <limits>
#include <iostream>
#include <fstream>
#include "KMeans.h"
#include "Exceptions.h"
#include "Cluster.h"


using namespace std;

namespace Clustering {
    // Constructor
    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter) {
        if (k == 0)
            throw ZeroClustersEx();
        //if (filename != )
        //throw DataFileOpenEx(filename);
        __dimensionality = dim, __k = k, __iFileName = filename, __maxIter = maxIter;


        for (int i = 0; i < __k; i++) {
            __clusters[i] = new Cluster(dim);
        }
        for (int i = 0; i < __k; i++) {
            __initCentroids[i] = new Point(dim);
        }
    }

    // Destructor
    KMeans::~KMeans() {
        for (int i = 0; i < __k; i++) {
            delete __clusters[i];
            delete __initCentroids[i];
        }

        delete[] __clusters;
        delete[] __initCentroids;
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
        return *__clusters[u];
    }

    const Cluster &KMeans::operator[](unsigned int u) const {
        return *__clusters[u];
    }

    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans) {
        ofstream output("");
        for (int i = 0; i < kmeans.__k; i++)
            output << kmeans.__clusters[i];

        for (int i = 0; i < kmeans.__k; i++)
            cout << kmeans.__clusters[i];

        output.close();

        return os;
    }

    void KMeans::run() {
    }
}

