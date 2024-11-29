/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  camera.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "doodle/environment.hpp"
#include "Camera.h"

using namespace doodle;

extern int window_width;
extern int window_height;

void Camera::SetPosition(Math::vec2 new_position) {
    position = new_position;
}

const Math::vec2& Camera::GetPosition() const {
    return position;
}

Math::TransformationMatrix Camera::GetMatrix() {
    return Math::TranslationMatrix(-position);
}

void Camera::SetLimit(Math::irect new_limit) {
    limit = new_limit;
}

void Camera::SetPzon(Math::rect new_zone)
{
    player_zone = new_zone;
}

void Camera::Update(const Math::vec2& player_position, bool& player_flipped) {
    if (player_flipped == false) {
        SetPzon({ { 0.15 * Width, 0 }, { 0.45 * Width, 100 } });
    }
    if (player_flipped == true) {
        SetPzon({ { 0.45 * Width, 0 }, { 0.85 * Width, 100 } });
    }
    if (player_position.y > window_height) {
            limit.point_2.y = window_height;
    }
    else {
            limit.point_2.y = 0;
    }
    if (player_position.x > player_zone.Right() + position.x) {
        position.x = player_position.x - player_zone.Right();
    }
    if (player_position.x - position.x < player_zone.Left()) {
        position.x = player_position.x - player_zone.Left();
    }
    if (player_position.y > player_zone.Top() + position.y) {
        position.y = player_position.y - player_zone.Top();
    }
    if (player_position.y - position.y < player_zone.Bottom()) {
        position.y = player_position.y - player_zone.Bottom();
    }

    if (position.x < limit.Left()) {
        position.x = limit.Left();
    }
    if (position.x > limit.Right()) {
        position.x = limit.Right();
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top()) {
        position.y = limit.Top();
    }
}
