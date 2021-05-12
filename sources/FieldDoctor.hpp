#include "Player.hpp"
namespace pandemic {

    class FieldDoctor: public Player {

        private:
        public:
        
        FieldDoctor(Board& b, const City& city): Player(b, city)
         {/*  std::cout << "FieldDoctor Created!" << std::endl;*/};


        FieldDoctor& treat(const City&) override;
        const std::string role() const override{return "FieldDoctor";}
    };
    
};