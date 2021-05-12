#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

TEST_CASE("Initialization"){
    SUBCASE("Board"){

    /*  nothing to see here... ->  */                                                                                                                                                                            cout << "(\\__/)    \033[1;31mAchiya\033[0m\n(>'.'<)   \033[1;31mZigler's\033[0m\n(\")_(\")   \033[1;31mTest\033[0m" << endl;
        CHECK_NOTHROW(Board b;);
        Board b;
        CHECK(b.is_clean());
    }

    //  defining new board
    Board board;

    SUBCASE("Player"){
        CHECK_NOTHROW(OperationsExpert p(board,City::Algiers););
    }

    //  defining new arbitrary player
    OperationsExpert player{board,City::Algiers};

    SUBCASE("Board Setup: Existance of all citys and operator[] well defined"){
        board[City::Algiers] = 1;
        board[City::Atlanta] = 1;
        board[City::Baghdad] = 1;
        board[City::Bangkok] = 1;
        board[City::Beijing] = 1;
        board[City::Bogota] = 1;
        board[City::BuenosAires] = 1;
        board[City::Cairo] = 1;
        board[City::Chennai] = 1;
        board[City::Chicago] = 1;
        board[City::Delhi] = 1;
        board[City::Essen] = 1;
        board[City::HoChiMinhCity] = 1;
        board[City::HongKong] = 1;
        board[City::Istanbul] = 1;
        board[City::Jakarta] = 1;
        board[City::Johannesburg] = 1;
        board[City::Karachi] = 1;
        board[City::Khartoum] = 1;
        board[City::Kinshasa] = 1;
        board[City::Kolkata] = 1;
        board[City::Lagos] = 1;
        board[City::Lima] = 1;
        board[City::London] = 1;
        board[City::LosAngeles] = 1;
        board[City::Madrid] = 1;
        board[City::Manila] = 1;
        board[City::MexicoCity] = 1;
        board[City::Miami] = 1;
        board[City::Milan] = 1;
        board[City::Montreal] = 1;
        board[City::Moscow] = 1;
        board[City::Mumbai] = 1;
        board[City::NewYork] = 1;
        board[City::Osaka] = 1;
        board[City::Paris] = 1;
        board[City::Riyadh] = 1;
        board[City::SanFrancisco] = 1;
        board[City::Santiago] = 1;
        board[City::SaoPaulo] = 1;
        board[City::Seoul] = 1;
        board[City::Shanghai] = 1;
        board[City::StPetersburg] = 1;
        board[City::Sydney] = 1;
        board[City::Taipei] = 1;
        board[City::Tehran] = 1;
        board[City::Tokyo] = 1;
        board[City::Washington] = 1;

        CHECK_EQ(board[City::Algiers], 1);

        stringstream os;
        CHECK_NOTHROW(os << board;);
    }
    SUBCASE("Experties: init all roles correctly"){
        CHECK_NOTHROW(Dispatcher dispatcher(board, City::Algiers););
        CHECK_NOTHROW(FieldDoctor fieldDoctor(board, City::Algiers););
        CHECK_NOTHROW(Virologist virologist(board, City::Algiers););
        CHECK_NOTHROW(OperationsExpert operationsExpert(board, City::Algiers););
        CHECK_NOTHROW(Medic medic(board, City::Algiers););
        CHECK_NOTHROW(GeneSplicer geneSplicer(board, City::Algiers););
        CHECK_NOTHROW(Researcher researcher(board, City::Algiers););
        CHECK_NOTHROW(Scientist scientist(board, City::Algiers, 4););
    }

    //  defining all role players
    Dispatcher dispatcher(board, City::Algiers);
    FieldDoctor fieldDoctor(board, City::Algiers);
    Virologist virologist(board, City::Algiers);
    OperationsExpert operationsExpert(board, City::Algiers);
    Medic medic(board, City::StPetersburg);
    GeneSplicer geneSplicer(board, City::Algiers);
    Researcher researcher(board, City::StPetersburg);
    Scientist scientist(board, City::Algiers, 4);

    // define disease level:
    board[City::StPetersburg] = 2;
    board[City::Algiers] = 1;
    board[City::Madrid] = 1;
    board[City::Washington] = 1;
    SUBCASE("Check if role Methods implemented well"){

        // scientist takes 4 cards (Color::Black):
        scientist.take_card(City::Algiers)
                .take_card(City::Baghdad)
                .take_card(City::Cairo)
                .take_card(City::Chennai);
        CHECK_NOTHROW(operationsExpert.build()); // operationExpert builds in Algiers
        CHECK_NOTHROW(dispatcher.fly_direct(City::StPetersburg)); // dispatcher doesn't need card to fly
        CHECK_NOTHROW(scientist.discover_cure(Color::Black);); // scientist throws 4 cards
        CHECK_THROWS(researcher.discover_cure(Color::Blue);); // researcher doesn't have cards

        // researcher takes 5 cards (Color::Blue):
        researcher.take_card(City::Atlanta)
                  .take_card(City::Chicago)
                  .take_card(City::Essen)
                  .take_card(City::London)
                  .take_card(City::Madrid);
        CHECK_EQ(board[City::StPetersburg], 2);
        CHECK_NOTHROW(researcher.discover_cure(Color::Blue););// researcher can discover even though there is no station
        CHECK_NOTHROW(researcher.treat(City::StPetersburg);); 
        CHECK_EQ(board[City::StPetersburg], 0);

        // define disease level:
        board[City::StPetersburg] = 2;

        CHECK_EQ(board[City::StPetersburg], 2);
        CHECK_NOTHROW(medic.treat(City::StPetersburg);); // medic treats completly
        CHECK_EQ(board[City::StPetersburg], 0);

        // virologist takes the Washington card
        virologist.take_card(City::Washington);
        CHECK_EQ(board[City::Washington], 1);
        CHECK_NOTHROW(virologist.treat(City::Washington)); // virologist can treat from distance
        CHECK_EQ(board[City::Washington], 0);

        // geneSplicer takes 5 cards different colors:
        geneSplicer.take_card(City::Milan) // Color::Blue
                   .take_card(City::Bangkok) // Color::Red
                   .take_card(City::Beijing) // Color::Red
                   .take_card(City::Bogota) // Color::Yellow
                   .take_card(City::Delhi); // Color::Black
        CHECK_NOTHROW(geneSplicer.discover_cure(Color::Black);); // geneSplicer can cure with different color cards

        CHECK_EQ(board[City::Madrid], 1);
        CHECK_NOTHROW(fieldDoctor.treat(City::Madrid);); // fieldDoctor can treat neighbor city disease
        CHECK_EQ(board[City::Madrid], 0);
    
    }

}
TEST_CASE("Basic player functionality"){
    Board board;
    CHECK(board.is_clean()); // new board
    OperationsExpert player{board, City::Algiers};


    // player takes 5 cards (Color::Black):
    player.take_card(City::Algiers)
        .take_card(City::Baghdad)
        .take_card(City::Cairo)
        .take_card(City::Chennai)
        .take_card(City::Delhi);


    SUBCASE("Moving by rules"){

        // drive
        CHECK_NOTHROW(player.drive(City::Madrid);); // player drive to neighbor city
        CHECK_THROWS(player.drive(City::Lima);); // player can't move to distanced city
        CHECK_NOTHROW(player.drive(City::Algiers).drive(City::Madrid);); // player drive to neighbor city and back

        // fly_direct
        CHECK_THROWS(player.fly_direct(City::Lima);); // player doesn't hold that card
        CHECK_NOTHROW(player.fly_direct(City::Cairo);); // player holds that card
        CHECK_NOTHROW(player.fly_direct(City::Chennai).fly_direct(City::Delhi)); // player fly_direct twice
        CHECK_THROWS(player.fly_direct(City::Algiers).fly_direct(City::Delhi)); // player doesn't hold that 2nd card
        CHECK_THROWS(player.fly_direct(City::Baghdad).fly_direct(City::Baghdad)); // player doesn't hold that 2nd card

        // player takes 5 cards (Color::Black):
        player.take_card(City::Algiers)
            .take_card(City::Baghdad)
            .take_card(City::Cairo)
            .take_card(City::Chennai)
            .take_card(City::Delhi);

        // player fly back to Algiers:
        player.fly_direct(City::Algiers);

        // fly_charter
        CHECK_THROWS(player.fly_charter(City::Lima);); // player doesn't hold his place card
        CHECK_THROWS(player.fly_charter(City::Baghdad);); // player doesn't hold his place card
        CHECK_THROWS(player.fly_charter(City::Algiers);); // player doesn't hold his place card

        player.drive(City::Cairo); // player drive to neighbor city

        CHECK_NOTHROW(player.fly_charter(City::Algiers);); // player throws his place card

        player.take_card(City::Algiers)
              .take_card(City::Cairo); // player takes those cards back
        
        CHECK_THROWS(player.fly_charter(City::Algiers).fly_charter(City::Cairo)); // order is wrong here

        player.take_card(City::Algiers); // player takes back this card

        CHECK_NOTHROW(player.fly_charter(City::Cairo).fly_charter(City::Algiers)); // fly_charter and back

        // fly_shuttle
        CHECK_THROWS(player.fly_shuttle(City::Delhi);); // no station in this city
        player.take_card(City::Algiers); // player takes back this card
        player.build(); // throws Algiers card
        player.fly_direct(City::Delhi)
              .take_card(City::Delhi)
              .build(); // player builds in 2 citys (Algiers, Delhi)
        player.take_card(City::Algiers) // player takes back this card
              .take_card(City::Delhi); // player takes back this card
        
        CHECK_NOTHROW(player.fly_shuttle(City::Algiers);); // player fly_shuttle to Algiers
        player.take_card(City::Algiers); // player takes back this card
        CHECK_NOTHROW(player.fly_shuttle(City::Delhi).fly_shuttle(City::Algiers);); // player fly_shuttle to Delhi and back
    }

    SUBCASE("discover, treat, build functionality"){
        board[City::Algiers] = 5;
        board[City::Paris] = 3;
        board[City::Cairo] = 2;

        Dispatcher d{board, City::Algiers};
        // player takes 6 cards (Color::Black):
        d.take_card(City::Algiers)
            .take_card(City::Baghdad)
            .take_card(City::Cairo)
            .take_card(City::Chennai)
            .take_card(City::Delhi)
            .take_card(City::Istanbul);

        CHECK_THROWS(d.discover_cure(Color::Black);); // there is no station in Algiers yet
        CHECK_NOTHROW(d.build();); // builds station in Algiers, throw Algiers card

        CHECK_EQ(board[City::Algiers], 5);
        CHECK_NOTHROW(d.discover_cure(Color::Black);); // player throws 5 Color::Black cards
        CHECK_NOTHROW(d.treat(City::Algiers);); // remove all disease level 5 to 0
        CHECK_EQ(board[City::Algiers], 0);

        CHECK_EQ(board[City::Cairo], 2);
        CHECK_NOTHROW(d.drive(City::Cairo).treat(City::Cairo)); // moving to neighbor city and treating only once!
        CHECK_THROWS(d.treat(City::Cairo);); // see reason next line
        CHECK_EQ(board[City::Cairo], 0); // cure to Color::Black disease has been found earlier so a single treat removes the disease!
        CHECK_THROWS(d.treat(City::Cairo);); // can't treat a healthy city

        CHECK_EQ(board[City::Paris], 3);
        CHECK_NOTHROW(d.drive(City::Algiers).drive(City::Paris).treat(City::Paris);); // navigating to paris through Algiers and treating
        CHECK_EQ(board[City::Paris], 2);
    }

    SUBCASE("OperationExpert Functionality"){
        OperationsExpert oe{board, City::Milan};
        CHECK_NOTHROW(oe.build();); // can build without throwing card.
    }
    SUBCASE("Dispatcher Functionality"){
        Dispatcher d{board, City::Essen};
        CHECK_THROWS(d.fly_direct(City::Madrid);); // no station in Essen yet
        d.take_card(City::Essen).build();
        CHECK_NOTHROW(d.fly_direct(City::Madrid););

    }
    SUBCASE("Scientist Functionality"){
        board[City::Manila] = 3;
        Scientist s{board, City::Manila, 2};
        s.take_card(City::HongKong).take_card(City::Jakarta); // takes 2 Color::Red cards

        CHECK_THROWS(s.discover_cure(Color::Red);); // no station yet
        s.take_card(City::Manila).build(); // builds station in Manila
        CHECK_NOTHROW(s.discover_cure(Color::Red);); // can discover with 2 cards
        CHECK_EQ(board[City::Manila], 3);
        s.treat(City::Manila);
        CHECK_EQ(board[City::Manila], 0);
    }
    SUBCASE("Researcher Functionality"){
        Researcher r{board, City::Moscow};

        // researcher takes 6 cards (Color::Black):
        r.take_card(City::Algiers)
            .take_card(City::Baghdad)
            .take_card(City::Cairo)
            .take_card(City::Chennai)
            .take_card(City::Delhi)
            .take_card(City::Istanbul);
        CHECK_NOTHROW(r.discover_cure(Color::Black);); // can discover without station

    }
    SUBCASE("Medic Functionality"){
        board.remove_cures(); // resets cures found
        board[City::Lima] = 2; // Color::Yellow
        board[City::Lagos] = 2; // Color::Yellow
        board[City::Santiago] = 2; // Color::Yellow
        board[City::Riyadh] = 8; // Color::Black

        Medic m{board, City::Lima};
        // medic takes 6 Color::Yellow cards
        m.take_card(City::Lima)
         .take_card(City::Lagos)
         .take_card(City::Santiago)
         .take_card(City::SaoPaulo)
         .take_card(City::Kinshasa)
         .take_card(City::Khartoum);
        m.build(); // throws Lima card
        CHECK_EQ(board[City::Lima], 2);
        m.treat(City::Lima);
        CHECK_EQ(board[City::Lima], 0); // medic treats well!
        m.discover_cure(Color::Yellow); // throws 5 Color::Yellow cards
        CHECK_EQ(board[City::Santiago], 2); 
        m.drive(City::Santiago);
        CHECK_EQ(board[City::Santiago], 0); // no need to treat, Color::Yellow cure found!

        m.take_card(City::Lagos); // takes Lagos card again
        CHECK_EQ(board[City::Lagos], 2); 
        m.fly_direct(City::Lagos);
        CHECK_EQ(board[City::Lagos], 0); // no need to treat, Color::Yellow cure found!

        m.take_card(City::Riyadh).fly_direct(City::Riyadh);
        CHECK_EQ(board[City::Riyadh], 8); // no Color::Black cure found...
        board[City::Riyadh] = 0;

    }
    SUBCASE("Virologist Functionality"){
        board[City::Beijing] = 1;
        board[City::NewYork] = 1;
        Virologist v{board, City::NewYork};
        CHECK_EQ(board[City::NewYork], 1);
        CHECK_NOTHROW(v.treat(City::NewYork);); // regular treat
        CHECK_EQ(board[City::NewYork], 0);
        CHECK_THROWS(v.treat(City::Beijing);); // not holding Beijing card yet
        v.take_card(City::Beijing);
        CHECK_EQ(board[City::Beijing], 1);
        CHECK_NOTHROW(v.treat(City::Beijing);); // virologist can treat from distance
        CHECK_EQ(board[City::Beijing], 0);

    }
    SUBCASE("GeneSplicer Functionality"){
        GeneSplicer g{board, City::Kolkata};
        // genesplicer takes mixed 6 cards
        g.take_card(City::Paris)
         .take_card(City::Kolkata)
         .take_card(City::Taipei)
         .take_card(City::Tokyo)
         .take_card(City::Tehran)
         .take_card(City::Jakarta);
        g.build(); // throws 1 card, builds station in Kolkata!
        CHECK_NOTHROW(g.discover_cure(Color::Yellow);); // can discover cure with 5 mixed coloColor::Red cards
        CHECK_THROWS(g.discover_cure(Color::Black);); // already threw her cards...
    }
    SUBCASE("FieldDoctor Functionality"){
        board[City::Paris] = 1;
        board[City::Milan] = 1;
        board[City::Algiers] = 1;
        board[City::Istanbul] = 1;
        FieldDoctor f{board, City::Paris};
        CHECK_NOTHROW(f.treat(City::Paris);); // simple treat
        CHECK_NOTHROW(f.treat(City::Milan);); // neighbor treat
        CHECK_NOTHROW(f.treat(City::Algiers);); // neighbor treat
        CHECK_THROWS(f.treat(City::Istanbul);); // not neighbors
        CHECK_NOTHROW(f.drive(City::Algiers).treat(City::Istanbul);); // neighbor treat
        CHECK_EQ(board[City::Paris] + board[City::Milan] + board[City::Algiers] + board[City::Istanbul], 0); // all disease treated
    }
}

