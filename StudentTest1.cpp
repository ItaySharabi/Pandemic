/**
 * AUTHORS: AlmogJakov
 * 
 * Date: 2021-04
 */
//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
/* include main classes */
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
/* include special skills players */
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
#include <stdexcept>
#include <map>
#include <set>
#include <sstream>
using namespace std;

struct city_st {
    string city;
    Color color;
    set<City> neighbors;
};
map<City,city_st> cities_mp;
set<City> research_stations_cities;
set<City> cities_to_test;
void init() {
	/* init cities map */
	cities_mp = {
		{City::Algiers,(city_st){"Algiers",Color::Black,{City::Madrid, City::Paris, City::Istanbul, City::Cairo}}},
        {City::Atlanta,(city_st){"Atlanta",Color::Blue,{City::Chicago, City::Miami, City::Washington}}},
        {City::Baghdad,(city_st){"Baghdad",Color::Black,{City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi}}},
        {City::Bangkok,(city_st){"Bangkok",Color::Red,{City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong}}},
        {City::Beijing,(city_st){"Beijing",Color::Red,{City::Shanghai, City::Seoul}}},
        {City::Bogota,(city_st){"Bogota",Color::Yellow,{City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires}}},
        {City::BuenosAires,(city_st){"BuenosAires",Color::Yellow,{City::Bogota, City::SaoPaulo}}},
        {City::Cairo,(city_st){"Cairo",Color::Black,{City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh}}},
        {City::Chennai,(city_st){"Chennai",Color::Black,{City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta}}},
        {City::Chicago,(city_st){"Chicago",Color::Blue,{City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal}}},
        {City::Delhi,(city_st){"Delhi",Color::Black,{City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata}}},
        {City::Essen,(city_st){"Essen",Color::Blue,{City::London, City::Paris, City::Milan, City::StPetersburg}}},
        {City::HoChiMinhCity,(city_st){"HoChiMinhCity",Color::Red,{City::Jakarta, City::Bangkok, City::HongKong, City::Manila}}},
        {City::HongKong,(city_st){"HongKong",Color::Red,{City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei}}},
        {City::Istanbul,(city_st){"Istanbul",Color::Black,{City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow}}},
        {City::Jakarta,(city_st){"Jakarta",Color::Red,{City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney}}},
        {City::Johannesburg,(city_st){"Johannesburg",Color::Yellow,{City::Kinshasa, City::Khartoum}}},
        {City::Karachi,(city_st){"Karachi",Color::Black,{City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi}}},
        {City::Khartoum,(city_st){"Khartoum",Color::Yellow,{City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg}}},
        {City::Kinshasa,(city_st){"Kinshasa",Color::Yellow,{City::Lagos, City::Khartoum, City::Johannesburg}}},
        {City::Kolkata,(city_st){"Kolkata",Color::Black,{City::Delhi, City::Chennai, City::Bangkok, City::HongKong}}},
        {City::Lagos,(city_st){"Lagos",Color::Yellow,{City::SaoPaulo, City::Khartoum, City::Kinshasa}}},
        {City::Lima,(city_st){"Lima",Color::Yellow,{City::MexicoCity, City::Bogota, City::Santiago}}},
        {City::London,(city_st){"London",Color::Blue,{City::NewYork, City::Madrid, City::Essen, City::Paris}}},
        {City::LosAngeles,(city_st){"LosAngeles",Color::Yellow,{City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney}}},
        {City::Madrid,(city_st){"Madrid",Color::Blue,{City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers}}},
        {City::Manila,(city_st){"Manila",Color::Red,{City::HongKong, City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney}}},
        {City::MexicoCity,(city_st){"MexicoCity",Color::Yellow,{City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota}}},
        {City::Miami,(city_st){"Miami",Color::Yellow,{City::Atlanta, City::MexicoCity, City::Washington, City::Bogota}}},
        {City::Milan,(city_st){"Milan",Color::Blue,{City::Essen, City::Paris, City::Istanbul}}},
        {City::Montreal,(city_st){"Montreal",Color::Blue,{City::Chicago, City::Washington, City::NewYork}}},
        {City::Moscow,(city_st){"Moscow",Color::Black,{City::StPetersburg, City::Istanbul, City::Tehran}}},
        {City::Mumbai,(city_st){"Mumbai",Color::Black,{City::Karachi, City::Delhi, City::Chennai}}},
        {City::NewYork,(city_st){"NewYork",Color::Blue,{City::Montreal, City::Washington, City::London, City::Madrid}}},
        {City::Osaka,(city_st){"Osaka",Color::Red,{City::Taipei, City::Tokyo}}},
        {City::Paris,(city_st){"Paris",Color::Blue,{City::Algiers, City::Essen, City::Madrid, City::Milan, City::London}}},
        {City::Riyadh,(city_st){"Riyadh",Color::Black,{City::Baghdad, City::Cairo, City::Karachi}}},
        {City::SanFrancisco,(city_st){"SanFrancisco",Color::Blue,{City::LosAngeles, City::Chicago, City::Tokyo, City::Manila}}},
        {City::Santiago,(city_st){"Santiago",Color::Yellow,{City::Lima}}},
        {City::SaoPaulo,(city_st){"SaoPaulo",Color::Yellow,{City::Bogota, City::BuenosAires, City::Lagos, City::Madrid}}},
        {City::Seoul,(city_st){"Seoul",Color::Red,{City::Beijing, City::Shanghai, City::Tokyo}}},
        {City::Shanghai,(city_st){"Shanghai",Color::Red,{City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo}}},
        {City::StPetersburg,(city_st){"StPetersburg",Color::Blue,{City::Essen, City::Istanbul, City::Moscow}}},
        {City::Sydney,(city_st){"Sydney",Color::Red,{City::Jakarta, City::Manila, City::LosAngeles}}},
        {City::Taipei,(city_st){"Taipei",Color::Red,{City::Shanghai, City::HongKong, City::Osaka, City::Manila}}},
        {City::Tehran,(city_st){"Tehran",Color::Black,{City::Baghdad, City::Moscow, City::Karachi, City::Delhi}}},
        {City::Tokyo,(city_st){"Tokyo",Color::Red,{City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco}}},
		{City::Washington,(city_st){"Washington",Color::Blue,{City::Atlanta, City::NewYork, City::Montreal, City::Miami}}}
	};
	/* choose random 16 cities to be with research stations */
	research_stations_cities.clear();
	while (research_stations_cities.size()<16) {
		auto it = cities_mp.begin();
		std::advance(it, (uint)rand() % cities_mp.size());
		research_stations_cities.insert(it->first);
    };
	/* choose random 10 cities to test */
	cities_to_test.clear();
	while (cities_to_test.size()<10) {
		auto it = cities_mp.begin();
		std::advance(it, (uint)rand() % cities_mp.size());
		cities_to_test.insert(it->first);
    };
}

