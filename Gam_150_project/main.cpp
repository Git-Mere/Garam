/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  main.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <iostream>
#include <doodle/doodle.hpp>
#include "Obstruct.h"
#include "character.h"
#include "Inventory.h"
#include "weapon.h"
#include "enemy.h"
#include "map.h"
#include "portal.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Boss4.h"
#include <chrono>
#include "button.h"
#include "SoundEffect.h"

using namespace doodle;

bool moveW = false;
bool moveA = false;
bool moveS = false;
bool moveD = false;
bool dashcheck = false;
bool jumpcheck = false;

int window_width = 1280;
int window_height = 720;

double dt = 0;
Camera camera;

Character Garam{ {120, 810}, camera };
Meretoss mere{ {600, 30}, camera };

Elementalist lux{ {600, 30}, camera };
Sandworm worm{ {600, 30}, camera };

direct_attack da{ { {Garam.position.x, Garam.position.y},{100, 30} } };
throw_attack charm;
TonBullet TonB{ {0, 0}, 0, camera };
E_Bullet ebullet{ {0,0}, 0, 0, camera };
Map map;

std::vector<Item*> tem;
extern std::vector<Portal*> portal;
extern std::vector<Enemy*> enemy;
extern std::vector<Obstruct*> obst;
extern std::vector<Tonkotsu*> tons;
extern std::vector<TonBullet*> tonb;
extern std::vector<E_Bullet*> eb;
extern std::vector<E_Bullet*> ub;
extern std::vector<E_Bullet*> db;

void all_draw();

std::chrono::system_clock::time_point last_tick = std::chrono::system_clock::now();
static constexpr double TargetFPS = 60.0;

enum Game
{
    Logo,
    Mainmenu,
    Credit,
    Play,
    Quit
};

Sprite mainbackground;
Sprite credit;

inline std::vector<MadeButton> Button{ MadeButton(Width, Height + 260, 300, 100, 250, 180, 75, 50, "", Game::Play),
                                      //MadeButton(Width , Height + 200 , 240, 60, 250, 75, 180, 255, " How to Play", Game::Howtoplay),
                                      MadeButton(Width , Height + 150 , 340, 100, 75, 180, 250, 50, "", Game::Credit),
                                      MadeButton(Width , Height + 30, 240, 100, 75, 100, 100, 50, "", Game::Quit),
                                          MadeButton(Width, Height, 120, 45, 75, 100, 100, 100, " BACK", Game::Mainmenu) };

int GameState = GameScene::dongool_stage1;
int bigstate = Game::Logo;
int end_count = 0;
double credit_timer = 0;

void reset();

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    create_window(window_width, window_height);
    set_window_title("Let's Garam");
    set_frame_of_reference(FrameOfReference::RightHanded_OriginBottomLeft);
    Garam.inventory.setkans();
    map.tem_create();
    Garam.Load();
    mere.Load();
    //ton.Load();
    //worm.Load();
    //lux.Load();
    map.Load();
    mainbackground.Load("Assets/background/main_background.png", { {0,0} });
    credit.Load("Assets/Dark DigiPen.png");

    while (!is_window_closed()) {
        auto now = std::chrono::system_clock::now();
        dt = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_tick).count();
        update_window();

        switch (bigstate) {
        case Game::Logo:
            clear_background(255); 
            {
                Image logo{ "Assets/DigiPen.png" };
                draw_image(logo, Width / 2.0 - logo.GetWidth() / 2.0, Height / 2.0 - logo.GetHeight() / 2.0);
                double timer = 0;
                timer += dt;
                if (timer > 4.0) {
                    bigstate = Game::Mainmenu;
                }
            }
            break;
        case Game::Mainmenu:
        {
            clear_background(255);
            CS230::SoundEffect::FeildBGM().stopAll();
            CS230::SoundEffect::BossBGM().stopAll();
            mainbackground.Draw(Math::TranslationMatrix(Math::ivec2{ 0,0 }) * Math::ScaleMatrix({Width/400.0, Height/200.0}));
            for (int i = 0; i < 3; i++) {
                Button[i].IMadeButton();
            }
        }
            break;
        case Game::Play:
            if (dt > 1.0 / TargetFPS) {
                last_tick = now;
                Garam.timer();
                charm.timer();
                if (!charm.bullets.empty()) {
                    charm.update();
                }
                map.update();
                //worm.update();
                if (GameState == GameScene::first_boss) {
                    //1스테이지 보스
                    mere.update();
                    mere.timer();
                }

                if (GameState == GameScene::forest_boss) {
                    ////2스테이지 보스 
                    for (auto tonkotsu : tons) {
                        tonkotsu->update();
                        tonkotsu->timer();
                    }
                }

                if (GameState == GameScene::volcano_boss) {
                    worm.update();
                    worm.timer();
                }

                if (GameState == GameScene::final_boss) {
                    //4스테이지 보스
                    lux.update();
                    lux.Timer();
                    ebullet.Timer();
                }

                camera.Update(Garam.position, Garam.flipped);
                Garam.update();
                da.update(Garam.position, Garam.flipped, Garam.AD);
                for (auto enem : enemy) {
                    enem->update();
                }
            }

            all_draw();
            if (!lux.alive) {
                end_count++;
                clear_background(end_count, 200);
                if (end_count > 250) {
                    bigstate = Game::Credit;
                }
            }
            if (Garam.dead) {
                draw_text("Press Esc keys", Width / 2.0-300, Height / 2.0);
                push_settings();
                set_fill_color(100, 100, 100, 100);
                draw_rectangle(0, 0, Width, Height);
                pop_settings();
            }
            break;
        case Game::Credit:
            clear_background(0);
            if (dt > 1.0 / TargetFPS) {
                credit_timer += 0.01;
                if (credit_timer >= 2 && credit_timer < 4) {
                    credit.Load("Assets/Game_credit.png");
                }
                else if (credit_timer >= 4 && credit_timer < 6) {
                    credit.Load("Assets/team_credit.png");
                }
                else if (credit_timer >= 6) {
                    credit.Load("Assets/credit1.png");
                }

                if (credit_timer < 2) {
                    credit.Draw(Math::TranslationMatrix(Math::ivec2{ Width / 2, Height / 2 }));
                }
                else {
                    credit.Draw(Math::TranslationMatrix(Math::ivec2{ Width / 2, Height / 2 }) * Math::ScaleMatrix(2), 1);
                }
            }
            Button[3].IMadeButton();
            break;
        case Game::Quit:
            close_window();
            break;
        }
    }
    return 0;
}

