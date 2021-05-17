#include "Scientist.hpp"

using namespace std;

namespace pandemic{

    Scientist& Scientist::discover_cure(const Color& color) {
        if(b.has_cure(color)) {return *this;}

        if (b.has_research_station(curr_city)) {
            unsigned int card_counter = 0;
            const int n = num_of_cards_to_discover;
            bool unique_cards = true;
            vector<City> good_cards = get_n_cards_from_hand(n, unique_cards, color);

            if (good_cards.size() == n) {
                b.set_cure(color);
                throw_cards(good_cards);
                
            } else {
                throw invalid_argument("Need 5 cards to discover a cure!");
            }
        } else {
            throw invalid_argument("No research station in current city! cannot discover cure!");
        }
        return *this;
    }
    
};  