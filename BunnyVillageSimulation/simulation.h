#pragma once


#include "Bunny.h"
#include <vector>
#include <string>


class Simulation
{
private:

    int year = 0;

    std::vector<Bunny> bunnies;

    std::vector<std::string> nameBank{
        "Clover",
        "Yuzu",
        "Basil",
        "Onigiri",
        "NafNaf",
        "Cicero",
        "Leo",
        "Biscotto",
        "Flopsy",
        "Coco",
        "Peanut",
        "BunBun"
    };


public:

    Simulation();

    int getYear() const;

    int getBunnyCount() const;

    void runOneTurn();




    
};
