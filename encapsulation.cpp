#include <iostream>
class Hero {
private:
    int hp;
    
public:
    Hero(int h) {
        hp = h;
    }
    
    int getHp() {
        return hp;
    }
    
    void takeDamage(int dmg) {
        if (dmg > 0) hp -= dmg;
    }
};

int main() {
    Hero h(100);
    std::cout << "HP: " << h.getHp() << std::endl;
    h.takeDamage(30);
    std::cout << "HP after damage: " << h.getHp() << std::endl;
    return 0;
}