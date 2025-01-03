#include "items.hpp"
#include <string>

namespace items {
    void WarMist::use(labyrinth::Labyrinth &lab) {
        lab.set_visibility_limit(1);
    }

    ItemType WarMist::get_type() const {
        return ItemType::WAR_MIST;
    }

    std::string WarMist::get_description() const {
        return "War Mist: Limits your visibility";
    }
}