/* for the purpose of discovering a cure for a city */
Researcher five_cards_researcher(Board& board, City city) {
	Researcher researcher(board, city);
	Color color = cities_mp[city].color;
	int counter = 0;
	for (auto &c : cities_mp) {
		if (c.second.color==color) counter++;
		researcher.take_card(c.first);
		if (counter==5) break;
	}
	return researcher;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////// Tests Methods //////////////////////////////
//////////////////////////////////////////////////////////////////////////

/* ---------------------------- Drive Test ---------------------------- */
void drive_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		/* attempt to travel to a non-neighboring city */
		for (auto &far_city : cities_mp) {
			if (city.first!=far_city.first&&city.second.neighbors.count(far_city.first)==0) {
				GeneSplicer some_player{board, city.first};
				/* should throw an error (non-neighboring cities) */
				CHECK_THROWS(some_player.drive(far_city.first));
			}
	    }
		/* attempt to travel to a neighboring city */
		for (auto &neighbor : city.second.neighbors) {
			GeneSplicer some_player{board, city.first};
			/* should not throw an error (iteration of the neighbors) */
			CHECK_NOTHROW(some_player.drive(neighbor));
	    }
	}
}

/* --------------------------- Fly Direct Test --------------------------- */
/* should run build_test before this test (to build research stations) */
/* Dispatcher Action */
void dispatcher_fly_direct_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		for (auto &other_city : cities_mp) {
			Dispatcher some_player(board, city.first);
			if (research_stations_cities.count(city.first)!=0) {
				if (city.first==other_city.first) {
					/* should throw an error (cannot fly from city to it self) */
					CHECK_THROWS(some_player.fly_direct(other_city.first));
				} else {
					CHECK_NOTHROW(some_player.fly_direct(other_city.first));
				}
			}
		}
	}
	return;
}
/* Other-Players Action (no special action when discovering cure) */
void fly_direct_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		for (auto &other_city : cities_mp) {
			Medic some_player{board, city.first};
			if (city.first==other_city.first) continue;
			/* should throw an error (no card of destinition city) */
			CHECK_THROWS(some_player.fly_direct(other_city.first));
			some_player.take_card(other_city.first);
			/* should not throw an error (card taken) */
			CHECK_NOTHROW(some_player.fly_direct(other_city.first));
	    }
	}
}

