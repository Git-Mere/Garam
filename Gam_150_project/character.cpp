/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  character.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <iostream>
#include <doodle/doodle.hpp>
#include "character.h"
#include "SoundEffect.h"
#include "Boss1.h"
#include "map.h"

using namespace doodle;

extern bool moveW;
extern bool moveA;
extern bool moveS;
extern bool moveD;
extern Meretoss mere;
extern Map map;
extern double dt;
extern std::vector<Obstruct*> obst;
extern direct_attack da;

Character::Character(Math::vec2 position, Camera& camera) :  position(position),
camera(camera), saved_position{ position }{};

void Character::update() {
    if (position.x - sprite.GetFrameSize().x / 2.0 < camera.GetPosition().x) {
        position.x = camera.GetPosition().x + sprite.GetFrameSize().x / 2.0;
        velocity.x = 0;
    }
    if (position.x + sprite.GetFrameSize().x / 2.0 > camera.GetPosition().x + Width) {
        position.x = camera.GetPosition().x + Width - sprite.GetFrameSize().x / 2.0;
        velocity.x = 0;
    }

    move();
    deter_animation();
    col_help();
    pos_reset();

    hp_reset();
    superstance();
    inventory.update();
    sprite.Update();
    object_matrix = Math::TranslationMatrix(position);

    if (flipped == true && !dead) {
        object_matrix *= Math::ScaleMatrix({ -1, 1 });
    }
    if (hp <= 0 && dead == false) { 
        dead = true; 
        saved_position = position;
        velocity = { 0,0 };
        position = { position.x, position.y + 300 };
    }

    if (velocity.y != 0) {
        is_sound_used = true;
    }
    else if (velocity.y == 0 && is_sound_used) {
        CS230::SoundEffect::Landing().play();
        is_sound_used = false;
    }
}

void Character::Load()
{
    sprite.Load2("Assets/character/Man.spt");
    hp_bar.Load("Assets/character/hp.png");
    RIP.Load("Assets/character/dead.png");
    sprite.deter_frame_size(1);
    velocity = { 0, 0 };
}

void Character::draw(Math::TransformationMatrix camera_matrix)
{
    if ((hit_timer == 0.0 || TickTock == true) && dead == false) {
        sprite.Draw2(camera_matrix * object_matrix * Math::ScaleMatrix({ scale, scale }));
    }
    else if (dead) {
        RIP.Draw(object_matrix);
    }
    draw_hp();

    hp_bar.Draw(Math::TranslationMatrix(Math::ivec2{ 70 , Height - 45 }));

}

