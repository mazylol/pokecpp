#ifndef POKECPP_POKECPP_H
#define POKECPP_POKECPP_H

#include <string>

#include "../src/pokemon/export.h"

Pokemon getPokemon(const std::string &name);

class PokeCPP : public Pokemon {

};

#endif //POKECPP_POKECPP_H
