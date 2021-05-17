#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include "sources/GameHeaders.hpp"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define GREEN   "\033[32m"      /* Green */

using namespace pandemic;
using namespace std;
const int num_of_players = 8;
const int num_of_cities = 48;

City random_city() {return getCity(rand() % num_of_cities);}
void print_players(Player**);
void random_movement(Player*);
void some_5_cards(Player*);
Player* choose_player(Player**);


int main() {

	srand(time(0)); // set to create pseudo-random numbers.

	Board b;

	Dispatcher dispatcher	{b, Atlanta};
	FieldDoctor fieldDoctor {b, Atlanta};
	GeneSplicer geneSplicer {b, Atlanta};
	Medic medic 			{b, Atlanta};
	OperationsExpert oper	{b, Atlanta};
	Researcher researcher	{b, Atlanta};
	Scientist scientist		{b, Atlanta, 1};
	Virologist virologist	{b, Atlanta};

	Player *players[num_of_players] = {&dispatcher, &fieldDoctor, &geneSplicer, &medic, 
									   &oper, &researcher, &scientist, &virologist};

	City infected_city;
	Player *p;
	cout << "Game Started!\nAll players spawned in Atlanta. The world is cured of disease so far...\n" << endl;

							/*Part A*/
	{ // A random city will be infected with a small disease count and
	  // some player will go to treat() the city.
		sleep(3);
		infected_city = random_city();	// Choose a random city to infect
		b[infected_city] = 10;				// increase disease lv. to 10
		cout << RED << "A disease was discovered in "  << RESET << getCity(infected_city) << endl;

		p = choose_player(players); // Takes I/O
		cout << p->role() + " is now flying to " + getCity(infected_city) << endl;
		sleep(2);
		
		p->take_card(infected_city);
		p->fly_direct(infected_city);
		cout << *p << endl;
		sleep(3);

		cout << RED <<"The disease level in " << RESET << getCity(infected_city) << " is " << b[infected_city] << endl;
		sleep(3);
		while (b[infected_city] > 0) {
			cout << p->role() + " is using treat()... " << "(disease lv: " << b[infected_city] << ")" << endl;
			sleep(1);
			p->treat(infected_city);
		}

		cout << getCity(infected_city) << " is " << GREEN << "clean!" << RESET << endl; 
		sleep(3);
	}

							/*Part B*/
	{ // A random city will be infected with a lot of disease -
	  // forcing the medic to go treat or a cure discovery

		infected_city = random_city();	// Choose a random city to infect
		b[infected_city] = 700;				// increase disease lv. to 10
		cout << RED << "\nA disease was discovered in "  << RESET << getCity(infected_city) << endl;

			p = choose_player(players);
			cout << p->role() + " is now flying to " + getCity(infected_city) << endl;
			sleep(2);
			
			p->take_card(infected_city);
			p->fly_direct(infected_city);
			cout << *p << endl;
			sleep(2);
			cout << RED << "The disease level in " << getCity(infected_city) << RESET << " is " << b[infected_city] << endl;


		if (p->role() != "Medic" && p->role() != "GeneSplicer") {
			cout << "-" + p->role() << ": It's gonna take forever to treat this city..." << endl;
			sleep(3);
			cout << "-GeneSplicer" << ": Let me discover a cure for you!\n" << endl;
			sleep(3);

			geneSplicer.take_card(getCity(geneSplicer.get_curr_city())).build();
			some_5_cards(&geneSplicer);
			cout << "GeneSplicer discovering cure...\n" << endl;
			sleep(3);

			geneSplicer.discover_cure(b.city_color(infected_city)); // discover a cure to where the current player is

			cout << getColor(b.city_color(infected_city)) << " cure discovered!\n" << endl;
			sleep(3);
			cout << "-GeneSplicer: Now you only need to treat once!\n" << endl;
			sleep(3);
			cout << p->role() + " is using treat()... " << "(disease lv: " << b[infected_city] << ")\n" << endl;
			sleep(3);
			cout << getCity(infected_city) << " is " << GREEN << "clean!" << RESET << endl << endl; 

		} else if ((*p).role() == "Medic"){
			// Player is Medic
			cout << "-Medic: This will be a peice of cake!\n" << endl; 
			sleep(2);
			cout << "Medic is using treat()... " << "(disease lv: " << b[infected_city] << ")\n" << endl;
			medic.treat(infected_city);
			sleep(2);
			cout << getCity(infected_city) << " is " << GREEN << "clean!\n" << RESET << endl; 


		} else {
			// Player is GeneSplicer
			cout << "-GeneSplicer: I can discover a cure with any 5 cards\n" << endl;
			sleep(4);
			geneSplicer.take_card(infected_city).build(); // build a research station
			some_5_cards(&geneSplicer);
			geneSplicer.discover_cure(b.city_color(infected_city));
			cout << endl << getColor(b.city_color(infected_city)) << " Cure was discovered!\n" << endl;
			
			cout << "-GeneSplicer: Now only one treat() is needed\n" << endl;
			sleep(2);
			cout << geneSplicer.role() + " is using treat()... " << "(disease lv: " << b[infected_city] << ")\n" << endl;
			sleep(2);
			geneSplicer.treat(infected_city);
			cout << getCity(infected_city) << " is " << GREEN << "clean!" << RESET << endl; 
		}
		cout << RED << "End of Demo" << RESET << endl;
	}

	return 0;
}

void print_players(Player** players) {
	for (int i = 0; i < num_of_players; i++) {
		cout << *(*(players + i));
	}
}

void some_5_cards(Player* player) {
	(*player).take_card(Atlanta).take_card(MexicoCity)
			 .take_card(Washington).take_card(Beijing)
			 .take_card(NewYork);
	cout << "5 cards were given to " << player->role() << endl;
}

Player* choose_player(Player** players) {
	cout << "Which player would you like to send in order to treat the disease?\n" << endl;
	cout << "Select Player: (1-8)"
		"\n1. Dispatcher"  
		"\n2. FieldDoctor"  
		"\n3. GeneSplicer"  
		"\n4. Medic"  
		"\n5. OperationsExpert"  
		"\n6. Researcher"  
		"\n7. Scientist"  
		"\n8. Virologist" << endl;

	short p_index;
	Player *p;

	if (cin >> p_index && p_index > 0 && p_index <= num_of_players) {
		p = (*(players + (p_index - 1)));
		return p;
	} else {
		return *players;
	}
}

// clear; clang++-9 -std=c++2a -o main main.cpp objects/*.o; ./main
// make clean; make; clear; clang++-9 -std=c++2a -o main main.cpp objects/*.o; ./main