void reset() {
    end_count = 0;
    credit_timer = 0;
    credit.Load("Assets/Dark DigiPen.png");
    bigstate = Game::Mainmenu;
    GameState = GameScene::dongool_stage1;

    map.Map_Reset();
    map.dongool_stage1_create();

    Garam.reset();

    mere.hp = 40;

    tem.clear();
    map.tem_create();

    Garam.inventory.clear();
    Garam.inventory.setkans();

    lux.reset();
    worm.reset();
    for (auto a : tons) {
        a->reset();
    }

}

void on_mouse_pressed(MouseButtons button)
{
    if (button == MouseButtons::Left && Garam.inventory.onscreen && Garam.dead == false) {
        Garam.inventory.touch();
        if (Garam.inventory.crafting_kans[2].on && Garam.inventory.make_ok) {
            Garam.inventory.craft_help();
        }
    }
}

void on_mouse_released(MouseButtons button)
{
    if (button == MouseButtons::Left && Garam.inventory.onscreen && Garam.dead == false) {
        Garam.inventory.inven_move();

    }
    if (button == MouseButtons::Right && Garam.inventory.onscreen && Garam.dead == false) {
        Garam.inventory.touch2();
    }
    if (button == MouseButtons::Left) { 
        ButtonRange(); 
    }
}

void on_key_pressed(KeyboardButtons button) {
    if (button == KeyboardButtons::Left)
    {
        moveA = true;
    }
    if (button == KeyboardButtons::Right)
    {
        moveD = true;
    }
    if (button == KeyboardButtons::Z)
    {
        Garam.is_sound_used = false;
        if (Garam.jump_count != 0 && Garam.jump_count > 0) {
            Garam.velocity.y = 17;
            Garam.jump_count -= 1;
            CS230::SoundEffect::Jump().play();
        }
    }
    if (button == KeyboardButtons::C && Garam.dash == false && Garam.stun == false) {
        Garam.dash = true;
        if (Garam.dash == true) {
            if (Garam.flipped == false) {
                Garam.velocity.x = Garam.dash_range;
                CS230::SoundEffect::Dash().Big_play();
            }
            else if (Garam.flipped == true) {
                Garam.velocity.x = -Garam.dash_range;
                CS230::SoundEffect::Dash().Big_play();
            }
        }
    }

}

