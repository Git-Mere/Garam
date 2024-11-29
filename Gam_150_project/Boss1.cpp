/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss1.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <iostream>
#include <doodle/doodle.hpp>
#include "Boss1.h"
#include "character.h"
#include"SoundEffect.h"
#include <cmath>
using namespace doodle;
extern int GameState;
extern double dt;
extern Character Garam;
extern Map map;
extern std::vector<Item*> tem;

Meretoss::Meretoss(Math::vec2 position, Camera& camera) : start_position(position), position(position),
camera(camera), saved_position{ position } {};

void Meretoss::Load() {
    sprite.Load2("Assets/Boss1/boss1.spt");
    sprite.deter_frame_size(1);
    Boss.Load("Assets/Boss1/boss_standing.png", { {62, 0} });
    Boss2.Load("Assets/Boss1/boss_attack.png", { {62, 0} });
    Boss3.Load("Assets/Boss1/boss_attack2.png", { {62, 0} });
    sprite.PlayAnimation(0);

    STUN.Load("Assets/Boss1/Howling_on.png", { { 70, -160 } });
}

void Meretoss::update() {
    if (hp <= 0) {
        alive = false;
    }

    if (hp > 0) {
        alive = true;
    }
    if (drop && !alive) {
        tem.push_back(new Item{ "blue_dyes",	9, Kind::meterial, {position.x - 30, position.y} , static_cast<GameScene>(GameState) });
        tem.push_back(new Item{ "so_ju",	10, Kind::potion, {position.x + 30, position.y}, static_cast<GameScene>(GameState) });
        drop = false;
    }


    if (alive == true) {
        object_matrix = Math::TranslationMatrix(position);
        if (a_delay == false && j_delay == false) {
            move();
        }
        if (moving_check == true) {
            if (velocity.x != 10) {
                sprite.PlayAnimation(0);
            }
            attack_timer = 0;
        }
        if (velocity.x == 0 && attack_timer > attack_timer_check && j_delay == false) {
            if (Garam.dash == false) {
                attack();
                if (Garam.hit == false && Garam.hp >= 0) {
                    Garam.hit = true;
                    Garam.hp -= 10;
                }
            }
            attack_timer = 0;
            jump_timer = 0;
            a_delay = true;
        }
        jump_attack();
        stun_activate();
        position += velocity;
    }
    sprite.Update();
}

void Meretoss::draw(Math::TransformationMatrix camera_matrix)
{
    if (velocity.x != 0 || a_delay == true) {
        if (right_check) {
            sprite.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,200 })) * Math::ScaleMatrix({ scale, scale }));
        }
        else if (left_check) {
            sprite.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,200 })) * Math::ScaleMatrix({ -scale, scale }));
        }
    }

    if (velocity.x == 0) {
        if (right_check == true) {
            if (moving_check == true && j_delay == false) {
                Boss.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ scale, scale }));
            }
            if (moving_check == false && a_delay == false && j_delay == false || velocity.y > 0 && j_delay == true) {
                Boss2.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ scale, scale }));
            }
            if (velocity.y <= 0 && j_delay == true) {
                Boss3.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ scale, scale }));
            }
        }
        if (left_check == true) {
            if (moving_check == true && j_delay == false) {
                Boss.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ -scale, scale }));
            }
            if (moving_check == false && a_delay == false && j_delay == false || velocity.y > 0 && j_delay == true) {
                Boss2.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ -scale, scale }));
            }
            if (velocity.y <= 0 && j_delay == true) {
                Boss3.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ -scale, scale }));
            }
        }
        if (stun_timer < 1 && Garam.stun == true) {
            STUN.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 100,0 })) * Math::ScaleMatrix({ scale, scale }));
        }
    }
}

void Meretoss::move() {
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

    if (Garam.position.x > position.x + 300)
    {
        moving_check = true;
        if (move_timer >= timer_check) {
            if (velocity.x >= 0) {
                velocity.x += x_acceleration;
                if (velocity.x > max_velocity)
                {
                    velocity.x = max_velocity;
                }
            }
            else {
                velocity.x += (x_drag * 2);
            }

        }
    }
    else if (Garam.position.x < position.x - 100)
    {
        moving_check = true;
        if (move_timer >= timer_check) {
            if (velocity.x <= 0) {
                velocity.x -= x_acceleration;
                if (velocity.x < -max_velocity) {
                    velocity.x = -max_velocity;
                }
            }
            else {
                velocity.x -= (x_drag * 2);
            }
        }
    }

    else if (Garam.position.x > position.x - 100 && Garam.position.x < position.x + 300) {
        //if (right_check == true) {
        //    Garam.velocity.x = 10;
        //}
        moving_check = false;
        move_timer = 0;
        stun_delay_timer = 0;
        max_velocity = 5;
        if (velocity.x >= x_drag) {
            velocity.x -= (x_drag * 2);
        }
        else if (velocity.x <= -x_drag) {
            velocity.x += (x_drag * 2);
        }
        else if (velocity.x < x_drag && velocity.x >= -x_drag) {
            velocity.x = 0;
        }
    }
}

