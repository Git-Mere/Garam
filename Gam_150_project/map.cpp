/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  map.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "map.h"
#include "enemy.h"
#include "weapon.h"
#include "character.h"
#include "portal.h"
#include "Obstruct.h"
#include "enemy.h"
#include "Boss1.h"
#include "Boss2.h"
#include "doodle/doodle.hpp"
#include "SoundEffect.h"
#include <iostream>
using namespace doodle;

extern int GameState;

extern Character Garam;
extern Camera camera;
extern Meretoss mere;
extern Tonkotsu ton;
extern Tonkotsu tonkotsu1;
extern Tonkotsu tonkotsu2;
extern std::vector<Item*> stage1tem;
extern std::vector<Obstruct*> obst;
extern std::vector<Portal*> portal;
extern std::vector<Item*> tem;
extern std::vector<Enemy*> enemy;
extern throw_attack charm;
extern std::vector<Tonkotsu*> tons;
extern std::vector<TonBullet*> tonb;


void Map::Map_Reset() {
    for (auto bullet_iter = charm.bullets.begin(); bullet_iter != charm.bullets.end(); )
    {
        delete (*bullet_iter);
        bullet_iter = charm.bullets.erase(bullet_iter);
    }

    for (auto obst_iter = obst.begin(); obst_iter != obst.end(); )
    {
        delete (*obst_iter);
        obst_iter = obst.erase(obst_iter);
    }

    for (auto port_iter = portal.begin(); port_iter != portal.end(); )
    {
        delete (*port_iter);
        port_iter = portal.erase(port_iter);
    }

    for (auto enemy_iter = enemy.begin(); enemy_iter != enemy.end(); )
    {
        delete (*enemy_iter);
        enemy_iter = enemy.erase(enemy_iter);
    }

    if (!charm.bullets.empty()) {
        for (int i = 0; i < charm.bullets.size(); i++) {
            if (charm.bullets[i]->position.x < 0 || charm.bullets[i]->position.x > Width) {
                delete charm.bullets[i];
                charm.bullets.erase(charm.bullets.begin() + i);
            }
        }
    }


}

void Map::Load()
{
    dongool_background.Load("Assets/background/donggul/cave_background1.png");
    bak_background.Load("Assets/background/bak/background_0.png");
    forest_background.Load("Assets/background/forest/forest_background.png");
    volcano_background.Load("Assets/background/volcano/volcano_background.png");
    temple_background.Load("Assets/background/temple/temple.png");
    tutorial.Load("Assets/background/donggul/tutorial.png");
    tutorial2.Load("Assets/background/donggul/tutorial2.png");

    //CS230::SoundEffect::FeildBGM().loopplay();

}

