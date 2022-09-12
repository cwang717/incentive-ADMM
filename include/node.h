#pragma once

#include <string>

namespace tntp {

class Node {
    public: 
        Node(std::string name, int id) : _name(name), _id(id) {}

    private:
        bool _is_od = false;
        std::string _name;
        int _id;
};

}
