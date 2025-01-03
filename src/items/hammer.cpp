#include "items.hpp"
#include <string>

namespace items {
    void Hammer::use(labyrinth::Labyrinth &lab) {
        lab.set_hammer(1);
    }
    ItemType Hammer::get_type() const {
        return ItemType::HAMMER;
    }
    std::string Hammer::get_description() const {
        return "Hammer: Allows you to go thru walls";
    }
}