# Bunny Village Simulation — C++

## Overview

A console-based, turn-based population simulation developed in C++ to practice object-oriented programming, dynamic memory management, and rule-based simulation systems.

The project models a population of bunnies whose characteristics and lifecycles evolve over time through reproduction, aging, radioactive infection, mortality, and food shortages.

## Features

### Entity Management

- Each bunny has individual attributes, including name, age, color, and gender or radioactive classification.
- The simulation maintains a dynamically allocated population using `std::vector<Bunny*>`.
- Individual bunnies encapsulate lifecycle-related operations and state checks.

### Reproduction

- Bunnies reach reproductive adulthood at age 2.
- Each eligible adult female produces one offspring per turn if at least one adult male exists.
- Newborn bunnies inherit their mother's color.
- Offspring receive a randomly selected name and a randomly assigned male or female gender.
- Radioactive bunnies cannot reproduce.

### Radioactive Infection

- Each radioactive bunny has a 30% chance per turn to infect another bunny.
- Infection targets are selected randomly from the non-radioactive population.
- Each target can be infected only once, as infected bunnies are removed from the eligible target pool.
- Infected bunnies become radioactive and follow the corresponding lifecycle rules.

### Aging and Mortality

- Every bunny ages by one year per turn.
- Regular bunnies die when their age exceeds 10 years.
- Radioactive bunnies die when their age exceeds 50 years.
- When the population exceeds 1,000, a food shortage removes half of the remaining population, selected randomly.

### Simulation Reporting

- Displays births, infections, aging, and deaths.
- Tracks the current simulation year and population size.
- Sorts the surviving population by age.
- Displays entity information in a formatted console table.

## Technical Implementation

The project separates individual entity behavior from simulation management:

- **`Bunny`** defines individual entity attributes, lifecycle checks, and reporting methods.
- **`Simulation`** coordinates the population and executes the different simulation phases.
- **Dynamic allocation:** Bunny objects are allocated on the heap and managed through pointers.
- **Pointer manipulation:** Population removal uses iterator-based erasure and index management.
- **Randomized mechanics:** Reproduction and infection use random selection to introduce variation between simulation runs.
- **Operator overloading:** A custom `operator<<` formats bunny information for console output.

## Concepts Practiced

- Object-oriented programming and encapsulation
- Dynamic memory allocation and resource ownership
- Pointers and object lifetimes
- STL containers and algorithms
- Random number generation
- Rule-based state transitions
- Entity lifecycle management
- Iterators and container modification

## Learning Objectives

The project provided an opportunity to explore concepts applicable to gameplay programming, particularly entity management, probabilistic events, and simulation systems.