void Map::update() 
{
    if (pos_change == true) {
        Map_Reset();
        switch (GameState) {
        case GameScene::dongool_stage1:
            dongool_stage1_create();
            break;
        case GameScene::dongool_stage2:
            dongool_stage2_create();
            break;
        case GameScene::dongool_stage3:
            dongool_stage3_create();
            break;
        case GameScene::dongool_stage4:
            dongool_stage4_create();
            break;
        case GameScene::bak_stage1:
            bak_stage1_create();
            break;
        case GameScene::bak_stage2:
            bak_stage2_create();
            break;
        case GameScene::first_boss:
            first_boss_create();
            break;
        case GameScene::bak_stage3:
            bak_stage3_create();
            break;
        case GameScene::forest_stage1:
            forest_stage1_create();
            break;
        case GameScene::forest_stage2:
            forest_stage2_create();
            break;
        case GameScene::forest_stage3:
            forest_stage3_create();
            break;
        case GameScene::forest_boss:
            forest_boss_create();
            break;
        case GameScene::volcano_stage1:
            volcano_stage1_create();
            break;
        case GameScene::volcano_stage2:
            volcano_stage2_create();
            break;
        case GameScene::volcano_stage3:
            volcano_stage3_create();
            break;
        case GameScene::volcano_boss:
            volcano_boss_create();
            break;
        case GameScene::temple_stage1:
            temple_stage1_create();
            break;
        case GameScene::temple_stage2:
            temple_stage2_create();
            break;
        case GameScene::temple_stage3:
            temple_stage3_create();
            break;
        case GameScene::final_boss:
            final_boss_create();
            break;
        }


        pos_change = false;
    }
    for (int i = 0; i < tem.size(); i++) {
        tem[i]->col(Garam);
    }

    for (int i = 0; i < enemy.size(); i++) {
        if (enemy[i]->hp <= 0) {
            enemy[i]->drop_tem();
            delete enemy[i];
            enemy.erase(enemy.begin() + i);
        }
    }

    if (GameState == GameScene::forest_boss) {
        for (int j = 0; j < charm.bullets.size(); ) { // 반복문 변수 j 업데이트를 삭제 과정 이후에 수행
            bool bulletDeleted = false; // 총알 삭제 여부 플래그

            for (int i = 0; i < tons.size(); i++) {
                if (charm.bullets[j]->position.x + charm.bullets[j]->Getspritesize().x / 2.0 >= tons[i]->position.x &&
                    charm.bullets[j]->position.x - charm.bullets[j]->Getspritesize().x / 2.0 <= tons[i]->position.x + 100 &&
                    charm.bullets[j]->position.y - charm.bullets[j]->Getspritesize().y / 2.0 <= tons[i]->position.y + 150 &&
                    charm.bullets[j]->position.y + charm.bullets[j]->Getspritesize().y / 2.0 >= tons[i]->position.y && tons[i]-> alive == true
                    )
                {
                    tons[i]->hp -= Garam.AD;
                    delete charm.bullets[j];
                    charm.bullets.erase(charm.bullets.begin() + j);
                    bulletDeleted = true; // 총알 삭제됨
                    break; // 내부 반복문 종료
                }
            }
            if (!bulletDeleted) {
                j++; // 총알이 삭제되지 않았을 경우에만 j를 증가시킴
            }
        }

        for (int k = 0; k < tonb.size(); k++)
        {
            if (tonb[k]->position.x < 0 || tonb[k]->position.x > Width+1000)
            {
                delete tonb[k];
                tonb.erase(tonb.begin() + k);
            }
        }
    }
}

void Map::draw(Camera& camera) {
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;


    Math::vec2 a = { 0 - pos_x, 0 - pos_y };
    if (GameState <= GameScene::dongool_stage4) {
        dongool_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 10, 10 }));
    }
    else if (GameState > dongool_stage4 && GameState <= first_boss) {
        bak_background.Draw(Math::TranslationMatrix(a + Math::vec2{ 0, 700 }) * Math::ScaleMatrix({ 4, 2 }));
        bak_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 4, 2 }));
    }
    else if (GameState == bak_stage3) {
        bak_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 4, 2 }));
        bak_background.Draw(Math::TranslationMatrix(a + Math::vec2{ 0, 720 }) * Math::ScaleMatrix({ 4, 2 }));
    }
    else if (GameState == forest_stage1) {
        forest_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 6, 8 }));
    }
    else if (GameState > forest_stage1 && GameState <= forest_boss) {
        forest_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 6, 4 }));
    }
    else if (GameState > forest_boss && GameState <= volcano_boss) {
        volcano_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 7, 4 }));
    }
    else if (GameState > volcano_boss && GameState <= final_boss) {
        temple_background.Draw(Math::TranslationMatrix(a) * Math::ScaleMatrix({ 5.5, 4 }));
    }



    Math::vec2 b = { 100 - pos_x, 360 - pos_y };
    if (GameState == GameScene::dongool_stage1)
    {
        tutorial.Draw(Math::TranslationMatrix(b) * Math::ScaleMatrix({ 2, 2 }));
    }
    if (GameState == GameScene::dongool_stage2)
    {
        tutorial2.Draw(Math::TranslationMatrix(b) * Math::ScaleMatrix({ 2, 2 }));
    }


    for (int i = 0; i < obst.size(); i++) {
        obst[i]->draw(camera);
    }

    for (int i = 0; i < portal.size(); i++) {
        portal[i]->draw(camera);
    }

    for (int i = 0; i < portal.size(); i++) {
        if (Garam.position.x >= portal[i]->x && Garam.position.x <= portal[i]->x + portal[i]->width && Garam.position.y <= portal[i]->y + portal[i]->height && Garam.position.y >= portal[i]->y) {
            Math::vec2 d = { portal[i]->x + 45 - pos_x, portal[i]->y + 145 - pos_y };
            portal[i]->F.Draw(Math::TranslationMatrix(d) * Math::ScaleMatrix({ 2, 2 }));
        }
    }

    for (int i = 0; i < tem.size(); i++) {
        Math::vec2 c = { tem[i]->position.x - 10 - pos_x, tem[i]->position.y + 30 - pos_y };
        if (tem[i]->can_drop == true && tem[i]->stage == GameState) {
            tem[i]->F.Draw(Math::TranslationMatrix(c) * Math::ScaleMatrix({ 2, 2 }));
        }
    }
    for (int i = 0; i < tem.size(); i++) {
        if (tem[i]->stage == GameState && tem[i]->live == true) {
            tem[i]->draw(camera);
        }
    }
}

