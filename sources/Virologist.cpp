#include "Virologist.hpp"


using namespace std;

namespace pandemic {
    /**
     *  @role: Virologist
     *  Can invoke treat(City) by discarding the matching city card,
     *  and treat the disease from afar.
     */
    Virologist& Virologist::treat(const City& city)  {

        if(cards[city]) {
            City temp = curr_city;
            try {
                curr_city = city;           // switch cities
                Player::treat(city);
                curr_city = temp;           
                cards[city] = false;        // throw card
            } catch(const exception& e) {
                curr_city = temp;           // restore city
                throw invalid_argument(e.what());
            }
        }else if(city == curr_city) {
            Player::treat(curr_city);       // regular treat()
        } else {
            throw invalid_argument("No matching card in hand!");
        }
        return *this;
    }

};