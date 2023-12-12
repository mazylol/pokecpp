#include "PokeCPP.h"

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <sstream>

Pokemon getPokemon(const std::string &name) {
    curlpp::Easy request;
    request.setOpt(new curlpp::options::Url("https://pokeapi.co/api/v2/pokemon/" + name + "/"));
    std::ostringstream response;
    response << request;

    auto text = response.str();

    return Pokemon(text);
}