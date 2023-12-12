#ifndef POKECPP_EXPORT_H
#define POKECPP_EXPORT_H

#include "base.h"
#include <string>

class Pokemon : public Base::Pokemon {
public:
    explicit Pokemon(std::string &json) : Base::Pokemon(json) {}
};

#endif //POKECPP_EXPORT_H
