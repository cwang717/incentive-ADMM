#pragma once

#include <memory>
#include <vector>

#include "network.h"
#include "path.h"

namespace tntp {

class OD {
    public: 
        OD(tntp::Network * const network,
           const int id,
           tntp::Node * const origin, 
           tntp::Node * const destination,
           const double demand) : _demand(demand) {
            _network = network;
            _origin = origin;
            _destination = destination;
        }

        void addPath(tntp::Path * const path) {
            _paths.push_back(path);
        }

    private:
        tntp::Network* _network;
        tntp::Node const * _origin;
        tntp::Node const * _destination;
        std::vector<tntp::Path*> _paths;

        double _demand;
};

}