#include <iostream> 

class Hero {
public:
    std::string name;
    int health;
    int damage;

    Hero(std::string n, int h, int d) {
        name = n;
        health = h;
        damage = d;
    }
    void printinfo() {
        std::cout << name << " HP: " << health << " DMG: " << damage << std::endl;
    }
};
class warrior : public Hero {
    public: 
    int armor = 10;
    warrior(std::string n, int h, int d) : Hero(n, h, d) {}
    void printinfo() 
    {
        std::cout << name << " HP: " << health << " DMG: " << damage << " ARMOR: " << armor << std::endl;
    }   ;
};
class mage : public Hero {
    public: 
    int mana = 100;
    mage(std::string n, int h, int d) : Hero(n, h, d) {}
    void printinfo() 
    {
        std::cout << name << " HP: " << health << " DMG: " << damage << " MANA: " << mana << std::endl;
    }   ;
};
int main() {
    Hero h1("Generic Hero", 100, 20);
    warrior w1("Conan", 150, 30);
    mage m1("Gandalf", 80, 25);

    h1.printinfo();
    w1.printinfo();
    m1.printinfo();

    return 0;
}