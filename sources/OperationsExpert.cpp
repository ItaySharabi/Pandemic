#include "OperationsExpert.hpp"

using namespace std;

namespace pandemic {

    OperationsExpert& OperationsExpert::build() {
        b.set_station(curr_city);
        return *this;
    }
};