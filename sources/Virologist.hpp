#include "Player.hpp"

namespace pandemic {

    class Virologist: public Player {

        private:
        public:
        Virologist(Board& b, const City& c):Player(b, c)
        {/*std::cout << "Virologist Created!" << std::endl;*/}

        Virologist& treat(const City&) override;
        const std::string role() const override{return "Virologist";}
    };
    
};