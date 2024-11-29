/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  portal.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <doodle/doodle.hpp>
#include "portal.h"
#include "character.h"
#include "map.h"


Portal::Portal(double x, double y, int p_num) : x(x), y(y), p_num(p_num){
    texture.Load("Assets/background/potal.png");
    F.Load("Assets/background/f.png");
}
std::vector<Portal*> portal;


void Portal::draw(Camera& camera)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    Math::vec2 a = { 0 - pos_x, 0 - pos_y };
    doodle::draw_image(texture.image, x- pos_x, y - pos_y, width, height);
}
