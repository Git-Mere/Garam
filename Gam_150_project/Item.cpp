/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Item.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "Item.h"
#include "character.h"
#include "map.h"
#include "SoundEffect.h"
#include <doodle/doodle.hpp>

extern int GameState;
extern Character Garam;
extern std::vector<Item*> tem;
extern direct_attack da;

Item::Item() : code{}, stage{}, kind{}
{
}

Item::Item(std::string name, int code, Kind kind) : name(name), code(code), kind(kind), stage{}
{
    Load();
    heal_Load();
}

Item::Item(std::string name, int code, Kind kind, Math::vec2 position, GameScene stage) : name(name), code(code), kind(kind), position(position), stage(stage)
{
    Load();
    heal_Load();
}

void Item::Load()
{
    F.Load("Assets/background/f.png");
    switch (code) {
    case 1:
        texture.Load("Assets/item/herb.png");
        break;
    case 2:
        texture.Load("Assets/item/mineral water.png");
        break;
    case 3:
        texture.Load("Assets/item/hp_potion.png");
        break;
    case 4:
        texture.Load("Assets/item/charm.png");
        break;
    case 5:
        texture.Load("Assets/item/leather.png");
        break;
    case 6:
        texture.Load("Assets/item/rice_cake.png");
        break;
    case 7:
        texture.Load("Assets/item/red_pepper_paste.png");
        break;
    case 8:
        texture.Load("Assets/item/white_clothes.png");
        break;
    case 9:
        texture.Load("Assets/item/blue_dyes.png");
        break;
    case 10:
        texture.Load("Assets/item/so_ju.png");
        break;
    case 11:
        texture.Load("Assets/item/skewer.png");
        break;
    case 12:
        texture.Load("Assets/item/Seasoned vegetables.png");
        break;
    case 13:
        texture.Load("Assets/item/red_ink.png");
        break;
    case 14:
        texture.Load("Assets/item/bamboo.png");
        break;
    case 15:
        texture.Load("Assets/item/mandu.png");
        break;
    case 16:
        texture.Load("Assets/item/gold.png");
        break;
    case 17:
        texture.Load("Assets/item/ink.png");
        break;
    case 18:
        texture.Load("Assets/item/black_clothes.png");
        break;
    case 19:
        texture.Load("Assets/item/broken_hammer.png");
        break;
    case 20:
        texture.Load("Assets/item/necklace.png");
        break;
    case 21:
        texture.Load("Assets/item/ramen.png");
        break;
    case 22:
        texture.Load("Assets/item/cane.png");
        break;
    case 23:
        texture.Load("Assets/item/cane2.png");
        break;
    case 24:
        texture.Load("Assets/item/blue_clothes.png");
        break;
    case 25:
        texture.Load("Assets/item/goldblack_clothes.png");
        break;

    }
}

    



void Item::heal_Load()
{
    if (kind == Kind::potion) {
        if (name == "herb") { healing_amount = 10; }
        else if (name == "Herb_tonic") { healing_amount = 30; }
        else if (name == "mineral_water") { healing_amount = 15; }
        else if (name == "rice_cake") { healing_amount = 10; }
        else if (name == "red_pepper_paste") { healing_amount = 10; }
        else if (name == "Seasoned_vegetables") { healing_amount = 50; }
        else if (name == "so_ju") { healing_amount = 140; }
        else if (name == "mandu") { healing_amount = 140; }
        else if (name == "Buldak") { healing_amount = 140; }
        else if (name == "skewer") { deal_amount = 1; }
    }
    else if (kind == Kind::weapon) {
        if (name == "skewer") { deal_amount = 1; }

        else {
            deal_amount = 3;
        }
    }
    else if (kind == Kind::armor) {
        hp_amount = 25;
    }
}

void Item::draw(Camera& camera)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    Math::vec2 a = { 0 - pos_x, 0 - pos_y };
    doodle::draw_image(texture.image, position.x - pos_x, position.y - pos_y, 40, 40);
}

void Item::col(Character garam)
{
    if (sqrt((position.x - garam.position.x) * (position.x - garam.position.x) + (position.y - garam.position.y) * (position.y - garam.position.y)) < 100) {
        can_drop = true;
    }
    else {
        can_drop = false;
    }
}

void Item::amount()
{
    if (kind == Kind::potion) {
        if (Garam.hp + healing_amount > Garam.max_hp) {
            Garam.hp += healing_amount - (Garam.hp + healing_amount - static_cast<int>(Garam.max_hp));
            CS230::SoundEffect::recovery1().Big_play();
        }
        else {
            Garam.hp += healing_amount;
            CS230::SoundEffect::recovery1().Big_play();
        }
        Garam.AD += deal_amount;
    }
    else if (kind == Kind::weapon) {
        Garam.AD += deal_amount;
        if (name == "Elder tree cane") { da.sprite.Load("Assets/character/ATTACK2.png"); CS230::SoundEffect::Weapon_change().Big_play();}
        else if (name == "Metal cane") { da.sprite.Load("Assets/character/ATTACK3.png"); CS230::SoundEffect::Weapon_change().Big_play();}
    }
    else if (kind == Kind::armor) {
        Garam.max_hp += hp_amount;
        if (name == "Blue Hanbok") { Garam.sprite.Load2("Assets/character/Blue_Man.spt");  CS230::SoundEffect::Weapon_change().Big_play(); }
        else if (name == "Black Hanbok") { Garam.sprite.Load2("Assets/character/Black_Man.spt");  CS230::SoundEffect::Weapon_change().Big_play(); }
    }
}
