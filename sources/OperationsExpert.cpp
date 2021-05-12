#include "OperationsExpert.hpp"

using namespace std;

namespace pandemic {

    OperationsExpert& OperationsExpert::build() {
         cards[curr_city] = true;
            if (!cards[curr_city]) {
                cards[curr_city] = true;
                Player::build();
            } else {
                Player::build();
                cards[curr_city] = true;
            }
        return *this;
    }

};