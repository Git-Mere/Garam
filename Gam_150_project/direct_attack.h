#pragma once
#include "vec2.h"
#include "rect.h"
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  direct_attack.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "camera.h"
#include "sprite.h"
#include "weapon.h"

class direct_attack{
public:
	direct_attack(Math::rect rect);
	void update(Math::vec2 position, bool garam_flp, int damage);
	void start();
	void draw(Math::TransformationMatrix camera_matrix, double scale);
	void attack(int damage);

	bool flipped = false; 
	bool go = false; // 공격 시작
	bool success = false; //한 번 휘두를 때, 공격 한 번만 맞는 거
	Sprite sprite;

private:
	Math::TransformationMatrix object_matrix;
	Math::rect rect;

	double how = 0;
	double speed = 3;
	double range = 70;
};