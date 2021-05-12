/************************************************************************************
 * C++ course, Ariel university.
 * Assignment number 4.
 *
 * AUTHORS: Eyal Levi
 * https://github.com/LeviEyal
 * Date: 2021-04
 ***********************************************************************************/

#include "doctest.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <ctime>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;
using namespace std;

const int NUMBER_OF_TESTS = 10;

const vector<City> all_cities {
    City::Algiers,City::Atlanta,City::Baghdad,City::Bangkok,City::Beijing,City::Bogota,City::BuenosAires,City::Cairo,City::Chennai,
    City::Chicago,City::Delhi,City::Essen,City::HoChiMinhCity,City::HongKong,City::Istanbul,City::Jakarta,City::Johannesburg,
    City::Karachi,City::Khartoum,City::Kinshasa,City::Kolkata,City::Lagos,City::Lima,City::London,City::LosAngeles,
    City::Madrid,City::Manila,City::MexicoCity,City::Miami,City::Milan,City::Montreal,City::Moscow,City::Mumbai,City::NewYork,
    City::Osaka,City::Paris,City::Riyadh,City::SanFrancisco,City::Santiago,City::SaoPaulo,City::Seoul,City::Shanghai,City::StPetersburg,
    City::Sydney,City::Taipei,City::Tehran,City::Tokyo,City::Washington
};

/* פונקציית עזר שבודקת אם שתי ערים מחוברות ביניהן */
bool is_connected(City c1, City c2);
/* פונקציית עזר שמגרילה עיר שמחוברת לעיר נתונה כלשהי */
City random_connected_city(City c);
/* פונקציית עזר שמגרילה עיר כלשהי */
City random_city();
City random_city_different_than(City c);
/* פונקציית עזר שמגרילה עיר  */
City random_city_colored(Color c);
/* פונקציית עזר המגרילה מספר מסוים של ערים בצבע נתון  */
set<City> pick_N_cities_colored(int N, Color c);
/* פונקציית עזר המגרילה 5 ערים שונות  */
set<City> pick_5_different_cities();
Color get_color(City c);

/*************************************************************************
 *  אופרטור סוגריים מרובעים
 */
TEST_CASE("Test the operator Board[]"){
    srand(time(0));
    Board board;

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        City city = random_city();
        CHECK_NOTHROW(board[city] = 10);
        CHECK(board[city] == 10);

        CHECK_NOTHROW(board[city]--);
        CHECK(board[city] == 9);

        CHECK_NOTHROW(board[city]++);
        CHECK(board[city] == 10);
        
        CHECK_NOTHROW(board[city] += 10);
        CHECK(board[city] == 20);
    }
}

/*************************************************************************
 *  בדיקת המתודה אם הלוח נקי
 */
TEST_CASE("Test the method Board::is_clean() "){
    Board board;

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        City city = random_city();
        CHECK_NOTHROW(board[city] = rand()%10 + 1);
        CHECK(board.is_clean() == false);
    }

    /* מחיקת כל קוביות המחלה */
    for(const auto& c: all_cities) {
        board[c] = 0;
    }

    /* וידוא שהלוח אכן נקי */
    CHECK(board.is_clean() == true);
}

/*************************************************************************
 *  drive() נסיעה רגילה
 */
TEST_CASE("Test the method Player::drive() "){
    Board board;
    City city = random_city();
    OperationsExpert operationsExpert{board, city};
    Dispatcher dispatcher{board, city};
    Scientist scientist{board, city, 4};
    Researcher researcher{board, city};
    Medic medic{board, city};
    Virologist virologist{board, city};
    GeneSplicer geneSplicer{board, city};
    FieldDoctor fieldDoctor{board, city};
    Player *players[] = {&operationsExpert,
                         &dispatcher,
                         &scientist,
                         &researcher,
                         &medic,
                         &virologist,
                         &geneSplicer,
                         &fieldDoctor};
    
    /* מעבר אקראי בין ערים מחוברות ע"י נסיעה רגילה */
    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        City c = random_city();
        /* אם העיר הבאה מחוברת לעיר הנוכחית - ניתן לבצע נסיעה רגילה */
        if(is_connected(city, c)) {
            for(auto& p: players) {
                CHECK_NOTHROW((*p).drive(c));
            }
            city = c;
        }
        /* אם העיר הבאה לא מחוברת לעיר הנוכחית - לא ניתן לבצע נסיעה רגילה */
        else {
            for(auto& p: players) {
                CHECK_THROWS((*p).drive(c));
            }
        }
    }
}

