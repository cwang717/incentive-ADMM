#include "../include/link.h"
#include "../include/common.h"

#include <math.h>

namespace tntp {

double tntp::Link::evaluateCost(double flow) {
    double vcRatio = flow / _capacity;

    // Protect against negative flows, 0^0 errors.
    if (vcRatio < ZERO) {
        return _freeflow_time;
    }

    double travelTime = _freeflow_time * (1 + _a * pow(vcRatio, _b));

    return travelTime;
}

double tntp::Link::evalueateBeckmannComponent(double flow) {
    double vcRatio = flow / _capacity;

    // Protect against negative flows, 0^0 errors.
    if (vcRatio < ZERO) {
        return 0.0;
    }

    double beckmann = flow * _freeflow_time * (1 + _a / (_b + 1) * pow(vcRatio, _b));

    return beckmann;
}

double tntp::Link::calculateCost() {
    return _cost = evaluateCost(_flow);
}

double tntp::Link::calculateBeckmannComponent() {
    return _beckmann_link = evaluateCost(_flow);
}

}