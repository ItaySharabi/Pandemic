#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <unistd.h>
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
    friend std::ostream& operator<< (std::ostream&, const Node&);
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
        bool are_neighbor_cities(const City&, const City&);
        bool has_research_station(const City&);
        void set_station(const City&);
        void remove_station(const City& city) {cities[city]._has_research_station = false;}
        bool has_cure(const Color& color) {return cures[color];}
        bool has_cure(const City& city) {return cures[cities[city]._color];}
        void set_cure(const Color& color) {cures[color] = true;}
        void remove_cures() {for (auto& cure : cures) { cure.second = false; }}
        const Color city_color(const City& city) {const Color c = cities[city]._color; return c;}


        void initGraph(std::ifstream& units_file){
            std::string line;
            std::string delimiter = " ";
            size_t pos = 0;
            std::string word;
            std::string city;
            while(std::getline(units_file, line)){
                int run = 0;
                int length = line.length();
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    word = line.substr(0, pos);
                    line.erase(0, pos + delimiter.length());
                    if(run == 0){
                        city = word;
                        cities[getCity(word)];
                        // Cure_discovered[getCity(word)] = false;
                        cities[getCity(word)]._disease_dice_count = 0;
                        cities[getCity(word)]._has_research_station = false;
                    }else if(run == 1){
                        cities[getCity(city)]._color = getColor(word); 
                    }else if(run > 1){
                        cities[getCity(city)]._neighbors.insert(getCity(word));
                    }
                    run++;
                }
                if(length > 0){
                    cities[getCity(city)]._neighbors.insert(getCity(line));
                }
            }

            
        }
  
  
    };

};