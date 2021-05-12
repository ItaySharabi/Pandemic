#include "GeneSplicer.hpp"
#include <array>

using namespace std;

namespace pandemic {


    GeneSplicer& GeneSplicer::discover_cure(const Color& color) {
        
        // cout << "(GeneSplicer) research station: " << boolalpha << b.has_research_station(curr_city) << endl;
        // cout << "Color to discover: " << getColor(color) << endl;
        if (b.has_research_station(curr_city)) {
            const int n = 5;
            bool unique_cards = true;
            vector<City> good_cards = get_n_cards_from_hand(n, !unique_cards, color);
            // cout << "good_cards.size() == " << good_cards.size() << endl;
            // for (auto& card : cards) {
            //     if (card.second){
            //         cout << "has card: " << getCity(card.first) << ", " << b.city_color(card.first) << endl;
            //     } // if has card
            // }
            

            if (good_cards.size()  == n) {
                b.set_cure(color);
            } else {
                throw invalid_argument("Not enough cards!");
            }
        } else {
            throw invalid_argument("No research station!");
        }


        //     unsigned int count = 0;
        //     bool has_card = false;
        //     const int req_cards_for_cure = 5;
        //     // City good_cities[5] = {};
        //     array<City,5> good_cards;

        //     for (const auto& card : cards) {
        //         has_card = card.second;

        //         if (has_card) {
        //             good_cards.at(count) = card.first;    // card.first = city represented by card
        //             count++;
        //             if (count == req_cards_for_cure) {break;}
        //         }
                
        //     }
        //     if (count == 5) {
        //         b.set_cure(color);
        //         unsigned int i = 0;
        //         for (i = 0; i < good_cards.size(); i++) {
        //             cards[good_cards.at(i)] = false;
        //         }
        //     } else {
        //         throw invalid_argument("Not enough cards!");
        //     }
        // } else {
        //     throw invalid_argument("No research station in current city!");
        // }


        return *this;
    }

};