#include "Simulation.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>

Simulation::Simulation()
{
    bunnies.reserve(100);

    bunnies.emplace_back("Fluffy", "white", Gender::Female, 0);
    bunnies.back().announceBirth();

    bunnies.emplace_back("TipTap", "brown", Gender::Male, 0);
    bunnies.back().announceBirth();

    bunnies.emplace_back("Gina", "grey", Gender::Female, 0);
    bunnies.back().announceBirth();

    bunnies.emplace_back("Tamburino", "black", Gender::Male, 0);
    bunnies.back().announceBirth();

    bunnies.emplace_back("Giulio Cesare", "gold", Gender::Radioactive, 0);
    bunnies.back().announceBirth();
}

int Simulation::getYear() const
{
    return year;
}

int Simulation::getBunnyCount() const
{
    return static_cast<int>(bunnies.size());
}

void Simulation::runOneTurn()
{
    year += 1;
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "           BUNNY VALLEY\n";
    std::cout << "               YEAR " << year << '\n';
    std::cout << "========================================\n\n";

    // Aging

    std::cout << "--- Aging ---\n";
    for (Bunny& b : bunnies) {
        b.aging();
    }

    // Find adult male bunny and adult female bunnies for breeding
    bool foundMale = false;
    std::vector<std::string> femaleColor;
    for (Bunny& b : bunnies) {
        if (b.getGender() == Gender::Male && b.isAdult()) {
            foundMale = true;
        }
        if (b.getGender() == Gender::Female && b.isAdult()) {
            femaleColor.push_back(b.getColor());
        }
    }

    // Breeding
    std::cout << "--- Births ---\n";
    if (foundMale) {
        for (size_t i = 0; i < femaleColor.size(); i++) {
            int nameIndex = rand() % static_cast<int>(nameBank.size());
            std::string namePick = nameBank[nameIndex];
            int genderPick = rand() % 2;
            Gender babyGender = (genderPick == 0) ? Gender::Male : Gender::Female;
            bunnies.emplace_back(namePick, femaleColor[i], babyGender, 0);
            bunnies.back().announceBirth();
        }
    }

    // Count vampire bunnies
    int findVampireBunnies = 0;
    for (Bunny& b : bunnies) {
        if (b.isRadioactive() && b.getAge() >= 2) {
            findVampireBunnies++;
        }
    }

    // Collect  (non-radioactive) conversion targets
    std::vector<int> collectEligibleBunnies{};
    for (int i = 0; i < static_cast<int>(bunnies.size()); i++) {
        if (!bunnies[i].isRadioactive() && bunnies[i].isAdult()) {
            collectEligibleBunnies.push_back(i);
        }
    }

    // Convert - before conversion, every mutant rolls their chance and if chance > 15, an eligible bunny picked randomly is infected
    std::cout << "--- Infections ---\n";
    for (int i = 0; i < findVampireBunnies; i++)
    {
        if (collectEligibleBunnies.empty())
        {
            break;
        }

        int infectionChance = rand() % 100;

        if (infectionChance < 30)
        {
            int pickIndex = rand() % static_cast<int>(collectEligibleBunnies.size());
            int pickBunny = collectEligibleBunnies[pickIndex];

            bunnies[pickBunny].gender = Gender::Radioactive;
            bunnies[pickBunny].canGetPregnant = false;
            bunnies[pickBunny].canMakeVampireBunny = true;
            bunnies[pickBunny].announceInfection();

            collectEligibleBunnies.erase(collectEligibleBunnies.begin() + pickIndex);
        }
    }
        

    // Deaths (old age)
    std::cout << "--- Deaths ---\n";
    for (auto it = bunnies.begin(); it != bunnies.end(); )
    {
        if (it->isTooOld())
        {
            it->announceDeath("old age");
            it = bunnies.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Food shortage
    if (bunnies.size() > 1000) {
        int half = bunnies.size() / 2;
        std::vector<int> pickHalfBunnies{};
        for (int i = 0; i < static_cast<int>(bunnies.size()); i++) {
            pickHalfBunnies.push_back(i);
        }
        std::vector<int> condemnedBunnies{};
        for (int i = 0; i < half; i++) {
            int pickIndex = rand() % static_cast<int>(pickHalfBunnies.size());
            int pickBunny = pickHalfBunnies[pickIndex];
            condemnedBunnies.push_back(pickBunny);
            pickHalfBunnies.erase(pickHalfBunnies.begin() + pickIndex);
        }
        std::sort(condemnedBunnies.begin(), condemnedBunnies.end(), std::greater<int>());
        for (int i = 0; i < static_cast<int>(condemnedBunnies.size()); i++)
        {
            int deadIndex = condemnedBunnies[i];
            bunnies[deadIndex].announceDeath("food shortage");
            bunnies.erase(bunnies.begin() + deadIndex);
        }
    }

    // Display all bunnies' details, sorted by age
    std::sort(bunnies.begin(), bunnies.end(), [](const Bunny& a, const Bunny& b) {
        return a.getAge() < b.getAge();
        });
    std::cout << "Current Bunny Population\n";
    std::cout << "-------------------------------------------------------------\n";

    std::cout << std::left
        << std::setw(20) << "Name"
        << std::setw(6) << "Age"
        << std::setw(15) << "Color"
        << std::setw(15) << "Gender" << '\n';

    std::cout << "-------------------------------------------------------------\n";

    for (const Bunny& b : bunnies)
    {
        std::cout << b << '\n';
    }

    std::cout << "-------------------------------------------------------------\n";
}

