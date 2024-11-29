/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  map.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "Obstruct.h"
#include "camera.h"
#include "sprite.h"

enum GameScene
{
    dongool_stage1 = 1,
    dongool_stage2 = 2,
    dongool_stage3 = 3,
    dongool_stage4 = 4,

    bak_stage1 = 5,
    bak_stage2 = 6,
    first_boss = 7,
    bak_stage3 = 8,

    forest_stage1 = 9,
    forest_stage2 = 10,
    forest_stage3 = 11,
    forest_boss = 12,

    volcano_stage1 = 13,
    volcano_stage2 = 14,
    volcano_stage3 = 15,
    volcano_boss = 16,

    temple_stage1 = 17,
    temple_stage2 = 18,
    temple_stage3 = 19,
    final_boss = 20
};

class Map {
public :
    bool pos_change = true;
    double x = 0;
    double y = 0;

    void update();
    void Load();
    void draw(Camera& camera);
    void Map_Reset();

    void portal_move();

    void dongool_stage1_create();
    void dongool_stage2_create();
    void dongool_stage3_create();
    void dongool_stage4_create();

    void bak_stage1_create();
    void bak_stage2_create();
    void first_boss_create();
    void bak_stage3_create();

    void forest_stage1_create();
    void forest_stage2_create();
    void forest_stage3_create();
    void forest_boss_create();

    void volcano_stage1_create();
    void volcano_stage2_create();
    void volcano_stage3_create();
    void volcano_boss_create();

    void temple_stage1_create();
    void temple_stage2_create();
    void temple_stage3_create();
    void final_boss_create();

    void tem_create();

private:
    Texture dongool_background;
    Texture bak_background;
    Texture forest_background;
    Texture volcano_background;
    Texture temple_background;
    Texture tutorial;
    Texture tutorial2;
};