/* --------------------------- Fly Charter Test --------------------------- */
// should take an empty board
void fly_charter_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		for (auto &other_city : cities_mp) {
			if (city.first==other_city.first) continue;
			Researcher some_player{board, city.first};
			/* should throw an error (no card of the current city) */
			CHECK_THROWS(some_player.fly_charter(other_city.first));
			some_player.take_card(city.first);
			/* should not throw an error (card taken) */
			CHECK_NOTHROW(some_player.fly_charter(other_city.first));
	    }
	}
}

/* ------------------------- Build & Fly Shuttle Test ------------------------- */
/* should run build_test before this test (to build research stations) */
void fly_shuttle_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		for (auto &other_city : cities_mp) {
			FieldDoctor some_player{board, city.first};
			if (research_stations_cities.count(city.first)==0||
				research_stations_cities.count(other_city.first)==0) {
				/* should throw an error (no research station in src/dest city) */
				CHECK_THROWS(some_player.fly_shuttle(other_city.first));
			} else {
				if (city.first==other_city.first) {
					/* should throw an error (cannot fly from city to it self) */
					CHECK_THROWS(some_player.fly_shuttle(other_city.first));
				} else {
					/* should not throw an error (both cities have a research station) */
					CHECK_NOTHROW(some_player.fly_shuttle(other_city.first));
				}
			}
	    }
	}
}

/* build research stations only for the cities generated randomly by init() method */
void operationsExpert_build_test(Board& board) {
	/* OperationsExpert Action */
	for (auto &city : research_stations_cities) {
		OperationsExpert same_player_role(board, city);
		/* will never throw an error (truth of the action is tested in fly_shuttle_test) */
		CHECK_NOTHROW(same_player_role.build());
	}
}
void build_test(Board& board) {
	for (auto &city : research_stations_cities) {
		/* Default-Player Action */
		Virologist same_player_role{board, city};
		/* should throw an error (no card) */
		CHECK_THROWS(same_player_role.build());
		same_player_role.take_card(city);
		/* should not throw an error (card taken) */
		CHECK_NOTHROW(same_player_role.build());
	}
}

void build_and_fly_shuttle_test(Board& board) {
	FieldDoctor player(board, City::Washington);
	/* build random research stations */
	build_test(board);
	/* pass the player (any type of player should behave the same way in fly_shuttle method) */
	fly_shuttle_test(board);
}

/* ---------------------------- Discover Cure Test ---------------------------- */
/* Scientist Action */
void scientist_discover_cure_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		/* n = Random number from 1 to 5 */
		int iRand = (rand() % 5) + 1;
		Scientist scientist(board, city.first, iRand);
		int counter = 0;
		for (auto &c : cities_mp) {
			if (city.second.color==c.second.color) {
				CHECK_THROWS(scientist.discover_cure(city.second.color));
				scientist.take_card(c.first);
				if ((++counter)==iRand) break;
			}
		}
		if (research_stations_cities.count(city.first)==0) {
			CHECK_THROWS(scientist.discover_cure(city.second.color));
		} else {
			CHECK_NOTHROW(scientist.discover_cure(city.second.color));
			board.remove_cures();
		}
	}
	return;
}
/* Researcher Action */
void researcher_discover_cure_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		Researcher researcher(board, city.first);
		int counter = 0;
		for (auto &c : cities_mp) {
			if (city.second.color==c.second.color) {
				CHECK_THROWS(researcher.discover_cure(city.second.color));
				researcher.take_card(c.first);
				if ((++counter)==5) break;
			}
		}
		CHECK_NOTHROW(researcher.discover_cure(city.second.color));
		board.remove_cures();
	}
	return;
}
/* GeneSplicer Action */
void geneSplicer_discover_cure_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		GeneSplicer geneSplicer(board, city.first);
		int counter = 0;
		set<City> cards{};
		while (cards.size()<5) {
			auto it = cities_mp.begin();
			std::advance(it, (uint)rand() % cities_mp.size());
			geneSplicer.take_card(it->first);
			cards.insert(it->first);
		}
		if (research_stations_cities.count(city.first)==0) {
			CHECK_THROWS(geneSplicer.discover_cure(city.second.color));
		} else {
			board.remove_cures();
			CHECK_NOTHROW(geneSplicer.discover_cure(city.second.color));
		}
	}
	return;
}
/* Other-Players Action (no special action when discovering cure) */
void discover_cure_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		OperationsExpert default_player{board, city.first};
		if (research_stations_cities.count(city.first)!=0) {
			int counter = 0;
			for (auto &other_city : cities_mp) {
				if (counter==5) {
					CHECK_NOTHROW(default_player.discover_cure(cities_mp[city.first].color));
					break;
				} else if (city.first!=other_city.first&&cities_mp[city.first].color==cities_mp[other_city.first].color) {
					CHECK_THROWS(default_player.discover_cure(cities_mp[city.first].color));
					default_player.take_card(other_city.first);
					counter++;
				}
			}
			board.remove_cures();
		} else {
			for (auto &other_city : cities_mp) {
				default_player.take_card(other_city.first);
			}
			for (auto &other_city : cities_mp) {
				CHECK_THROWS(default_player.discover_cure(cities_mp[city.first].color));
			}
		}
	}
}

