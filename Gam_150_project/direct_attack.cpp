/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  direct_attack.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "direct_attack.h"
#include "enemy.h"

#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Boss4.h"
#include "character.h"
#include "SoundEffect.h"

extern int GameState;
extern std::vector<Enemy*> enemy;
extern Meretoss mere;
extern std::vector<Tonkotsu*> tons;
extern Sandworm worm;
extern Elementalist lux;

direct_attack::direct_attack(Math::rect rect) : rect(rect)
{
	sprite.Load("Assets/character/ATTACK.png");
}

void direct_attack::update(Math::vec2 position, bool garam_flp, int damage)
{ 
	flipped = garam_flp;
	object_matrix = Math::TranslationMatrix(position);

	if (flipped == false) {
		rect = { {position.x +30, position.y + how}, {position.x + range, position.y - how + 30} };
	}
	else if (flipped == true) {
		rect = { {position.x - 30, position.y + how}, {position.x - range, position.y - how + 30} };
	}
	if (go == true) {
		attack(damage);
		if (how < 50) {
			how += speed;
		}
		else {
			how = 0;
			go = false;
			success = false;
		}
	}
}

void direct_attack::start()
{
	if (go == false) {
		go = true;
		CS230::SoundEffect::MeleeAttack().play();
	}
}


void direct_attack::draw(Math::TransformationMatrix camera_matrix, double scale)
{
	if (go) {
	    if (!flipped) {
	        sprite.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 65,0 })) * Math::ScaleMatrix({ scale, scale }));
	    }
	    else {
			sprite.Draw((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ -65,0 })) * Math::ScaleMatrix({ -scale, scale }));
	    }
	}
}

void direct_attack::attack(int damage)
{
		for (int i = 0; i < enemy.size(); i++) 
		{
			if (rect.Right() >= enemy[i]->position.x - enemy[i]->sprite.GetFrameSize().x / 2.0 &&
				rect.Left() <= enemy[i]->position.x + enemy[i]->sprite.GetFrameSize().x / 2.0 &&
				rect.Bottom() <= enemy[i]->position.y + enemy[i]->sprite.GetFrameSize().y / 2.0 &&
				rect.Top() >= enemy[i]->position.y - enemy[i]->sprite.GetFrameSize().y / 2.0
				)
			{
				if (success == false) {
					enemy[i]->hp -= damage;
					success = true;
					CS230::SoundEffect::Attack().play();
				}
			}
		}

		if (GameState == GameScene::first_boss && mere.alive == true) {
			if (rect.Right() >= mere.position.x + mere.sprite.GetFrameSize().x / 4.0 &&
				rect.Left() <= mere.position.x + mere.sprite.GetFrameSize().x / 2.0 &&
				rect.Bottom() <= mere.position.y + mere.sprite.GetFrameSize().y / 2.0 &&
				rect.Top() >= mere.position.y - mere.sprite.GetFrameSize().y / 2.0
				)
			{
				if (success == false) {
					mere.jump_timer = 0;
					mere.hp -= damage;
					success = true;
					CS230::SoundEffect::Attack().play();
				}
			}
		}

		if (GameState == GameScene::forest_boss) {
			for (int i = 0; i < tons.size(); i++)
			{
				if (rect.Right() >= tons[i]->position.x &&
					rect.Left() <= tons[i]->position.x + 100 &&
					rect.Bottom() <= tons[i]->position.y + 150 &&
					rect.Top() >= tons[i]->position.y
					)
				{
					if (success == false) {
						tons[i]->hp -= damage;
						success = true;
						break;
						CS230::SoundEffect::Attack().play();
					}
				}
			}
		}

		if (GameState == GameScene::volcano_boss && worm.alive == true) {
			if (rect.Right() >= worm.position.x &&
				rect.Left() <= worm.position.x + 200 &&
				rect.Bottom() <= worm.position.y + 450 &&
				rect.Top() >= worm.position.y
				)
			{
				if (success == false) {
					worm.hp -= damage;
					success = true;
					CS230::SoundEffect::Attack().play();
				}
			}
		}

		if (GameState == GameScene::final_boss && lux.alive == true) {
			if (rect.Right() >= lux.position.x &&
				rect.Left() <= lux.position.x + 100 &&
				rect.Bottom() <= lux.position.y + 150 &&
				rect.Top() >= lux.position.y
				)
			{
				if (success == false) {
					lux.hp -= damage;
					success = true;
					CS230::SoundEffect::Attack().play();
				}
			}
		}
}
