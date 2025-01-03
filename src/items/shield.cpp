#include "items.hpp"
#include <string>

namespace items {
    void Shield::use(labyrinth::Labyrinth &lab) {
        lab.set_shield(1);
    }
    ItemType Shield::get_type() const {
        return ItemType::SHIELD;
    }
    std::string Shield::get_description() const {
        return "Shield: Protects you from the Minotaur";
    }
}