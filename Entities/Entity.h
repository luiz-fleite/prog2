#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

using std::cout;
using std::string;

class Entity {
public:
    Entity();
    Entity(const Entity &other_entity);
    ~Entity();

    inline string getName() const{ return name; }
    inline int getAge() const{ return age; }
    inline double getCoins() const { return coins; }
    inline int getHealth() const { return health; }
    inline int getStamina() const { return stamina; }
    inline string getCategory() const { return category; }
    inline int getLevel() const { return level; }
    inline int getTotal_defense() const { return total_defense; }
    inline bool getIs_stunned() const { return is_stunned; }

    void setName(string name);
    void setAge(int age);
    void setCoins(double coins);
    void setHealth(int health);
    void setStamina(int stamina);
    void setCategory(string category);
    void setLevel(int level);
    void setTotal_defense(int total_defense);
    inline void setIs_stunned(bool is_stunned) { this->is_stunned = is_stunned; }

    void print_info() const;
    virtual void update_total_defense() = 0;
    virtual void attack(Entity &) = 0;
    virtual void receive_damage(int);
    virtual void talk();
    virtual void walk();
protected:
    string name;
    int age;
    double coins;
    int health;
    int stamina;
    string category;
    int level;
    int total_defense;
    bool is_stunned = false;

    const static string CATEGORIES[7];
    const static int MAX_NAME_SIZE = 20;
};

inline void Entity::talk() { cout << name << " says: \"Hello!\"\n"; }

inline void Entity::walk() { cout << name << " is walking.\n"; }


#endif // ENTITY_H
