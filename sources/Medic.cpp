#include "Medic.hpp"


namespace pandemic {

    /**
     *  @role: Medic
     *  A medic's treat() is more powerful than a Player's, and sets
     *  the disease level to 0 instantly when treat() is invoked!
     *  Moreover - When some cure is discovered, the Medic "Auto Heals"
     *  any city of the same color.
     */
    Medic& Medic::fly_charter(const City& city) {
        Player::fly_charter(city);
        auto_heal();
        return *this;
    }

    Medic& Medic::fly_shuttle(const City& city) {
        Player::fly_shuttle(city);
        auto_heal();
        return *this;
    }

    Medic& Medic::fly_direct(const City& city) {
        Player::fly_direct(city);
        auto_heal();
        return *this;
    }

    Medic& Medic::drive(const City& city) {
        Player::drive(city);
        auto_heal();
        return *this;
    }

    Medic& Medic::treat(const City& city) {

        if(curr_city == city) {
            if(b[curr_city] > 0) {
                    b[curr_city] = 0;
            } else {
                throw std::invalid_argument("No disease in current city!");
            }
        } else {
            throw std::invalid_argument("Cannot cure outside of current city!");
        }
        return *this;
    }

    void Medic::auto_heal() {
        if(b.has_cure(curr_city)) {
            b[curr_city] = 0;
        }
    }
};