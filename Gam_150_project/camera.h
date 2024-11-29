/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  camera.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "matrix.h"

class Camera {
public:
    void SetPosition(Math::vec2 new_position);
    const Math::vec2& GetPosition() const;
    void SetLimit(Math::irect new_limit);
    void SetPzon(Math::rect new_zone);
    void Update(const Math::vec2& player_position, bool& player_flipped);
    Math::TransformationMatrix GetMatrix();
    Math::vec2 position;
    Math::irect limit;
private:
    Math::rect player_zone;
};
