#include "../include/vehicle.h"

namespace assignment {

assignment::Vehicle::Vehicle(tntp::OD* const od, 
                             const std::vector<double>& vehicle_params) : _od(od) {
    _alpha = vehicle_params[0];
    _beta = vehicle_params[1];
    _gamma = vehicle_params[2];
}

void assignment::Vehicle::initLocal(const std::vector<tntp::Path*>& od_paths) {
    double average_p = 1.0/od_paths.size();
    for (auto path_ptr : od_paths) {
        _p[path_ptr->getId()] = average_p;
        _local_incentives[path_ptr->getId()] = 1.0;
    }
}

}