#include "items.hpp"
#include "utils.hpp"

namespace items {
    Item* get_random_item(){
        int foo = utils::get_random_int(0,3);
        switch (foo) {
            case 0:
                return new WarMist();
            case 1:
                return new Sword();
            case 2:
                return new Shield();
            case 3:
                return new Hammer();
            default:
                return nullptr;
        }
    }
}