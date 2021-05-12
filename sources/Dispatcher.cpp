#include "Dispatcher.hpp"

using namespace std;

namespace pandemic {

    Dispatcher& Dispatcher::fly_direct(const City& city) {
        // cout << "has research: " << b.has_research_station(curr_city) << endl;
        // cout << "fly_direct(" << getCity(city) << ") From " << getCity(curr_city) << endl;
        if (city == curr_city) {throw invalid_argument("Cannot fly from city to itself");}
        if(b.has_research_station(curr_city)) {
            if(!cards[city]) {
                curr_city = city;
            } else {
                Player::fly_direct(city);
                cards[city] = true;
            }
        } else {
            try {
                Player::fly_direct(city);
            } catch (const exception& e) {
                throw invalid_argument(e.what());
            }
        }

        return *this;
    }

};