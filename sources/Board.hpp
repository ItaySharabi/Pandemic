#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include "City.hpp"
#include "Color.hpp"

namespace pandemic {

                                        /*==============//
                                        ||    Node      ||
                                        ||    Struct    ||
                                        //==============*/
struct Node {
    Color _color;               // City color
    int _disease_dice_count;    // Diseas count
    bool _has_research_station; // Research station 
    std::set<City> _neighbors;  // Neighbor cities
};// Node

    class Board {

        private:
            std::map<Color, bool> cures;
            std::map<City, Node> cities;

        public:

        Board();
        ~Board();

        // Required methods:
        bool is_clean() const;
        int& operator[] (const City&);
        friend std::ostream& operator<< (std::ostream&, const Board&);

        // My additions:
        bool are_neighbor_cities(const City& c1, const City& c2){return cities[c1]._neighbors.count(c2) > 0;}
        bool has_research_station(const City& city){return cities[city]._has_research_station;}
        void set_station(const City& city){cities[city]._has_research_station = true;}
        void remove_station(const City& city) {cities[city]._has_research_station = false;}
        bool has_cure(const Color& color) {return cures[color];}
        bool has_cure(const City& city) {return cures[cities[city]._color];}
        void set_cure(const Color& color) {cures[color] = true;}
        void remove_cures() {for (auto& cure : cures) { cure.second = false; }}
        const Color city_color(const City& city) {const Color c = cities[city]._color; return c;}


        void initBoard(std::ifstream&);
  
  
    };

};