#include "raylib.h"
#include <vector>
#include <algorithm>

const float GRAVITY    = 1200.f;
const float JUMP_SPEED = -600.f;
const float MOVE_SPEED = 250.f;

// ─── Platform ────────────────────────────────────────────────────────────────

class Platform {
private:
    float x, y, width, height;

public:
    Platform(float x, float y, float w, float h)
        : x(x), y(y), width(w), height(h) {}

    float getX()      const { return x; }
    float getY()      const { return y; }
    float getWidth()  const { return width; }
    float getHeight() const { return height; }

    void draw() const {
        DrawRectangle((int)x, (int)y, (int)width, (int)height, GREEN);
    }
};

// ─── Player ──────────────────────────────────────────────────────────────────

class Player {
private:
    float x, y, velX, velY;
    bool onGround;

public:
    static constexpr float WIDTH  = 32.f;
    static constexpr float HEIGHT = 48.f;

    Player(float startX, float startY)
        : x(startX), y(startY), velX(0.f), velY(0.f), onGround(false) {}

    float getX()      const { return x; }
    float getY()      const { return y; }
    float getWidth()  const { return WIDTH; }
    float getHeight() const { return HEIGHT; }

    void setX(float v)       { x = v; }
    void setY(float v)       { y = v; }
    void setVelY(float v)    { velY = v; }
    void setOnGround(bool b) { onGround = b; }

    void jump() {
        if (onGround) {
            velY = JUMP_SPEED;
            onGround = false;
        }
    }

    void update(float dt) {
        // check jump before resetting onGround (uses last frame's collision result)
        if (IsKeyPressed(KEY_SPACE)) jump();

        onGround = false;

        // gravity
        velY += GRAVITY * dt;

        // horizontal input
        velX = 0.f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  velX = -MOVE_SPEED;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  velX =  MOVE_SPEED;

        x += velX * dt;
        y += velY * dt;

        // keep inside window
        if (x < 0.f) x = 0.f;
        if (x + WIDTH > 800.f) x = 800.f - WIDTH;
    }

    void draw() const {
        DrawRectangle((int)x, (int)y, (int)WIDTH, (int)HEIGHT, SKYBLUE);
    }
};

// ─── Collision ───────────────────────────────────────────────────────────────

void resolveCollisions(Player& player, std::vector<Platform>& platforms) {
    for (auto& platform : platforms) {
        float px = player.getX(), py = player.getY();
        float pw = player.getWidth(), ph = player.getHeight();
        float plx = platform.getX(), ply = platform.getY();
        float plw = platform.getWidth(), plh = platform.getHeight();

        bool overlaps = px < plx + plw && px + pw > plx &&
                        py < ply + plh && py + ph > ply;
        if (!overlaps) continue;

        float overlapTop    = (py + ph)  - ply;
        float overlapBottom = (ply + plh) - py;
        float overlapLeft   = (px + pw)  - plx;
        float overlapRight  = (plx + plw) - px;

        float minOverlap = std::min({overlapTop, overlapBottom, overlapLeft, overlapRight});

        if (minOverlap == overlapTop) {
            player.setY(ply - ph);
            player.setVelY(0.f);
            player.setOnGround(true);
        } else if (minOverlap == overlapBottom) {
            player.setY(ply + plh);
            player.setVelY(0.f);
        } else if (minOverlap == overlapLeft) {
            player.setX(plx - pw);
        } else {
            player.setX(plx + plw);
        }
    }
}

// ─── Main ────────────────────────────────────────────────────────────────────

int main() {
    InitWindow(800, 600, "Platformer");
    SetTargetFPS(60);

    Player player(100.f, 400.f);

    std::vector<Platform> platforms = {
        {   0.f, 550.f, 800.f, 50.f },
        { 100.f, 420.f, 200.f, 20.f },
        { 350.f, 320.f, 150.f, 20.f },
        { 550.f, 220.f, 180.f, 20.f },
        { 200.f, 180.f, 120.f, 20.f },
    };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;

        player.update(dt);
        resolveCollisions(player, platforms);

        BeginDrawing();
            ClearBackground({ 30, 30, 40, 255 });
            for (auto& p : platforms) p.draw();
            player.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
