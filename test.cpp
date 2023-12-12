#include <iostream>

#include "PokeCPP.h"

int main() {
    auto pokemon = getPokemon("pikachu");

    std::cout << pokemon.name << std::endl;
    std::cout << pokemon.abilities[0].ability.name << std::endl;
    return 0;
}