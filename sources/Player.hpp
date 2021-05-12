#pragma once
#include "City.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include <map>
#include <vector>
#include <iostream>

namespace pandemic {


    class Player {

        protected: 
            Board& b;
            City curr_city;
            std::string name;
            // // std::vector<bool> cards; // a vector of size 48 to hold a bool value in every city index
            std::map<City, bool> cards;
            bool has_card(const City& city){ return cards[city]; }

            // const std::string player_role;
            std::vector<City> get_n_cards_from_hand(const int&, bool, const Color&);
            
        public:
            Player(Board&, const City&);
            ~Player(){}
            
            Player& take_card(const City&);
            virtual Player& drive(const City&);
            virtual Player& fly_charter(const City&);
            virtual Player& fly_shuttle(const City&);
            virtual Player& build();  // Allows runtime polymorphism
            virtual Player& discover_cure(const Color&);
            virtual Player& fly_direct(const City&);
            virtual Player& treat(const City&);
            virtual const std::string role() const {return "Player";} 
    };

    
};
