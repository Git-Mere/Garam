/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss2.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <iostream>
#include <doodle/doodle.hpp>
#include "Boss2.h"
#include "character.h"
#include "SoundEffect.h"
using namespace doodle;
extern double dt;
extern Character Garam;
extern TonBullet TonB;
extern Camera camera;
extern std::vector<Item*> tem;
extern int GameState;

std::vector<TonBullet*> tonb;

Tonkotsu::Tonkotsu(Math::vec2 position, Camera& camera, const std::filesystem::path& file_path) : start_position(position), position(position),
camera(camera), saved_position{ position }, currentPattern(nullptr) {
    sprite.Load2(file_path);
    
};

TonBullet::TonBullet(Math::vec2 position, int direction, Camera& camera) : position(position), direction(direction), camera(camera) {
    sprite.Load("Assets/Boss2/effect.png");
}

Tonkotsu tonkotsu1({ 50, 100 }, camera, "Assets/Boss2/boss2.1.spt");
Tonkotsu tonkotsu2({ 1550, 100 }, camera, "Assets/Boss2/boss2.2.spt");

std::vector<Tonkotsu*> tons{ &tonkotsu1 , &tonkotsu2 };

Tonkotsu::Pattern* currentPattern = nullptr;

const Tonkotsu::Pattern Tonkotsu::patterns[3] = {
    Tonkotsu::Pattern(1),
    Tonkotsu::Pattern(2),
    Tonkotsu::Pattern(3)
};

Tonkotsu::Pattern* Tonkotsu::GetRandomPattern() {
    int randomIndex = rand() % 3;
    return const_cast<Pattern*>(&patterns[randomIndex]);
}

void Tonkotsu::ExecutePattern(Pattern* pattern) {
    if (pattern->value == 1) {
        jump();
    }
    else if (pattern->value == 2) {
        long_range_attack();
    }
    else if (pattern->value == 3) {
        dash();
    }
}

void Tonkotsu::reset()
{
     hp = 30;

     pattern_delay_time = 0;
     jump_delay_time = 0;
     dash_delay_time = 0;

     alive = true;
     right_dash = false;
     left_dash = false;
     right_check = false;
     left_check = false;
     jump_check = false;
     dash_check = false;
     jump_delay = false;
     dash_delay = false;
     pattern_delay = false;
     is_position_fixed = false;
     drop = true;
}

void Tonkotsu::update() {
    if (hp <= 0) {
        alive = false;
    }

    if (hp > 0) {
        alive = true;
    }
    if (drop && !alive) {
        if (!tons[0]->alive == !tons[1]->alive) {
            tem.push_back(new Item{ "gold",	16, Kind::meterial, position , static_cast<GameScene>(GameState) });
        }
        else {
            tem.push_back(new Item{ "mandu",15, Kind::potion, position, static_cast<GameScene>(GameState) });
        }
        drop = false;
    }

    if (alive == true) {
        object_matrix = Math::TranslationMatrix(position);

        move();
        gravity();
        direction_check();
        jump_attack(currentPattern);
        dash_attack(currentPattern);
        position += velocity;

        if (currentPattern == nullptr) {
            currentPattern = GetRandomPattern();
            ExecutePattern(currentPattern);
        }

        else {
            if (IsPatternFinished(currentPattern)) {
                pattern_delay = true;
                is_position_fixed = false;
            }
        }
        if (Garam.dash == false) {
            attack(currentPattern);
        }
    }

    for (int i = 0; i < tonb.size(); i++) {
        tonb[i]->update();
    }
}

void TonBullet::update() {
    if (direction == 0)
    {
        if (velocity.x >= -max_velocity)
        {
            velocity.x -= 0.3;
        }
        else {
            velocity.x = -max_velocity;
        }
    }

    if (direction == 1)
    {
        if (velocity.x <= max_velocity)
        {
            velocity.x += 0.3;
        }
        else {
            velocity.x = max_velocity;
        }
    }
    position += velocity;
    object_matrix = Math::TranslationMatrix(position);
}

void Tonkotsu::direction_check() {
    if (currentPattern == nullptr) {
        if (Garam.position.x > position.x + 50)
        {
            right_check = true;
            left_check = false;
        }
        else
        {
            right_check = false;
            left_check = true;

        }
    }
}


bool Tonkotsu::IsPatternFinished(Pattern* pattern) {

    if (pattern->value == 1) {
        return !jump_check;
    }
    else if (pattern->value == 2) {
        return true;
    }
    else if (pattern->value == 3) {
        return !dash_check;
    }

    return true;
}

void Tonkotsu::draw(Math::TransformationMatrix camera_matrix)
{
    sprite.Update();
    if (left_check) {
        sprite.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 50,90 })) * Math::ScaleMatrix({ 1, 1 }));
    }
    else{
        sprite.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 50,90 })) * Math::ScaleMatrix({ -1, 1 }));
    }
}

void TonBullet::draw(Math::TransformationMatrix camera_matrix)
{
    if (direction == 0) {
        sprite.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 5,40 })) * Math::ScaleMatrix({ scale, scale }));
    }
    else if (direction == 1) {
        sprite.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 5,40 })) * Math::ScaleMatrix({ -scale, scale }));
    }
}


