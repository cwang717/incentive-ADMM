#pragma once

#include <unordered_map>

#include "common.h"
#include "od.h"

namespace assignment {

class Vehicle {
    public:
        Vehicle(tntp::OD* const od, 
                const std::vector<double>& vehicle_params);

        void initLocal(const std::vector<tntp::Path*>& od_paths);

        const std::unordered_map<int, double> getLocalP() {
            return _p;
        }
    private:
        // (path_id->possibility)
        std::unordered_map<int, double> _p;
        // (path_id->incentive)
        std::unordered_map<int, double> _local_incentives;
        tntp::OD* _od;

        double _alpha;
        double _beta;
        double _gamma;
};

}