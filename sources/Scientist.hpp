#include <iostream>
#include "Player.hpp"

namespace pandemic {

    class Scientist: public Player {

        private:
            int min;
            
        public:
        Scientist(Board& b, const City& c):Player(b, c)
        {min = 4; std::cout << "Scientist Created!" << std::endl;}
        Scientist(Board& b, const City& c, const int& min_cards_to_cure):Player(b,c), min(min_cards_to_cure)
        {/*std::cout << "Scientist Created!2" << std::endl;*/}

        Scientist& discover_cure(const Color&) override;
        const std::string role() const override{return "Scientist";}

    };
    
};