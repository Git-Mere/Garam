/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  enemy.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "enemy.h"
#include "weapon.h"
#include "doodle/doodle.hpp"
#include "character.h"
#include "SoundEffect.h"
#include <iostream>
using namespace doodle;

std::vector<Enemy*> enemy;
extern Character Garam;
extern Camera camera;
extern int GameState;
extern std::vector<Item*> tem;
extern int bigstate;

Enemy::Enemy(Math::vec2 position, double range, int code) :  position(position), range({position.x + range, position.y})
, start_position(position), item_code(code) {
    sprite.Load2("Assets/enemy/enemy.spt");
    Setblood(GameState);

};

void Enemy::draw(Math::TransformationMatrix camera_matrix)
{
    if (flipped == false) {
        sprite.Draw2(camera_matrix * object_matrix * Math::ScaleMatrix({ scale, scale }));
    }
    else if (flipped == true) {
        sprite.Draw2(camera_matrix * object_matrix * Math::ScaleMatrix({ -scale, scale }));

    }
    draw_hp(camera_matrix);
}

void Enemy::attack()
{
    for (int i = 0; i < enemy.size(); i++) {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= enemy[i]->position.x - enemy[i]->sprite.GetFrameSize().x / 2.0 &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= enemy[i]->position.x + enemy[i]->sprite.GetFrameSize().x / 2.0 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= enemy[i]->position.y + enemy[i]->sprite.GetFrameSize().y / 2.0 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= enemy[i]->position.y - enemy[i]->sprite.GetFrameSize().y / 2.0)
        {
            if (Garam.hit == false && Garam.hp >= 0) {
                Garam.hit = true;
                Garam.hp -= 10;
                if (Garam.hp >= 0)
                    CS230::SoundEffect::Attacked().play();
                if (Garam.flipped == false) {
                    Garam.velocity = { 10, 3 };
                    Garam.flipped = false;
                }
                else if (Garam.flipped == true) {
                    Garam.velocity = { -10, 3 };
                    Garam.flipped = true;

                }
            }
        }
    }

}

Math::ivec2 Enemy::Getspritesize()
{
    return sprite.GetTextureSize() * static_cast<int>(scale);
}



void Enemy::update()
{
    if (position.x > range.x) {
        speed *= -1;
        flipped = false;
    }
    if (position.x < start_position.x) {
        speed *= -1;
        flipped = true;
    }
    attack();
    drop_tem();
    sprite.Update();
    velocity = { speed, 0 };
    position += velocity;

    object_matrix = Math::TranslationMatrix(position);
}

void Enemy::draw_hp(Math::TransformationMatrix camera_matrix)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    double black_hp = sprite.GetFrameSize().x - 20;
    double red_hp = hp / max_hp * black_hp;
    set_outline_width(1);
    push_settings();
    set_fill_color(0, 0, 0);
    draw_rectangle(position.x - pos_x - 20, position.y + sprite.GetFrameSize().y /2.0 + 20 - pos_y, black_hp, 10);
    pop_settings();

    if (hp >= 0) {
        push_settings();
        set_fill_color(128, 0, 0);
        draw_rectangle(position.x - pos_x - 20, position.y + sprite.GetFrameSize().y / 2.0 + 20 - pos_y, red_hp, 10);
        pop_settings();
    }
}

void Enemy::drop_tem()
{
    if (drop && hp <= 0) {
        switch (item_code) {
        case 0:
            break;
        case 1:
            tem.push_back(new Item{ "herb",	1, Kind::potion, {position.x, position.y- 30}, static_cast<GameScene>(GameState) });
            break;
        case 2:
            tem.push_back(new Item{ "mineral_water", 2, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 3:
            tem.push_back(new Item{ "Herb_tonic", 3, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 4:
            tem.push_back(new Item{ "talisman", 4, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 5:
            tem.push_back(new Item{ "leather", 5, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 6:
            tem.push_back(new Item{ "rice_cake", 6, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 7:
            tem.push_back(new Item{ "red_pepper_paste", 7, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 8:
            tem.push_back(new Item{ "white_clothes", 8, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 9:
            tem.push_back(new Item{ "blue_dyes", 9, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 10:
            tem.push_back(new Item{ "so_ju", 10, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 11:
            tem.push_back(new Item{ "skewer", 11, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 12:
            tem.push_back(new Item{ "Seasoned_vegetables", 12, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 13:
            tem.push_back(new Item{ "red_ink", 13, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 14:
            tem.push_back(new Item{ "bamboo", 14, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 15:
            tem.push_back(new Item{ "mandu", 15, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 16:
            tem.push_back(new Item{ "gold", 16, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 17:
            tem.push_back(new Item{ "ink", 17, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 18:
            tem.push_back(new Item{ "black_clothes", 18, Kind::armor, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 19:
            tem.push_back(new Item{ "broken_hammer", 19, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 20:
            tem.push_back(new Item{ "Amulet", 20, Kind::meterial, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;
        case 21:
            tem.push_back(new Item{ "Buldak", 21, Kind::potion, {position.x, position.y - 30}, static_cast<GameScene>(GameState) });
            break;

        }
        drop = false;

    }
}

void Enemy::Setblood(int value)
{
    if (value <= 4) {
        sprite.PlayAnimation(0); //동굴 몬스터
        max_hp = 5;
        hp = 5;
    }
    else if (value > 4 && value <= 12) {
        sprite.PlayAnimation(1); //밖 몬스터
        max_hp = 10;
        hp = 10;
    }
    else if (value > 12 && value <= 16) {
        sprite.PlayAnimation(2); //화산 몬스터
        max_hp = 15;
        hp = 15;
    }
    ///신전 시작
    else if (value == 17) {
        sprite.PlayAnimation(1); //밖 몬스터
        max_hp = 10;
        hp = 10;
    }
    else if (value == 18) {
        sprite.PlayAnimation(2); //화산 몬스터
        max_hp = 15;
        hp = 15;
    }
    else if (value == 19) {
        sprite.PlayAnimation(3); //신전 몬스터
        max_hp = 20;
        hp = 20;
    }

}