void Map::tem_create() {
    //tem.push_back(new Item{ "herb",	1, Kind::potion,{ 200, 100 }, dongool_stage1 });
    //tem.push_back(new Item{ "herb",	1, Kind::potion,{ 200, 100 }, dongool_stage1 });
    //tem.push_back(new Item{ "herb",	1, Kind::potion,{ 200, 100 }, dongool_stage1 });
    tem.push_back(new Item{ "herb",	1, Kind::potion,{ 200, 100 }, dongool_stage1 });
    tem.push_back(new Item{ "herb",	1, Kind::potion,{ 1650, 100 }, dongool_stage1 });

    tem.push_back(new Item{ "mineral_water",2, Kind::potion,{ 600, 40 }, dongool_stage4 });

    tem.push_back(new Item{ "red_pepper_paste",	7, Kind::potion,{ 270, 360 }, bak_stage2 }); //고추장

    tem.push_back(new Item{ "Seasoned_vegetables",	12, Kind::potion,{ 1000, 350 }, bak_stage3 }); //나물무침(seasoned vegetable이라고 되어있는 거)
    tem.push_back(new Item{ "red_pepper_paste",	7, Kind::meterial,{ 50, 350 }, bak_stage3 }); //부적 재료
    tem.push_back(new Item{ "red_pepper_paste",	7, Kind::meterial,{ 100, 350 }, bak_stage3 }); //부적 재료
    tem.push_back(new Item{ "red_pepper_paste",	7, Kind::meterial,{ 150, 350 }, bak_stage3 }); //부적 재료
    tem.push_back(new Item{ "red_pepper_paste",	7, Kind::potion,{ 700, 50 }, bak_stage3 }); //떡고치


    tem.push_back(new Item{ "skewer",	11, Kind::potion,{ 830, 1100 }, forest_stage1 }); //떡꼬치

    tem.push_back(new Item{ "rice_cake",	6, Kind::meterial,{ 30, 160 }, forest_stage3 }); 
    tem.push_back(new Item{ "rice_cake",	6, Kind::meterial,{ 330, 100 }, forest_stage3 }); 

    tem.push_back(new Item{ "rice_cake",	6, Kind::meterial,{ 700, 270 }, forest_stage3 }); 
    tem.push_back(new Item{ "rice_cake",	6, Kind::meterial,{ 750, 270 }, forest_stage3 }); 
    tem.push_back(new Item{ "herb",	1, Kind::potion,{ 850, 270 }, forest_stage3 }); 
    tem.push_back(new Item{ "herb",	1, Kind::potion,{ 900, 270 }, forest_stage3 }); 
    tem.push_back(new Item{ "leather",	5, Kind::meterial,{ 1400, 100 }, forest_stage3 }); 
    tem.push_back(new Item{ "leather",	5, Kind::meterial,{ 1450, 100 }, forest_stage3 }); 
    tem.push_back(new Item{ "leather",	5, Kind::meterial,{ 1500, 100 }, forest_stage3 }); 
    tem.push_back(new Item{ "leather",	5, Kind::meterial,{ 1300, 100 }, forest_stage3 }); 
    tem.push_back(new Item{ "leather",	5, Kind::meterial,{ 1350, 100 }, forest_stage3 }); 
    tem.push_back(new Item{ "leather",	5, Kind::meterial,{ 1550, 100 }, forest_stage3 }); 
    tem.push_back(new Item{ "red_pepper_paste",	7, Kind::meterial,{ 1800, 250 }, forest_stage3 }); 

    tem.push_back(new Item{ "skewer",	11, Kind::potion,{ 1250, 280 }, volcano_stage3 }); // 떡꼬치
}

