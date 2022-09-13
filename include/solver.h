#pragma once

#include <glog/logging.h>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"
#include "network.h"
#include "vehicle.h"
#include "util.h"

namespace admm {

class State {
    public:
        State(tntp::Network* const network) : _network(network) {}

        State(const State& st);

        void initVehicles(std::mt19937& random_gen);

        void printState();
    private:
        tntp::Network* _network;
        // veh_id -> vehicle ptr
        std::unordered_map<int, std::shared_ptr<assignment::Vehicle>> _vehicles;
        // (veh_id, path_id) -> incentive
        std::unordered_map<int, std::unordered_map<int, double>> _global_p;
};

class Solver {
    public:
        Solver(tntp::Network* const network, 
               const std::uint_least32_t random_seed) : _network(network),
                                                        _random_seed(random_seed) {
            _random_gen.seed(_random_seed);
        }
        
        Solver(tntp::Network* const network) {
            LOG(WARNING) << "Random seed not provided, getting it from /dev/urandom";
            std::uint_least32_t seed;
            sysrandom(&seed, sizeof(seed));
            Solver(network, seed);
        }

        void init();

    private:
        tntp::Network* _network;
        std::vector<std::shared_ptr<admm::State>> _states;
        admm::State* _init_state;

        std::mt19937 _random_gen;
        std::uint_least32_t _random_seed; 
};

}