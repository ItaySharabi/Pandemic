#include "Player.hpp"
namespace pandemic {

    class Researcher: public Player {

        private:
        public:
        
        Researcher(Board& b, const City& c):Player(b, c)
            {/*std::cout << "Researcher Created!" << std::endl;*/}


        Researcher& discover_cure(const Color&) override;
        const std::string role() const override{return "Researcher";}


    };
    
};