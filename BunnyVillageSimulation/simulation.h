#pragma once


#include "Bunny.h"
#include <vector>
#include <string>


class Simulation
{
private:

    int year = 0;

    std::vector<Bunny*> bunnies;

    std::vector<std::string> nameBank{
        "Clover",
        "Yuzu",
        "Basilico",
        "Onigiri",
        "NafNaf",
        "Cicerone",
        "Leo",
        "Biscotto",
        "Flopsy",
        "Coco",
        "Peanut",
        "BunBun", 
        "Carota",
        "Fiji", 
        "Miso",
        "Carbone",
        "Batuffolo",
        "Lilo"

    };


public:

    Simulation();

    ~Simulation();

Simulation(const Simulation&) = delete;
Simulation& operator=(const Simulation&) = delete;


    int getYear() const;

    int getBunnyCount() const;

    void runOneTurn();




    
};