TEST_CASE("Game Simulation"){
    Board board;

    //  defining all role players
    Dispatcher dispatcher(board, City::Washington); // Color::Blue
    FieldDoctor fieldDoctor(board, City::HoChiMinhCity); // Color::Red
    Virologist virologist(board, City::Montreal); // Color::Blue
    OperationsExpert operationsExpert(board, City::Santiago); // Color::Yellow
    Medic medic(board, City::StPetersburg); // Color::Blue
    GeneSplicer geneSplicer(board, City::Algiers); // Color::Black
    Researcher researcher(board, City::StPetersburg); // Color::Blue
    Scientist scientist(board, City::Jakarta, 4); // Color::Red

    // defining disease levels:
    board[City::Algiers] = 1; // Color::Black
    board[City::Atlanta] = 1; // Color::Blue
    board[City::Baghdad] = 2; // Color::Black
    board[City::Bangkok] = 2; // Color::Red
    board[City::Beijing] = 2; // Color::Red
    board[City::Bogota] = 2; // Color::Yellow
    board[City::BuenosAires] = 2; // Color::Yellow

    // Game Starts
    // each turn each player takes 3 cards and has 4 actions to do

    // "turn 1 : Dispatcher's turn"
        // location: Washington
        CHECK_EQ(board[City::Algiers], 1);
        CHECK_NOTHROW(
            dispatcher.take_card(City::Algiers) // Color::Black
                    .take_card(City::Atlanta) // Color::Blue
                    .take_card(City::Jakarta) // Color::Black
                    .fly_direct(City::Algiers) // throws 1 card
                    .treat(City::Algiers);
        );

        CHECK_EQ(board[City::Algiers], 0);
        CHECK_THROWS(dispatcher.treat(City::Algiers);); // no disease in Algiers

        CHECK_NOTHROW(
            dispatcher.drive(City::Istanbul)
                      .drive(City::Baghdad);
        );
    
    // "turn 2 : FieldDoctor's turn"
        // location: HoChiMinhCity
        CHECK_NOTHROW(fieldDoctor.take_card(City::Bangkok)
                                 .take_card(City::Beijing)
                                 .take_card(City::Bogota)
                                 .treat(City::Bangkok)
                                 .treat(City::Bangkok)
                                 .fly_direct(City::Beijing) // throws 1 card
                                 .treat(City::Beijing);
        );
        CHECK_EQ(board[City::Bangkok], 0);
        CHECK_EQ(board[City::Beijing], 1);
    
    //"turn 3 : Virologist's turn"
        // location: Montreal
        CHECK_NOTHROW(virologist.take_card(City::BuenosAires)
                                 .take_card(City::Cairo)
                                 .take_card(City::Chennai)
                                 .treat(City::BuenosAires) // throws 1 card
                                 .drive(City::Chicago)
                                 .drive(City::Atlanta)
                                 .treat(City::Atlanta); // throws 1 card
        );
        CHECK_EQ(board[City::BuenosAires], 1);
        CHECK_EQ(board[City::Atlanta], 0);
    
    //"turn 4 : OperationsExpert's turn"
        // location: Santiago
        CHECK_NOTHROW(operationsExpert.take_card(City::Chicago)
                                 .take_card(City::Delhi)
                                 .take_card(City::Essen)
                                 .drive(City::Lima)
                                 .drive(City::Bogota)
                                 .build(); // not throwing any card, station in Bogota!
                 operationsExpert.treat(City::Bogota); // throws 1 card
        );
        CHECK_EQ(board[City::Bogota], 1);
    
    //"turn 5 : Medic's turn"
        // location: StPetersburg
        CHECK_NOTHROW(medic.take_card(City::Baghdad)
                                 .take_card(City::HongKong)
                                 .take_card(City::Istanbul)
                                 .drive(City::Istanbul)
                                 .drive(City::Baghdad)
                                 .treat(City::Baghdad)
                                 .build(); // throws 1 card, station in Bagdhad!
        );
        CHECK_EQ(board[City::Baghdad], 0);

    //"turn 6 : GeneSplicer's turn"
        // location: Algiers
        CHECK_NOTHROW(geneSplicer.take_card(City::HoChiMinhCity)
                                 .take_card(City::Johannesburg)
                                 .take_card(City::Karachi)
                                 .fly_direct(City::HoChiMinhCity) // throws 1 card
                                 .drive(City::HongKong)
                                 .drive(City::Shanghai)
                                 .drive(City::Beijing);
        );

    //"turn 7 : Researcher's turn"
        // location: StPetersburg
        CHECK_NOTHROW(researcher.take_card(City::Khartoum)
                                 .take_card(City::Kinshasa)
                                 .take_card(City::Kolkata)
                                 .fly_direct(City::Kinshasa) // throws 1 card
                                 .drive(City::Lagos)
        );
        CHECK_THROWS(researcher.discover_cure(Color::Yellow);); // doesn't hold 5 Color::Yellow cards
                                 
        CHECK_NOTHROW(researcher.drive(City::SaoPaulo)
                                .drive(City::BuenosAires);
        );
    
    //"turn 8 : Scientist's turn"
        // location: Jakarata
        CHECK_NOTHROW(scientist.take_card(City::Lagos)
                                 .take_card(City::Lima)
                                 .take_card(City::London)
                                 .fly_direct(City::Lima) // throws 1 card
                                 .drive(City::Bogota)
                                 .treat(City::Bogota)
                                 .drive(City::BuenosAires)
        );
        CHECK_EQ(board[City::Bogota], 0);

    // "turn 9 : Dispatcher's turn"
        // location: Baghdad
        // holds: Atlanta, Jakarta
        CHECK_NOTHROW(
            dispatcher.take_card(City::LosAngeles) 
                    .take_card(City::Madrid) 
                    .take_card(City::Manila) 
                    .fly_direct(City::Madrid) // doesn't throw card! station in Baghdad!
                    .build(); // throws 1 card, station in Madrid!
            dispatcher.drive(City::NewYork)
                    .drive(City::Washington);
        );

    // "turn 10 : FieldDoctor's turn"
        // location: Beijing
        // holds: Bangkok, Bogota
        CHECK_NOTHROW(fieldDoctor.take_card(City::MexicoCity)
                                 .take_card(City::Miami)
                                 .take_card(City::Milan)
                                 .treat(City::Beijing)
                                 .drive(City::Seoul)
                                 .drive(City::Tokyo)
                                 .drive(City::SanFrancisco);
        );
        CHECK_EQ(board[City::Beijing], 0);
    //"turn 11 : Virologist's turn"
        // location: Atlanta
        // holds: Cairo, Chennai
        CHECK_NOTHROW(virologist.take_card(City::Montreal)
                                .take_card(City::Moscow)
                                .take_card(City::Mumbai)
                                .drive(City::Chicago)
                                .drive(City::Montreal)
                                .build(); // throws 1 card, station in Montreal!
                                 //skiping 1 action turn
        );
    //"turn 12 : OperationsExpert's turn"
        // location: Bogota
        //holds: Chicago, Delhi, Essen
        CHECK_NOTHROW(operationsExpert.take_card(City::NewYork)
                                      .take_card(City::Osaka)
                                      .take_card(City::Paris)
                                      .drive(City::SaoPaulo)
                                      .drive(City::BuenosAires)
                                      .treat(City::BuenosAires);
        );
        CHECK_EQ(board[City::BuenosAires], 0);
    
    // all diseases have been cured!
    CHECK(board.is_clean());
}