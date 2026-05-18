#include <iostream>

class Hero {
public:
    std::string name;
    
    Hero(std::string n) {
        name = n;
    }
    
    virtual void attack() {
        std::cout << name << " attacks!" << std::endl;
    }
};

class Warrior : public Hero {
public:
    Warrior(std::string n) : Hero(n) {}
    
    void attack() override {
        std::cout << name << " swings sword!" << std::endl;
    }
};

class Mage : public Hero {
public:
    Mage(std::string n) : Hero(n) {}
    
    void attack() override {
        std::cout << name << " casts fireball!" << std::endl;
    }
};

int main() {
    Warrior w("Axe");
    Mage m("Invoker");
    
    w.attack();
    m.attack();
    
    return 0;
}