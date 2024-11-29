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

	bool on = false; //마우스가 그 위에 있는지
	bool have_tem = false; // 칸에 아이템이 있는지
	Math::vec2 leftbot; // 왼쪽 하단 좌표
	Math::vec2 righttop; // 우측 상단 좌표
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

	void update(); // 인벤토리 창에 손 댔을 때, 그거 확인하고 bool 로 말해주는 함수 and 칸에 템이 있으면 칸의 have_tem 을 true 로 해주는 함수
	void draw();
	void drawUI(); // 화면 오른쪽에 작게 있는 미니 인벤토리
	void drawScreen();// I 누르면 화면 만드는 함수
	void setkans(); // 인벤토리 칸 위치 정해주는 함수
	void is_clicked_draw(); // 템 클릭하고 있을 때, 그려주는 함수
	void receive(Item tem); // 템 줏었을 때, 칸 벡터로 넣어주는 함수
	void inven_move(); // 인벤토리 내에서 템 이동시킬 수 있게 해주는 함수
	void touch(); // 인벤토리 내에서 템 집을 수 있게 하는 함수
	void touch2(); // 인벤토리 내에서 템 먹을 수 있게 하는 함수
	void craft(); // 아이템 코드로 크래프팅하는 함수
	void craft_help(); // 아이템 만들고 남은 창 비워주는 함수
	kan& find_tem(int code);
	int sum_find_tem(int code);
	void clear();

	kan button; // 크래프팅할 때, 누르는 버튼
	std::pair<Item, int> is_clicked; // 인벤에서 이동시킬 때, 사용되는 페어
	int previous_is_clicked_number = 0; // 인벤에서 이동시킬 때, 사용되는 페어
	std::vector<kan> kans{ 10 }; // 칸들, 사실상 인벤토리
	std::vector<kan> crafting_kans{ 3 }; //인벤토리 맨 위에 있는 크래프팅 하는 칸
	bool onscreen = false; // I 누르면 이게 껏다 켜졌다 하면서 화면 나옴

};