/*************************************************************************
 * קצין מבצעים - OperationsExpert
 *                      ,יכול לבצע פעולת "בנייה" בכל עיר שהוא נמצא בה
 *                                            בלי להשליך קלף-עיר מתאים
 */
TEST_CASE("Test OperationsExpert"){
    Board board;

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        City r = random_city();
        OperationsExpert player{board, r};
        CHECK(player.role() == "OperationsExpert");

        /* מעבר בין 20 ערים אקראיות */
        for(int j = 0; j < 20; j++) {
            r = random_connected_city(r);
            CHECK_NOTHROW(player.drive(r));

            /* פעולה אפשרית - קצין מבצעים יכול לבנות גם ללא קלף */
            CHECK_NOTHROW(player.build());
        }
    }
}

/************************************************************************
 * קצין תעבורה - Dispatcher:
 *                                             ,כשהוא נמצא בתחנת-מחקר
 *              ,הוא יכול לבצע פעולת "טיסה ישירה" לכל עיר שהוא רוצה
 *                                                 .ללא השלכת קלף-עיר
 * 
 */
TEST_CASE("Test Dispatcher"){

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        Board b;
        City dest = random_city();
        Dispatcher player{b, dest};
        CHECK(player.role() == "Dispatcher");
        CHECK_NOTHROW(player.take_card(dest));
        CHECK_NOTHROW(player.build());

        /* מעבר בין עשרים ערים אקראיות ע"י טיסה ישירה */
        for(int j = 0; j < 20; j++) {
            dest = random_city_different_than(dest);
            /* הקצין תעבורה יכול לטוס ישירות ללא קלף*/
            CHECK_NOTHROW(player.fly_direct(dest));
            CHECK_NOTHROW(player.take_card(dest));
            CHECK_NOTHROW(player.build());
        }
    }
}

/************************************************************************
 * מדענית - Scientist:
 *                                     "יכולה לבצע פעולת "גילוי תרופה
 *                                                 ,קלפים בלבד n בעזרת
 *                     (במשחק המקורי n=4) .מועבר בבנאי n כאשר הפרמטר
 */
TEST_CASE("Test Scientist"){

    for(int i = 0; i < 5; i++) {
        Board b;
        City dest = random_city();
        Scientist player{b, dest, i};
        CHECK(player.role() == "Scientist");

        /* פעולה לא אפשרית - למדענית אין 2 קלפים מאותו צבע של העיר הנוכחית */
        for(Color color: {Color::Black, Color::Blue, Color::Red, Color::Yellow}) {
            CHECK_THROWS(player.discover_cure(color));
        }

        /* מעבר בין עשרים ערים אקראיות ע"י טיסה ישירה */
        for(int j = 0; j < 20; j++) {

            /* מעבר לעיר רנדומלית אחרת ובנייה של תחנת-מחקר בה */
            dest = random_city_different_than(dest);
            CHECK_NOTHROW(player.take_card(dest).fly_direct(dest));
            CHECK_NOTHROW(player.take_card(dest).build());

            Color color = get_color(dest);

            /* לקיחה של פחות מ5 קלפים באותו הצבע */
            for(City city: pick_N_cities_colored(i, color)) {
                CHECK_NOTHROW(player.take_card(city));
            }

            /* אמור לעבוד למרות שיש למדענית פחות מ-5 קלפים באותו צבע */
            CHECK_NOTHROW(player.discover_cure(color));
        }
    }
}

/************************************************************************
 * חוקרת - Researcher:
 *                           ,יכולה לבצע פעולת "גילוי תרופה" בכל עיר 
 *                                         .לא חייבת להיות בתחנת מחקר
 */
TEST_CASE("Test Researcher"){

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        Board b;
        City r = random_city();
        Researcher player{b, r};
        CHECK(player.role() == "Researcher");

        /* פעולה לא אפשרית - לחוקרת אין 5 קלפים מאותו צבע של העיר הנוכחית */
        for(Color color: {Color::Black, Color::Blue, Color::Red, Color::Yellow}) {
            CHECK_THROWS(player.discover_cure(color));
        }
        
        /* מעבר בין עשרים ערים אקראיות ע"י טיסה ישירה */
        for(int j = 0; j < 20; j++) {
            /* מעבר לעיר רנדומלית אחרת ובנייה של תחנת-מחקר בה */
            r = random_city_different_than(r);
            CHECK_NOTHROW(player.take_card(r).fly_direct(r));

            Color color = get_color(r);

            /* לקיחה של 5 קלפים באותו הצבע */
            for(City city: pick_N_cities_colored(5, color)) {
                // cout << cities_colors.at(city) << endl;
                CHECK_NOTHROW(player.take_card(city));
            }

            CHECK_NOTHROW(player.discover_cure(color));
        }
    }
}