void Map::portal_move()
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    for (int i = 0; i < portal.size(); i++) {
        if (Garam.position.x >= portal[i]->x && Garam.position.x <= portal[i]->x + portal[i]->width && Garam.position.y <= portal[i]->y + portal[i]->height && Garam.position.y >= portal[i]->y)
        {
            if (portal[i]->p_num == 0 && GameState == dongool_stage1)
            {
                GameState = dongool_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(120, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 1 && GameState == dongool_stage2)
            {
                GameState = dongool_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(1100, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 2 && GameState == dongool_stage2)
            {
                GameState = dongool_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(130, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 3 && GameState == dongool_stage3)
            {
                GameState = dongool_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(1800, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 4 && GameState == dongool_stage3)
            {
                GameState = dongool_stage4;
                pos_change = true;
                Garam.saved_position = Math::vec2(130, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 5 && GameState == dongool_stage4)
            {
                GameState = dongool_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(1500, 400);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 6 && GameState == dongool_stage4)
            {
                GameState = bak_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(120, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 7 && GameState == bak_stage1)
            {
                GameState = dongool_stage4;
                pos_change = true;
                Garam.saved_position = Math::vec2(2600, 450);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 8 && GameState == bak_stage1)
            {
                GameState = bak_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(120, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 9 && GameState == bak_stage2)
            {
                GameState = bak_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(2500, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 10 && GameState == bak_stage2)
            {
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().loopplay();
                GameState = first_boss;
                pos_change = true;
                Garam.saved_position = Math::vec2(150, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 11 && GameState == first_boss)
            {
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().loopplay();
                GameState = bak_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(1950, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 12 && GameState == first_boss)
            {
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().loopplay();
                GameState = bak_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(150, 800);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 13 && GameState == bak_stage3)
            {
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().loopplay();
                GameState = first_boss;
                pos_change = true;
                Garam.saved_position = Math::vec2(1850, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 14 && GameState == bak_stage3)
            {
                GameState = forest_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(800, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 15 && GameState == forest_stage1)
            {
                GameState = bak_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(1850, 100);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 16 && GameState == forest_stage1)
            {
                GameState = forest_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(150, 220);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 17 && GameState == forest_stage2)
            {
                GameState = forest_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(850, 360);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 18 && GameState == forest_stage2)
            {
                GameState = volcano_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(50, 50);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 19 && GameState == forest_stage2)
            {
                GameState = forest_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(200, 300);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 20 && GameState == forest_stage3)
            {
                GameState = forest_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(1850, 300);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 21 && GameState == forest_stage3)
            {
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().loopplay();
                GameState = forest_boss;
                pos_change = true;
                Garam.saved_position = Math::vec2(200, 300);
                //tons.push_back(&tonkotsu1);
                //tons.push_back(&tonkotsu2);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 22 && GameState == forest_boss)
            {
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().loopplay();
                GameState = forest_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(2150, 300);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 23 && GameState == volcano_stage1)
            {
                GameState = forest_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(950, 500);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 24 && GameState == volcano_stage1)
            {
                GameState = volcano_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 350);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 25 && GameState == volcano_stage2)
            {
                GameState = volcano_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(2050, 500);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 26 && GameState == volcano_stage2)
            {
                GameState = volcano_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(2300, 50);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 27 && GameState == volcano_stage3)
            {
                GameState = volcano_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(2000, 300);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 28 && GameState == volcano_stage3)
            {
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().loopplay();
                GameState = volcano_boss;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 50);
                CS230::SoundEffect::Portal().play();
            }

            if (portal[i]->p_num == 29 && GameState == volcano_boss)
            {
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().loopplay();
                GameState = volcano_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 370);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 31 && GameState == volcano_stage3)
            {
                GameState = temple_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 50);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 32 && GameState == temple_stage1)
            {
                GameState = volcano_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(2200, 370);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 33 && GameState == temple_stage1)
            {
                GameState = temple_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 50);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 34 && GameState == temple_stage2)
            {
                GameState = temple_stage1;
                pos_change = true;
                Garam.saved_position = Math::vec2(1850, 100);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 35 && GameState == temple_stage2)
            {
                GameState = temple_stage3;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 50);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 36 && GameState == temple_stage3)
            {
                GameState = temple_stage2;
                pos_change = true;
                Garam.saved_position = Math::vec2(1850, 100);
                CS230::SoundEffect::Portal().play();
            }
            if (portal[i]->p_num == 37 && GameState == temple_stage3)
            {
                CS230::SoundEffect::BossBGM().stopAll();
                CS230::SoundEffect::FeildBGM().stopAll();
                CS230::SoundEffect::BossBGM().loopplay();
                GameState = final_boss;
                pos_change = true;
                Garam.saved_position = Math::vec2(100, 50);
                CS230::SoundEffect::Portal().play();
            }
            Garam.position = Garam.saved_position;
        }
    }
}


void Map::dongool_stage1_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 700, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 0, 0, 700, 50, 1900 });
    obst.push_back(new Obstruct{ 0, 150, 700, 2500, 900 });

    obst.push_back(new Obstruct{ 0, 0, 0, 3000, 40 });
    obst.push_back(new Obstruct{ 5, 50, 50, 200, 50 });
    obst.push_back(new Obstruct{ 5, 350, 150, 200, 50 });
    obst.push_back(new Obstruct{ 5, 600, 250, 200, 50 });
    obst.push_back(new Obstruct{ 6, 900, 0, 150, 400 });
    obst.push_back(new Obstruct{ 5, 1250, 300, 300, 50 });
    obst.push_back(new Obstruct{ 5, 1500, 50, 300, 50 });
    obst.push_back(new Obstruct{ 5, 1700, 150, 140, 40 });


    ///portal
    portal.push_back(new Portal{ 1100, 30, 0 });

    ///enemy
    enemy.push_back(new Enemy{ {370, 230}, 100 , 0 });


}

void Map::dongool_stage2_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1000, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 0, 0, 700, 3000, 900 });


    obst.push_back(new Obstruct{ 1, 0, 0, 420, 40 });
    obst.push_back(new Obstruct{ 4, 1120, 0, 2000, 40 });
    obst.push_back(new Obstruct{ 6, 380, 0, 230, 160 });
    obst.push_back(new Obstruct{ 6, 565, 0, 200, 250 });
    obst.push_back(new Obstruct{ 6, 760, 0, 200, 160 });
    obst.push_back(new Obstruct{ 5, 1100, 250, 200, 50 });
    obst.push_back(new Obstruct{ 5, 1295, 330, 200, 50 });
    obst.push_back(new Obstruct{ 5, 1620, 400, 200, 50 });   
    obst.push_back(new Obstruct{ 5, 2000, 300, 200, 50 });

    ///portal
    portal.push_back(new Portal{ 100, 30, 1 });
    portal.push_back(new Portal{ 1800, 30, 2 });

    ///enemy
    enemy.push_back(new Enemy{ {2020, 380}, 150 , 2 });
    //enemy.push_back(new Enemy{  });

}

