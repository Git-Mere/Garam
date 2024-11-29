/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  weapon.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <cmath>
#include "weapon.h"
#include "enemy.h"
#include "character.h"
#include "doodle/doodle.hpp"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Boss4.h"
#include "SoundEffect.h"

using namespace doodle;
extern double dt;
extern Character Garam;
extern std::vector<Enemy*> enemy;
extern int GameState;
extern Meretoss mere;
extern std::vector<Tonkotsu*> tons;
extern Sandworm worm;
extern Elementalist lux;

//캐릭터랑 생긴건 똑같은데 direction 추가해서 왼쪽 오른쪽 구별해서 객체별로 넣어줌
Bullet::Bullet(Math::vec2 position, bool flipped) :  position(position), flipped(flipped), first_position(position){
    sprite.Load("Assets/item/charm.png");
}

void Bullet::draw(Math::TransformationMatrix camera_matrix)
{
    if (!flipped) {
        sprite.Draw(camera_matrix * object_matrix * Math::ScaleMatrix({ -scale, scale }));
    }
    else if(flipped) {
        sprite.Draw(camera_matrix * object_matrix * Math::ScaleMatrix({ scale, scale }));
    }
}

//이제 총알마다 x값 y값 direction값이 들어있는데 그게 생성됐을때 0이면 왼쪽 1이면 오른쪽
void Bullet::bullet_info()
{
    if (flipped)
    {
        position.x -= 20;
    }
    else if (!flipped)
    {
        position.x += 20;
    }

    object_matrix = Math::TranslationMatrix(position);
}

Math::ivec2 Bullet::Getspritesize()
{
    return sprite.GetTextureSize() * static_cast<int>(scale);
}

void throw_attack::add(Math::vec2 position, bool flipped)
{
    if (Garam.inventory.sum_find_tem(4) > 0) {
        bullets.push_back(new Bullet{ position, flipped });
        Garam.inventory.find_tem(4).tem.second -= 1;
    }
}
throw_attack::throw_attack()
{
    sprite.Load2("Assets/character/swap.spt");
    sprite.PlayAnimation(1);
}
void throw_attack::draw(Math::TransformationMatrix camera_matrix)
{
    sprite.Update();

    for (auto bul : bullets) {
        bul->draw(camera_matrix);
    }
    sprite.Draw2(Math::TranslationMatrix(Math::ivec2{ Width - 100 , Height - 670 }) * Math::ScaleMatrix(2));
    if (Garam.current_weapon == 2) {
        push_settings();
        set_outline_color(255);
        set_font_size(20);
        no_fill();
        draw_text(std::to_string(Garam.inventory.sum_find_tem(4)), Width - 100, Height - 690);

        pop_settings();
    }
}
void throw_attack::timer()
{
    if (shoot == true) {
        bullet_timer += dt;
    }
    if (bullet_timer >= bullet_delay) {
        bullet_timer = 0;
        shoot = false;
    }
}
void throw_attack::update()
{

    for (int j = 0; j < bullets.size(); j++)
    {
        bullets[j]->bullet_info();

        if (abs(bullets[j]->position.x - bullets[j]->first_position.x) >= range) {
            delete bullets[j];
            bullets.erase(bullets.begin() + j);
        }
    }
    for (int j = 0; j < bullets.size(); j++) {
        for (int i = 0; i < enemy.size(); i++) {
            if (bullets[j]->position.x + bullets[j]->Getspritesize().x / 2.0 >= enemy[i]->position.x - enemy[i]->sprite.GetFrameSize().x / 2.0 &&
                bullets[j]->position.x - bullets[j]->Getspritesize().x / 2.0 <= enemy[i]->position.x + enemy[i]->sprite.GetFrameSize().x / 2.0 &&
                bullets[j]->position.y - bullets[j]->Getspritesize().y / 2.0 <= enemy[i]->position.y + enemy[i]->sprite.GetFrameSize().y / 2.0 &&
                bullets[j]->position.y + bullets[j]->Getspritesize().y / 2.0 >= enemy[i]->position.y - enemy[i]->sprite.GetFrameSize().y / 2.0
                )
            {
                enemy[i]->hp -= charm_damage;
                CS230::SoundEffect::B4_Fireball().play();
                delete bullets[j];
                bullets.erase(bullets.begin() + j);
                break;
            }
        }
    }

    if (GameState == GameScene::first_boss && mere.alive == true) {
        for (int i = 0; i < bullets.size(); i++) {
            if (bullets[i]->position.x + bullets[i]->Getspritesize().x / 2.0 >= mere.position.x + 100 &&
                bullets[i]->position.x - bullets[i]->Getspritesize().x / 2.0 <= mere.position.x + 140)
            {
                mere.hp -= charm_damage;
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                CS230::SoundEffect::B4_Fireball().play();
            }
        }
    }

    if (GameState == GameScene::forest_boss) {
        for (int j = 0; j < bullets.size(); j++) {
            for (int i = 0; i < tons.size(); i++) {
                if (tons[i]->alive == true) {
                    if (bullets[j]->position.x + bullets[j]->Getspritesize().x / 2.0 >= tons[i]->position.x &&
                        bullets[j]->position.x - bullets[j]->Getspritesize().x / 2.0 <= tons[i]->position.x + 100 &&
                        bullets[j]->position.y - bullets[j]->Getspritesize().y / 2.0 <= tons[i]->position.y + 150 &&
                        bullets[j]->position.y + bullets[j]->Getspritesize().y / 2.0 >= tons[i]->position.y
                        )
                    {
                        tons[i]->hp -= charm_damage;
                        delete bullets[j];
                        bullets.erase(bullets.begin() + j);
                        CS230::SoundEffect::B4_Fireball().play();
                        break;
                    }
                }
            }
        }
    }

    if (GameState == GameScene::volcano_boss && worm.alive == true) {
        for (int i = 0; i < bullets.size(); i++) {
            if (bullets[i]->position.x + bullets[i]->Getspritesize().x / 2.0 >= worm.position.x &&
                bullets[i]->position.x - bullets[i]->Getspritesize().x / 2.0 <= worm.position.x + 200 &&
                bullets[i]->position.y - bullets[i]->Getspritesize().y / 2.0 <= worm.position.y + 450 &&
                bullets[i]->position.y + bullets[i]->Getspritesize().y / 2.0 >= worm.position.y
                )
            {
                worm.hp -= charm_damage;
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                CS230::SoundEffect::B4_Fireball().play();
            }
        }
    }

    if (GameState == GameScene::final_boss && lux.alive == true) {
        for (int i = 0; i < bullets.size(); i++) {
            if (bullets[i]->position.x + bullets[i]->Getspritesize().x / 2.0 >= lux.position.x &&
                bullets[i]->position.x - bullets[i]->Getspritesize().x / 2.0 <= lux.position.x + 100 &&
                bullets[i]->position.y - bullets[i]->Getspritesize().y / 2.0 <= lux.position.y + 150 &&
                bullets[i]->position.y + bullets[i]->Getspritesize().y / 2.0 >= lux.position.y
                )
            {
                lux.hp -= charm_damage;
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                CS230::SoundEffect::B4_Fireball().play();
            }
        }
    }
    
}
