#include "GeneSplicer.hpp"
#include <array>

using namespace std;

namespace pandemic {


    GeneSplicer& GeneSplicer::discover_cure(const Color& color) {
        
        if (b.has_research_station(curr_city)) {
            const int n = 5;
            bool unique_cards = true;
            vector<City> good_cards = get_n_cards_from_hand(n, !unique_cards, color);

            if (good_cards.size()  == n) {
                b.set_cure(color);
            } else {
                throw invalid_argument("Not enough cards!");
            }
        } else {
            throw invalid_argument("No research station!");
        }
        return *this;
    }

};