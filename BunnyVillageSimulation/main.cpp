#include "Simulation.h"

#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "-------------- Bunny Valley --------------------" << "\n";
    std::cout << " Starting the simulation..." << "\n";
    std::cout << std::endl;

    Simulation newGame;
    
    while (newGame.getBunnyCount() > 0)
    {
        newGame.runOneTurn();

        if (newGame.getBunnyCount() > 0)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }

    std::cout << "\nAll bunnies have gone extinct after "
        << newGame.getYear() << " years.\n";




    return 0;
}
