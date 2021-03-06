#include "GeneSplicer.hpp"

using namespace std;

namespace pandemic {

    /**
     *  @role: GeneSplicer
     *  Can discover a cure using ANY N=5 cards in hand.
     */
    GeneSplicer& GeneSplicer::discover_cure(const Color& color) {
        
        if (b.has_research_station(curr_city)) {
            const int n = num_of_cards_to_discover;
            bool unique_cards = true;               
            vector<City> good_cards = get_n_cards_from_hand(n, !unique_cards, color);

            if (good_cards.size()  == n) {
                b.set_cure(color);
                throw_cards(good_cards);
            } else {
                throw invalid_argument("Not enough cards!");
            }
        } else {
            throw invalid_argument("No research station!");
        }
        return *this;
    }

};