void Map::dongool_stage3_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 700, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 0, 0, 700, 3000, 900 });

    obst.push_back(new Obstruct{ 0, 0, 0, 2500, 40 });
    obst.push_back(new Obstruct{ 5, 300, 95, 200, 50 });
    obst.push_back(new Obstruct{ 5, 550, 200, 200, 50 });
    obst.push_back(new Obstruct{ 5, 800, 300, 200, 50 });
    obst.push_back(new Obstruct{ 6, 1290, 30, 400, 300 });
    obst.push_back(new Obstruct{ 6, 1150, 30, 300, 200 });
    obst.push_back(new Obstruct{ 6, 1580, 30, 200, 150 });

    ///portal
    portal.push_back(new Portal{ 100, 30, 3 });
    portal.push_back(new Portal{ 1500, 320, 4 });

    enemy.push_back(new Enemy{ {1350, 360}, 250 , 0 });
}

void Map::dongool_stage4_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1800, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 2, 0, 0, 640, 40 });


    obst.push_back(new Obstruct{ 2, 0, 0, 640, 40 });

    obst.push_back(new Obstruct{ 5, 850, 0, 50, 80 });
    obst.push_back(new Obstruct{ 5, 750, 70, 250, 40 });

    obst.push_back(new Obstruct{ 5, 1200, 0, 50, 185 });
    obst.push_back(new Obstruct{ 5, 1100, 170, 250, 40 });

    obst.push_back(new Obstruct{ 6, 1550, 0, 50, 295 });
    obst.push_back(new Obstruct{ 5, 1450, 270, 250, 40 });

    obst.push_back(new Obstruct{ 5, 1050, 390, 250, 40 });
    obst.push_back(new Obstruct{ 5, 1500, 450, 250, 40 });

    obst.push_back(new Obstruct{ 6, 2050, 0, 50, 525 });
    obst.push_back(new Obstruct{ 5, 1950, 500, 250, 40 });

    obst.push_back(new Obstruct{ 6, 2300, 200, 50, 550 });
    obst.push_back(new Obstruct{ 5, 2200, 180, 250, 40 });

    obst.push_back(new Obstruct{ 5, 2300, 0, 50, 40 });
    obst.push_back(new Obstruct{ 5, 2180, 30, 290, 40 });

    obst.push_back(new Obstruct{ 5, 2500, 320, 350, 40 });

    obst.push_back(new Obstruct{ 0, 0, 700, 3700, 900 });

    ///portal
    portal.push_back(new Portal{ 100, 30, 5 });
    portal.push_back(new Portal{ 2600, 350, 6 });

    //enemy
    enemy.push_back(new Enemy{ {1480, 340}, 150 , 1 });
    enemy.push_back(new Enemy{ {2200, 100}, 240 , 1 });
}

