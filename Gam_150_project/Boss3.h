/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss3.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "vec2.h"
#include "camera.h"
#include "sprite.h"

enum ShapeType {
	ELLIPSE,
	RECTANGLE,
	RECTANGLE2
};

class Elementalist
{
public:
	struct Pattern {
		int value;
		Pattern(int val) : value(val) {}
	};

	static const Pattern patterns[3];

	Elementalist(Math::vec2 position, Camera& camera);

	int hp = 70;
	int teleport_range = 200;

	double burst_timer = 0;
	double max_velocity = 5;
	double pattern_delay_time = 0;
	double pattern_delay_check = 2.5;
	double casting_timer = 0;
	double scale = 1;

	void fly();
	void ub_update();
	void magic_casting();
	void Bullet_Create(Pattern* pattern);
	void Bullet_Create2(Pattern* pattern);
	void update();
	void attack(Pattern* pattern);
	void draw(Math::TransformationMatrix camera_matrix);
	void draw_hp(Math::TransformationMatrix camera_matrix);
	void player_hit();
	void Timer();
	void Teleport();
	void direction_check();
	void bullet_chase();

	void reset();

	bool alive = true;
	bool burst = false;
	bool reload = false;
	bool fly_check = false;
	bool is_casting = false;
	bool musicisplayed = false;
	bool right_check = false;
	bool left_check = false;
	bool jump_check = false;
	bool IsPatternFinished(Pattern* pattern);
	bool pattern_delay = false;
	
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

class E_Bullet
{
public:

	E_Bullet(Math::vec2 position, int direction, double b_num, Camera& camera);

	int b_num_count = 0;

	bool spinning = true;
	bool positioning = false;
	bool targeting = false;
	bool chasing = false;
	bool falling = false;
	bool soundCheck = false;

	double x = 0;
	double y = 0;
	double scale = 2;
	double direction = 0;
	double b_num = 0;
	double shooting_timer = 0;
	double e_bullet_timer = 0;
	double eb_angle = 0;
	double angle = 0;
	double player_x = 0;
	double player_y = 0;
	double ebul_x = 0;
	double ebul_y = 0;
	double speed = 20;
	double diff_x = 0;
	double diff_y = 0;
	double magnitude = 0;
	double normalized_diff_x = 0;
	double normalized_diff_y = 0;

	void reset();

	void setShape(ShapeType shapeType) {
		this->shapeType = shapeType;
	}

	ShapeType getShape() const {
		return shapeType;
	}

	void Timer();
	void draw(Math::TransformationMatrix camera_matrix);
	Math::vec2 position;
	Math::vec2 velocity;
	Camera& camera;
	Sprite fire;
	Sprite magic;
	Sprite rock;
private:
	ShapeType shapeType = ELLIPSE;
	Math::TransformationMatrix object_matrix;
};