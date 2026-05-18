#include <iostream>

class Player {
public:
    std::string name;
    int score;
    
    Player(std::string n, int s) {
        name = n;
        score = s;
    }
    
    void printInfo() {
        std::cout << name << " : " << score << std::endl;
    }

    void addScore(int points) {
        score = score + points;
    }
};

int main() {
    Player p1("Adeka", 100);
    Player p2("Budi", 150);
    
    p1.printInfo();
    p2.printInfo();
    p1.addScore(50);
    p1.printInfo();
    return 0;
}