/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  character.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "Inventory.h"
#include "Obstruct.h"
#include "vec2.h"
#include "matrix.h"
#include "sprite.h"
#include "camera.h"
#include "weapon.h"
#include "direct_attack.h"

class Inventory;
class Item;

class Character {

public:
    Character(Math::vec2 position, Camera& camera);
    bool can_drop = false;
    bool open_inven = false;
    bool hit = false;
    bool flipped = false;
    bool landing_check = false;
    bool dash = false;
    bool stun = false;
    bool dead = false;
    bool TickTock = false;
    bool is_sound_used = false;

    double max_velocity = 7;
    double hit_timer = 0;
    double dash_timer = 0;
    double dash_delay = 0.55;
    double scale = 1.5;

    int dash_range = 17;
    int jump_count = 0;
    double max_hp = 100;
    int hp = 100;
    int AD = 1;
    int current_weapon = 1;

    void update();
    void Load();
    void draw(Math::TransformationMatrix camera_matrix);

    void col(Obstruct*);
    void col_help();
    void draw_hp();
    void superstance();
    void move();
    void timer();
    void hp_reset();
    void pos_reset();
    Math::ivec2 Getspritesize();
    Math::ivec2 GetFrameSize();
    void deter_animation();

    void reset();

    Math::vec2 position;
    Math::vec2 saved_position;
    Math::vec2 velocity;
    Inventory inventory;
    Sprite sprite;
    Sprite hp_bar;
    Sprite RIP;

    Math::TransformationMatrix object_matrix;
    Camera& camera;
private:
    static constexpr double x_acceleration = 1.5;
    static constexpr double x_drag = 0.5;
    static constexpr double gravity_c = 0.8;
};
