#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "network.h"
#include "vehicle.h"

namespace admm {

class State {
    public:
        
        State(const State& st);
    
    private:
        tntp::Network* _network;
        std::unordered_set<std::shared_ptr<assignment::Vehicle>> _vehicles;
        std::unordered_map<int, double> _global_incentives;
};

class Solver {

    private:
        tntp::Network* _network;
        std::vector<std::shared_ptr<admm::State>> _states;
        admm::State* _init_state;
};

}