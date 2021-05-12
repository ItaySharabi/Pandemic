#include "Player.hpp"
namespace pandemic {

    class GeneSplicer: public Player {

        private:
        public:
        
        GeneSplicer(Board& b, const City& c): Player(b, c)
        {/*std::cout << "GeneSplicer Created!" << std::endl;*/}

        GeneSplicer& discover_cure(const Color&) override;
        const std::string role() const override{return "GeneSplicer";}

    };
    
};
