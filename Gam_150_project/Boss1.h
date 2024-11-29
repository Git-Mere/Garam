/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss1.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "vec2.h"
#include "camera.h"
#include "sprite.h"
class Meretoss {

public:
    Meretoss(Math::vec2 position, Camera& camera);

    double max_velocity = 5;
    double move_timer = 0;
    double timer_check = 1.5;
    double attack_timer = 0;
    double attack_timer_check = 1;
    double jump_timer = 0;
    double jump_timer_check = 4;
    double a_delay_timer = 0;
    double a_delay_check = 1;
    double j_delay_timer = 0;
    double j_delay_check = 0.8;
    double stun_timer = 0;
    double stun_timer_check = 1;
    double stun_delay_timer = 0;
    double stun_delay_t_check = 4;

    double scale = 1.7;

    int hp = 40;

    bool mere_move = false;
    bool moving_check = false;
    bool left_check = false;
    bool right_check = false;
    bool attack_check = false;
    bool a_delay = false;
    bool j_delay = false;
    bool stun_delay = false;
    bool alive = true;
    bool drop = true;

    void update();
    void Load();
    void move();
    void attack();
    void jump_attack();
    void timer();
    void stun_activate();
    void draw(Math::TransformationMatrix camera_matrix);
    void draw_hp(Math::TransformationMatrix camera_matrix);
    Math::ivec2 Getspritesize();

    Camera& camera;

    Math::vec2 position;
    Math::vec2 velocity;
    Math::vec2 saved_position;
    Sprite sprite;
    Sprite Boss;
    Sprite Boss2;
    Sprite Boss3;
    Sprite STUN;
    Math::TransformationMatrix object_matrix;
private:
    Math::vec2 start_position;
    static constexpr double x_acceleration = 1.2;
    static constexpr double x_drag = 0.6;
    static constexpr double gravity_c = 0.8;
};