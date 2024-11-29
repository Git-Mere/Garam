/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  sprite.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/

#pragma once
#include <string>
#include "Vec2.h"
#include "Texture.h"
#include "Matrix.h"
#include "animation.h"


class Sprite {
public:
    void Update();
    void Load(const std::filesystem::path& texture_path);
    void Load(const std::filesystem::path& texture_path, std::initializer_list<Math::ivec2> spots);
    void Load2(const std::filesystem::path& sprite_file);
    void Draw(Math::TransformationMatrix display_matrix, int hotspot = 0);
    void Draw2(Math::TransformationMatrix display_matrix);
    Math::ivec2 GetTextureSize();
    Math::ivec2 GetHotSpot(int index);
    Math::ivec2 GetFrameSize();

    void PlayAnimation(int animation);
    bool AnimationEnded();

    void deter_frame_size(int frame_size);
    void reset();
    int get_current_animation() {
        return current_animation;
    }
private:
    Math::ivec2 GetFrameTexel(int index) const;

    Texture texture;
    std::vector<Math::ivec2> hotspots;
    std::vector<Animation*> animations;

    int current_animation = 0;
    int current_frame_size = 0;
    //Math::ivec2 frame_size;
    std::vector<Math::ivec2> frame_texels;
    std::vector<Math::ivec2> frame_size;
};

