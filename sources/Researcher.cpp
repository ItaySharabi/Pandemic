#include "Researcher.hpp"
#include <array>

using namespace std;

namespace pandemic {

    Researcher& Researcher::discover_cure(const Color& color) {
        // cout << "Researcher discover_cure(" << getColor(color) << ")" << endl;
        if (b.has_cure(color)) {return *this;}

        const int n = 5;
        bool unique = true;
        vector<City> good_cards = get_n_cards_from_hand(n, unique, color);
        if (good_cards.size() == n) {  
            // cout << "I have just discovered a" << getColor(color) << "cure!" << endl;
            // cout << "Curr city: " << getCity(curr_city) << endl;
            
            b.set_cure(color);
            // cout << boolalpha << "is cure found? " << b.has_cure(color) << b.has_cure(curr_city) << endl;
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