void on_key_released(KeyboardButtons button) {
    if (button == KeyboardButtons::Left) {
        moveA = false;
    }
    if (button == KeyboardButtons::Right) {
        moveD = false;
    }
    if (button == KeyboardButtons::I) {
        if (Garam.inventory.onscreen == true) {
            Item gar;
            Garam.inventory.onscreen = false;
            Garam.inventory.is_clicked = { gar, 0 };
        }
        else if (Garam.inventory.onscreen == false) {
            Garam.inventory.onscreen = true;
        }
    }
    if (button == KeyboardButtons::F && Garam.dead == false) {
        for (int i = 0; i < tem.size(); i++) { // 떨어진 아이템들 범위
            if (tem[i]->can_drop == true && tem[i]->stage == GameState) { //떨어진 아이템을 줏을 수 있는 범위체크(can_drop)
                if (!Garam.inventory.full || Garam.inventory.find_tem(tem[i]->code).tem.first.code == tem[i]->code) {
                    Garam.inventory.receive(*tem[i]);
                    tem[i]->live = false;
                    CS230::SoundEffect::Item().play();
                    tem.erase(tem.begin() + i);
                }
            }
        }
        map.portal_move();
        Garam.landing_check = false;
    }
    if (button == KeyboardButtons::X && Garam.dead == false)
    {
        if (Garam.current_weapon == 1)
        {
            da.start();
        }
        else if (Garam.current_weapon == 2 && charm.shoot == false) {
            charm.shoot = true;

            if (charm.shoot == true) {
                charm.add(Garam.position, Garam.flipped);
            }
        }
    }

    if (button == KeyboardButtons::V && Garam.dead == false)
    {
        if (Garam.current_weapon == 1) {
            Garam.current_weapon = 2;
            charm.sprite.PlayAnimation(0);
        }
        else if (Garam.current_weapon == 2)
        {
            Garam.current_weapon = 1;
            charm.sprite.PlayAnimation(1);
        }
    }
    if (Garam.dead == false && Garam.hp < Garam.max_hp) {
        if (button == KeyboardButtons::_1) {
            if (Garam.inventory.kans[0].have_tem == true) {
                if (Garam.inventory.kans[0].tem.first.kind == Kind::potion) {
                    Garam.inventory.kans[0].tem.first.amount();
                    Garam.inventory.kans[0].tem.second -= 1;
                }
            }
        }
        if (button == KeyboardButtons::_2) {
            if (Garam.inventory.kans[1].have_tem == true) {
                if (Garam.inventory.kans[1].tem.first.kind == Kind::potion) {
                    Garam.inventory.kans[1].tem.first.amount();
                    Garam.inventory.kans[1].tem.second -= 1;
                }
            }
        }
        if (button == KeyboardButtons::_3) {
            if (Garam.inventory.kans[2].have_tem == true) {
                if (Garam.inventory.kans[2].tem.first.kind == Kind::potion) {
                    Garam.inventory.kans[2].tem.first.amount();
                    Garam.inventory.kans[2].tem.second -= 1;
                }
            }
        }
        if (button == KeyboardButtons::_4) {
            if (Garam.inventory.kans[3].have_tem == true) {
                if (Garam.inventory.kans[3].tem.first.kind == Kind::potion) {
                    Garam.inventory.kans[3].tem.first.amount();
                    Garam.inventory.kans[3].tem.second -= 1;
                }
            }
        }

    }
    if (button == KeyboardButtons::Escape && Garam.dead) {
        bigstate = Mainmenu;
        reset();
    }
    if (button == KeyboardButtons::Tilde) {
        Garam.AD = 8600;
    }
}


void all_draw() {
    Math::TransformationMatrix camera_matrix = camera.GetMatrix();

    map.draw(camera);
    if (GameState == GameScene::first_boss  && mere.alive == true ) {

        //1스테이지 보스 
        mere.draw(camera_matrix);
        mere.draw_hp(camera_matrix);
    }
    if (GameState == GameScene::forest_boss) {
        //2스테이지 보스
        for (auto tonkotsu : tons) {
            if (tonkotsu->alive == true) {
                tonkotsu->draw(camera_matrix);
                tonkotsu->draw_hp(camera_matrix);
            }
        };
        for (auto tonbullet : tonb) {
            tonbullet->draw(camera_matrix);
        };
    }
    if (GameState == GameScene::volcano_boss && worm.alive == true) {
        //3스테이지 보스
        worm.draw(camera_matrix);
        worm.draw_hp(camera_matrix);
    }
    if (GameState == GameScene::final_boss && lux.alive == true) {
        //4스테이지 보스
        lux.draw(camera_matrix);
        lux.draw_hp(camera_matrix);
        for (auto ebullets : eb) {
            ebullets->draw(camera_matrix);
        }
        for (auto ebullets : ub) {
            ebullets->draw(camera_matrix);
        }
        for (auto ebullets : db) {
            ebullets->draw(camera_matrix);
        }
    }
    Garam.draw(camera_matrix);

    for (auto enem : enemy) {
        enem->draw(camera_matrix);
    }


    ///////////////////////////////////
    //Garam.draw_hp();
    da.draw(camera_matrix, Garam.scale);
    charm.draw(camera_matrix);

    Garam.inventory.draw();
    
}
