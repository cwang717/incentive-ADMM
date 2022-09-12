#pragma once

#include <list>
#include <vector>

#include "link.h"

namespace tntp {

class Path {
    public:
        Path(tntp::Network* const network,
             const int id,
             const std::vector<std::string>& path_link_names);

        double calculateCost();
        
        double evaluateCost(double flow);
    
    private:
        tntp::Network* _network;
        int _id;
        std::vector<tntp::Link*> _links;
};

}