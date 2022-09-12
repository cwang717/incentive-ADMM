
#include "solver.h"

int main() {
    std::shared_ptr<tntp::Network> network = std::make_shared<tntp::Network>();
    network->addLink("1", "2", 4.0, 10.0, 1.0, 1.0);

    return 0;
}