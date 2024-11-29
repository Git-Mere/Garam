/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss4.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "vec2.h"
#include "camera.h"
#include "sprite.h"

class Sandworm
{
public:
	struct Pattern {
		int value;
		Pattern(int val) : value(val) {}
	};

	static const Pattern patterns[2];

	Sandworm(Math::vec2 position, Camera& camera);

	int hp = 50;

	double randomNumber = 0;
	double rise_timer = 0;
	double dive_timer = 0;
	double hit_timer = 0;
	double blast_timer = 0;
	double max_velocity = 5;
	double nextXCoordinate = 0;
	double pattern_delay_time = 0;
	double pattern_delay_check = 3;
	double scale = 2;

	void update();
	void draw(Math::TransformationMatrix camera_matrix);
	void move();
	void diving();
	void timer();
	void draw_hp(Math::TransformationMatrix camera_matrix);
	void direction_check();
	void attack(Pattern* pattern);
	void player_hit();

	void reset();

	bool alive = true;
	bool blast = true;
	bool dive = false;
	bool rise_attack = false;
	bool blast_right = false;
	bool blast_left = false;
	bool right_check = false;
	bool left_check = false;
	bool jump_check = false;
	bool isPatternGenerated = false;
	bool IsPatternFinished(Pattern* pattern);
	bool pattern_delay = false;
	bool is_diricection_check = false;
	bool drop = true;

	Pattern* currentPattern;
	static Pattern* GetRandomPattern();
	void ExecutePattern(Pattern* pattern);

	Camera& camera;
	Math::vec2 position;
	Math::vec2 velocity;
	Math::vec2 saved_position;
	Math::TransformationMatrix object_matrix;
	Sprite up;
	Sprite swim;
	Sprite circle;
private:
	Math::vec2 start_position;
	static constexpr double x_acceleration = 1.2;
	static constexpr double x_drag = 0.6;
	static constexpr double gravity_c = 0.8;
};