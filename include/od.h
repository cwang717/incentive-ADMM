#pragma once

#include <memory>
#include <random>
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
           const double demand);

        void addPath(tntp::Path * const path) {
            _paths.push_back(path);
        }

        std::vector<double> sampleVehicleParams(std::mt19937& random_gen);

        const std::vector<tntp::Path*>& getPaths() {
            return _paths;
        }
        
        int getId() {
            return _id;
        }
        
        double getDemand() {
            return _demand;
        }

    private:
        tntp::Network* _network;
        tntp::Node const * _origin;
        tntp::Node const * _destination;
        std::vector<tntp::Path*> _paths;

        int _id;
        double _demand;

        std::uniform_real_distribution<double> _alpha_dist;
        std::uniform_real_distribution<double> _beta_dist;
        std::uniform_real_distribution<double> _gamma_dist;
};

}