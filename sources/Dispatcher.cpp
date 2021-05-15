#include "Dispatcher.hpp"

using namespace std;

namespace pandemic {

    Dispatcher& Dispatcher::fly_direct(const City& city) {
        if (city == curr_city) {throw invalid_argument("Cannot fly from city to itself");}
        if(b.has_research_station(curr_city)) {
            curr_city = city;
        } else { // If there is no research station - then try flying using a card
                Player::fly_direct(city);
        }
        return *this;
    }

};