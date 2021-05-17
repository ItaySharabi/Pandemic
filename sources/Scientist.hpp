#include "Player.hpp"

namespace pandemic {

    class Scientist: public Player {
           
        public:
        Scientist(Board& b, const City& c):Player(b, c)
        {/*std::cout << "Scientist Created!" << std::endl;*/}

        Scientist(Board& b, const City& c, const int& min_cards_to_cure):Player(b,c)
        {num_of_cards_to_discover = min_cards_to_cure;}

        Scientist& discover_cure(const Color&) override;
        const std::string role() const         override{return "Scientist";}
    };
};