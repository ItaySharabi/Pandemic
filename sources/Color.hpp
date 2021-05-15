#pragma once
#include <iostream>

enum Color{
    Black,
    Blue,
    Red,
    Yellow
};

inline std::string getColor(Color color) {

    switch (color){
        case 0:
            return "Black";
        case 1:
            return "Blue";
        case 2:
            return "Red";
        case 3:
            return "Yellow";
    }
}

inline Color getColor(std::string color) {

    return (color == "Black") ? Black :
    (color == "Blue") ? Blue : 
    (color == "Yellow") ? Yellow :
    Red;
}