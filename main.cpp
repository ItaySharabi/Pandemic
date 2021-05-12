#include <iostream>
#include "sources/GameHeaders.hpp"

using namespace pandemic;
using namespace std;
int main() {

	// /*
	// 	check for board
	// */
	// Board board;
	// // cout << board;
	// // set level to 100 and research_station true
	// for(auto &x : board.getVertex()){
	// 	board[x.first] = 100;	
	// 	x.second.research_station = true;
	// }
	// cout << "board.is_clean = " << ((board.is_clean())? "true": "false") << "\n";

	// //set Cure_discovered true
	// for (auto &x : board.getCure_discovered()){
	// 	x.second = true;
	// }

	// // cout << board << endl;
	// //remove all research_station
	// board.remove_cures();

	// board.remove_stations();
	// //remove all level cure to 0
	// for(auto &x : board.getVertex()){
	// 	board[x.first] = 0;	
	// }

	// cout << "board.is_clean = " << ((board.is_clean())? "true": "false") << "\n\n\n\n\n\n\n\n";
	// // cout << board << endl;

	// /*
	// 	check for player
	// */
	// // cout << getCityAsString(getRandomCity()) << endl;
	// City c = City::Algiers;
	// City ni[4] = {
	// 	City::Cairo,
	// 	City::Istanbul,
	// 	City::Madrid,
	// 	City::Paris
	// };
	// City notNi[4] = {
	// 	City::Chicago,
	// 	City::Miami,
	// 	City::Washington,
	// 	City::Karachi
	// };
	// cout << "check drive to ni city\n" ;
	// //check drive to ni city
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	p.drive(ni[i]);
	// }
	// cout << "\ncheck drive to not ni city\n" ;
	// //check drive to not ni city
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	p.drive(notNi[i]);
	// }
	// cout << "\n\n\n" ;

	
	// cout << "check take_card and fly_direct\n";
	// //check take_card and fly_direct
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	cout <<  "curr_city  = " << getCityAsString(p.getCurrCity()) << "\n";
	// 	p.take_card(notNi[i]);
	// 	cout << "check the card of the city  => ( "<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	p.fly_direct(notNi[i]);
	// 	cout << "check the card of the city  => ( "<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	cout << "curr city after call to fly_direct =  "<< getCityAsString(p.getCurrCity()) << "\n\n";
	// }
	// cout << "\n\n\n" ;


	// cout << "check take_card and fly_direct with no card of the city\n";
	// //check take_card and fly_direct
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	cout <<  "curr_city  = " << getCityAsString(p.getCurrCity()) << "\n";
	// 	p.take_card(notNi[i]);
	// 	cout << "check the card of the city  => ( "<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	p.fly_direct(ni[i]);
	// 	cout << "check the card of the city  => ( "<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	cout << "curr city after call to fly_direct=  "<< getCityAsString(p.getCurrCity()) << "\n\n";
	// }
	// cout << "\n\n\n" ;




		
	// cout << "check take_card and fly_charter\n";
	// //check take_card and fly_charter
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	cout <<  "curr_city  = " << getCityAsString(p.getCurrCity()) << "\n";
	// 	p.take_card(notNi[i]);
	// 	cout << "check the card of the city  => ( "<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	p.fly_charter(notNi[i]);
	// 	cout << "check the card of the city  => ( "<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	cout << "curr city after call to fly_charter =  "<< getCityAsString(p.getCurrCity()) << "\n\n";
	// }
	// cout << "\n\n\n" ;


	// cout << "check take_card and fly_charter with no card of the city\n";
	// //check take_card and fly_charter
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	cout <<  "curr_city  = " << getCityAsString(p.getCurrCity()) << "\n";
	// 	p.take_card(notNi[i]);
	// 	cout << "check the card of the city  => ("<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	p.fly_charter(ni[i]);
	// 	cout << "check the card of the city  => ("<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	cout << "curr city after call to fly_charter=  "<< getCityAsString(p.getCurrCity()) << "\n\n";
	// }
	// cout << "\n\n\n" ;

	// // cout << "Memory address of board = "<< &board << endl;
	// //init research station in all the city to true
	// for (int i = 0; i < 48; i++){
	// 	board.getVertex()[getCityAsObject(cities.at(i))].research_station = true;
	// }
	
	// cout << "check take_card and fly_shuttle\n";
	// //check take_card and fly_shuttle
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	// board.getVertex()[p.getCurrCity()].research_station = true;
	// 	// cout << "Memory address of board in for= "<< &p.getBoard() << endl;
	// 	cout <<  "curr_city  = " << getCityAsString(p.getCurrCity()) << "\n";
	// 	cout <<  "research_station in the city  = " << ((board.getVertex()[p.getCurrCity()].research_station)? "true" : "false") << "\n";
	// 	// p.take_card(notNi[i]);
	// 	// cout << "check the card of the city  => ("<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	p.fly_shuttle(notNi[i]);
	// 	// cout << "check the card of the city  => ("<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	cout << "curr city after call to fly_shuttle =  "<< getCityAsString(p.getCurrCity()) << "\n\n";
	// }
	// cout << "\n\n\n" ;

	// //init research station in all the city to false
	// for (int i = 0; i < 48; i++){
	// 	board.getVertex()[getCityAsObject(cities.at(i))].research_station = false;
	// }
	// cout << "check take_card and fly_shuttle with no card of the city\n";
	// //check take_card and fly_shuttle
	// for (size_t i = 0; i < 4; i++){
	// 	Player p {board,c};
	// 	cout <<  "curr_city  = " << getCityAsString(p.getCurrCity()) << "\n";
	// 	// p.take_card(notNi[i]);
	// 	// cout << "check the card of the city  => ("<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	p.fly_shuttle(ni[i]);
	// 	// cout << "check the card of the city  => ("<< getCityAsString(notNi[i]) << ") = " << ((p.checkCardByCity(notNi[i]))? "true": "false") << "\n";
	// 	cout << "curr city after call to fly_shuttle=  "<< getCityAsString(p.getCurrCity()) << "\n\n";
	// }
	// cout << "\n\n\n" ;
	return 0;
}