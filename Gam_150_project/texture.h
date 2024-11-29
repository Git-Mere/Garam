/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  texture.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include <doodle/image.hpp>
#include "Vec2.h"
#include "Matrix.h"


class Texture {
public:
    Texture();
    Texture(const std::filesystem::path& file_path);
    void Load(const std::filesystem::path& file_path);
    void Draw(Math::TransformationMatrix display_matrix);
    void Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size);

    Math::ivec2 GetSize();
    doodle::Image image;

private:
};

