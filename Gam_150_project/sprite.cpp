/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  sprite.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/

#include <doodle/doodle.hpp>
#include "Sprite.h"
#include <fstream>


void Sprite::Update()
{
	animations[current_animation]->Update();
}

void Sprite::Load(const std::filesystem::path& texture_path) {
	texture.Load(texture_path);
	hotspots.push_back(GetTextureSize() / 2);
}

void Sprite::Load(const std::filesystem::path& texture_path, std::initializer_list<Math::ivec2> spots) {
	texture.Load(texture_path);
	for (Math::ivec2 spot : spots) {
		hotspots.push_back(spot);
	}
}

void Sprite::Load2(const std::filesystem::path& sprite_file) {
    if (sprite_file.extension() != ".spt") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .spt file");
    }
    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }
    animations.clear();
    hotspots.clear();
    frame_texels.clear();

    std::string text;
    in_file >> text;
    texture.Load(text);
    frame_size.push_back(texture.GetSize());

    in_file >> text;
    while (in_file.eof() == false) {
        if (text == "FrameSize") {
            int size_x, size_y;
            in_file >> size_x;
            in_file >> size_y;
            frame_size.push_back({ size_x, size_y });
            hotspots.push_back({ frame_size[frame_size.size() - 1] / 2 });
        }
        else if (text == "NumFrames") {
            int frame_count;
            in_file >> frame_count;
            for (int i = 0; i < frame_count; i++) {
                frame_texels.push_back( { frame_size[frame_size.size()-1].x * i, 0});
            }
        }
        else if (text == "Frame") {
            int frame_location_x, frame_location_y;
            in_file >> frame_location_x;
            in_file >> frame_location_y;
            frame_texels.push_back({ frame_location_x, frame_location_y });
        }
        else if (text == "HotSpot") {
            int hotspot_x, hotspot_y;
            in_file >> hotspot_x;
            in_file >> hotspot_y;
            hotspots.push_back({ hotspot_x, hotspot_y });
        }
        else if (text == "Anim") {
            std::string anim;
            in_file >> anim;
            animations.push_back(new Animation{ anim });
        }
        else {
            //Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
    if (frame_texels.empty() == true) {
        frame_texels.push_back({ 0,0 });
    }
    if (animations.empty() == true) {
        animations.push_back(new Animation{});
    }
    //if (hotspots.empty() == true) {
    //    hotspots.push_back({frame_size/2});
    //}
    PlayAnimation(0);
    deter_frame_size(1);
}

void Sprite::Draw(Math::TransformationMatrix display_matrix, int hotspot) {
	texture.Draw(display_matrix * Math::TranslationMatrix(-GetHotSpot(hotspot)));
}

void Sprite::Draw2(Math::TransformationMatrix display_matrix) {
	texture.Draw(display_matrix * Math::TranslationMatrix(-GetHotSpot(0)), GetFrameTexel(animations[current_animation]->CurrentFrame()), GetFrameSize());
}

Math::ivec2 Sprite::GetFrameSize()
{
	return frame_size[current_frame_size];
}

Math::ivec2 Sprite::GetTextureSize()
{
    return texture.GetSize();
}
Math::ivec2 Sprite::GetHotSpot(int index)
{
	if (index >= hotspots.size() || index < 0) {
		return { 0,0 };
	}
	return hotspots[index];
}

void Sprite::PlayAnimation(int animation)
{
    if (animation < 0 || animation >= animations.size()) {
        //Engine::GetLogger().LogError("the animation doesn¡¯t exist.");
    }
    else {
        if (current_animation != animation) {
            current_animation = animation;
            animations[current_animation]->Reset();
        }
    }
}

bool Sprite::AnimationEnded()
{
    if (animations[current_animation]->Ended()) {
        return true;
    }
    return false;
}

void Sprite::deter_frame_size(int frame_size)
{
    current_frame_size = frame_size;
}

void Sprite::reset()
{
    animations[current_animation]->Reset();
}

Math::ivec2 Sprite::GetFrameTexel(int index) const
{
    if (index < 0 || index >= frame_texels.size()) {
        //Engine::GetLogger().LogError("Invalid index");
        return { 0,0 };
    }
    return frame_texels[index];
}