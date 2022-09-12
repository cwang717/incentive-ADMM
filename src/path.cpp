#include <algorithm>

#include "../include/path.h"

namespace tntp {

tntp::Path::Path(tntp::Network* const network,
                 const int id,
                 const std::vector<std::string>& path_link_names) : _network(network),
                                                                    _id(id) {
    auto& links_by_names = _network->getLinksByNames(); 
    std::transform(path_link_names.begin(), 
                   path_link_names.end(), 
                   std::back_inserter(_links),
                   [&links_by_names](const auto& link_name) {
                       return links_by_names.at(link_name).get();
                   });
}

}