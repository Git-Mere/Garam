/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Item.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include <string>
#include "vec2.h"
#include "map.h"
#include "camera.h"
#include "texture.h"

class Character;

enum class Kind { // �۵� ����
	potion,
	weapon,
	armor,
	meterial
};

class Item {
public:
	Item();
	Item(std::string name, int code, Kind kind);
	Item(std::string name, int code, Kind kind, Math::vec2 position, GameScene stage);
	void Load();
	void heal_Load();
	void draw(Camera& camera);
	void col(Character garam); // ĳ���Ͷ� �浹���� ���ִ� �Լ�
	void amount(); // ������ ������ �׿� �´� ȿ�� �ö󰡴� �Լ�

	int healing_amount = 0;
	int deal_amount = 0;
	int hp_amount = 0;

	bool live = true;
	GameScene stage;
	bool can_drop = false; //�������� ���� �� �ִ� ��������

	std::string name;
	int code;
	Kind kind;
	Math::vec2 position;

	Texture texture;
	Texture F;
private:

};