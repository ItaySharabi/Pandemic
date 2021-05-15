#include "Scientist.hpp"

using namespace std;

namespace pandemic{

    Scientist& Scientist::discover_cure(const Color& color) {

        if(b.has_cure(color)) {return *this;}
        if (b.has_research_station(curr_city)) {
            unsigned int card_counter = 0;
            const int n = num_of_cards_to_discover;
            bool unique = true;
            vector<City> good_cards = get_n_cards_from_hand(n, unique, color);
            if (good_cards.size() == n) {
                unsigned int i = 0;
                b.set_cure(color);

                for (unsigned int i = 0; i < good_cards.size(); i++) { // Throw cards
                    cards[good_cards.at(i)] = false;
                }
            } else {
                throw invalid_argument("Need 5 cards to discover a cure!");
            }
        } else {
               
            throw invalid_argument("No research station in current city! cannot discover cure!");
        }
        return *this;
    }
    
};  