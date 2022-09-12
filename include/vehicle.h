#pragma once

#include <unordered_map>

#include "od.h"

namespace assignment {

class Vehicle {

    private:
        std::unordered_map<int, double> _local_incentives;
        tntp::OD* _od;

        double _alpha;
        double _beta;
        double _gamma;
};

}