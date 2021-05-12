#include <iostream>
#include "Player.hpp"


namespace pandemic {

    class Dispatcher: public Player {

        private:
        public:
        
        Dispatcher(Board& b, const City& c): Player(b, c)
        {/*std::cout << "Dispatcher Created!" << std::endl;*/}

        Dispatcher& fly_direct(const City&) override;
        const std::string role() const override{return "Dispatcher";}
    };
    
};