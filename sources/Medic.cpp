#include "Medic.hpp"


namespace pandemic {


    Medic& Medic::fly_charter(const City& city) {
        Player::fly_charter(city);
        if(b.has_cure(curr_city)) {
            b[curr_city] = 0;
        }
        return *this;
    }

    Medic& Medic::fly_shuttle(const City& city) {
        Player::fly_shuttle(city);
        if(b.has_cure(curr_city)) {
            b[curr_city] = 0;
        }
        return *this;
    }

    Medic& Medic::fly_direct(const City& city) {
        Player::fly_direct(city);
        if(b.has_cure(curr_city)) {
            b[curr_city] = 0;
        }
        return *this;
    }


    Medic& Medic::drive(const City& city) {

        Player::drive(city);
        // try {
        //     Player::drive(city);
        //     // std::cout << "ride() MEDIC OVERRIDE" << std::endl;
        if(b.has_cure(curr_city)) {
            b[curr_city] = 0;
        }
        // } catch (const std::exception& e) {
        //     std::cout << e.what() << std::endl;
        // }

        
        return *this;
    }

    Medic& Medic::treat(const City& city) {

        if(curr_city == city) {
            if(b[curr_city] > 0) {
                // if (!b.has_cure(curr_city)) {
                    b[curr_city] = 0;
                // }
            } else {
                throw std::invalid_argument("No disease in current city!");
            }
        } else {
            throw std::invalid_argument("Cannot cure outside of current city!");
        }
        // std::cout << "b[" << getCity(city) << "] = " << b[city] << std::endl;
        return *this;
    }

};