#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include "labyrinth.hpp"
namespace items {
    enum class ItemType {
        WAR_MIST,
        SWORD,
        SHIELD,
        HAMMER
    };
   
    class Item{
    public:
        virtual ~Item() = default;

        // Uses the item on the given labyrinth.
        virtual void use(labyrinth::Labyrinth &lab) = 0;

        // Gets the type of the item.
        virtual ItemType get_type() const = 0;

        // Gets the description of the item.
        virtual std::string get_description() const = 0;
    };

    class WarMist : public Item{
    public:
        void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };

    class Sword : public Item{
    public:
        void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };

    class Shield : public Item{
    public:
        void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };

    class Hammer : public Item{
    public:
        void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };

    // Gets a random item.
    Item* get_random_item();
}

#endif