void Map::bak_stage1_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1500, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 0, 0, 0, 4000, 40 });
    obst.push_back(new Obstruct{ 5, -190, 30, 200, 300 });
    obst.push_back(new Obstruct{ 6, 600, -120, 350, 200 });
    obst.push_back(new Obstruct{ 6, 940, -130, 300, 250 });

    obst.push_back(new Obstruct{ 5, 1350, 170, 50, 50 });
    obst.push_back(new Obstruct{ 5, 1500, 200, 50, 50 });
    obst.push_back(new Obstruct{ 5, 1650, 230, 50, 50 });

    obst.push_back(new Obstruct{ 6, 1850, 0, 150, 350 });
    obst.push_back(new Obstruct{ 6, 1980, -10, 300, 250 });
    obst.push_back(new Obstruct{ 6, 2260, -10, 200, 150 });

    ///portal
    portal.push_back(new Portal{ 100, 30, 7 });
    portal.push_back(new Portal{ 2500, 30, 8 });

    enemy.push_back(new Enemy{ {1880, 380}, 100 , 7 });
}

void Map::bak_stage2_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1020, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 6, 600, -20, 350, 280 });
    obst.push_back(new Obstruct{ 0, 1550, 0, 2000, 65 });
    obst.push_back(new Obstruct{ 0, 0, 0, 1600, 40 });
    obst.push_back(new Obstruct{ 6, 450, -100, 320, 280 });
    obst.push_back(new Obstruct{ 6, 700, -120, 450, 235 });

    obst.push_back(new Obstruct{ 5, 200, 300, 200, 60 });


    ///portal
    portal.push_back(new Portal{ 100, 30, 9 });
    portal.push_back(new Portal{ 1950, 50, 10 });

    enemy.push_back(new Enemy{ {630, 290}, 300 , 0 });
    enemy.push_back(new Enemy{ {1550, 95}, 300 , 8 });
}

void Map::first_boss_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 720, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });


    ///portal
    portal.push_back(new Portal{ 100, 30, 11 });
    portal.push_back(new Portal{ 1850, 30, 12 });
}

void Map::bak_stage3_create()
{
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 2500, 40 });
    obst.push_back(new Obstruct{ 5, 0, 700, 250, 50 });
    obst.push_back(new Obstruct{ 5, 400, 700, 250, 50 });
    obst.push_back(new Obstruct{ 5, 850, 700, 250, 50 });
    obst.push_back(new Obstruct{ 5, 1450, 700, 250, 50 });
    obst.push_back(new Obstruct{ 5, 1200, 700, 50, 50 });
    obst.push_back(new Obstruct{ 5, 1250, 520, 50, 50 });
    obst.push_back(new Obstruct{ 5, 1200, 340, 50, 50 });
    obst.push_back(new Obstruct{ 5, 0, 300, 250, 50 });
    obst.push_back(new Obstruct{ 5, 400, 300, 250, 50 });
    obst.push_back(new Obstruct{ 5, 850, 300, 250, 50 });
    obst.push_back(new Obstruct{ 6, -10, 0, 340, 200 });
    obst.push_back(new Obstruct{ 6, 100, -50, 350, 170 });

    //portal
    portal.push_back(new Portal{ 60, 745, 13 });
    portal.push_back(new Portal{ 1850, 30, 14 });

}

