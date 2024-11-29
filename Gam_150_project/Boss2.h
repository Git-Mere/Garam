/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss2.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "vec2.h"
#include "camera.h"
#include "sprite.h"

class Tonkotsu
{
public:
	struct Pattern {
	int value;
	Pattern(int val) : value(val) {}
	};

	static const Pattern patterns[3];

	Tonkotsu(Math::vec2 position, Camera& camera, const std::filesystem::path& file_path);

	int hp = 30;

	double max_velocity = 5;
	double pattern_delay_time = 0;
	double pattern_delay_check = 1.8;
	double jump_delay_time = 0;
	double jump_delay_check = 1;
	double dash_delay_time = 0;
	double dash_delay_check = 2;

	void reset();

	void update();
	void direction_check();
	void draw(Math::TransformationMatrix camera_matrix);
	void move();
	void gravity();
	void timer();
	void attack(Pattern* pattern);
	void dash();
	void jump();
	void jump_attack(Pattern* pattern);
	void player_hit();
	void long_range_attack();
	void dash_attack(Pattern* pattern);
	void draw_hp(Math::TransformationMatrix camera_matrix);

	bool alive = true;
	bool right_dash = false;
	bool left_dash = false;
	bool right_check = false;
	bool left_check = false;
	bool jump_check = false;
	bool dash_check = false;
	bool jump_delay = false;
	bool dash_delay = false;
	bool pattern_delay = false;
	bool is_position_fixed = false;
	bool drop = true;
	bool IsPatternFinished(Pattern* pattern);


	Pattern* currentPattern;
	static Pattern* GetRandomPattern();
	void ExecutePattern(Pattern* pattern);
	Camera& camera;
	Math::vec2 position;
	Math::vec2 velocity;
	Math::vec2 saved_position;
	Math::TransformationMatrix object_matrix;
	Sprite sprite;
private:
	Math::vec2 start_position;
	static constexpr double x_acceleration = 1.2;
	static constexpr double x_drag = 0.6;
	static constexpr double gravity_c = 0.8;
};

class TonBullet
{
public:
	TonBullet(Math::vec2 position, int direction, Camera& camera);

	int direction = 0;
	bool shoot = false;

	double scale = 0.75;
	double max_velocity = 7;
	double bullet_timer = 0;
	double bullet_delay = 0.5;

	void update();
	void draw(Math::TransformationMatrix camera_matrix);

	Camera& camera;
	Math::vec2 position;
	Math::TransformationMatrix object_matrix;
	Sprite sprite;
private:

	Math::vec2 start_position;
	Math::vec2 velocity;
};