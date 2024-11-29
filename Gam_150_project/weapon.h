/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  weapon.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "doodle/doodle.hpp"
#include "vec2.h"
#include "camera.h"
#include "sprite.h"
#include "matrix.h"

class Bullet
{
public:
    Bullet(Math::vec2 position, bool flipped);

    bool flipped = false;
    bool collision = false;
    double scale = 2;

    void draw(Math::TransformationMatrix camera_matrix);
    void bullet_info();
    Math::ivec2 Getspritesize();

    Math::vec2 position;
    Math::vec2 first_position;
    Math::TransformationMatrix object_matrix;
    Sprite sprite;
private:

};

class throw_attack {
public:
    throw_attack();
    void draw(Math::TransformationMatrix camera_matrix);
    void update();
    void timer();
    void add(Math::vec2 position, bool flipped);
    bool shoot = false;
    int count = 5;
    double range = 400;
    int charm_damage = 4;
    std::vector<Bullet*> bullets;
    Sprite sprite;
private:
    double bullet_timer = 0;
    double bullet_delay = 0.5;
};