void Character::move() {
    if (dead == false) {
        if (moveD == true && dash == false && stun == false) {
            flipped = false;
            sprite.PlayAnimation(2);
            if (velocity.x >= 0) {
                velocity.x += x_acceleration;
                if (velocity.x > max_velocity) {
                    velocity.x = max_velocity;
                }
            }
            else {
                velocity.x += (x_drag * 2);
            }
        }
        else if (moveA == true && dash == false && stun == false) {
            sprite.PlayAnimation(2);

            flipped = true;
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
        else {
            sprite.PlayAnimation(0);

            if (velocity.x >= x_drag) {
                velocity.x -= x_drag;

            }
            else if (velocity.x <= -x_drag) {
                velocity.x += x_drag;

            }
            else if (velocity.x < x_drag && velocity.x >= -x_drag) {
                velocity.x = 0;
            }
        }
        velocity.y -= gravity_c;
        position += velocity;
    }
    if (dead == true) {
        if (saved_position.y < position.y + GetFrameSize().y / 4.0) {
            velocity.y -= gravity_c;
            position += velocity;
        }
    }
}

void Character::pos_reset() {
    if (position.y <= -300 ) {
        if (hp - 10 > 0) {
            position = saved_position;
            CS230::SoundEffect::Attacked().play();
        }
        hp -= 10;
    }
}

Math::ivec2 Character::Getspritesize()
{
    return sprite.GetTextureSize() * static_cast<int>(scale);
}

Math::ivec2 Character::GetFrameSize()
{
    return sprite.GetFrameSize() * static_cast<int>(scale);
}

void Character::deter_animation()
{
    if (jump_count == 0) {
        sprite.PlayAnimation(1);
    }
    if (dash) {
        sprite.PlayAnimation(3);
    }
    if (da.go) {
        sprite.PlayAnimation(4);
    }
    if (stun) {
        sprite.PlayAnimation(5);
    }
}

void Character::reset()
{
     can_drop = false;
     open_inven = false;
     hit = false;
     flipped = false;
     landing_check = false;
     dash = false;
     stun = false;
     dead = false;

     max_velocity = 7;
     hit_timer = 0;
     dash_timer = 0;
     dash_delay = 0.55;
     scale = 1.5;

     dash_range = 17;
     jump_count = 0;
     max_hp = 100;
     hp = 100;
     AD = 1;
     current_weapon = 1;

     position = { 120, 1500 };
     velocity = { 0,0 };
}


void Character::col(Obstruct* ob) {
    double left_x = ob->x;
    double right_x = ob->x + ob->width;
    double up_y = ob->y + ob->height;
    double down_y = ob->y;

    double pos_left_x = position.x - sprite.GetFrameSize().x / 2.0;
    double pos_right_x = position.x + sprite.GetFrameSize().x / 2.0;
    double pos_up_y = position.y + sprite.GetFrameSize().y / 2.0;
    double pos_down_y = position.y - sprite.GetFrameSize().y / 2.0;

    if (right_x >= pos_left_x && left_x <= pos_right_x && down_y <= pos_up_y && up_y >= pos_down_y && dead == false)
    {
        double left_diff = abs(pos_left_x - right_x);
        double right_diff = abs(left_x - pos_right_x);
        double up_diff = abs(pos_up_y - down_y);
        double down_diff = abs(up_y - pos_down_y);

        double min_diff = std::min(std::min(left_diff, right_diff), std::min(up_diff, down_diff));

        if (min_diff == left_diff) {           
            if (position.y > down_y && position.y < up_y) {
                position.x = right_x + sprite.GetFrameSize().x / 2.0;
                velocity.x = 0;
            }
        }
        else if (min_diff == right_diff) {         
            if (position.y > down_y && position.y < up_y) {
                position.x = left_x - sprite.GetFrameSize().x / 2.0;
                velocity.x = 0;
            }
        }
        else if (min_diff == up_diff) {
            if (position.x > left_x && position.x < right_x) {
                position.y = down_y - sprite.GetFrameSize().y / 2.0;
                velocity.y = 0;
            }
        }
        else if (min_diff == down_diff) {
            if (position.x > left_x && position.x < right_x) {
                position.y = up_y + sprite.GetFrameSize().y / 2.0;

                landing_check = true;
                velocity.y = 0;
                jump_count = 1;
            }
        }
    }
}

void Character::col_help()
{
    for (int i = 0; i < obst.size(); i++) {
        col(obst[i]);
    }
}

void Character::hp_reset() 
{
    if (hp <= 0)
    {
        hp = 0;
    }
}

void Character::draw_hp()
{
    if (hp >= 0) {
        push_settings();
        set_fill_color(0);
        set_outline_color(0);
        draw_rectangle(75, Height - 60, max_hp*3, 27);
        pop_settings();

        push_settings();
        set_fill_color(128, 0, 0);
        draw_rectangle(75, Height - 60, hp / max_hp * max_hp*3, 27);
        pop_settings();
    }
    push_settings();
    set_font_size(15);
    draw_text("Damage : " + std::to_string(AD), 70, Height - 80);
    draw_text("Max hp : " + std::to_string(static_cast<int>(max_hp)), 70, Height - 100);
    pop_settings();

}

void Character::superstance()
{
    if (hit_timer > 1) {
        hit = false;
        hit_timer = 0;
    }
    if (dash_timer >= dash_delay) {
        dash = false;
        dash_timer = 0;
    }
}

void Character::timer()
{
    if (hit == true) {
        hit_timer += dt;
        TickTock = !TickTock;
    }
    if (dash == true) {
        dash_timer += dt;
    }
}
