#include "items.hpp"
#include <string>

namespace items {
    void Sword::use(labyrinth::Labyrinth &lab) {
        lab.set_sword(1);
    }
    ItemType Sword::get_type() const {
        return ItemType::SWORD;
    }
    std::string Sword::get_description() const {
        return "Sword: Allows you to kill the Minotaur";
    }
}