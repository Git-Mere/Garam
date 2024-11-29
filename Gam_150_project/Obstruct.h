/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Obstruct.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "vec2.h"
#include "matrix.h"
#include "sprite.h"
#include "camera.h"

class Obstruct
{
public:
    Obstruct(int code, double x, double y, double width, double height);

    int code;
    double x = 0;
    double y = 0;
    double width;
    double height;

    void draw(Camera& camera);

private:
    Texture texture;
};

