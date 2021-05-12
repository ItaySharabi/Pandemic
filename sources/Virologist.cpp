#include "Virologist.hpp"


using namespace std;

namespace pandemic {

    Virologist& Virologist::treat(const City& city)  {

        if(cards[city]) {
            City temp = curr_city;
            try {
                curr_city = city;
                Player::treat(city);
                curr_city = temp;
                cards[city] = false;
            } catch(const exception& e) {
                curr_city = temp;
                throw invalid_argument(e.what());
            }
        }else if(city == curr_city) {
            try {
                Player::treat(curr_city);
            } catch (const exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else {
            throw invalid_argument("No matching card in hand!");
        }
        return *this;
    }

};