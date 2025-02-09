#include <iostream>
#include <string>

#include "Human.h"

using std::cout;

Human::Human() {
    //cout << "Creating a new Human...\n";
    name = "Peasant";
    age = 30;
    coins = 50.00;

    category = CATEGORIES[0];
    level = 0;
    xp = 0;

    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);

    equipped.steel_sword = 0;
    equipped.armor = 0;

    is_stunned = false;

    date_of_birth = Date(1, 1, 1000 - age);

    update_all_resistances();
    update_all_weaknesses();
}

Human::Human(string name, 
            int age, 
            double coins, 
            int level,
            string category) {
                
    setName(name);
    setAge(age);
    setCoins(coins);

    setCategory(category);

    if (level == AUTO)
        level = Entity::getGlobal_danger();

    setLevel(level);
    setXp(0);
    update_atributes();
    life_regen(max_health);
    stamina_regen(max_stamina);


    equipped.steel_sword = new Sword();
    equipped.armor = new Armor();

    is_stunned = false;

    date_of_birth = Date(1, 1, 1000 - age);

    update_all_resistances();
    update_all_weaknesses();
}

Human::Human(const Human &other_human) : Entity(other_human) {
    //cout << "Copying Human...\n";

    if (other_human.equipped.steel_sword == 0) equipped.steel_sword = 0;
    else equipped.steel_sword = new Sword(*other_human.equipped.steel_sword);

    if (other_human.equipped.armor == 0) equipped.armor = 0;
    else equipped.armor = new Armor(*other_human.equipped.armor);

}

Human::~Human() {
    //cout << "Destroying Human...\n";
    delete equipped.steel_sword;
    delete equipped.armor;
}

void Human::equip_item(int item_type, int item_index) {
    if (item_type == SWORD) {
        if (item_index < 0 || item_index >= inventory.swords.size()) {
            cout << "Invalid sword index.\n";
            return;
        }
        if (equipped.steel_sword != 0) {
            cout << "Unequipped " << *equipped.steel_sword << ".\n";
            unequip_item(item_type);
        }
        equipped.steel_sword = new Sword(*inventory.swords[item_index]);
        cout << "Equipped " << *equipped.steel_sword << ".\n";
        delete inventory.swords[item_index];
        inventory.swords.erase(inventory.swords.begin() + item_index);
    }
    else if (item_type == ARMOR) {
        if (item_index < 0 || item_index >= inventory.armors.size()) {
            cout << "Invalid armor index.\n";
            return;
        }
        if (equipped.armor != 0) {
            cout << "Unequipped " << *equipped.armor << ".\n";
            unequip_item(item_type);
        }
        equipped.armor = new Armor(*inventory.armors[item_index]);
        cout << "Equipped " << *equipped.armor << ".\n";
        delete inventory.armors[item_index];
        inventory.armors.erase(inventory.armors.begin() + item_index);
        update_all_resistances();
    }
    else {
        cout << "Item type not recognized.\n";
    }
}

void Human::unequip_item(int item_type) {
    if (item_type == SWORD) {
        if (equipped.steel_sword == 0) {
            cout << "No sword equipped.\n";
            return;
        }
        add_item(*equipped.steel_sword);
        equipped.steel_sword = 0;
    }
    else if (item_type == ARMOR) {
        if (equipped.armor == 0) {
            cout << "No armor equipped.\n";
            return;
        }
        add_item(*equipped.armor);
        equipped.armor = 0;
        update_all_resistances();
    }
    else {
        cout << "Item type not recognized.\n";
    }
}

void Human::print_equipped_items() {
    cout << "==========Equipped Items==========\n";
    bool check_if_empty = true;

    if (equipped.steel_sword != 0) {
        cout << "==========Steel Sword==========\n";
        cout << *equipped.steel_sword << "\n";
        check_if_empty = false;
    }
    
    cout << "==========Armor==========\n";
    if (equipped.armor != 0) {
        cout << *equipped.armor << "\n";
        check_if_empty = false;
    }

    if (check_if_empty) cout << "None\n";
}

