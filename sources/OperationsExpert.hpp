#include "Player.hpp"
namespace pandemic {

    class OperationsExpert: public Player {

        private:
        public:
        
        OperationsExpert(Board& b, const City& c): Player(b, c)
        {/*std::cout << "OperationsExpert Created!" << std::endl;*/}

        OperationsExpert& build() override;
        const std::string role() const override{return "OperationsExpert";}
    };
    
};