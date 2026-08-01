#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

enum class Gender {
	Male,
	Female,
	Radioactive
};


class Simulation;

class Bunny
{

	friend class Simulation;

private:
	std::string name;
	std::string color;
	Gender gender;
	int age;
	bool canGetPregnant;
	bool canMakeVampireBunny;

public:
	// constructor
	Bunny(const std::string& givenName, const std::string& birthColor, const Gender& birthGender, const int& ageAtBirth)
	{
		color = birthColor;
		name = givenName;
		gender = birthGender;
		age = ageAtBirth;
		canGetPregnant = (gender == Gender::Female);
		canMakeVampireBunny = (gender == Gender::Radioactive);
	}

	void announceBirth() const
	{
		std::cout << "A new bunny is born! Their name is " << name << ". \n";
	}
	void aging()
	{
		age += 1;
		std::cout << name << " is now " << age << " years old. \n";
	}

	// Destructor
	
	     ~Bunny()
	{
		std::cout << "Bunny " << name << " has died! \n";
	}
	

	// Getters for bunny data useful for breeding and turning bunnies
	std::string getColor() const { return color; }
	Gender getGender() const { return gender; }
	bool isAdult() const { return age >= 2; }
	bool isRadioactive() const { return gender == Gender::Radioactive; };

};



class Simulation
{
private:
	int year = 0;
	std::vector<Bunny> bunnies;
public:
	Simulation()
	{
		// Creating the 5 starter bunnies
		bunnies.reserve(100);
		bunnies.emplace_back("Fluffy", "white", Gender::Female, 0);
		bunnies.back().announceBirth();
		bunnies.emplace_back("TipTap", "brown", Gender::Female, 0);
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

	// Name pool 
	std::vector<std::string> nameBank{ "Clover", "Yuzu", "Basil", "Onigiri", "NafNaf", "Cicero", "Leo", "Biscotto", "Flopsy", "Coco", "Peanut", "BunBun" };

	// Getting current year and number of bunnies 
	int getYear() const { return year; }
	int getBunnyCount() const { return bunnies.size(); }

	void runOneTurn()
	{
		year += 1;
		std::cout << "--- Year " << year << " ---\n";
		for (Bunny& b : bunnies)
		{
			b.aging();
		}

		// Find males and collect mom color
		bool foundMale{};
		std::vector<std::string> femaleColor;
		for (Bunny& b : bunnies)
		{
			if (b.getGender() == Gender::Male && b.isAdult() && !b.isRadioactive())
			{
				foundMale = true;
			}
			if (b.getGender() == Gender::Female && b.isAdult() && !b.isRadioactive())
			{
				femaleColor.push_back(b.getColor());
			}
		}

		// Start breeding
		if (foundMale)
		{
			for (int i = 0; i < femaleColor.size(); i++)
			{
				int nameIndex = rand() % nameBank.size();
				std::string namePick = nameBank[nameIndex];
				int genderPick = rand() % 2;
				Gender babyGender;
				if (genderPick == 0) { babyGender = Gender::Male; }
				else { babyGender = Gender::Female; }
				bunnies.emplace_back(namePick, femaleColor[i], babyGender, 0);
				bunnies.back().announceBirth();
			}
		}

		// Find bunny who can infect other bunnies

		int findVampireBunnies{};

		for (Bunny& b : bunnies)
		{
			if (b.isRadioactive())
			{
				findVampireBunnies++;
			}
		}

		if (findVampireBunnies >= 1)
		{
			int convertedCount{};

			for (Bunny& b : bunnies)
			{

				if (!b.isRadioactive())
				{


					b.gender = Gender::Radioactive;
					b.canGetPregnant = false;
					b.canMakeVampireBunny = true;
					convertedCount++;

					if (convertedCount == findVampireBunnies)
					{
						
						std::cout << b.name << " was turned into a Vampire Bunny! \n";
						break;
					}


				}

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
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	newGame.runOneTurn();
	return 0;
}