/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  portal.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "vec2.h"
#include "camera.h"
#include "texture.h"

class Portal
{
public:
    Portal(double x, double y, int p_num);
    int p_num = 0;
    double x = 0;
    double y = 0;
    double width = 150;
    double height = 160;

    void draw(Camera& camera);

    Texture texture;
    Texture F;
private:

};