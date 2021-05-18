#include "Board.hpp"

using namespace std;

namespace pandemic {

    Board::Board() {
        std::ifstream units_file{"cities_map.txt"};
        cures[Color::Black] = false;
        cures[Color::Blue] = false;
        cures[Color::Red] = false;
        cures[Color::Yellow] = false;
        read_cities(units_file);
    }

    Board::~Board() {}
    
    /**
     * @is_clean: A city is clean iff its disease level is 0
     * This method iterates over the cities map, if all cities are clean.
    */
    bool Board::is_clean() const{
        for (const auto& pair : cities) {
            if (pair.second._disease_dice_count > 0) {
                return false;    
            }        
        }
        return true;
    }

    /**
     * @param city: A 'City' enum reference that is passed
     *              in order to set the city's disease level to some integer >= 0
    */
    int& Board::operator[] (const City& city){
        return cities[city]._disease_dice_count;
    }
    
    // Removes all cures that were found
    void Board::remove_cures() {
        for (auto& cure : cures) { cure.second = false; }
    }

    /**
     * @param os: An output stream object reference to print data into.
     * @param board: A board object to be printed.
     * 
     * Iterate over the cities (struct) of the board and print the stats:
     * 
     * 1. Disease level: If disease > 0 -> print in GREEN, else print in RED
     * 2. Cures discovered: If a cure is discovered -> print in GREEN, else print in RED.
     * 3. Research stations: If a research stations exists in city c -> print c in GREEN, else in RED.
     */
    ostream& operator<< (ostream& os, const Board& board) {
        // os << "Board: " << endl;
        // cout << "Cures Status: " << endl;
        int disease = 0;

        os << BOLDCYAN << "=========================== Game Stats ===========================" << RESET << endl;

        os << MAGENTA << "level of disease:" << RESET << endl;
        for(const auto& city: board.cities) {
            disease = city.second._disease_dice_count;
            if (disease > 0) {
                os << "\t" << RED << getCity(city.first) << ": \t\t" << disease << RESET << endl;
            } else {
                os << "\t" << GREEN << getCity(city.first) << ": \t\t" << disease << RESET << endl;
            }
        }

        os << MAGENTA << "Cures Discovered:" << RESET << endl;
        for(const auto& cure: board.cures) {
            if (board.has_cure(cure.first)) {
                os << "\t" << GREEN << getColor(cure.first) << RESET << endl;
            } else {
                os << "\t" << RED << getColor(cure.first) << RESET << endl;
            }
        }

        os << MAGENTA << "Research stations:" << RESET << endl;
        for(const auto& rs: board.cities) {
            if (board.has_research_station(rs.first)) {
                os << "\t" << GREEN << getCity(rs.first) << RESET << endl;
            } else {
                os << "\t" << RED << getCity(rs.first) << RESET << endl;
            }
        }
        os << BOLDCYAN << "==================================================================" << RESET << endl;

        /* print cities and their neighbors:*/
        // for (const auto &pair : board.cities) {
        //     os << "City: " << getCity(pair.first) << "(" << getColor(pair.second._color) << ")" << endl << "{\n";
        //     os << "\tDisease level:    " << board.cities.at(pair.first)._disease_dice_count << endl;
        //     os << "\tResearch station: " << board.cities.at(pair.first)._disease_dice_count << endl;
        //     for (const auto &neighbor : board.cities.at(pair.first)._neighbors) {
        //         os << "\tNeighbor: " << getCity(neighbor) << endl;
        //     }   
        //     os << "}\n";
        // }
        return os;
    }

    /**
     * @param units_file: A reference to an ifstream object that points to a text file, 
     *                    containing all cities, their color and neighbors.
     */
    void Board::read_cities(ifstream& units_file) {
        
            string city;
            string color;
            string neighbors;
            string neighbor;
            char c = 0;

            while(units_file.good()){
                
                units_file >> city >> color;
                cities[getCity(city)];                               // init City 'Node'
                cities[getCity(city)]._disease_dice_count = 0;       // fill in Node fields
                cities[getCity(city)]._has_research_station = false;
                cities[getCity(city)]._color = getColor(color); 

                getline(units_file, neighbors);
                istringstream iss{neighbors}; // insert neighbors string into an input stream

                while (iss >> neighbor) { // empty the stream into 'neighbor', seperated by white-spaces.
                    cities[getCity(city)]._neighbors.insert(getCity(neighbor)); // add neighbor to neighbors set.           
                }
            }
        }
};

 