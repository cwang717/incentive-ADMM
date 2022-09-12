#include <vector>

#include "../include/network.h"
#include "../include/util.h"

namespace tntp {

using namespace tntp;

void Network::addNode(const std::string& name) {
    int id = _nodes_by_names.size();
    _nodes_by_names.at(name) = std::make_shared<tntp::Node>(name, id);
    _nodes.at(id) = _nodes_by_names.at(name);
}

void Network::addLink(const std::string& tail_name,
                      const std::string& head_name,
                      const double capacity, 
                      const double freeflow_time,
                      const double bpr_a,
                      const double bpr_b) {
    std::string link_name = tail_name + ">" + head_name;
    addLink(link_name, tail_name, head_name, capacity, freeflow_time, bpr_a, bpr_b);
}

void Network::addLink(const std::string& link_name,
                      const std::string& tail_name,
                      const std::string& head_name,
                      const double capacity, 
                      const double freeflow_time,
                      const double bpr_a,
                      const double bpr_b) {
    if (_nodes_by_names.find(tail_name) == _nodes_by_names.end()) {
        addNode(tail_name);
    }
    if (_nodes_by_names.find(head_name) == _nodes_by_names.end()) {
        addNode(head_name);
    }
    
    int id = _links_by_names.size();
    _links_by_names.at(link_name) = std::make_shared<tntp::Link>(this,
                                                                 id,
                                                                 _nodes_by_names.at(tail_name),
                                                                 _nodes_by_names.at(head_name),
                                                                 capacity, 
                                                                 freeflow_time, 
                                                                 bpr_a,
                                                                 bpr_b);
    _links.at(id) = _links_by_names.at(link_name);
}

void Network::addOD(const std::string& od_str, const double demand) {
    int id = _ods_by_names.size();
    std::vector<std::string> od = splitStr(od_str, ':');
    _ods_by_names.at(od_str) = std::make_shared<tntp::OD>(this,
                                                          id,
                                                          _nodes_by_names.at(od[0]).get(),
                                                          _nodes_by_names.at(od[1]).get(),
                                                          demand);
    _ods.at(id) = _ods_by_names.at(od_str);
}

void Network::addPath(const std::string& nodes_str) {
    int id = _paths_by_names.size();
    std::vector<std::string> path_links;
    std::vector<std::string> path_nodes = splitStr(nodes_str, '>');
    for (int i = 0; i < path_nodes.size() - 1; ++i) {
        path_links.push_back(path_nodes[i] + ">" + path_nodes[i+1]);
    }
    _paths_by_names.at(nodes_str) = std::make_shared<tntp::Path>(this, id, path_links);
    _paths.at(id) = _paths_by_names.at(nodes_str);
}

void Network::buildNetwork() {
    
}

} // namespace tntp
