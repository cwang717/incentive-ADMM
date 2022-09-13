#include <glog/logging.h>

#include "../include/common.h"
#include "../include/network.h"
#include "../include/solver.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_alsologtostderr = 1;
    FLAGS_v = 10;

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

    network->buildNetwork();

    if (FLAGS_v > 5) {
        network->printNetwork();
    }
    
    std::uint_least32_t seed = 31;
    admm::Solver solver(network.get(), seed);
    LOG(INFO) << "Initializing solver";
    solver.init();

    return 0;
}