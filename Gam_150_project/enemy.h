/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  enemy.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include <vector>
#include "doodle/doodle.hpp"
#include "vec2.h"
#include "Sprite.h"
#include "matrix.h"

enum class type {
    dongool,
    bak
};

class Enemy
{
public:
    Enemy(Math::vec2 position, double range, int code);

    double speed = 1;
    double scale = 1.5;

    double max_hp = 5;
    double hp = 0;

    bool flipped = true;
    bool drop = true;
    int item_code;

    //void Load();
    void draw(Math::TransformationMatrix camera_matrix);
    void update();
    void attack();
    void draw_hp(Math::TransformationMatrix camera_matrix);
    void drop_tem();
    Math::ivec2 Getspritesize();
    void Setblood(int value);

    Math::vec2 position;
    Math::vec2 range;
    Math::TransformationMatrix object_matrix;
    Sprite sprite;
    Math::vec2 velocity;

private:
    Math::vec2 start_position;
};