/************************************************************************
 * פראמדיק - Medic:
 *                                    ,"כשהוא מבצע פעולת "טיפול במחלה
 *      .הוא מוריד את כל קוביות-המחלה מהעיר שהוא נמצא בה ולא רק אחת
 *                                    
 *                                         ,אם כבר התגלתה תרופה למחלה
 *      ,הוא אוטומטית מוריד את כל קוביות-המחלה מכל עיר שהוא נמצא בה
 *                                   ."גם בלי לבצע פעולת "טיפול במחלה
 */
TEST_CASE("Test Medic"){
    Board b;

    SUBCASE("Test treat()") {
        City r = random_city();
        Medic player{b, r};
        CHECK(player.role() == "Medic");

        /* פעולה לא אפשרית - אין מחלות בשום מקום */
        for(City city: all_cities) {
            CHECK_THROWS(player.treat(city));
        }

        for(int i = 0; i < NUMBER_OF_TESTS; i++) {

            /* מעבר רנדומלי בין הערים השונות */
            for(int j = 0; j < 20; j++) {
                r = random_city_different_than(r);
                CHECK_NOTHROW(player.take_card(r).fly_direct(r));

                b[r] = 10;
                CHECK(b[r] == 10);
                CHECK_NOTHROW(player.treat(r));
                CHECK(b[r] == 0);
            }
        }
    }
    SUBCASE("Cure is already discoverd") {
            City city = random_city();
            Color color = get_color(city);
            Medic player{b, city};
            CHECK_NOTHROW(player.take_card(city).build());
            /* לקיחה של 5 קלפים באותו הצבע */
            for(City c: pick_N_cities_colored(5, color)) {
                CHECK_NOTHROW(player.take_card(c));
            }
            CHECK_NOTHROW(player.discover_cure(color));

            /* השמת 10 קוביות מחלה בכל עיר */
            for(City c: all_cities) {
                CHECK_NOTHROW(b[c] = 10);
            }

            /* מעבר רנדומלי בין הערים השונות בעזרת טיסה ישירה */
            for(int j = 0; j < 20; j++) {
                city = random_city_different_than(city);
                player.take_card(city).fly_direct(city);

                if(get_color(city) == color) {
                    CHECK(b[city] == 0);
                }
                else {
                    CHECK(b[city] == 10);
                }
            }     

            /* השמת 10 קוביות מחלה בכל עיר */
            for(City c: all_cities) {
                CHECK_NOTHROW(b[c] = 10);
            }

            /* מעבר רנדומלי בין הערים השונות בעזרת טיסת זיכיון */
            for(int j = 0; j < 20; j++) {
                player.take_card(city);
                city = random_city_different_than(city);
                player.fly_charter(city);

                if(get_color(city) == color) {
                    CHECK(b[city] == 0);
                }
                else {
                    CHECK(b[city] == 10);
                }
            }        

            /* השמת 10 קוביות מחלה בכל עיר */
            for(City c: all_cities) {
                CHECK_NOTHROW(b[c] = 10);
            }
            
            /* מעבר רנדומלי בין הערים השונות בעזרת נסיעה רגילה */
            for(int j = 0; j < 20; j++) {
                city = random_connected_city(city);
                player.drive(city);

                if(get_color(city) == color) {
                    CHECK(b[city] == 0);
                }
                else {
                    CHECK(b[city] == 10);
                }
            }            
    }
}

/************************************************************************
 * וירולוגית - Virologist:
 *                                    ,"יכולה לבצע פעולת "טיפול במחלה
 *                       לא רק בעיר שהיא נמצאת בה, אלא בכל עיר בעולם
 *                                        .ע"י השלכת קלף של אותה העיר
 */
TEST_CASE("Test Virologist"){
    Board b;

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        City start_city = random_city();
        Virologist player{b, start_city};
        CHECK(player.role() == "Virologist");

        for(City city: all_cities) {
            if(city != start_city) {
                /* פעולה לא אפשרית - לוירולוגית אין אף קלף */
                CHECK_THROWS(player.treat(city));
            }

            CHECK_NOTHROW(b[city] = 10);
            CHECK(b[city] == 10);
            /* פעולה אפשרית - לוירולוגית יש את הקלף הדרוש */
            CHECK_NOTHROW(player.take_card(city).treat(city));
            CHECK(b[city] == 9);
        }
    }
}

/************************************************************************
 * פורסת גנים - GeneSplicer:
 *               יכולה לבצע פעולת "גילוי תרופה" בעזרת 5 קלפים כלשהם
 *                                           .לא דווקא מהצבע של המחלה
 */