void Tonkotsu::timer()
{
    if (pattern_delay == true)
    {
        pattern_delay_time += dt;
    }
    if (pattern_delay_time >= pattern_delay_check)
    {
        pattern_delay = false;
        pattern_delay_time = 0;
        currentPattern = nullptr;
    }
    if (jump_delay == true)
    {
        jump_delay_time += dt;
    }
    if (jump_delay_time >= jump_delay_check) {
        velocity.y = -70;
        CS230::SoundEffect::B2_jump_Attack().Big_play();
        jump_delay = false;
        jump_delay_time = 0;
    }
    if (dash_delay == true)
    {
        dash_delay_time += dt;
    }
    if (dash_delay_time >= dash_delay_check) {
        sprite.PlayAnimation(4);
        if (right_dash == true) {
            velocity.x = 25;
            CS230::SoundEffect::B2_baldosool().Big_play();
        }
        if (left_dash == true) {
            velocity.x = -25;
            CS230::SoundEffect::B2_baldosool().Big_play();
        }
        right_dash = false;
        left_dash = false;
        dash_delay = false;
        dash_check = false;
        dash_delay_time = 0; // jump_delay_time을 초기화
    }
}

void Tonkotsu::jump() {
    velocity.y = 30;
    jump_check = true;
    CS230::SoundEffect::Jump().play();
    if (sprite.get_current_animation() == 3) {
        sprite.reset();
    }
    else {
        sprite.PlayAnimation(3);
    }
}

void Tonkotsu::dash() {
    double player_pos = Garam.position.x - 50;
    if (Garam.flipped == false)
    {
        position.x = player_pos - 50;
        right_check = true;
        left_check = false;
        right_dash = true;
        left_dash = false;
    }
    if (Garam.flipped == true)
    {
        position.x = player_pos + 50;
        right_check = false;
        left_check = true;
        left_dash = true;
        right_dash = false;
    }
    dash_check = true;
    CS230::SoundEffect::B2_pew().Big_play();
    if (sprite.get_current_animation() == 1) {
        sprite.reset();
    }
    else {
        sprite.PlayAnimation(1);
    }
}

void Tonkotsu::jump_attack(Pattern* pattern) {
    if (pattern != nullptr && pattern->value == 1 && position.y >= 500 && jump_delay == false) {

        if (!is_position_fixed) {
            velocity.y = 0;
            position.y = 500;
            double player_pos = Garam.position.x - 50;
            position.x = player_pos;
            jump_delay = true;
            is_position_fixed = true;
        }
    }
}

void Tonkotsu::dash_attack(Pattern* pattern) {
    if (pattern != nullptr && pattern->value == 3 && dash_check == true) {
        dash_delay = true;
    }
}

void Tonkotsu::move() {
    if (velocity.x > x_drag) {
        velocity.x -= x_drag;
    }
    else if (velocity.x <= -x_drag) {
        velocity.x += x_drag;
    }
    else if (velocity.x < x_drag && velocity.x >= -x_drag) {
        velocity.x = 0;
    }
}

void Tonkotsu::gravity()
{
    if (position.y < 35)
    {
        position.y = 35;
        velocity.y = 0;
        jump_check = false;
    }
    if (position.y > 35 && jump_delay == false)
    {
        velocity.y -= gravity_c;
    }
}

void Tonkotsu::long_range_attack() {

    if (this == &tonkotsu1 && currentPattern->value == 2) {
        if (left_check) {
            tonb.push_back(new TonBullet({ position.x + 40, position.y }, 0, camera));
            CS230::SoundEffect::B2_swordBeam().Big_play();
        }
        else if (right_check) {
            tonb.push_back(new TonBullet({ position.x + 40, position.y }, 1, camera));
            CS230::SoundEffect::B2_swordBeam().Big_play();
        }
    }
    else if (this == &tonkotsu2 && currentPattern->value == 2) {
        if (left_check) {
            tonb.push_back(new TonBullet({ position.x + 40, position.y }, 0, camera));
            CS230::SoundEffect::B2_swordBeam().Big_play();
        }
        else if (right_check) {
            tonb.push_back(new TonBullet({ position.x + 40, position.y }, 1, camera));
            CS230::SoundEffect::B2_swordBeam().Big_play();
        }
    }
    if (sprite.get_current_animation() == 2) {
        sprite.reset();
    }
    sprite.PlayAnimation(2);
}


void Tonkotsu::draw_hp(Math::TransformationMatrix camera_matrix)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    set_outline_width(1);
    push_settings();
    set_fill_color(0, 0, 0);
    draw_rectangle(position.x-10 - pos_x, position.y + 170 - pos_y, 120, 10);
    pop_settings();

    if (hp >= 0) {
        push_settings();
        set_fill_color(128, 0, 0);
        draw_rectangle(position.x-10 - pos_x, position.y + 170 - pos_y, (hp * 4), 10);
        pop_settings();
    }
}

void Tonkotsu::player_hit()
{
    if (Garam.hit == false && Garam.hp >= 0) {
        Garam.hit = true;
        Garam.hp -= 10;
        if (right_check == true) {
            Garam.velocity = { 15, 3 };
            Garam.flipped = false;
        }
        else if (right_check == false) {
            Garam.velocity = { -15, 3 };
            Garam.flipped = true;

        }
    }
}

void Tonkotsu::attack(Pattern* pattern)
{
    if (pattern->value == 1 && velocity.y < 0 || pattern->value == 3 && velocity.x > 0) {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= position.x &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= position.x + 100 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= position.y + 150 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= position.y)
        {
            player_hit();
        }
    }

    for (int k = 0; k < tonb.size(); k++)
    {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= tonb[k]->position.x &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= tonb[k]->position.x + 20 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= tonb[k]->position.y + 80 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= tonb[k]->position.y)
        {
            player_hit();
        }
    }
}