/* ---------------------------- Treat Test ---------------------------- */
/* Medic Action */
void medic_treat_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		Medic some_player(board, city.first);
		/* calculate a random variable (between 1 and 9) for the level of disease in the current city */
		int iRand = (rand() % 9) + 1;
		board[city.first] = iRand;
		/* should not throw an error (medic set the disease to 0) */
		CHECK_NOTHROW(some_player.treat(city.first));
		/* default player */
		Dispatcher p{board, city.first};
		/* should throw an error (medic already set the disease to 0) */
		CHECK_THROWS(p.treat(city.first));
	}
	return;
}
/* Virologist Action */
void virologist_treat_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		/* calculate a random variable (between 1 and 9) for the level of disease in the current city */
		int iRand = (rand() % 9) + 1;
		board[city.first] = iRand;
		auto it = cities_mp.begin();
		while (it->first==city.first) {
			it = cities_mp.begin();
			std::advance(it, (uint)rand() % cities_mp.size());
		}
		Virologist some_player(board, it->first);
		/* should throw an error (no card) */
		CHECK_THROWS(some_player.treat(city.first));
		/* take the card */
		some_player.take_card(city.first);
		/* should not throw an error (card taken) */
		CHECK_NOTHROW(some_player.treat(city.first));
	}
	return;
}
/* FieldDoctor Action */
void fieldDoctor_treat_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		FieldDoctor some_player(board, city.first);
		/* calculate a random variable (between 1 and 9) for the level of disease in the current city */
		int iRand = (rand() % 9) + 1;
		board[city.first] = iRand;
		/* should throw an error (medic set the disease to 0) */
		auto it = cities_mp.begin();
		it = cities_mp.begin();
		std::advance(it, (uint)rand() % cities_mp.size());
		board[it->first] = iRand;
		if (city.first==it->first || cities_mp[city.first].neighbors.count(it->first)) {
			/* should not throw an error (nearby city) */
			CHECK_NOTHROW(some_player.treat(it->first));
		} else {
			/* should throw an error (not a nearby city) */
			CHECK_THROWS(some_player.treat(it->first));
		}
	}
	return;
}
/* Other-Players Action */
void treat_test(Board& board) {
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		OperationsExpert some_player{board, city.first};
		/* calculate a random variable (between 1 and 9) for the level of disease in the current city */
		board.remove_cures();
		int iRand = (rand() % 9) + 1;
		board[city.first] = iRand;
		/* simulate a scenario where a cure is found (only for numbers greater than 5) */
		if (iRand>5) {
			/* discover a cure for the current city */
			Researcher researcher = five_cards_researcher(board, city.first);
			researcher.discover_cure(city.second.color);
			/* should not throw an error (disease level is greater than 0)) */
			CHECK_NOTHROW(some_player.treat(city.first));
			stringstream des;
			des << board[city.first];
			/* check if the disease level has been set to 0 (cure has been found) */
			CHECK(des.str() == "0");
			board.remove_cures();
		} else {
			/* simulate a scenario where a cure is not found (only for numbers smaller than 5) */
			while (iRand>=0) {
				/* should throw an error (trying to treat while disease level is 0) */
				if (iRand==0) {
					CHECK_THROWS(some_player.treat(city.first));
					break;
				}
				/* should not throw an error (reduce disease level by 1) */
				CHECK_NOTHROW(some_player.treat(city.first));
				iRand--;
				stringstream des;
				des << board[city.first];
				/* check if the disease level has been reduces by 1 */
				CHECK(des.str() == to_string(iRand));
			}
		}
		
	}
}

