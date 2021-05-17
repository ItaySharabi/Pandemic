#include "Researcher.hpp"

using namespace std;

namespace pandemic {

    Researcher& Researcher::discover_cure(const Color& color) {
        if (b.has_cure(color)) {return *this;}

        const int n = num_of_cards_to_discover;
        bool unique = true;
        vector<City> good_cards = get_n_cards_from_hand(n, unique, color);

        if (good_cards.size() == n) {   // If n cards were found in player's hand
            b.set_cure(color);
            throw_cards(good_cards);
        } else {
            throw invalid_argument("Not enough cards!");
        }
        return *this;
    }

};