TEST_CASE("Test GeneSplicer"){

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        Board b;
        City city = random_city();
        GeneSplicer player{b, city};
        CHECK(player.role() == "GeneSplicer");
        CHECK_NOTHROW(player.take_card(city).build());

        /* פעולה לא אפשרית - לפורסת גנים אין 5 קלפים כלשהם */
        for(Color color: {Color::Black, Color::Blue, Color::Red, Color::Yellow}) {
            CHECK_THROWS(player.discover_cure(color));
        }

        Color color = get_color(city);

        /* בחירה של 5 ערים כלשהן בכל צבע אפשרי */
        for(City c: pick_5_different_cities()) {
            CHECK_THROWS(player.discover_cure(color));
            CHECK_NOTHROW(player.take_card(c));
        }

        CHECK_NOTHROW(player.discover_cure(color));
    }
}

/************************************************************************
 * רופא שטח - FieldDoctor:
 *           ,יכול לבצע פעולת "טיפול במחלה" לא רק בעיר שהוא נמצא בה 
 *            ,אלא בכל עיר סמוכה לעיר שהוא נמצא בה (ע"פ מפת הקשרים)
 *                                                .בלי להשליך קלף עיר
 */
TEST_CASE("Test FieldDoctor"){

    for(int i = 0; i < NUMBER_OF_TESTS; i++) {
        Board b;
        City city = random_city();
        FieldDoctor player{b, city};
        CHECK(player.role() == "FieldDoctor");
        CHECK_THROWS(player.treat(city)); //no disease cubes

        /* מעבר רנדומלי בין הערים השונות בעזרת נסיעה רגילה */
        for(int j = 0; j < 20; j++) {
            city = random_connected_city(city);

            CHECK_NOTHROW(b[city] = 10);
            CHECK(b[city] == 10);
            CHECK_NOTHROW(player.treat(city));
            CHECK(b[city] == 9);
            CHECK_NOTHROW(player.drive(city));
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------

const map<City, Color> city_color {
    { City::Algiers, Color::Black },{ City::Atlanta, Color::Blue },{ City::Baghdad, Color::Black },{ City::Bangkok, Color::Red },
    { City::Beijing, Color::Red },{ City::Bogota, Color::Yellow },{ City::BuenosAires, Color::Yellow },{ City::Cairo, Color::Black },
    { City::Chennai, Color::Black },{ City::Chicago, Color::Blue },{ City::Delhi, Color::Black },{ City::Essen, Color::Blue },
    { City::HoChiMinhCity, Color::Red },{ City::HongKong, Color::Red },{ City::Istanbul, Color::Black },{ City::Jakarta, Color::Red },
    { City::Johannesburg, Color::Yellow },{ City::Karachi, Color::Black },{ City::Khartoum, Color::Yellow },{ City::Kinshasa, Color::Yellow },
    { City::Kolkata, Color::Black },{ City::Lagos, Color::Yellow },{ City::Lima, Color::Yellow },{ City::London, Color::Blue },
    { City::LosAngeles, Color::Yellow },{ City::Madrid, Color::Blue },{ City::Manila, Color::Red },{ City::MexicoCity, Color::Yellow },
    { City::Miami, Color::Yellow },{ City::Milan, Color::Blue },{ City::Montreal, Color::Blue },{ City::Moscow, Color::Black },
    { City::Mumbai, Color::Black },{ City::NewYork, Color::Blue },{ City::Osaka, Color::Red },{ City::Paris, Color::Blue },
    { City::Riyadh, Color::Black },{ City::SanFrancisco, Color::Blue },{ City::Santiago, Color::Yellow },{ City::SaoPaulo, Color::Yellow },
    { City::Seoul, Color::Red },{ City::Shanghai, Color::Red },{ City::StPetersburg, Color::Blue },{ City::Sydney, Color::Red },
    { City::Taipei, Color::Red },{ City::Tehran, Color::Black },{ City::Tokyo, Color::Red },{ City::Washington, Color::Blue }
};
const map<City, vector<City>> cities {
    { City::Algiers, {City::Madrid, City::Paris, City::Istanbul, City::Cairo } },
    { City::Atlanta, {City::Chicago, City::Miami, City::Washington } },
    { City::Baghdad, {City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi } },
    { City::Bangkok, {City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong } },
    { City::Beijing, {City::Shanghai, City::Seoul } },
    { City::Bogota, {City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires } },
    { City::BuenosAires, {City::Bogota, City::SaoPaulo } },
    { City::Cairo, {City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh } },
    { City::Chennai, {City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta } },
    { City::Chicago, {City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal } },
    { City::Delhi, {City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata } },
    { City::Essen, {City::London, City::Paris, City::Milan, City::StPetersburg } },
    { City::HoChiMinhCity, {City::Jakarta, City::Bangkok, City::HongKong, City::Manila } },
    { City::HongKong, {City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei } },
    { City::Istanbul, {City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow } },
    { City::Jakarta, {City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney } },
    { City::Johannesburg, {City::Kinshasa, City::Khartoum } },
    { City::Karachi, {City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi } },
    { City::Khartoum, {City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg } },
    { City::Kinshasa, {City::Lagos, City::Khartoum, City::Johannesburg } },
    { City::Kolkata, {City::Delhi, City::Chennai, City::Bangkok, City::HongKong } },
    { City::Lagos, {City::SaoPaulo, City::Khartoum, City::Kinshasa } },
    { City::Lima, {City::MexicoCity, City::Bogota, City::Santiago } },
    { City::London, {City::NewYork, City::Madrid, City::Essen, City::Paris } },
    { City::LosAngeles, {City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney } },
    { City::Madrid, {City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers } },
    { City::Manila, {City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney } },
    { City::MexicoCity, {City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota } },
    { City::Miami, {City::Atlanta, City::MexicoCity, City::Washington, City::Bogota } },
    { City::Milan, {City::Essen, City::Paris, City::Istanbul } },
    { City::Montreal, {City::Chicago, City::Washington, City::NewYork } },
    { City::Moscow, {City::StPetersburg, City::Istanbul, City::Tehran } },
    { City::Mumbai, {City::Karachi, City::Delhi, City::Chennai } },
    { City::NewYork, {City::Montreal, City::Washington, City::London, City::Madrid } },
    { City::Osaka, {City::Taipei, City::Tokyo } },
    { City::Paris, {City::Algiers, City::Essen, City::Madrid, City::Milan, City::London } },
    { City::Riyadh, {City::Baghdad, City::Cairo, City::Karachi } },
    { City::SanFrancisco, {City::LosAngeles, City::Chicago, City::Tokyo, City::Manila } },
    { City::Santiago, {City::Lima } },
    { City::SaoPaulo, {City::Bogota, City::BuenosAires, City::Lagos, City::Madrid } },
    { City::Seoul, {City::Beijing, City::Shanghai, City::Tokyo } },
    { City::Shanghai, {City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo } },
    { City::StPetersburg, {City::Essen, City::Istanbul, City::Moscow } },
    { City::Sydney, {City::Jakarta, City::Manila, City::LosAngeles } },
    { City::Taipei, {City::Shanghai, City::HongKong, City::Osaka, City::Manila } },
    { City::Tehran, {City::Baghdad, City::Moscow, City::Karachi, City::Delhi } },
    { City::Tokyo, {City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco } },
    { City::Washington, {City::Atlanta, City::NewYork, City::Montreal, City::Miami } }
};

Color get_color(City c) {
    return city_color.at(c);
}

/* פונקציית עזר שבודקת אם שתי ערים מחוברות ביניהן */
bool is_connected(City c1, City c2) {
    for(const auto& c: cities.at(c1)) {
        if(c == c2) return true;
    }
    return false;
}

/* פונקציית עזר שמגרילה עיר שמחוברת לעיר נתונה כלשהי */
City random_connected_city(City c) {
    size_t adjes = (size_t)rand() % (size_t)cities.at(c).size();
    return cities.at(c).at(adjes);
}

/* פונקציית עזר שמגרילה עיר כלשהי */
City random_city() {
    size_t t = (size_t)rand() % 47;
    int i = 0;
    for(const auto& city: cities) {
        if(i == t) {
            return city.first;
        }
        i++;
    }
    return City::Algiers;
}

/* פונקציית עזר שמגרילה עיר כלשהי */
City random_city_different_than(City c) {
    City r = random_city();
    while((r = random_city()) == c){}
    return (City)r;
}

/* פונקציית עזר שמגרילה עיר  */
City random_city_colored(Color c) {
    while(true) {
        City r = random_city();
        if(city_color.at(r) == c) {
            return r;
        }
    }
    return City::Algiers;
}

/* פונקציית עזר המגרילה מספר מסוים של ערים בצבע נתון  */
set<City> pick_N_cities_colored(int N, Color c) {
    set<City> ans;
    while(ans.size() < N) {
        ans.insert(random_city_colored(c));
    }
    return ans;
}

/* פונקציית עזר המגרילה 5 ערים שונות  */
set<City> pick_5_different_cities() {
    set<City> ans;
    while(ans.size() < 5) {
        ans.insert(random_city());
    }
    return ans;
}