// #pragma once

// namespace pandemic {

//     enum class City {

//             Chicago, Miami, LosAngeles, SanFrancisco, Atlanta, MexicoCity, Bogota,
//             Lima, Santiago, BuenosAires, SaoPaulo, Lagos, Kinshasa, Johannesburg, 
//             Khartoum, Cairo, Algiers, Riyadh, Baghdad, Istanbul, Paris, Madrid, 
//             Karachi, Mumbai, Chennai, Moscow, StPetersburg, Essen, London, Milan,
//             Tehran, Delhi, Jakarta, HoChiMinhCity, Manila, Taipei, Osaka,
//             Sydney, Shanghai, Beijing, Seoul, Tokyo, Kolkata, Montreal, NewYork,
//             Washington, Bangkok, HongKong
//     };
    
// };
#pragma once
#include <iostream>

enum City{
    Algiers,
    Atlanta,
    Baghdad,
    Bangkok,
    Beijing,
    Bogota,
    BuenosAires,
    Cairo,
    Chennai,
    Chicago,
    Delhi,
    Essen,
    HoChiMinhCity,
    HongKong,
    Istanbul,
    Jakarta,
    Johannesburg,
    Karachi,
    Khartoum,
    Kinshasa,
    Kolkata,
    Lagos,
    Lima,
    London,
    LosAngeles,
    Madrid,
    Manila,
    MexicoCity,
    Miami,
    Milan,
    Montreal,
    Moscow,
    Mumbai,
    NewYork,
    Osaka,
    Paris,
    Riyadh,
    SanFrancisco,
    Santiago,
    SaoPaulo,
    Seoul,
    Shanghai,
    StPetersburg,
    Sydney,
    Taipei,
    Tehran,
    Tokyo,
    Washington
};

inline std::string getCity(City city){
    switch (city){
    case Algiers : return "Algiers"; break; 
    case Atlanta : return "Atlanta"; break; 
    case Baghdad : return "Baghdad"; break; 
    case Bangkok : return "Bangkok"; break; 
    case Beijing : return "Beijing"; break; 
    case Bogota : return "Bogota"; break; 
    case BuenosAires : return "BuenosAires"; break; 
    case Cairo : return "Cairo"; break; 
    case Chennai : return "Chennai"; break; 
    case Chicago : return "Chicago"; break; 
    case Delhi : return "Delhi"; break; 
    case Essen : return "Essen"; break; 
    case HoChiMinhCity : return "HoChiMinhCity"; break; 
    case HongKong : return "HongKong"; break; 
    case Istanbul : return "Istanbul"; break; 
    case Jakarta : return "Jakarta"; break; 
    case Johannesburg : return "Johannesburg"; break; 
    case Karachi : return "Karachi"; break; 
    case Khartoum : return "Khartoum"; break; 
    case Kinshasa : return "Kinshasa"; break; 
    case Kolkata : return "Kolkata"; break; 
    case Lagos : return "Lagos"; break; 
    case Lima : return "Lima"; break; 
    case London : return "London"; break; 
    case LosAngeles : return "LosAngeles"; break; 
    case Madrid : return "Madrid"; break; 
    case Manila : return "Manila"; break; 
    case MexicoCity : return "MexicoCity"; break; 
    case Miami : return "Miami"; break; 
    case Milan : return "Milan"; break; 
    case Montreal : return "Montreal"; break; 
    case Moscow : return "Moscow"; break; 
    case Mumbai : return "Mumbai"; break; 
    case NewYork : return "NewYork"; break; 
    case Osaka : return "Osaka"; break; 
    case Paris : return "Paris"; break; 
    case Riyadh : return "Riyadh"; break; 
    case SanFrancisco : return "SanFrancisco"; break; 
    case Santiago : return "Santiago"; break; 
    case SaoPaulo : return "SaoPaulo"; break; 
    case Seoul : return "Seoul"; break; 
    case Shanghai : return "Shanghai"; break; 
    case StPetersburg : return "StPetersburg"; break; 
    case Sydney : return "Sydney"; break; 
    case Taipei : return "Taipei"; break; 
    case Tehran : return "Tehran"; break; 
    case Tokyo : return "Tokyo"; break; 
    case Washington : return "Washington"; break; 
    }
    return "None";
}
inline City getCity(std::string city){
        if(city == "Algiers") return Algiers;
        else if(city == "Atlanta") return Atlanta;
        else if(city == "Baghdad") return Baghdad;
        else if(city == "Bangkok") return Bangkok;
        else if(city == "Beijing") return Beijing;
        else if(city == "Bogota") return Bogota;
        else if(city == "BuenosAires") return BuenosAires;
        else if(city == "Cairo") return Cairo;
        else if(city == "Chennai") return Chennai;
        else if(city == "Chicago") return Chicago;
        else if(city == "Delhi") return Delhi;
        else if(city == "Essen") return Essen;
        else if(city == "HoChiMinhCity") return HoChiMinhCity;
        else if(city == "HongKong") return HongKong;
        else if(city == "Istanbul") return Istanbul;
        else if(city == "Jakarta") return Jakarta;
        else if(city == "Johannesburg") return Johannesburg;
        else if(city == "Karachi") return Karachi;
        else if(city == "Khartoum") return Khartoum;
        else if(city == "Kinshasa") return Kinshasa;
        else if(city == "Kolkata") return Kolkata;
        else if(city == "Lagos") return Lagos;
        else if(city == "Lima") return Lima;
        else if(city == "London") return London;
        else if(city == "LosAngeles") return LosAngeles;
        else if(city == "Madrid") return Madrid;
        else if(city == "Manila") return Manila;
        else if(city == "MexicoCity") return MexicoCity;
        else if(city == "Miami") return Miami;
        else if(city == "Milan") return Milan;
        else if(city == "Montreal") return Montreal;
        else if(city == "Moscow") return Moscow;
        else if(city == "Mumbai") return Mumbai;
        else if(city == "NewYork") return NewYork;
        else if(city == "Osaka") return Osaka;
        else if(city == "Paris") return Paris;
        else if(city == "Riyadh") return Riyadh;
        else if(city == "SanFrancisco") return SanFrancisco;
        else if(city == "Santiago") return Santiago;
        else if(city == "SaoPaulo") return SaoPaulo;
        else if(city == "Seoul") return Seoul;
        else if(city == "Shanghai") return Shanghai;
        else if(city == "StPetersburg") return StPetersburg;
        else if(city == "Sydney") return Sydney;
        else if(city == "Taipei") return Taipei;
        else if(city == "Tehran") return Tehran;
        else if(city == "Tokyo") return Tokyo;
        else if(city == "Washington") return Washington;

     return Algiers;
}
