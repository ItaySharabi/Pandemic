#pragma once
#include "City.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include <map>
#include <exception>
#include <vector>
#include <iostream>

const int N = 5;    // Default number of cards to discover a cure for any player

namespace pandemic {
// const int N = 5;    // Default number of cards to discover a cure for any player

    class Player {

        protected: 
            Board& b;
            City curr_city; 
            std::map<City, bool> cards;
            int num_of_cards_to_discover;

            std::vector<City> get_n_cards_from_hand(const int&, const bool&, const Color&);
            void throw_cards(const std::vector<City>&); // throws cards found in the vector
            
        public:
            Player(Board&, const City&);
            /*virtual*/ ~Player(){}

            // Required methods: 
            Player& take_card(const City&);
            Player& remove_cards();

            virtual Player& drive(const City&);
            virtual Player& fly_direct(const City&);
            virtual Player& fly_charter(const City&);
            virtual Player& fly_shuttle(const City&);
            virtual Player& build();  
            virtual Player& discover_cure(const Color&);
            virtual Player& treat(const City&);
            virtual const std::string role() const {return "Player";} 

            // My additions:
            const std::string get_curr_city() const{const std::string s = getCity(curr_city); return s;}
            friend std::ostream& operator<< (std::ostream&, const Player&);
    };
};
