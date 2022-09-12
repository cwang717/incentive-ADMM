
#include "../include/common.h"

#include "../include/network.h"

int main() {
    std::shared_ptr<tntp::Network> network = std::make_shared<tntp::Network>();
    network->addLink("1", "2", 4.0, 10.0, 1.0, 1.0);
    network->addLink("1", "3", 4.0, 2.0, 1.0, 1.0);
    network->addLink("3", "4", 4.0, 5.0, 1.0, 1.0);
    network->addLink("4", "2", 4.0, 4.0, 1.0, 1.0);
    network->addLink("5", "3", 4.0, 3.0, 1.0, 1.0);
    network->addLink("4", "6", 4.0, 3.0, 1.0, 1.0);
    network->addLink("5", "6", 4.0, 11.0, 1.0, 1.0);

    network->addOD("1:2", 6.0);
    network->addPath("1>2");
    network->addPath("1>3>4>2");

    network->addOD("5:6", 6.0);
    network->addPath("5>6");
    network->addPath("5>3>4>6");

    return 0;
}