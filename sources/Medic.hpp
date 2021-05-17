#include "Player.hpp"
namespace pandemic {

    class Medic: public Player {
        private:
            void auto_heal();
        public:
        
        Medic(Board& b, const City& c): Player(b, c)// Init line
        {/*std::cout << "Medic Created!" << std::endl;*/}

        Medic& drive(const City&)       override;
        Medic& treat(const City&)       override;
        Medic& fly_shuttle(const City&) override;
        Medic& fly_direct(const City&)  override;
        Medic& fly_charter(const City&) override;
        const std::string role() const  override{return "Medic";}
    };
};