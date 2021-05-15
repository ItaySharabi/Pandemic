#pragma once
#include "City.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include <map>
#include <exception>
#include <vector>
#include <iostream>

namespace pandemic {
const int N = 5;

    class Player {

        protected: 
            Board& b;
            City curr_city; 
            std::map<City, bool> cards;
            std::vector<City> get_n_cards_from_hand(const int&, bool, const Color&);
            int num_of_cards_to_discover;
            void throw_cards(std::vector<City>&);
            
        public:
            Player(Board&, const City&);
            ~Player(){}

            // Required methods: 
            Player& take_card(const City&);

            virtual Player& drive(const City&);
            virtual Player& fly_charter(const City&);
            virtual Player& fly_shuttle(const City&);
            virtual Player& build();  
            virtual Player& discover_cure(const Color&);
            virtual Player& fly_direct(const City&);
            virtual Player& treat(const City&);
            virtual const std::string role() const {return "Player";} 
    };
};
