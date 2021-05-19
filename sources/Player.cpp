#include "Player.hpp"
using namespace std;


namespace pandemic {

    Player::Player(Board& board, const City& city): 
    b(board), curr_city(city), num_of_cards_to_discover(N) /* Init line */{/*Constructor*/}

    Player& Player::take_card(const City& city) {
        cards[city] = true; // need to cast from ulong to uint
        return *this;
    }

    Player& Player::remove_cards() {
        for (auto& card : cards) {
            card.second = false;
        }
        return *this;
    }

    Player& Player::drive(const City& city) {
        if(b.are_neighbor_cities(curr_city, city)) {
            curr_city = city;
        } else {
            throw invalid_argument( "Cannot drive to " + getCity(city) + ", Not a neighbor city!");
        }
        return *this;
    }

    Player& Player::fly_direct(const City& city) {
        // cout << "fly_direct(" << getCity(city) << ") Player invoked" << endl;
        if (city == curr_city) {throw invalid_argument("Cannot fly direct from city to itself!");}
        if(cards[city]) {          // if has dest city card
            cards[city] = false;   // discard 
            curr_city = city;      // move to city
        } else {
            throw invalid_argument("No card! Cannot fly directly to " + getCity(city));
        }
        return *this;
    }

    Player& Player::fly_charter(const City& city) {
        // cout << "fly_charter(" << getCity(city) << ") invoked" << endl;
        if (city == curr_city) {throw invalid_argument("Cannot fly charter from city to itself!");}

         if(cards[curr_city]) {        // if has current city card
            cards[curr_city] = false;  // discard current city card
            curr_city = city;               // move to city
        } else {
            throw invalid_argument("No card! Cannot fly charter to " + getCity(city));
        }
        return *this;
    }
  
    Player& Player::fly_shuttle(const City& city) {
        // cout << "fly_shuttle(" << getCity(city) << ") invoked" << endl;
        if (city == curr_city) {throw invalid_argument("Cannot fly shuttle from city to itself!");}

        if (b.has_research_station(curr_city) && b.has_research_station(city)) {
            curr_city = city;
        } else {
            throw invalid_argument("There is no research station in one of the cities!");
        }
        return *this;
    }

    Player& Player::discover_cure(const Color& color) {
        if (b.has_cure(color)) {return *this;}

        if (b.has_research_station(curr_city)) {
            const int n = num_of_cards_to_discover; // all players need 5 cards to cure a disease
            bool unique_cards = true;               // all players need unique colored cards to cure.
            vector<City> good_cards = get_n_cards_from_hand(n, unique_cards, color);

            if (good_cards.size() == n) { // if the amount of cards in hand is exactly n
                b.set_cure(color);        // discover cure - set true in cures[color] to indicate cure is found
                
                throw_cards(good_cards);  // throw the cards collected
            } else {
                throw invalid_argument("Not enough cards! Need cards to discover a cure");
            }
        } else {
            throw invalid_argument("No Research station!");
        }

        return *this;
    }

    Player& Player::build() {
        if(!b.has_research_station(curr_city)) {

            if(cards[curr_city]) {
                b.set_station(curr_city);
                cards[curr_city] = false;
            } else {
                throw invalid_argument("Missing " + getCity(curr_city) + " card!");
            }
        }
        return *this;
    }

    Player& Player::treat(const City& city) {
        if (city == curr_city) {
            if (b[city] > 0) {
                if (!b.has_cure(city)) {
                    // City has no cure - treat heals 1 disease level
                    b[city]--;
                } else {
                    // City has a cure - treat heals all disease in the city
                    b[city] = 0;
                }
            } else {
                throw invalid_argument("City is clear of disease! Cannot use treat(City)");
            }
        } else {
            throw invalid_argument(role() + " Cannot use treat() outside of city");
        }
        return *this;
    }

    ostream& operator<< (ostream& os, const Player& p) {

        os << p.role() + ": " << endl;
        os << "\tCurrent City: " + p.get_curr_city() << endl;        
        return os;
    }

        /** This method iterates over the players card collection and
        pushes "good cards" into a vector and returns the vector:
        @param n: How many cards to draw?
        @param unique_color: Should the cards be unique? set TRUE
                                                Otherwise - FALSE.
        @param color: The disease color to cure, if cards should be unique 
                            - then the card color should be 'color'.    
    */
    vector<City> Player::get_n_cards_from_hand(const int& n, const bool& unique_color, const Color& color) {

            int card_counter = 0;
            City city = City::Algiers; // Initialized for make tidy, otherwise - init in for loop
            // save cards in a vector of City
            vector<City> good_cards = {};
            for(const auto& pair : cards) {
                city = pair.first;
                if(card_counter == n){break;}
                //    has card  && shouldn't be unique OR has card &&  card color is unique   
                if((cards[city] && !unique_color) || ((cards[city] && b.city_color(city) == color ))) {
                    // found color card
                    good_cards.push_back(city);
                    card_counter++;
                } 
            }
            if (card_counter == n) {
                return good_cards;
            } 
            return vector<City>(0);
    }

    // Throws all cards that are found in the given vector
    void Player::throw_cards(const vector<City>& vector) {
        for (unsigned int i = 0; i < vector.size(); i++) { // Throw cards
            cards[vector.at(i)] = false;
        }
    }
};      
