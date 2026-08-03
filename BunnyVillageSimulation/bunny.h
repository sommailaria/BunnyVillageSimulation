#pragma once
#ifndef BUNNY_H
#define BUNNY_H

#include <iostream>
#include <string>
#include <iomanip>


enum class Gender { Male, Female, Radioactive };


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

    Bunny(const std::string& givenName,
        const std::string& birthColor,
        const Gender& birthGender,
        const int& ageAtBirth);


    void announceBirth() const;

    void aging();

    void announceInfection() const;

    void announceDeath(const std::string& cause) const;


    std::string getColor() const;

    Gender getGender() const;

    bool isAdult() const;

    bool isRadioactive() const;

    int getAge() const;

    std::string getName() const;


    bool isTooOld() const;


    ~Bunny() = default;
};


std::string genderToString(Gender g);


std::ostream& operator<<(std::ostream& os, const Bunny& b);


#endif
