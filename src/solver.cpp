#include <glog/logging.h>
#include <iostream>

#include "../include/solver.h"

namespace admm {

void State::initVehicles(std::mt19937& random_gen) {
    for (const auto& od_p : _network->getOds()) {
        auto od = od_p.second.get();
        VLOG(6) << "Initializing vehicles for od " << od->getId();

        double od_demand = od->getDemand();
        int num_vehicles = od_demand + 0.5; // truction
        for (int i = 0; i < num_vehicles; ++i) {
            int veh_id = _vehicles.size();
            _vehicles[veh_id] = std::make_shared<assignment::Vehicle>(od,
                                                                      od->sampleVehicleParams(random_gen));
            auto veh_ptr = _vehicles[veh_id].get();
            veh_ptr->initLocal(od->getPaths());
            _global_p[veh_id] = veh_ptr->getLocalP();
        }   
    }
}

void State::printState() {
    for (const auto& veh_p : _global_p) {
        std::cout << "Vehicle " << veh_p.first << "\t";
        for (const auto& pp : veh_p.second) {
            std::cout << "(" << pp.first << ":" << pp.second << "), ";
        }
        std::cout << std::endl;
    }
}

void Solver::init() {
    _states.push_back(std::make_shared<admm::State>(_network));
    _init_state = (*_states.begin()).get();
    VLOG(5) << "Initializing vehicles for init_state";
    _init_state->initVehicles(_random_gen);
    if (FLAGS_v > 5) {
        _init_state->printState();
    }
}

}