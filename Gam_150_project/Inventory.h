/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Inventory.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include "Item.h"
#include <vector>

class Item;

struct kan {
	std::pair<Item, int> tem;

	bool on = false; //���콺�� �� ���� �ִ���
	bool have_tem = false; // ĭ�� �������� �ִ���
	Math::vec2 leftbot; // ���� �ϴ� ��ǥ
	Math::vec2 righttop; // ���� ��� ��ǥ
};

class Inventory {
private:
	double x = 400;
	double y = 225;
	double width = 600;
	double height = 376;
public:
	bool invenon = false;
	bool make_ok = false;
	bool full = false;

	void update(); // �κ��丮 â�� �� ���� ��, �װ� Ȯ���ϰ� bool �� �����ִ� �Լ� and ĭ�� ���� ������ ĭ�� have_tem �� true �� ���ִ� �Լ�
	void draw();
	void drawUI(); // ȭ�� �����ʿ� �۰� �ִ� �̴� �κ��丮
	void drawScreen();// I ������ ȭ�� ����� �Լ�
	void setkans(); // �κ��丮 ĭ ��ġ �����ִ� �Լ�
	void is_clicked_draw(); // �� Ŭ���ϰ� ���� ��, �׷��ִ� �Լ�
	void receive(Item tem); // �� �޾��� ��, ĭ ���ͷ� �־��ִ� �Լ�
	void inven_move(); // �κ��丮 ������ �� �̵���ų �� �ְ� ���ִ� �Լ�
	void touch(); // �κ��丮 ������ �� ���� �� �ְ� �ϴ� �Լ�
	void touch2(); // �κ��丮 ������ �� ���� �� �ְ� �ϴ� �Լ�
	void craft(); // ������ �ڵ�� ũ�������ϴ� �Լ�
	void craft_help(); // ������ ����� ���� â ����ִ� �Լ�
	kan& find_tem(int code);
	int sum_find_tem(int code);
	void clear();

	kan button; // ũ�������� ��, ������ ��ư
	std::pair<Item, int> is_clicked; // �κ����� �̵���ų ��, ���Ǵ� ���
	int previous_is_clicked_number = 0; // �κ����� �̵���ų ��, ���Ǵ� ���
	std::vector<kan> kans{ 10 }; // ĭ��, ��ǻ� �κ��丮
	std::vector<kan> crafting_kans{ 3 }; //�κ��丮 �� ���� �ִ� ũ������ �ϴ� ĭ
	bool onscreen = false; // I ������ �̰� ���� ������ �ϸ鼭 ȭ�� ����

};

