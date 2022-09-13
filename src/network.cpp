#include <glog/logging.h>
#include <iostream>
#include <vector>

#include "../include/network.h"
#include "../include/od.h"
#include "../include/util.h"

namespace tntp {

using namespace tntp;

void Network::addNode(const std::string& name) {
    int id = _nodes_by_names.size();
    _nodes_by_names[name] = std::make_shared<tntp::Node>(name, id);
    _nodes[id] = _nodes_by_names.at(name);
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
    _links_by_names[link_name] = std::make_shared<tntp::Link>(this,
                                                                 id,
                                                                 _nodes_by_names.at(tail_name).get(),
                                                                 _nodes_by_names.at(head_name).get(),
                                                                 capacity, 
                                                                 freeflow_time, 
                                                                 bpr_a,
                                                                 bpr_b);
    _links[id] = _links_by_names.at(link_name);
}

void Network::addOD(const std::string& od_str, const double demand) {
    int id = _ods_by_names.size();
    std::vector<std::string> od = splitStr(od_str, ':');
    _ods_by_names[od_str] = std::make_shared<tntp::OD>(this,
                                                          id,
                                                          _nodes_by_names.at(od[0]).get(),
                                                          _nodes_by_names.at(od[1]).get(),
                                                          demand);
    _ods[id] = _ods_by_names.at(od_str);
}

void Network::addPath(const std::string& nodes_str) {
    int id = _paths_by_names.size();
    std::vector<std::string> path_links;
    std::vector<std::string> path_nodes = splitStr(nodes_str, '>');
    for (int i = 0; i < path_nodes.size() - 1; ++i) {
        path_links.push_back(path_nodes[i] + ">" + path_nodes[i+1]);
    }
    _paths_by_names[nodes_str] = std::make_shared<tntp::Path>(this, id, path_links);
    _paths[id] = _paths_by_names.at(nodes_str);

    std::string parent_od = *path_nodes.begin() + ":" + *path_nodes.rbegin();
    if (_ods_by_names.find(parent_od) == _ods_by_names.end()) {
        // error log
        std::cout << "Parent OD " << parent_od << " not added yet for path " << nodes_str << std::endl; 
    }
    _ods_by_names.at(parent_od)->addPath(_paths_by_names.at(nodes_str).get());
}

void Network::buildNetwork() {
    if (_ods.size() != _ods_by_names.size() ||
        _paths.size() != _paths_by_names.size() ||
        _links.size() != _links_by_names.size() ||
        _nodes.size() != _nodes_by_names.size()) {
        LOG(ERROR) << "Inconsistent ids and names";
    }
}

void Network::printNetwork() {
    std::cout << "ODs: " << std::endl; 
    for (const auto& od_p : _ods_by_names) {
        std::cout << od_p.first << "; ";
    }
    std::cout << std::endl << "Paths: " << std::endl;
    for (const auto& path_p : _paths_by_names) {
        std::cout << path_p.first << "; ";
    }
    std::cout << std::endl << "Links: " << std::endl;
    for (const auto& link_p : _links_by_names) {
        std::cout << link_p.first << "; ";
    }
    std::cout << std::endl;
}

} // namespace tntp