void Map::forest_stage1_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 10, 400, 0, 900, 40 });

    obst.push_back(new Obstruct{ 15, 50, 170, 250, 50 });
    obst.push_back(new Obstruct{ 15, 1400, 170, 250, 50 });

    obst.push_back(new Obstruct{ 15, 400, 300, 300, 70 });
    obst.push_back(new Obstruct{ 15, 700, 300, 300, 70 });
    obst.push_back(new Obstruct{ 15, 1000, 300, 300, 70 });

    obst.push_back(new Obstruct{ 15, 1400, 450, 50, 50 });
    obst.push_back(new Obstruct{ 15, 1450, 600, 50, 50 });
    obst.push_back(new Obstruct{ 15, 1500, 750, 50, 50 });
    obst.push_back(new Obstruct{ 15, 1350, 900, 50, 50 });
    obst.push_back(new Obstruct{ 15, 1200, 1050, 50, 50 });
    obst.push_back(new Obstruct{ 15, 1050, 1200, 50, 50 });


    obst.push_back(new Obstruct{ 15, 730, 1050, 250, 50 });


    obst.push_back(new Obstruct{ 15, 250, 450, 50, 50 });
    obst.push_back(new Obstruct{ 15, 200, 600, 50, 50 });
    obst.push_back(new Obstruct{ 15, 150, 750, 50, 50 });
    obst.push_back(new Obstruct{ 15, 300, 900, 50, 50 });
    obst.push_back(new Obstruct{ 15, 450, 1050, 50, 50 });
    obst.push_back(new Obstruct{ 15, 600, 1200, 50, 50 });


    //portal
    portal.push_back(new Portal{ 800, 30, 15 });
    portal.push_back(new Portal{ 800, 360, 16 });

    enemy.push_back(new Enemy{ {80, 250}, 200 , 6 });
    enemy.push_back(new Enemy{ {1430, 250}, 200 , 6 });
}

void Map::forest_stage2_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 10, 0, 0, 2500, 40 });
    obst.push_back(new Obstruct{ 16, 0, -200, 500, 380 });
    obst.push_back(new Obstruct{ 16, 850, -100, 350, 180 });
    obst.push_back(new Obstruct{ 16, 1530, -200, 500, 380 });

    obst.push_back(new Obstruct{ 10, 510, 300, 1000, 70 });
    obst.push_back(new Obstruct{ 15, 880, 380, 300, 50 });


    //portal
    portal.push_back(new Portal{ 100, 170, 17 });
    portal.push_back(new Portal{ 950, 425, 18 });
    portal.push_back(new Portal{ 1750, 170, 19 });

    enemy.push_back(new Enemy{ {880, 110}, 200 , 5 });
    enemy.push_back(new Enemy{ {1230, 80}, 220 , 5 });
    enemy.push_back(new Enemy{ {570, 80}, 250 , 5 });
}

void Map::forest_stage3_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1100, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 15, 0, 60, 300, 80 });
    obst.push_back(new Obstruct{ 15, 200, 0, 200, 80 });

    obst.push_back(new Obstruct{ 15, 600, 200, 450, 80 });
    obst.push_back(new Obstruct{ 15, 550, 160, 130, 80 });
    obst.push_back(new Obstruct{ 15, 980, 160, 130, 80 });

    obst.push_back(new Obstruct{ 15, 1260, 30, 380, 80 });
    obst.push_back(new Obstruct{ 16, 1250, 30, 50, 180 });
    obst.push_back(new Obstruct{ 16, 1600, 30, 50, 300 });

    obst.push_back(new Obstruct{ 15, 1700, 170, 250, 80 });

    obst.push_back(new Obstruct{ 15, 2000, 30, 350, 50 });



    //portal
    portal.push_back(new Portal{ 120, 130, 20 });
    portal.push_back(new Portal{ 2100, 70, 21 });

    enemy.push_back(new Enemy{ {630, 310}, 350 , 14 });
}

void Map::forest_boss_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 10, 0, 0, 3500, 40 });


    //portal
    portal.push_back(new Portal{ 100, 30, 22 });
}

void Map::volcano_stage1_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1300, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 5, 0, 0, 150, 40 });
    obst.push_back(new Obstruct{ 5, 150, 50, 150, 40 });
    obst.push_back(new Obstruct{ 5, 300, 100, 150, 40 });
    obst.push_back(new Obstruct{ 5, 450, 150, 150, 40 });
    obst.push_back(new Obstruct{ 5, 600, 200, 150, 40 });
    obst.push_back(new Obstruct{ 5, 750, 250, 150, 40 });
    obst.push_back(new Obstruct{ 5, 900, 300, 150, 40 });
    obst.push_back(new Obstruct{ 5, 1050, 350, 150, 40 });
    obst.push_back(new Obstruct{ 5, 1200, 350, 150, 40 });
    obst.push_back(new Obstruct{ 5, 1350, 350, 150, 40 });
    obst.push_back(new Obstruct{ 5, 1500, 350, 150, 40 });
    obst.push_back(new Obstruct{ 5, 1850, 400, 500, 100 });

    //portal
    portal.push_back(new Portal{ 0, 30, 23 });
    portal.push_back(new Portal{ 2050, 485, 24 });

    enemy.push_back(new Enemy{ {1080, 420}, 100 , 0 });
    enemy.push_back(new Enemy{ {1200, 420}, 100 , 0 });
    enemy.push_back(new Enemy{ {1320, 420}, 100 , 18 });
    enemy.push_back(new Enemy{ {1440, 420}, 100 , 0 });
}

