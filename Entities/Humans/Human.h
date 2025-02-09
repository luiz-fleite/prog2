#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string>

#include "../Entity.h"

using std::ostream;


enum attack_options {
    UNARMED = 0,
    // Weapons
    STEEL_SWORD = 1,
    SILVER_SWORD = 2,
    CROSSBOW = 3,
    // Signs
    IGNI = 4
};


struct equipped_items {
    Sword* steel_sword; 
    Armor* armor;
};

class Human: public Entity {
    friend ostream &operator<< (ostream &out, const Human &human);
public:
    Human();
    Human(string name,
        int age = 30, 
        double coins = 100, 
        int level = AUTO,
        string category = "E");
    Human(const Human &other_human);
    ~Human();

    virtual void equip_item(int item_type, int item_index);
    virtual void unequip_item(int item_type);
    virtual void print_equipped_items();

    virtual void level_up();
    virtual void update_atributes();
    virtual void update_all_resistances();
    virtual void update_all_weaknesses();
    
    virtual void attack(Entity &entity, int weapon_type = UNARMED, int technique = 0);
    virtual void receive_damage(int physical_damage, 
                                int fire_damage = 0, 
                                int poison_damage = 0, 
                                int ice_damage = 0, 
                                int silver_damage = 0);

    virtual void drop_all_items(vector<Item*> &floor_items);

    const Human &operator=(const Human &);
    bool operator==(const Human &other_human) const;
    bool operator!=(const Human &other_human) const;
    bool operator!() const;
protected:
    equipped_items equipped;
private:
    const static int HEALTH_LINEAR_COEF = 5;
    const static int HEALTH_ANGULAR_COEF = 3;

    const static int STAMINA_LINEAR_COEF = 5;
    const static int STAMINA_ANGULAR_COEF = 3;
};

inline void Human::attack(Entity &entity, int weapon_type, int technique) { cout << "Human is too weak and afraid to attack " << entity.getName() << ".\n"; }

#endif // HUMAN_H
