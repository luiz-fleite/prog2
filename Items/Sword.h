#ifndef SWORD_H
#define SWORD_H

#include <string>

using std::ostream;
using std::string;

class Sword {
    friend ostream &operator<< (ostream &out, const Sword &sword);
public:
    Sword();
    Sword(string name, int damage=10);
    Sword(const Sword &other_sword);
    ~Sword();
    
    inline string getName() const { return name; }
    inline int getDamage() const { return damage; }
    //inline string getCategory() const { return category; }
    
    void setName(string name);
    void setDamage(int damage);
    //void setCategory(string category);

private:
    string name;
    int damage;
    //string category;

    //const static string CATEGORIES[7];
    const static int MAX_NAME_SIZE = 20;
};

#endif // SWORD_H
