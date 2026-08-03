#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

enum class Gender { Male, Female, Radioactive };

class Simulation;

class Bunny {
    friend class Simulation;
private:
    std::string name;
    std::string color;
    Gender gender;
    int age;
    bool canGetPregnant;
    bool canMakeVampireBunny;
public:
    Bunny(const std::string& givenName, const std::string& birthColor, const Gender& birthGender, const int& ageAtBirth)
    {
        color = birthColor;
        name = givenName;
        gender = birthGender;
        age = ageAtBirth;
        canGetPregnant = (gender == Gender::Female);
        canMakeVampireBunny = (gender == Gender::Radioactive);
    }

    void announceBirth() const { std::cout << "A new bunny is born! Their name is " << name << ". \n"; }
    void aging() { age += 1; std::cout << name << " is now " << age << " years old. \n"; }
    void announceInfection() const { std::cout << name << " has been infected and is now a vampire bunny! \n"; }
    void announceDeath(const std::string& cause) const { std::cout << name << " has died of " << cause << ". \n"; }

    ~Bunny() {}

    // Getters useful for breeding, conversion, death checks, and printing
    std::string getColor() const { return color; }
    Gender getGender() const { return gender; }
    bool isAdult() const { return age >= 2; }
    bool isRadioactive() const { return gender == Gender::Radioactive; }
    int getAge() const { return age; }
    std::string getName() const { return name; }

    // Death conditions (old age)
    bool isTooOld() const
    {
        if (isRadioactive())
        {
            return age > 50;
        }
        return age > 10;
    }
};

// Functions to print bunny details, sorted by age
std::string genderToString(Gender g)
{
    switch (g)
    {
    case Gender::Male: return "Male";
    case Gender::Female: return "Female";
    case Gender::Radioactive: return "Radioactive";
    }
    return "Unknown";
}

std::ostream& operator<<(std::ostream& os, const Bunny& b)
{
    os << b.getName() << ", age " << b.getAge() << ", " << b.getColor()
        << ", " << genderToString(b.getGender());
    return os;
}

class Simulation {
private:
    int year = 0;
    std::vector<Bunny> bunnies;
public:
    Simulation()
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
        bunnies.emplace_back("Lila", "dotted", Gender::Female, 0);
        bunnies.back().announceBirth();
        bunnies.emplace_back("Fiji", "cream", Gender::Female, 0);
        bunnies.back().announceBirth();
    }

    std::vector<std::string> nameBank{ "Clover", "Yuzu", "Basil", "Onigiri", "NafNaf", "Cicero", "Leo", "Biscotto", "Flopsy", "Coco", "Peanut", "BunBun" };

    int getYear() const { return year; }
    int getBunnyCount() const { return static_cast<int>(bunnies.size()); }

    void runOneTurn()
    {
        year += 1;
        std::cout << "Bunny Valley is now on Year " << year << ".\n";

        // Aging
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
            if (b.isRadioactive() && b.isAdult()) {
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

        // Convert
        for (int i = 0; i < findVampireBunnies; i++) {
            if (collectEligibleBunnies.size() == 0) {
                break;
            }
            int pickIndex = rand() % static_cast<int>(collectEligibleBunnies.size());
            int pickBunny = collectEligibleBunnies[pickIndex];
            bunnies[pickBunny].gender = Gender::Radioactive;
            bunnies[pickBunny].canGetPregnant = false;
            bunnies[pickBunny].canMakeVampireBunny = true;
            bunnies[pickBunny].announceInfection();
            collectEligibleBunnies.erase(collectEligibleBunnies.begin() + pickIndex);
        }

        // Deaths (old age)
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
        std::cout << "Here are the bunnies currently living in Bunny Valley: \n";
        for (const Bunny& b : bunnies) {
            std::cout << b << "\n";
        }
    }
};

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