/* ------------------------- Medic Auto-heal Test ------------------------- */
void medic_auto_heal_test(Board& board) {
	Board b;
	Medic medic{b, City::Algiers};
	set<Color> auto_heal_cities;
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		/* choose 2 random medications (out of the 4) */
		if (auto_heal_cities.size()<2&&auto_heal_cities.count(city.second.color)==0) {
			auto_heal_cities.insert(city.second.color);
			Researcher researcher = five_cards_researcher(b, city.first);
			researcher.discover_cure(city.second.color);
		}
		/* choose a random disease level from 1 to 9 to any city */
		b[city.first] = (rand() % 9) + 1;
	}
	/* travel to the city to set the disease to 0 by traveling (auto heal) */
	for (auto &city : cities_mp) {
		if (cities_to_test.count(city.first)==0) continue;
		/* random way to go to the city (drive,fly_direct,fly_charter,fly_shuttle) */
		int iRand = (rand() % 4) + 1;
		/* go the one of the neighbors of the current city */
		auto some_neighbor = city.second.neighbors.begin();
		std::advance(some_neighbor, 0);
		Medic some_player(b, *some_neighbor);
		if (iRand==1) {
			/* Checking the correctness of the auto-heal by driving to the city */
			Medic some_player(b, *some_neighbor);
			some_player.drive(city.first);
		} else if (iRand==2) {
			/* Checking the correctness of the auto-heal by fly_direct to the city */
			some_player.take_card(city.first);
			some_player.fly_direct(city.first);
		} else if (iRand==3) {
			/* Checking the correctness of the auto-heal by fly_charter to the city */
			some_player.take_card(*some_neighbor);
			some_player.fly_charter(city.first);
		} else { /* iRand==4 */
		/* Checking the correctness of the auto-heal by fly_shuttle to the city */
			OperationsExpert b1(b, city.first);
			b1.build();
			OperationsExpert b2(b, *some_neighbor);
			b2.build();
			some_player.fly_shuttle(city.first);
		}
		/* If the disease in the current city has been treated */
		if (auto_heal_cities.count(city.second.color)!=0) {
			Dispatcher p{b, city.first};
			/* should throw an error (presence of the medic already set the disease to 0) */
			CHECK_THROWS(p.treat(city.first));
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////  ________________________________________  ///////////////
/////////////// |                                        | ///////////////
/////////////// |              Tests Cases               | ///////////////
/////////////// |________________________________________| ///////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEST_CASE("No-Special-Skills Test") {
	/* init */
	init();
	Board board;
	/* Should run build_and_fly_shuttle_test before all to build research stations */
	build_and_fly_shuttle_test(board);
	SUBCASE("Player Drive Test") {
		drive_test(board);
	}
	SUBCASE("Player Fly Direct Test") {
		fly_direct_test(board);
	}
	SUBCASE("Player Fly Charter Test") {
		fly_charter_test(board);
	}
	SUBCASE("Player Discover Cure Test") {
		discover_cure_test(board);
	}
	
}

TEST_CASE("No-Special-Skills Test2") {
	/* init */
	init();
	Board board;
	SUBCASE("Player Treat Test") {
		treat_test(board);
	}
}

TEST_CASE("Researcher Test") {
	/* init */
	init();
	Board board;
	SUBCASE("Researcher Discover Cure Test") {
		researcher_discover_cure_test(board);
	}
}

TEST_CASE("Scientist Test") {
	/* init */
	init();
	Board board;
	/* Should build random research stations for discover_cure test */
	build_test(board);
	SUBCASE("Scientist Discover Cure Test") {
		scientist_discover_cure_test(board);
	}
}

TEST_CASE("FieldDoctor Test") {
	/* init */
	init();
	Board board;
	SUBCASE("FieldDoctor Treat Test") {
		fieldDoctor_treat_test(board);
	}
}

TEST_CASE("GeneSplicer Test") {
	/* init */
	init();
	Board board;
	/* Should build random research stations for discover_cure test */
	build_test(board);
	SUBCASE("GeneSplicer Discover Cure Test") {
		geneSplicer_discover_cure_test(board);
	}
}

TEST_CASE("OperationsExpert Test") {
	/* init */
	init();
	Board board;
	operationsExpert_build_test(board);
	fly_shuttle_test(board);
}

TEST_CASE("Dispatcher Test") {
	/* init */
	init();
	Board board;
	/* Should build random research stations for fly_direct test */
	build_test(board);
	SUBCASE("Dispatcher Fly Direct Test") {
		dispatcher_fly_direct_test(board);
	}
}

TEST_CASE("Medic Test") {
	/* init */
	init();
	Board board;
	SUBCASE("Medic Treat Test") {
		medic_treat_test(board);
	}
	SUBCASE("Medic Auto-heal Test") {
		medic_auto_heal_test(board);
	}
}

TEST_CASE("Virologist Test") {
	/* init */
	init();
	Board board;
	SUBCASE("Virologist Treat Test") {
		virologist_treat_test(board);
	}
}