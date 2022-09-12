#pragma once

#include <memory>
#include <unordered_map>

#include "common.h"
#include "link.h"
#include "node.h"
#include "od.h"
#include "path.h"

namespace tntp {

class Network {
    public:
        Network(){}

        Network(const tntp::Network& network);

        void addLink(const std::string& tail_name,
                     const std::string& head_name,
                     const double capacity, 
                     const double freeflow_time,
                     const double bpr_a,
                     const double bpr_b);
        
        void addLink(const std::string& link_name,
                     const std::string& tail_name,
                     const std::string& head_name,
                     const double capacity, 
                     const double freeflow_time,
                     const double bpr_a,
                     const double bpr_b);
        /**
         * @brief parse ODs from string
         * 
         * @param od_str in format "o1:d1"
         */
        void addOD(const std::string& od_str, const double demand);

        /**
         * @brief parse paths from string
         * 
         * @param nodes_str in format "n1>n2>n3"
         */
        void addPath(const std::string& nodes_str);

        void buildNetwork();

        void generateVehicles();

        const std::unordered_map<int, std::shared_ptr<tntp::Node>>& getNodes() {
            return _nodes;
        }
        
        const std::unordered_map<std::string, std::shared_ptr<tntp::Link>>& getLinksByNames() {
            return _links_by_names;
        }

        std::shared_ptr<const tntp::Node> getNode(int node_id);

    private:
        void addNode(const std::string& name);

    private:
        /**
         * network: nodes, links, paths, ods
         * od: path
         * path: link
         * link: node
         */
        
        std::unordered_map<std::string, std::shared_ptr<tntp::Node>> _nodes_by_names;
        std::unordered_map<std::string, std::shared_ptr<tntp::Link>> _links_by_names;
        std::unordered_map<std::string, std::shared_ptr<tntp::Path>> _paths_by_names;
        std::unordered_map<std::string, std::shared_ptr<tntp::OD>> _ods_by_names;

        std::unordered_map<int, std::shared_ptr<tntp::Node>> _nodes;
        std::unordered_map<int, std::shared_ptr<tntp::Link>> _links;
        std::unordered_map<int, std::shared_ptr<tntp::Path>> _paths;
        std::unordered_map<int, std::shared_ptr<tntp::OD>> _ods;

};

}