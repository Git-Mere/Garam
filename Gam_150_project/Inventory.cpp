/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Inventory.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "Inventory.h"
#include <doodle/doodle.hpp>
#include <string>
#include "map.h"
#include "ItemTable.h"
#include "character.h"

using namespace doodle;

extern std::vector<Item*> tem;
extern int GameState;
extern Character Garam;

std::vector <Image> inventory =
{
	Image{ "Assets/item/inventory.png" },
	Image{ "Assets/item/mini_inventory.png" }
};

void Inventory::update() // 인벤토리 창에 손 댔을 때, 그거 확인하고 bool 로 말해주는 함수 and 칸에 템이 있으면 칸의 have_tem 을 true 로 해주는 함수
{
	Item gar{};
	int count = 0;
	if (get_mouse_x() < x + width && get_mouse_x() > x && get_mouse_y() > y && get_mouse_y() < y + height) {

		invenon = true;
	}
	else {
		invenon = false;
	}
	//kans 벡터 on, have_tem 체크
	for (int i = 0; i < kans.size(); i++) {
		if (get_mouse_x() < kans[i].righttop.x && get_mouse_x() > kans[i].leftbot.x && get_mouse_y() > kans[i].leftbot.y && get_mouse_y() < kans[i].righttop.y) {
			kans[i].on = true;
		}
		else {
			kans[i].on = false;
		}
	}
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].tem.second != 0) {
			kans[i].have_tem = true;
		}
		else {
			kans[i].have_tem = false;
			kans[i].tem = { gar,0 };
		}
	}

	//crafting_kans 벡터 on, have_tem 체크
	for (int i = 0; i < crafting_kans.size(); i++) {
		if (get_mouse_x() < crafting_kans[i].righttop.x && get_mouse_x() > crafting_kans[i].leftbot.x &&
			get_mouse_y() > crafting_kans[i].leftbot.y && get_mouse_y() < crafting_kans[i].righttop.y) {
			crafting_kans[i].on = true;
		}
		else {
			crafting_kans[i].on = false;
		}
	}
	for (int i = 0; i < crafting_kans.size(); i++) {
		if (crafting_kans[i].tem.second != 0) {
			crafting_kans[i].have_tem = true;
		}
		else {
			crafting_kans[i].have_tem = false;
		}
	}

	full = std::all_of(kans.begin(), kans.end(), [](kan i) {return i.have_tem; });
	craft();
}

void Inventory::draw()
{
	drawUI();
	if (onscreen) {
		drawScreen();
	}
	is_clicked_draw();
}

void Inventory::drawUI() // 화면 오른쪽에 작게 있는 미니 인벤토리
{
	push_settings();
	set_outline_color(0);
	set_font_size(1);
	no_fill();
	draw_image(inventory[1], Width - 100, Height / 2.0, 100, 200);
	for (int i = 0; i < kans.size(); i++) {
		set_font_size(20);
		if (kans[i].have_tem == true && i < 4) {
			draw_image(kans[i].tem.first.texture.image, Width - 55, (Height / 2.0) + (40 * i) + 25, 30, 30);
			draw_text(std::to_string(kans[i].tem.second), Width - 35, (Height / 2.0) + (40 * i) + 15);
		}
	}
	pop_settings();
}

void Inventory::drawScreen() // I 누르면 화면 만드는 함수
{
	push_settings();
	set_outline_color(0);
	set_font_size(20);
	no_fill();
	draw_image(inventory[0], x, y, width, height);

	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].have_tem == true) {
			draw_image(kans[i].tem.first.texture.image, kans[i].leftbot.x + 15, kans[i].leftbot.y + 15, 50, 50);
			draw_text(std::to_string(kans[i].tem.second), kans[i].leftbot.x+60, kans[i].leftbot.y);
		}
	}
	for (int i = 0; i < crafting_kans.size(); i++) {
		if (crafting_kans[i].have_tem == true) {
			draw_image(crafting_kans[i].tem.first.texture.image, crafting_kans[i].leftbot.x + 20, crafting_kans[i].leftbot.y + 20, 60, 60);
			draw_text(std::to_string(crafting_kans[i].tem.second), crafting_kans[i].leftbot.x+80, crafting_kans[i].leftbot.y);
		}
	}
	pop_settings();
}


