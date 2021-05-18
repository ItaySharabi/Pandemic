#include "OperationsExpert.hpp"

using namespace std;

namespace pandemic {

    /**
     *  @role: OperationsExpert
     *  Can invoke build(), and build a research station in any city,
     *  without throwing any card.
     */
    OperationsExpert& OperationsExpert::build() {
        b.set_station(curr_city);
        return *this;
    }
};