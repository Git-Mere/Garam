/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Obstruct.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <doodle/doodle.hpp>
#include "Obstruct.h"
#include "map.h"

Obstruct::Obstruct(int code, double x, double y, double width, double height) : code(code), x(x), y(y), width(width), height(height) {
    switch (code) {
        ///donggul
    case 0:
        texture.Load("Assets/background/donggul/stage1_ground.png");
        break;
    case 1:
        texture.Load("Assets/background/donggul/stage2_ground.png");
        break;
    case 2:
        texture.Load("Assets/background/donggul/stage4_ground.png");
        break;
    case 3:
        texture.Load("Assets/background/donggul/ground1-1.png");
        break;
    case 4:
        texture.Load("Assets/background/donggul/stage2-2_ground.png");
        break;
    case 5:
        texture.Load("Assets/background/donggul/ground3.png");
        break;
    case 6:
        texture.Load("Assets/background/donggul/ground2-1.png");
        break;
    case 7:
        texture.Load("Assets/background/donggul/ground2.png");
        break;

        ////forest
    case 10:
        texture.Load("Assets/background/forest/stage1_ground.png");
        break;
    case 13:
        texture.Load("Assets/background/forest/forest_ground1-1.png");
        break;
    case 17:
        texture.Load("Assets/background/forest/forest_ground2.png");
        break;
    case 16:
        texture.Load("Assets/background/forest/forest_ground2-1.png");
        break;
    case 15:
        texture.Load("Assets/background/forest/forest_ground3.png");
        break;


        ///volcano
    case 20:
        texture.Load("Assets/background/volcano/stage1_ground.png");
        break;
    case 23:
        texture.Load("Assets/background/volcano/volcano_ground1-1.png");
        break;
    case 27:
        texture.Load("Assets/background/volcano/volcano_ground2.png");
        break;
    case 26:
        texture.Load("Assets/background/volcano/volcano_ground2-1.png");
        break;
    case 25:
        texture.Load("Assets/background/volcano/volcano_ground3.png");
        break;

        ///magma
    case 30:
        texture.Load("Assets/background/volcano/gagma.png");
        break;
}

}
std::vector<Obstruct*> obst;
extern int GameState;

void Obstruct::draw(Camera& camera)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    Math::vec2 a = { 0 - pos_x, 0 - pos_y };
    //texture.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 2, 2 }));
    doodle::draw_image(texture.image, x - pos_x, y - pos_y, width, height);
}


   