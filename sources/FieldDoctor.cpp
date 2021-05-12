#include "FieldDoctor.hpp"

using namespace std;

namespace pandemic {

    FieldDoctor& FieldDoctor::treat(const City& city)  {
        if(b.are_neighbor_cities(city, curr_city) || city == curr_city) {
            City t = curr_city;
            
            try {           
                curr_city = city;                   // switch to neighbor city
                Player::treat(city);
                curr_city = t;                      // restore
                                
            } catch (const invalid_argument& e) {
                curr_city = t;                      // if fails - restore
                throw invalid_argument(e.what());
            }
        } else {
            throw invalid_argument("Not connected cities");
        }
            return *this;
        } 
};
