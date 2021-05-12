#include <iostream>
#include "Board.hpp"


using namespace std;

namespace pandemic {

    Board::Board() {

        std::ifstream units_file{"cities_map.txt"};
        initBoard(units_file);
    }

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

    void Board::initBoard(ifstream& units_file) {
        
            string line;
            string delimiter = " ";
            size_t pos = 0;
            string word;
            string city;

            while(getline(units_file, line)){
                int word_index = 0;
                int length = line.length();
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    word = line.substr(0, pos);
                    line.erase(0, pos + delimiter.length());
                    if(word_index == 0){
                        city = word;
                        cities[getCity(word)];
                        // Cure_discovered[getCity(word)] = false;
                        cities[getCity(word)]._disease_dice_count = 0;
                        cities[getCity(word)]._has_research_station = false;
                    }else if(word_index == 1){
                        cities[getCity(city)]._color = getColor(word); 
                    }else if(word_index > 1){
                        cities[getCity(city)]._neighbors.insert(getCity(word));
                    }
                    ++word_index;
                }
                if(length > 0){
                    cities[getCity(city)]._neighbors.insert(getCity(line));
                }
            }
    }
};

 