void Inventory::setkans() // 인벤토리 칸 위치 초기화 해주는 함수
{
	for (int i = 0; i < kans.size(); i++) {
		if (i < 5) {
			kans[i].leftbot = { 440 + (i * 100.0), 370 };
			kans[i].righttop = { 520 + (i * 100.0), 450 };
		}
		else if (i >= 5) {
			kans[i].leftbot = { 440 + ((i - 5) * 100.0), 270 };
			kans[i].righttop = { 520 + ((i - 5) * 100.0), 350 };
		}
	}
	for (int i = 0; i < crafting_kans.size(); i++) {
		crafting_kans[i].leftbot = { 440.0 + (i * 200), 470.0 };
		crafting_kans[i].righttop = { 540.0 + (i * 200), 570.0 };
	}
	button.leftbot = { 770, 490 };
	button.righttop = { 820, 540 };

	//kans[0].tem = { Item{ "charm",4, Kind::meterial},5 };
	kans[0].tem = { Item{ "leather",5, Kind::meterial},5 };

	//kans[2].tem = { Item{ "bamboo",14, Kind::meterial},1 };
	//kans[3].tem = { Item{ "red_pepper_paste",7, Kind::potion},1 };
	//kans[4].tem = { Item{ "blue_dyes",9, Kind::meterial},1 };
	//kans[5].tem = { Item{ "white_clothes",8, Kind::meterial},1 };
	//kans[6].tem = { Item{ "gold",16, Kind::meterial},1 };
	//kans[7].tem = { Item{ "black_clothes",18, Kind::meterial},1 };

}

void Inventory::is_clicked_draw() { // 템 클릭하고 있을 때, 그려주는 함수
	push_settings();
	set_font_size(20);

	if (is_clicked.second != 0) {
		draw_image(is_clicked.first.texture.image, get_mouse_x(), get_mouse_y(), 50, 50);
		draw_text(is_clicked.first.name, get_mouse_x()+30, get_mouse_y());
	}
	pop_settings();
}

void Inventory::receive(Item tem) // 템 줏었을 때, 칸 벡터로 넣어주는 함수
{
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].tem.first.code == tem.code && GameState == tem.stage) {
			kans[i].tem.second++;
			return;
		}
	}
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].tem.second == 0 && GameState == tem.stage) {
			kans[i].tem = { tem, 1 };
			return;
		}
	}
}

void Inventory::inven_move() // 인벤토리 내에서 템 이동시킬 수 있게 해주는 함수
{
	Item gar;
	bool success = false;
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].on == true && kans[i].have_tem == true) {
			if (is_clicked.first.code == kans[i].tem.first.code) {
				kans[i].tem.second++;
				success = true;
			}
		}
		else if (kans[i].on == true && kans[i].have_tem == false) {
			kans[i].tem = is_clicked;
			success = true;

			is_clicked = { gar, 0 };
		}
	}
	for (int i = 0; i < crafting_kans.size() - 1; i++) {
		if (crafting_kans[i].on == true && crafting_kans[i].have_tem == true) {
			if (is_clicked.first.code == crafting_kans[i].tem.first.code) {
				crafting_kans[i].tem.second++;
				success = true;

			}
		}
		else if (crafting_kans[i].on == true && crafting_kans[i].have_tem == false) {
			crafting_kans[i].tem = is_clicked;
			success = true;

			is_clicked = { gar, 0 };
		}
	}
	if (invenon == true && is_clicked.first.code > 0) {
		if (previous_is_clicked_number >= 100) {
			if (success == false) {
				if (crafting_kans[previous_is_clicked_number - 100].tem.second > 1) {
					crafting_kans[previous_is_clicked_number - 100].tem.second++;
				}
				else {
					crafting_kans[previous_is_clicked_number - 100].tem = is_clicked;

				}

			}
		}
		else {
			if (success == false) {
				if (kans[previous_is_clicked_number].tem.second > 1) {
					kans[previous_is_clicked_number].tem.second++;
				}
				else {
					kans[previous_is_clicked_number].tem = is_clicked;

				}
			}
		}
	}
	is_clicked = { gar, 0 };
}

void Inventory::touch() //좌클릭
{
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].on == true && kans[i].have_tem == true) {
			is_clicked = { kans[i].tem.first, 1 };
			kans[i].tem.second -= 1;
			previous_is_clicked_number = i;
		}
	}
	for (int i = 0; i < crafting_kans.size(); i++) {
		if (crafting_kans[i].on == true && crafting_kans[i].have_tem == true) {
			is_clicked = { crafting_kans[i].tem.first, 1 };
			crafting_kans[i].tem.second -= 1;
			previous_is_clicked_number = i + 100;
		}
	}
}

