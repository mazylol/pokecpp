#ifndef POKECPP_BASE_H
#define POKECPP_BASE_H


#include <iostream>
#include <vector>

#include "nlohmann/json.hpp"

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

                base_experience = object.at("base_experience").get<int>();

                auto form = Form{};
                for (auto& f : object.at("forms")) {
                    form.name = f.at("name").get<std::string>();
                    form.url = f.at("url").get<std::string>();
                    forms.push_back(form);
                }

                auto game_index = GameIndex{};
                for (auto& gi : object.at("game_indices")) {
                    game_index.game_index = gi.at("game_index").get<int>();
                    auto version = Version{};
                    version.name = gi.at("version").at("name").get<std::string>();
                    version.url = gi.at("version").at("url").get<std::string>();
                    game_index.version = version;
                    game_indices.push_back(game_index);
                }

                height = object.at("height").get<int>();

                auto held_item = HeldItem{};
                for (auto& hi : object.at("held_items")) {
                    auto item = Item{};
                    item.name = hi.at("item").at("name").get<std::string>();
                    item.url = hi.at("item").at("url").get<std::string>();
                    held_item.item = item;

                    auto version_detail = VersionDetail{};
                    version_detail.rarity = hi.at("version_details").at(0).at("rarity").get<int>();

                    auto version = Version{};
                    version.name = hi.at("version_details").at(0).at("version").at("name").get<std::string>();
                    version.url = hi.at("version_details").at(0).at("version").at("url").get<std::string>();
                    version_detail.version = version;

                    held_item.version_details.push_back(version_detail);
                    held_items.push_back(held_item);
                }

                id = object.at("id").get<int>();

                is_default = object.at("is_default").get<bool>();

                location_area_encounters = object.at("location_area_encounters").get<std::string>();

                auto move_container = MoveContainer{};
                for (auto& move : object.at("moves")) {
                    auto m = Move{};
                    m.name = move.at("move").at("name").get<std::string>();
                    m.url = move.at("move").at("url").get<std::string>();
                    move_container.move = m;

                    auto version_group_detail = VersionGroupDetail{};
                    version_group_detail.level_learned_at = move.at("version_group_details").at(0).at("level_learned_at").get<int>();

                    auto move_learn_method = MoveLearnMethod{};
                    move_learn_method.name = move.at("version_group_details").at(0).at("move_learn_method").at("name").get<std::string>();
                    move_learn_method.url = move.at("version_group_details").at(0).at("move_learn_method").at("url").get<std::string>();
                    version_group_detail.move_learn_method = move_learn_method;

                    auto version_group = VersionGroup{};
                    version_group.name = move.at("version_group_details").at(0).at("version_group").at("name").get<std::string>();
                    version_group.url = move.at("version_group_details").at(0).at("version_group").at("url").get<std::string>();
                    version_group_detail.version_group = version_group;

                    move_container.version_group_details.push_back(version_group_detail);
                    moves.push_back(move_container);
                }

                name = object.at("name").get<std::string>();

                order = object.at("order").get<int>();

                auto type_container = TypeContainer{};
                for (auto& type : object.at("types")) {
                    type_container.slot = type.at("slot").get<int>();

                    auto type_internal = TypeInternal{};
                    type_internal.name = type.at("type").at("name").get<std::string>();
                    type_internal.url = type.at("type").at("url").get<std::string>();
                    type_container.type = type_internal;

                    types.push_back(type_container);
                }

                species.name = object.at("species").at("name").get<std::string>();
                species.url = object.at("species").at("url").get<std::string>();

                auto back_default = object.at("sprites").at("back_default");
                if (!back_default.is_null()) {
                    sprites.back_default = back_default.get<std::string>();
                }
                auto back_female = object.at("sprites").at("back_female");
                if (!back_female.is_null()) {
                    sprites.back_female = back_female.get<std::string>();
                }
                auto back_shiny = object.at("sprites").at("back_shiny");
                if (!back_shiny.is_null()) {
                    sprites.back_shiny = back_shiny.get<std::string>();
                }
                auto back_shiny_female = object.at("sprites").at("back_shiny_female");
                if (!back_shiny_female.is_null()) {
                    sprites.back_shiny_female = back_shiny_female.get<std::string>();
                }
                auto front_default = object.at("sprites").at("front_default");
                if (!front_default.is_null()) {
                    sprites.front_default = front_default.get<std::string>();
                }
                auto front_female = object.at("sprites").at("front_female");
                if (!front_female.is_null()) {
                    sprites.front_female = front_female.get<std::string>();
                }
                auto front_shiny = object.at("sprites").at("front_shiny");
                if (!front_shiny.is_null()) {
                    sprites.front_shiny = front_shiny.get<std::string>();
                }
                auto front_shiny_female = object.at("sprites").at("front_shiny_female");
                if (!front_shiny_female.is_null()) {
                    sprites.front_shiny_female = front_shiny_female.get<std::string>();
                }

                auto stat_container = StatContainer{};
                for (auto& stat : object.at("stats")) {
                    stat_container.base_stat = stat.at("base_stat").get<int>();
                    stat_container.effort = stat.at("effort").get<int>();

                    auto stat_internal = Stat{};
                    stat_internal.name = stat.at("stat").at("name").get<std::string>();
                    stat_internal.url = stat.at("stat").at("url").get<std::string>();
                    stat_container.stat = stat_internal;

                    stats.push_back(stat_container);
                }

                weight = object.at("weight").get<int>();
            } catch (const std::exception &e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }
    };
};


#endif //POKECPP_BASE_H
