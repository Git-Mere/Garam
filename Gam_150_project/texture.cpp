/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  texture.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <doodle/drawing.hpp>
#include "Texture.h"

Texture::Texture() {}

Texture::Texture(const std::filesystem::path& file_path) {
    Load(file_path);
}


void Texture::Load(const std::filesystem::path& file_path) {
    image = doodle::Image{ file_path };

}


void Texture::Draw(Math::TransformationMatrix display_matrix) {
    doodle::push_settings();
    doodle::apply_matrix(
        display_matrix[0][0],
        display_matrix[1][0],
        display_matrix[0][1],
        display_matrix[1][1],
        display_matrix[0][2],
        display_matrix[1][2]);
    doodle::draw_image(image, 0, 0);
    doodle::pop_settings();
}

void Texture::Draw(Math::TransformationMatrix display_matrix, Math::ivec2 texel_position, Math::ivec2 frame_size) {
    doodle::push_settings();
    doodle::apply_matrix(display_matrix[0][0], display_matrix[1][0], display_matrix[0][1], display_matrix[1][1], display_matrix[0][2], display_matrix[1][2]);
    doodle::draw_image(image, 0, 0, static_cast<double>(frame_size.x), static_cast<double>(frame_size.y), texel_position.x, texel_position.y);
    doodle::pop_settings();
}

Math::ivec2 Texture::GetSize() {
    return {
        image.GetWidth(), image.GetHeight()
    };
}
