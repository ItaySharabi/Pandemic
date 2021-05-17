#pragma once

namespace pandemic {

    enum Color{
        Black,
        Blue,
        Red,
        Yellow
    };

    static std::string getColor(const Color& color) {

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

    static Color getColor(const std::string& color) {

        return (color == "Black") ? Black :
        (color == "Blue") ? Blue : 
        (color == "Yellow") ? Yellow :
        Red;
    }
};
