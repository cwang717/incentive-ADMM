#pragma once

#include <memory>

#include "common.h"
#include "node.h"
#include "network.h"

namespace tntp {

class Link {
    public:
        Link(tntp::Network * const network,
             const int id,
             tntp::Node * const tail,
             tntp::Node * const head,
             const double capacity, 
             const double freeflow_time,
             const double bpr_a,
             const double bpr_b) : _id(id),
                                   _capacity(capacity),
                                   _freeflow_time(freeflow_time),
                                   _a(bpr_a),
                                   _b(bpr_b),
                                   _speed_limit(30.0) {
            _network = network;
            _tail = tail;
            _head = head;
            _length = _speed_limit * _freeflow_time;
        }

        Link(tntp::Network * const network,
             const int id,
             tntp::Node * const tail,
             tntp::Node * const head,
             const double capacity, 
             const double length,
             const double freeflow_time,
             const double bpr_a,
             const double bpr_b,
             const double speed_limit) : _id(id),
                                         _capacity(capacity),
                                         _length(length),
                                         _freeflow_time(freeflow_time),
                                         _a(bpr_a),
                                         _b(bpr_b),
                                         _speed_limit(speed_limit) {
            _network = network;
            _tail = tail;
            _head = head;
        }
        /**
         * @brief Calculates the cost of the link using the BPR relation and record in _cost
         * 
         * @return double 
         */
        double calculateCost();

        /**
         * @brief Evaluate the cost of the link using the BPR relation.
         * 
         * @param flow 
         * @return double 
         */
        double evaluateCost(double flow);

        /**
         * @brief Calculate BeckmannComponent and record in _beckmann_link
         * 
         * @return double 
         */
        double calculateBeckmannComponent();

        /**
         * @brief Evaluate Beckmann component 
         * 
         * @param flow 
         * @return double 
         */
        double evalueateBeckmannComponent(double flow);
        
    
    private:
        tntp::Network*  _network;
        tntp::Node* _head;
        tntp::Node* _tail;

        int _id;
        double _capacity;
        double _length;
        double _freeflow_time;
        double _a;
        double _b;
        double _speed_limit;

        double _flow;
        double _cost;
        double _beckmann_link;
};

}