void Map::volcano_stage2_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1300, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });
    obst.push_back(new Obstruct{ 6, 0, 0, 350, 300 });
    obst.push_back(new Obstruct{ 6, 250, -100, 250, 300 });
    obst.push_back(new Obstruct{ 6, 400, -200, 250, 300 });

    obst.push_back(new Obstruct{ 5, 500, 380, 150, 50 });
    obst.push_back(new Obstruct{ 5, 700, 450, 150, 50 });

    obst.push_back(new Obstruct{ 5, 900, 380, 150, 50 });
    obst.push_back(new Obstruct{ 5, 1100, 450, 150, 50 });

    obst.push_back(new Obstruct{ 5, 1300, 380, 150, 50 });
    obst.push_back(new Obstruct{ 5, 1550, 400, 150, 50 });


    obst.push_back(new Obstruct{ 5, 1800, 250, 350, 50 });

    //portal
    portal.push_back(new Portal{ 100, 285, 25 });
    portal.push_back(new Portal{ 1900, 280, 26 });

    enemy.push_back(new Enemy{ {1330, 460}, 100 , 19 });
    enemy.push_back(new Enemy{ {800, 70}, 1000 , 3 });
}

void Map::volcano_stage3_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 1220, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });

    obst.push_back(new Obstruct{ 5, 500, 160, 200, 40 });
    obst.push_back(new Obstruct{ 5, 300, 200, 200, 40 });
    obst.push_back(new Obstruct{ 5, 1800, 160, 200, 40 });
    obst.push_back(new Obstruct{ 5, 2000, 200, 200, 40 });

    obst.push_back(new Obstruct{ 5, 50, 300, 250, 80 });
    obst.push_back(new Obstruct{ 5, 2150, 300, 250, 80 });


    obst.push_back(new Obstruct{ 6, 1150, 30, 200, 250 });
    obst.push_back(new Obstruct{ 6, 1300, 30, 200, 150 });
    obst.push_back(new Obstruct{ 6, 1000, 30, 200, 150 });


    //portal
    portal.push_back(new Portal{ 2200, 30, 27 });
    portal.push_back(new Portal{ 100, 370, 28 });
    portal.push_back(new Portal{ 2200, 370, 31 });

    enemy.push_back(new Enemy{ {1030, 210}, 100 , 0 });
    enemy.push_back(new Enemy{ {1360, 210}, 100 , 0 });
}

void Map::volcano_boss_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct
    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });

    //portal
    portal.push_back(new Portal{ 100, 30, 29 });
}

void Map::temple_stage1_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });

    //portal
    portal.push_back(new Portal{ 100, 30, 32 });
    portal.push_back(new Portal{ 1800, 30, 33 });

    enemy.push_back(new Enemy{ {350, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {500, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {650, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {800, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {950, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {1100, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {1250, 70}, 100 , 0 });
}
void Map::temple_stage2_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });

    //portal
    portal.push_back(new Portal{ 100, 30, 34 });
    portal.push_back(new Portal{ 1800, 30, 35 });

    enemy.push_back(new Enemy{ {350, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {500, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {650, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {800, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {950, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {1100, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {1250, 70}, 100 , 0 });
}
void Map::temple_stage3_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });

    //poertal
    portal.push_back(new Portal{ 100, 30, 36 });
    portal.push_back(new Portal{ 1800, 30, 37 });

    enemy.push_back(new Enemy{ {350, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {500, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {650, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {800, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {950, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {1100, 70}, 100 , 0 });
    enemy.push_back(new Enemy{ {1250, 70}, 100 , 0 });
}
void Map::final_boss_create()
{
    ///set_camera
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { 750, 0 } });
    ///obstruct

    obst.push_back(new Obstruct{ 0, 0, 0, 3500, 40 });
}