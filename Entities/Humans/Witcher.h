#ifndef WITCHER_H
#define WITCHER_H

using std::cerr;

#include <string>
using std::getline;
using std::to_string;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::istringstream;


#include "Human.h"
#include "../../Spells/Signs/Igni.h"



struct Signs {
    Igni * igni;
};

class Witcher: public Human {
    friend ostream &operator<< (ostream &out, const Witcher &witcher);
public:
    Witcher();
    Witcher(string name,
        int age=200,
        double coins=200, 
        int level = AUTO,
        string category="E");
    Witcher(const Witcher &other_witcher);
    ~Witcher();

    inline void setIs_close_to_chest(bool is_close_to_chest) { this->is_close_to_chest = is_close_to_chest; };

    inline bool getIs_close_to_chest() const { return is_close_to_chest; }

    void load_inventory(string file_name_swords="./save-files/config-witcher/config_swords.txt", 
                        string file_name_armors="./save-files/config-witcher/config_armors.txt");
    void save_inventory(string file_name_swords="./save-files//config-witcher/config_swords.txt", 
                        string file_name_armors="./save-files/config-witcher/config_armors.txt");

    void store_item(int item_type, int item_index);
    void unstore_item(string item_name);
    void print_personal_chest() const;

    void update_atributes();

    // simply attack one entity
    void attack(Entity &entity, int attack_option = UNARMED, int technique = 0);
    // attacks one or more entities
    /*
    void attack(vector<Entity*> &entities, 
                int entity_index = 0, 
                int attack_option = UNARMED, 
                int attack_type = 0);
    */

    const Witcher &operator=(const Witcher &);
    bool operator==(const Witcher &other_witcher) const;
    bool operator!=(const Witcher &other_witcher) const;
    bool operator!() const;
private:
    const static int HEALTH_LINEAR_COEF = 10;
    const static int HEALTH_ANGULAR_COEF = 5;
    
    const static int STAMINA_LINEAR_COEF = 10;
    const static int STAMINA_ANGULAR_COEF = 5;

    Signs signs;

    bool is_close_to_chest;
    map<string, Item*> personal_chest;

    const static int WITCHER_ATTACK_COST = 10;
    const static int MAX_WITCHER_DAMAGE = 10;
    const static int MIN_WITCHER_DAMAGE = 7;
    //static int player_level;
};

#endif // WITCHER_H
