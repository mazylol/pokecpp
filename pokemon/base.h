#ifndef POKECPP_BASE_H
#define POKECPP_BASE_H


#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>

class Base {
    struct Ability {
        std::string name;
        std::string url;
    };

    struct Abilities {
        Ability ability;
        bool is_hidden;
        int slot;
    };

    struct Form {
        std::string name;
        std::string url;
    };

    struct Version {
        std::string name;
        std::string url;
    };

    struct GameIndex {
        int game_index;
        Version version;
    };

    struct Item {
        std::string name;
        std::string url;
    };

    struct VersionDetail {
        int rarity;
        Version version;
    };

    struct HeldItem {
        Item item;
        std::vector<VersionDetail> version_details;
    };

    struct Move {
        std::string name;
        std::string url;
    };

    struct MoveLearnMethod {
        std::string name;
        std::string url;
    };

    struct VersionGroup {
        std::string name;
        std::string url;
    };

    struct VersionGroupDetail {
        int level_learned_at;
        MoveLearnMethod move_learn_method;
        VersionGroup version_group;
    };

    struct MoveContainer {
        Move move;
        std::vector<VersionGroupDetail> version_group_details;
    };

    struct Generation {
        std::string name;
        std::string url;
    };

    struct PastTypeInternal {
        std::string name;
        std::string url;
    };

    struct PastTypeContainer {
        PastTypeInternal type;
        int slot;
    };

    struct PastType {
        Generation generation;
        std::vector<PastTypeContainer> types;
    };

    struct TypeInternal {
        std::string name;
        std::string url;
    };

    struct TypeContainer {
        int slot;
        TypeInternal type;
    };

    struct Species {
        std::string name;
        std::string url;
    };

    struct Sprites {
        std::string back_default;
        std::string back_female;
        std::string back_shiny;
        std::string back_shiny_female;
        std::string front_default;
        std::string front_female;
        std::string front_shiny;
        std::string front_shiny_female;
    };

    struct Stat {
        std::string name;
        std::string url;
    };

    struct StatContainer {
        int base_stat;
        int effort;
        Stat stat;
    };

public:
    struct Pokemon {
        std::vector<Abilities> abilities;
        int base_experience{};
        std::vector<Form> forms;
        std::vector<GameIndex> game_indices;
        int height{};
        std::vector<HeldItem> held_items;
        int id{};
        bool is_default{};
        std::string location_area_encounters;
        std::vector<MoveContainer> moves;
        std::string name;
        int order{};
        std::vector<PastType> past_types;
        std::vector<TypeContainer> types;
        Species species;
        Sprites sprites;
        std::vector<StatContainer> stats;
        int weight{};

        explicit Pokemon(const std::string& json) {
            try {
                nlohmann::json object = nlohmann::json::parse(json);

                auto abs = Abilities{};
                for (auto& ability : object.at("abilities")) {
                    abs.ability.name = ability.at("ability").at("name").get<std::string>();
                    abs.ability.url = ability.at("ability").at("url").get<std::string>();
                    abs.is_hidden = ability.at("is_hidden").get<bool>();
                    abs.slot = ability.at("slot").get<int>();
                    abilities.push_back(abs);
                }

                name = object.at("name").get<std::string>();
            } catch (const std::exception &e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }
    };
};


#endif //POKECPP_BASE_H