void Meretoss::attack()
{
    if (right_check == true) {
        Garam.velocity.x = 15;
        Garam.flipped = false;
        CS230::SoundEffect::B1_swing().Big_play();

    }
    else {
        Garam.velocity.x = -15;
        Garam.flipped = true;
        CS230::SoundEffect::B1_swing().Big_play();

    }
}

void Meretoss::jump_attack()
{
    if (position.y < 35)
    {
        position.y = 35;
        velocity.y = 0;
    }
    if (position.y > 35)
    {
        velocity.y -= gravity_c;
    }

    double b_distance = Garam.position.x - (position.x + 100);
    if (abs(b_distance) > 600) {
        sprite.PlayAnimation(1);
        max_velocity = 10;
        stun_delay = false;
        stun_delay_timer = 0;
    }
    else {
        stun_delay = true;
    }

    if (jump_timer >= jump_timer_check)
    {
        velocity.y = 16;
        jump_timer = 0;
        j_delay = true;
    }

    if (j_delay_timer >= j_delay_check)
    {
        j_delay_timer = 0;
        attack_timer = 0;
        j_delay = false;

        if (left_check == true) {
            Garam.velocity.x = -30;
            Garam.flipped = true;
        }
        if (right_check == true) {
            Garam.velocity.x = 30;
            Garam.flipped = false;
        }

        if (Garam.hit == false && Garam.hp >= 0) {
            Garam.hit = true;
            Garam.hp -= 10;
        }
        Garam.stun = true;
        CS230::SoundEffect::B1_JumpAttack().Big_play();
    }
}

void Meretoss::stun_activate()
{
    if (stun_delay_timer >= stun_delay_t_check)
    {
        stun_delay = false;
        Garam.stun = true;
        Garam.velocity.x = true;
        stun_delay_timer = 0;
    }

    if (stun_timer >= stun_timer_check)
    {
        Garam.stun = false;
        stun_timer = 0;
    }
}

void Meretoss::timer()
{
    if (moving_check == true && move_timer <= timer_check)
    {
        move_timer += dt;
    }
    if (velocity.x == 0 && moving_check == false && GameState == GameScene::first_boss && j_delay == false && a_delay == false)
    {
        attack_timer += dt;
        sprite.PlayAnimation(2);
    }
    if (velocity.x == 0 && GameState == GameScene::first_boss && a_delay == false)
    {
        sprite.deter_frame_size(2);
        jump_timer += dt;
    }
    if (velocity.x != 0)
    {
        sprite.deter_frame_size(2);
        jump_timer = 0;
    }
    if (a_delay == true)
    {
        sprite.deter_frame_size(2);
        a_delay_timer += dt;
    }
    if (a_delay_timer >= a_delay_check)
    {
        sprite.deter_frame_size(2);
        a_delay_timer = 0;
        a_delay = false;
    }
    if (j_delay == true)
    {
        j_delay_timer += dt;
    }
    if (stun_delay == true && Garam.stun == false)
    {
        stun_delay_timer += dt;
    }
    if (Garam.stun == true)
    {
        stun_timer += dt;
    }
}

void Meretoss::draw_hp(Math::TransformationMatrix camera_matrix)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    set_outline_width(1);
    push_settings();
    set_fill_color(0, 0, 0);
    draw_rectangle(position.x + 20 - pos_x, position.y + 350 - pos_y, 160, 10);
    pop_settings();

    if (hp >= 0) {
        push_settings();
        set_fill_color(128, 0, 0);
        draw_rectangle(position.x + 20 - pos_x, position.y + 350 - pos_y, (hp * 4), 10);
        pop_settings();
    }
}

Math::ivec2 Meretoss::Getspritesize()
{
    return sprite.GetTextureSize() * static_cast<int>(scale);
}
