#pragma once
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include "City.hpp"
#include "Color.hpp"

const std::string RESET       = "\033[0m";       /* Default White*/
const std::string BLACK       = "\033[30m";      /* Black */
const std::string RED         = "\033[31m";      /* Red */
const std::string YELLOW      = "\033[33m";      /* Yellow */
const std::string BLUE        = "\033[34m";      /* Blue */
const std::string GREEN       = "\033[32m";      /* Green */
const std::string MAGENTA     = "\033[35m";      /* Magenta */
const std::string BOLDMAGENTA = "\033[1m\033[35m";      /* Bold Magenta */
const std::string BOLDCYAN    = "\033[1m\033[36m";      /* Bold Cyan */

namespace pandemic {
                    /*==============//
                    ||    City      ||
                    ||    Struct    ||
                    //==============*/
struct Node {
    Color _color;               // City color
    int _disease_dice_count;    // Disease count
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
            void remove_cures();
            friend std::ostream& operator<< (std::ostream&, const Board&);

            // My additions: (Getters and Setters)
            const Color city_color(const City& city)                 const {const Color c = cities.at(city)._color; return c;}
            const bool are_neighbor_cities(const City& c1, const City& c2) const {return cities.at(c1)._neighbors.count(c2) > 0;} 
            const bool has_research_station(const City& city)        const {return cities.at(city)._has_research_station;}
            const bool has_cure(const Color& color)                  const {return cures.at(color);}
            const bool has_cure(const City& city)                    const {return cures.at(cities.at(city)._color);}
            void set_station(const City& city)                             {cities[city]._has_research_station = true;}
            void set_cure(const Color& color)                              {cures[color] = true;}

            // Board initialization:
            void read_cities(std::ifstream&); 
  
    };

};