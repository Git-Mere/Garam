/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss4.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <iostream>
#include <doodle/doodle.hpp>
#include <random>
#include <cmath>
#include "Boss4.h"
#include "character.h"
#include "SoundEffect.h"
using namespace doodle;
extern double dt;
extern Character Garam;
std::random_device rd_new;
std::mt19937 gen_new(rd_new());
extern std::vector<Item*> tem;
extern int GameState;

Sandworm::Sandworm(Math::vec2 position, Camera& camera) : start_position(position), position(position),
camera(camera), saved_position{ position }, currentPattern(nullptr) {
    up.Load2("Assets/Boss4/boss4up.spt");
    swim.Load2("Assets/Boss4/boss4swim.spt");
    circle.Load("Assets/Boss4/wyrm2.png");
};

Sandworm::Pattern* currentPattern = nullptr;

const Sandworm::Pattern Sandworm::patterns[2] = {
    Sandworm::Pattern(1),
    Sandworm::Pattern(2)
};

Sandworm::Pattern* Sandworm::GetRandomPattern() {
    int randomIndex = rand() % 2;
    return const_cast<Pattern*>(&patterns[randomIndex]);
}

void Sandworm::ExecutePattern(Pattern* pattern) {
    if (pattern->value == 1 || pattern->value == 2) {
        position.y = 35;
        rise_timer = 0;
    }
    if (pattern->value == 1) {
        dive = true;
    }
}

bool Sandworm::IsPatternFinished(Pattern* pattern) {

    if (pattern->value == 1) {
        return !dive;
    }
    else if (pattern->value == 2) {
        return true;
    }
    return true;
}

void Sandworm::update() {
    if (hp <= 0) {
        alive = false;
    }

    if (hp > 0) {
        alive = true;
    }
    if (drop && !alive) {
        tem.push_back(new Item{ "Amulet",	20, Kind::meterial, {position.x - 30, position.y} , static_cast<GameScene>(GameState) });
        tem.push_back(new Item{ "Buldak",	21, Kind::potion, {position.x + 30, position.y}, static_cast<GameScene>(GameState) });
        drop = false;
    }
    if (alive == true) {
        object_matrix = Math::TranslationMatrix(position);
        position += velocity;
        diving();
        direction_check();
        if (currentPattern == nullptr) {
            position.y = -1000;

            if (!isPatternGenerated) {
                move();
                isPatternGenerated = true;
            }

            if (rise_timer > 2) {
                rise_attack = true;
                //up.reset();
                up.PlayAnimation(1);
                currentPattern = GetRandomPattern();
                ExecutePattern(currentPattern);
                isPatternGenerated = false;
            }
        }
        else {
            if (IsPatternFinished(currentPattern)) {
                pattern_delay = true;
            }
            attack(currentPattern);
        }
    }
}

void Sandworm::timer()
{
    if (pattern_delay == true)
    {
        pattern_delay_time += dt;
    }
    if (pattern_delay_time >= 2.8)
    {
        up.PlayAnimation(2);
    }

    if (pattern_delay_time >= pattern_delay_check)
    {
        pattern_delay = false;
        pattern_delay_time = 0;
        currentPattern = nullptr;
    }
    if (position.y == -1000) {
        rise_timer += dt;
    }
    if (dive == true) {
        dive_timer += dt;
    }

    if (blast == true) {
        blast_timer += dt;
    }

    if (rise_attack == true) {
        hit_timer += dt;
    }

    if (hit_timer >= 0.4) {
        CS230::SoundEffect::B3_Bbaeggom().play();
        rise_attack = false;
        hit_timer = 0;
        up.PlayAnimation(0);
    }
}

void Sandworm::draw(Math::TransformationMatrix camera_matrix)
{
    up.Update();
    swim.Update();
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    if (position.y >= 0) {
        if (left_check) {
            up.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,180 })) * Math::ScaleMatrix({ scale, scale }));
        }
        else {
            up.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,180 })) * Math::ScaleMatrix({ -scale, scale }));

        }
    }
    if (position.y == -1000) {
        circle.Draw(camera_matrix * Math::TranslationMatrix(Math::vec2{ randomNumber + 100, 20 }) * Math::ScaleMatrix(scale));
    }
    if (dive_timer > 3 && dive_timer <= 6) {
        circle.Draw(camera_matrix * Math::TranslationMatrix(Math::vec2{ randomNumber, 20 }) * Math::ScaleMatrix({ 12, scale }));
    }
    if (dive_timer > 6 && dive_timer <= 6.6) {
        swim.Draw2((camera_matrix * Math::TranslationMatrix(Math::vec2{ position.x + 50, 200 })) * Math::ScaleMatrix({ 3.5, scale }));
    }
}

void Sandworm::direction_check() {
    if (Garam.position.x > position.x + 100)
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

void Sandworm::move() {
    int pos_x = static_cast<int>(camera.GetPosition().x);
    // 땅속에서 가능한 X 좌표 범위 정의 (예시: 100부터 Width-100까지)
    int minX = 100 + pos_x;
    int maxX = Width - 100 + pos_x;
    std::uniform_int_distribution<int> dist(minX, maxX);
    randomNumber = dist(gen_new);
    position.x = randomNumber;
}

void Sandworm::diving() {
    if (dive_timer > 2.8) {
        up.PlayAnimation(2);
    }

    if (dive_timer > 3 && dive_timer <= 6) {
        position.y = -900;
        swim.PlayAnimation(0);
    }

    if (dive_timer >= 6) {
        if (dive_timer < 6.028)
        {
            CS230::SoundEffect::B3_WormJump().play();
        }
        swim.PlayAnimation(1);
    }

    if (dive_timer > 6.6) {
        dive = false;
        dive_timer = 0;
    }
}

void Sandworm::player_hit()
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

void Sandworm::reset()
{
    hp = 50;

    randomNumber = 0;
    rise_timer = 0;
    dive_timer = 0;
    hit_timer = 0;
    blast_timer = 0;

    pattern_delay_time = 0;
    pattern_delay_check = 3;

    alive = true;
    drop = true;

    position = { 600, 30 };
}

void Sandworm::attack(Pattern* pattern)
{
    if (rise_attack == true) {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= position.x &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= position.x + 200 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= position.y + 450 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= position.y)
        {
            player_hit();
        }
    }

    if (dive_timer > 6 && dive_timer <= 6.6) {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= position.x - 600 &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= position.x + 600 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= 20 + 450 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= 20)
        {
            player_hit();
        }
    }
}

void Sandworm::draw_hp(Math::TransformationMatrix camera_matrix)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    set_outline_width(1);
    push_settings();
    set_fill_color(0, 0, 0);
    draw_rectangle(position.x - pos_x, position.y + 350 - pos_y, 200, 10);
    pop_settings();

    if (hp >= 0) {
        push_settings();
        set_fill_color(128, 0, 0);
        draw_rectangle(position.x - pos_x, position.y + 350 - pos_y, (hp * 4), 10);
        pop_settings();
    }
}