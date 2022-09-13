#include "../include/od.h"

namespace tntp {

tntp::OD::OD(tntp::Network * const network,
             const int id,
             tntp::Node * const origin, 
             tntp::Node * const destination,
             const double demand) : _id(id), _demand(demand) {
    _network = network;
    _origin = origin;
    _destination = destination;
    
    _alpha_dist = std::uniform_real_distribution<double>(8.0, 15.0);
    _beta_dist = std::uniform_real_distribution<double>(0.8, 1.2);
    _gamma_dist = std::uniform_real_distribution<double>(2.0, 4.0);
}

std::vector<double> tntp::OD::sampleVehicleParams(std::mt19937& random_gen) {
    std::vector<double> result;
    result.push_back(_alpha_dist(random_gen));
    result.push_back(_beta_dist(random_gen));
    result.push_back(_gamma_dist(random_gen));

    return result;
}

}