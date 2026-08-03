#include "Bunny.h"

Bunny::Bunny(const std::string& givenName,
    const std::string& birthColor,
    const Gender& birthGender,
    const int& ageAtBirth)
{
    color = birthColor;
    name = givenName;
    gender = birthGender;
    age = ageAtBirth;

    canGetPregnant = (gender == Gender::Female);
    canMakeVampireBunny = (gender == Gender::Radioactive);
}

void Bunny::announceBirth() const
{
    std::cout << "A new bunny is born! Their name is "
        << name << ".\n";
}


void Bunny::aging()
{
    age += 1;
    std::cout << name
        << " is now "
        << age
        << " years old.\n";
}


void Bunny::announceInfection() const
{
    std::cout << name
        << " has been infected and is now a vampire bunny!\n";
}


void Bunny::announceDeath(const std::string& cause) const
{
    std::cout << name
        << " has died of "
        << cause
        << ".\n";
}

std::string Bunny::getColor() const
{
    return color;
}


Gender Bunny::getGender() const
{
    return gender;
}


bool Bunny::isAdult() const
{
    return age >= 2 && !isRadioactive();
}


bool Bunny::isRadioactive() const
{
    return gender == Gender::Radioactive;
}


int Bunny::getAge() const
{
    return age;
}


std::string Bunny::getName() const
{
    return name;
}

bool Bunny::isTooOld() const
{
    if (isRadioactive())
    {
        return age > 50;
    }

    return age > 10;
}

std::string genderToString(Gender g)
{
    switch (g)
    {
    case Gender::Male:
        return "Male";

    case Gender::Female:
        return "Female";

    case Gender::Radioactive:
        return "Radioactive";
    }

    return "Unknown";
}


std::ostream& operator<<(std::ostream& os, const Bunny& b)
{
    os << std::left
        << std::setw(20) << b.getName()
        << std::setw(6) << b.getAge()
        << std::setw(15) << b.getColor()
        << std::setw(15) << genderToString(b.getGender());

    return os;
}