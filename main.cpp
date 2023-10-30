#include <iostream>
#include <string>
#include <unistd.h>  

#include "./Entities/Entity.cpp"
#include "./Entities/Human.cpp"
#include "./Entities/Monsters/Ghoul.cpp"
#include "./Events/Battle.cpp"
#include "./Entities/Witcher.cpp"
#include "./Items/Sword.cpp"
#include "./Items/Armor.cpp"
#include "./Utils/Date.cpp"

// carregamento de arquivo
using std::cerr;
using std::getline;
#include <fstream>
using std::fstream;
using std::ifstream;
#include <sstream>
using std::istringstream;

int main(void) {
    Witcher w1 = Witcher();
    cout << w1 << "\n";

    ifstream inputFile("./Items/swords_chest.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file." << '\n';
        return 1; // Exit with an error code
    }

    string line;    
    string variableName;
    char equalsSign;
    double value;
    while (getline(inputFile, line)) 
    {
        istringstream iss(line);
        if (iss >> variableName >> equalsSign >> value && equalsSign == '=') {
            Sword * loaded_sword = new Sword(variableName, value);
            w1.store_sword(*loaded_sword);
            delete loaded_sword;
        }
        else {
            cerr << "Error parsing line: " << line << '\n';
        }
    }

    inputFile.close();

    w1.print_chest_swords();

    return 0;
}