void Human::update_all_resistances() {
    if (equipped.armor != 0) {
        map<string, int> defenses_buffer = equipped.armor->use();
        setTotal_physical_resistance(defenses_buffer["physical_defense"]);
        setTotal_fire_resistance(defenses_buffer["fire_defense"]);
        setTotal_poison_resistance(defenses_buffer["poison_defense"]);
        setTotal_ice_resistance(defenses_buffer["ice_defense"]);
        setTotal_silver_resistance(defenses_buffer["silver_defense"]);
    }
    else {
        setTotal_physical_resistance(0);
        setTotal_fire_resistance(0);
        setTotal_poison_resistance(0);
        setTotal_ice_resistance(0);
        setTotal_silver_resistance(0);
    }
}

void Human::update_all_weaknesses() {
    physical_weakness = 1;
    fire_weakness = 1;
    poison_weakness = 1;
    ice_weakness = 1;
    silver_weakness = 0;
}

void Human::level_up() {
    level++;
    cout << "Level up! " << name << " is now level " << this->level << ".\n";
    Entity::update_global_danger(level);

    update_atributes();

    life_regen(max_health);
    stamina_regen(max_stamina);

}

void Human::update_atributes() {
    next_level_xp = NEXT_LEVEL_XP_LINEAR_COEF + NEXT_LEVEL_XP_ANGULAR_COEF * level;
    max_health = HEALTH_LINEAR_COEF + HEALTH_ANGULAR_COEF * level;
    max_stamina = STAMINA_LINEAR_COEF + STAMINA_ANGULAR_COEF * level;
    xp_reward = level * NEXT_LEVEL_XP_ANGULAR_COEF / 2;
}

void Human::receive_damage(int physical_damage, int fire_damage, int poison_damage, int ice_damage, int silver_damage) {
    Entity::receive_damage(physical_damage, fire_damage, poison_damage, ice_damage, silver_damage);
}

void Human::drop_all_items(vector<Item*> &floor_items) {
    // First unequips all items and
    // tests if items are equipped 2 times for not printing
    // the "not equipped" message when dying
    if (equipped.steel_sword != 0) {
        unequip_item(SWORD);
    }
    if (equipped.armor != 0) {
        unequip_item(ARMOR);
    }
    // Calls the Entity drop_loot function
    Entity::drop_all_items(floor_items);
}

ostream &operator<< (ostream &out, const Human &human){
    human.print_info();

    out << "==========Equipped Items==========\n";

    bool check_if_empty = true;

    if (human.equipped.steel_sword != 0) {
        out << "==========Steel Sword==========\n";
        out << *human.equipped.steel_sword << "\n";
        check_if_empty = false;
    }
    
    out << "==========Armor==========\n";
    if (human.equipped.armor != 0) {
        out << *human.equipped.armor << "\n";
        check_if_empty = false;
    }

    if (check_if_empty) out << "None\n";

    return out;
}

const Human &Human::operator=(const Human &other_human) {
    if (this != &other_human) {
        // forma não permitida pela classe abstrata
        //*static_cast< Entity * >( this ) = static_cast< Entity >( other_human );
        // forma sugerida pela IA
        Entity::operator=(other_human);
        if (other_human.equipped.steel_sword == 0) equipped.steel_sword = 0;
        else {
            delete equipped.steel_sword;
            equipped.steel_sword = new Sword(*other_human.equipped.steel_sword);
        }

        if (other_human.equipped.armor == 0) equipped.armor = 0;
        else {
            delete equipped.armor;
            equipped.armor = new Armor(*other_human.equipped.armor);
        }
    }
    return *this;
}

bool Human::operator==(const Human &other_human) const {
    Entity::operator==(other_human);

    // First checks if its empty
    if (equipped.steel_sword == 0 && other_human.equipped.steel_sword != 0) return false;
    if (equipped.steel_sword != 0 && other_human.equipped.steel_sword == 0) return false;
    // Then checks if its equal
    if (equipped.steel_sword != 0 && other_human.equipped.steel_sword != 0) {
        if (*equipped.steel_sword != *other_human.equipped.steel_sword) return false;
    }

    // First checks if its empty
    if (equipped.armor == 0 && other_human.equipped.armor != 0) return false;
    if (equipped.armor != 0 && other_human.equipped.armor == 0) return false;
    // Then checks if its equal
    if (equipped.armor != 0 && other_human.equipped.armor != 0) {
        if (*equipped.armor != *other_human.equipped.armor) return false;
    }

    return true;
}

bool Human::operator!=(const Human &other_human) const {
    return !(*this == other_human);
}

bool Human::operator!() const {
    return Entity::operator!();
}
