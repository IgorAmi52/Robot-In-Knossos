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
        virtual void use(labyrinth::Labyrinth &lab) = 0;
        virtual ItemType get_type() const = 0;
        virtual std::string get_description() const = 0;
    };
    class WarMist : public Item{
    public:
        virtual void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };
    class Sword : public Item{
    public:
        virtual void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };
    class Shield : public Item{
    public:
        virtual void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };
    class Hammer : public Item{
    public:
        virtual void use(labyrinth::Labyrinth &lab) override;
        ItemType get_type() const override;
        std::string get_description() const override;
    };
     Item* get_random_item();
}


#endif