void Inventory::touch2() // 우클릭
{
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].on == true && kans[i].have_tem == true) {
			if (kans[i].tem.first.kind == Kind::weapon || kans[i].tem.first.kind == Kind::armor) {
				kans[i].tem.first.amount();
				kans[i].tem.second -= 1;
			}
		}
	}

	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].on == true && kans[i].have_tem == true) {
			if (kans[i].tem.first.kind == Kind::potion && Garam.hp < Garam.max_hp) {
				kans[i].tem.first.amount();
				kans[i].tem.second -= 1;
			}
		}
	}
} 

void Inventory::craft() // 아이템 코드로 크래프팅하는 함수
{
	Item tem1 = crafting_kans[0].tem.first;
	Item tem2 = crafting_kans[1].tem.first;

	if (crafting_kans[0].tem.second != 0 || crafting_kans[1].tem.second != 0) {
		if ((tem1.name == "leather" && !crafting_kans[1].have_tem) || (!crafting_kans[0].have_tem && tem2.name == "leather"))
		{crafting_kans[2].tem = { talisman,1 }; make_ok = true;}
		else { Item gar{}; crafting_kans[2].tem = { gar,0 }; make_ok = false; }

		if (crafting_kans[0].have_tem && crafting_kans[1].have_tem) {
			if ((tem1.name == "herb" && tem2.name == "mineral_water") || (tem1.name == "mineral_water" && tem2.name == "herb")) { crafting_kans[2].tem = { Herb_tonic,1 }; make_ok = true; }
			else if ((tem1.name == "herb" && tem2.name == "red_pepper_paste") || (tem1.name == "red_pepper_paste" && tem2.name == "herb")) { crafting_kans[2].tem = { Seasoned_vegetables,1 }; make_ok = true; }
			else if ((tem1.name == "rice_cake" && tem2.name == "red_pepper_paste") || (tem1.name == "red_pepper_paste" && tem2.name == "rice_cake")) { crafting_kans[2].tem = { skewer,1 }; make_ok = true; }
			else if ((tem1.name == "leather" && tem2.name == "bamboo") || (tem1.name == "bamboo" && tem2.name == "leather")) { crafting_kans[2].tem = { cane,1 }; make_ok = true; }
			else if ((tem1.name == "Amulet" && tem2.name == "broken_hammer") || (tem1.name == "broken_hammer" && tem2.name == "Amulet")) { crafting_kans[2].tem = { cane2,1 }; make_ok = true; }
			else if ((tem1.name == "white_clothes" && tem2.name == "blue_dyes") || (tem1.name == "blue_dyes" && tem2.name == "white_clothes")) { crafting_kans[2].tem = { blue_clothes,1 }; make_ok = true; }
			else if ((tem1.name == "gold" && tem2.name == "black_clothes") || (tem1.name == "black_clothes" && tem2.name == "gold")) { crafting_kans[2].tem = { blackgold_clothes,1 }; make_ok = true; }
			else { Item gar{}; crafting_kans[2].tem = { gar,0 }; make_ok = false; }

		}
	}
	else { Item gar{}; crafting_kans[2].tem = { gar,0 }; make_ok = false; }
}

void Inventory::craft_help()
{
	Item gar{};
	if (crafting_kans[0].have_tem && crafting_kans[1].have_tem) {
		crafting_kans[0].tem.second--;
		crafting_kans[1].tem.second--;
		return;
	}
	if (crafting_kans[0].have_tem) {
		crafting_kans[0].tem.second--;
	}
	else if(crafting_kans[1].have_tem){
		crafting_kans[1].tem.second--;
	}
	crafting_kans[2].tem.first = gar;
}



kan& Inventory::find_tem(int code)
{
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].tem.first.code == code) {
			return kans[i];
		}
	}

	return button;
}

int Inventory::sum_find_tem(int code)
{
	int sum = 0;
	for (int i = 0; i < kans.size(); i++) {
		if (kans[i].tem.first.code == code) {
			sum += kans[i].tem.second;
		}
	}
	return sum;
}

void Inventory::clear()
{
	Item gar{};
	std::pair<Item, int> a{ gar, 0 };
	for (int i = 0; i < kans.size(); i++) {
		kans[i].tem = a;
		kans[i].on = false;
		kans[i].have_tem = false;
	}
	for (int i = 0; i < crafting_kans.size(); i++) {
		crafting_kans[i].tem = a;
		crafting_kans[i].on = false;
		crafting_kans[i].have_tem = false;
	}
}
