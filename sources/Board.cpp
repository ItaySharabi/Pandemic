#include <iostream>
#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <map>
// #include "UndirectedGraph.hpp"

using namespace std;

namespace pandemic {

    Board::Board()/*: cures(map<Color, bool>)*/ {

        std::ifstream units_file{"cities_map.txt"};
        initGraph(units_file);

        cures[Color::Black] = false;
        cures[Color::Blue] = false;
        cures[Color::Red] = false;
        cures[Color::Yellow] = false;
    }

    ostream& operator<< (ostream& os, const Node& node) {

        // os << "Color: " << getColor(node._color) << endl;
        return os;
    }

    // void Board::connect(City c1, City c2) {
    //     cities[c1]._neighbors.insert(c2);
    //     cities[c2]._neighbors.insert(c1);
    // }

    // void Board::newCity(City c, Color c2, int d, bool s){
    //     cities[City::Miami];
    //     cities[c]._color = c2;
    //     cities[c]._disease_dice_count = d;
    //     cities[c]._has_research_station = s;

    // }
    Board::~Board() {}
    
    bool Board::is_clean() const{
        bool clean = true;

        for (const auto& pair : cities) {
            Node city = pair.second;

            if (city._disease_dice_count > 0) {
                return !clean;    
            }        
        }

        return clean;
    }

    bool Board::are_neighbor_cities(const City& c1, const City& c2){ // Reconcider function signature in hpp file
        
        return cities[c1]._neighbors.count(c2) > 0;
    }

    bool Board::has_research_station(const City& city){
        return cities[city]._has_research_station;
    }

    void Board::set_station(const City& city) {
        cities[city]._has_research_station = true;
    }

    void set_station(const City&);


    int& Board::operator[] (const City& city){

        return cities[city]._disease_dice_count;
    }
    
    ostream& operator<< (ostream& os, const Board& board) {
        os << "Board: " << endl;
        for (const auto &pair : board.cities) {
            os << "City#" << getCity(pair.first) << ", Color#" << getColor(pair.second._color) << endl << "{\n";
            for (const auto &pair2 : board.cities.at(pair.first)._neighbors) {
                os << "\tNeighbor: City#" << getCity(pair2) << ", " << endl;

            }   
            os << "}\n";
        }
        return os;
    }
};

 