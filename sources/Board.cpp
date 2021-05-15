#include <iostream>
#include "Board.hpp"


using namespace std;

namespace pandemic {

    Board::Board() {

        std::ifstream units_file{"cities_map.txt"};
        read_cities(units_file);
    }

    Board::~Board() {}
    
    /**
     * @is_clean: A city is clean if its disease level is 0
     * This method iterates over the cities map, if all cities are clean.
    */
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

    /**
     * @param city: A 'City' enum reference that is passed
     *              in order to set the city's disease level to some integer >= 0
    */
    int& Board::operator[] (const City& city){

        return cities[city]._disease_dice_count;
    }
    
    /**
     * @param os: An output stream object reference to print data into.
     * @param board: A board object to be printed.
     * 
     * Simply iterate over the board and for each city, print
     * the city name and color, and all of its neighbor cities.
     */
    ostream& operator<< (ostream& os, const Board& board) {
        os << "Board: " << endl;
        for (const auto &pair : board.cities) {
            os << "City: " << getCity(pair.first) << ", Color: " << getColor(pair.second._color) << endl << "{\n";
            for (const auto &pair2 : board.cities.at(pair.first)._neighbors) {
                os << "\tNeighbor: " << getCity(pair2) << ", " << endl;
            }   
            os << "}\n";
        }
        return os;
    }

    /**
     * @param units_file: A reference to an ifstream object that points to a text file, 
     *                    containing all cities, their color and neighbors.
     */
    // void Board::read_cities(ifstream& units_file) {
        
    //         string line;
    //         string delimiter = " ";
    //         size_t pos = 0;
    //         string word;
    //         string city;

    //         while(getline(units_file, line)){
    //             int i = 0;
    //             int length = line.length();
    //             while ((pos = line.find(delimiter)) != std::string::npos) {
    //                 word = line.substr(0, pos);
    //                 line.erase(0, pos + delimiter.length());
    //                 if(i == 0){
    //                     city = word;
    //                     cities[getCity(word)];
    //                     cities[getCity(word)]._disease_dice_count = 0;
    //                     cities[getCity(word)]._has_research_station = false;
    //                 }else if(i == 1){
    //                     cities[getCity(city)]._color = getColor(word); 
    //                 }else if(i > 1){
    //                     cities[getCity(city)]._neighbors.insert(getCity(word));
    //                 }
    //                 ++i;
    //             }
    //             if(length > 0){
    //                 cities[getCity(city)]._neighbors.insert(getCity(line));
    //             }
    //         }
    //     }

        void Board::read_cities(ifstream& units_file) {
        
            string city;
            string color;
            string neighbors;
            string neighbor;
            char c = 0;

            while(units_file.good()){
                
                units_file >> city >> color;
                cities[getCity(city)];       // init City 'Node'
                cities[getCity(city)]._disease_dice_count = 0;
                cities[getCity(city)]._has_research_station = false;
                cities[getCity(city)]._color = getColor(color); 

                getline(units_file, neighbors);
                istringstream iss{neighbors}; // insert neighbor string into an input stream

                while (iss >> neighbor) { // empty the stream into 'neighbor', seperated by white-spaces.
                    cities[getCity(city)]._neighbors.insert(getCity(neighbor)); // add neighbor to neighbors set.           
                }
            }
        }
};

 