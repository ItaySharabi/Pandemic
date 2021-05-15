#include "FieldDoctor.hpp"
using namespace std;

namespace pandemic {

    FieldDoctor& FieldDoctor::treat(const City& city)  {
        if(b.are_neighbor_cities(city, curr_city) || city == curr_city) {
            City t = curr_city;
            
            try {           
                curr_city = city;                   // switch to neighbor city
                Player::treat(city);                // treat()
                curr_city = t;                      // restore curr_city
                                
            } catch (const exception& e) {
                curr_city = t;                      // if fails - restore current city
                throw e;
            }
        } else {
            throw invalid_argument(role() + " can only treat his current city or it's neighbor cities!");
        }
            return *this;
        } 
};
