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

        OD(tntp::Network * const network,
           const int id,
           const int origin_id, 
           const int destination_id,
           const double demand) : _demand(demand) {
            _network = network;
            _origin = network->getNode(origin_id).get();
            _destination = network->getNode(destination_id).get();
        }

    private:
        tntp::Network* _network;
        tntp::Node const * _origin;
        tntp::Node const * _destination;
        std::vector<tntp::Path*> _paths;

        double _demand;
};

}