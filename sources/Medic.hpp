#include "Player.hpp"
#include <exception>
namespace pandemic {

    class Medic: public Player {

        public:
        
        Medic(Board& b, const City& c): Player(b, c)// Init line
        {/*std::cout << "Medic Created!" << std::endl;*/}

        Medic& drive(const City&) override;
        Medic& treat(const City&) override;
        Medic& fly_shuttle(const City&) override;
        Medic& fly_direct(const City&) override;
        Medic& fly_charter(const City&) override;
        const std::string role() const override{return "Medic";}
    };
};