#include "Researcher.hpp"

using namespace std;

namespace pandemic {

    Researcher& Researcher::discover_cure(const Color& color) {
        if (b.has_cure(color)) {return *this;}

        const int n = num_of_cards_to_discover;
        bool unique = true;
        vector<City> good_cards = get_n_cards_from_hand(n, unique, color);
        if (good_cards.size() == n) {  
            
            b.set_cure(color);
            for (unsigned int i = 0; i < good_cards.size(); i++) {
                City c = good_cards.at(i);
                cards[c] = false;
            }
        } else {
            throw invalid_argument("Not enough cards!");
        }
        return *this;
    }

};