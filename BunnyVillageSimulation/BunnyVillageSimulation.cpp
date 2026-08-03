#include <iostream>
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

    ~Bunny() {}   // teardown only — all death messaging goes through announceDeath()

    // Getters useful for breeding, conversion, and death checks
    std::string getColor() const { return color; }
    Gender getGender() const { return gender; }
    bool isAdult() const { return age >= 2; }
    bool isRadioactive() const { return gender == Gender::Radioactive; }
    bool isTooOld() const
    {
        if (isRadioactive())
        {
            return age > 50;
        }
        return age > 10;
    }
};

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
        std::cout << "--- Year " << year << " ---\n";

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
            if (b.isRadioactive()) {
                findVampireBunnies++;
            }
        }

        // Collect eligible (non-radioactive) conversion targets
        std::vector<int> collectEligibleBunnies{};
        for (int i = 0; i < static_cast<int>(bunnies.size()); i++) {
            if (!bunnies[i].isRadioactive()) {
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
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "-------------- Bunny Valley --------------------" << "\n";
    std::cout << " Starting the simulation..." << "\n";
    std::cout << std::endl;

    Simulation newGame;
    newGame.runOneTurn();
    newGame.runOneTurn();
    newGame.runOneTurn();
    newGame.runOneTurn();
    newGame.runOneTurn();
    newGame.runOneTurn();
    newGame.runOneTurn();

    return 0;
}