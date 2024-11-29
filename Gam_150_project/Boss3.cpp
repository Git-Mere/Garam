/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Boss3.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include <iostream>
#include <doodle/doodle.hpp>
#include <random>
#include <cmath>
#include "Boss3.h"
#include "character.h"
#include "SoundEffect.h"

using namespace doodle;
extern double dt;
extern Character Garam;
extern Elementalist lux;
extern E_Bullet ebullet;
std::random_device rd;
std::mt19937 gen(rd());
std::vector<E_Bullet*> eb;
std::vector<E_Bullet*> ub;
std::vector<E_Bullet*> db;

Elementalist::Elementalist(Math::vec2 position, Camera& camera) : start_position(position), position(position),
camera(camera), saved_position{ position }, currentPattern(nullptr) {
    sprite.Load2("Assets/Boss3/boss3.spt");
};

E_Bullet::E_Bullet(Math::vec2 position, int direction, double b_num, Camera& camera) : position(position), direction(direction), b_num(b_num), camera(camera) {
    fire.Load2("Assets/Boss3/fireball.spt");
    magic.Load2("Assets/Boss3/magic.spt");
    rock.Load("Assets/Boss3/stone.png");
}

Elementalist::Pattern* currentPattern = nullptr;

const Elementalist::Pattern Elementalist::patterns[3] = {
    Elementalist::Pattern(1),
    Elementalist::Pattern(2),
    Elementalist::Pattern(3)
};

Elementalist::Pattern* Elementalist::GetRandomPattern() {
    int randomIndex = rand() % 3;
    return const_cast<Pattern*>(&patterns[randomIndex]);
}

void Elementalist::ExecutePattern(Pattern* pattern) {
    if (pattern->value == 1) {
        fly();
    }
    else if (pattern->value == 2) {
        magic_casting();
        Bullet_Create(pattern);
    }
    else if (pattern->value == 3) {
        magic_casting();
        Bullet_Create2(pattern);
    }
}

bool Elementalist::IsPatternFinished(Pattern* pattern) {

    if (pattern->value == 1) {
        sprite.PlayAnimation(1);
        return !fly_check;
    }
    else if (pattern->value == 2) {
        sprite.PlayAnimation(2);
        return !is_casting;
    }
    else if (pattern->value == 3) {
        sprite.PlayAnimation(3);
        return !is_casting;
    }

    return true;
}


void Elementalist::update()
{
    if (hp <= 0) {
        alive = false;
    }

    if (hp > 0) {
        alive = true;
    }

    if (alive == true) {
        object_matrix = Math::TranslationMatrix(position);
        ub_update();
        direction_check();
        bullet_chase();
        position += velocity;
        if (Garam.dash == false) {
            attack(currentPattern);
        }

        if (currentPattern == nullptr)
        {
            Teleport();
            currentPattern = GetRandomPattern();
            ExecutePattern(currentPattern);
        }
        else
        {
            if (IsPatternFinished(currentPattern))
            {
                position.y = 30;
                sprite.PlayAnimation(0);
                pattern_delay = true;
            }
        }
    }

    // 삭제할 E_Bullet 객체 제거
    for (auto it = eb.begin(); it != eb.end();)
    {
        if ((*it)->position.y < -150)
        {
            delete* it;
            it = eb.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // 삭제할 E_Bullet 객체 제거
    for (auto it = ub.begin(); it != ub.end();)
    {
        if ((*it)->position.y < -150)
        {
            delete* it;
            it = ub.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Elementalist::fly() {
    position.y = 400;
    fly_check = true;
}

void Elementalist::magic_casting() {
    is_casting = true;
}

void Elementalist::Bullet_Create(Pattern* pattern) {
    int pos_x = static_cast<int>(camera.GetPosition().x);
    std::uniform_int_distribution<int> dist(0 + pos_x, Width - 100 + pos_x);
    CS230::SoundEffect::B4_Psychokinesis().Big_play();
    for (int i = 0; i < 6; i++) {
        bool overlap = false;
        Math::vec2 bulletPosition;

        do {
            double randomNumber = dist(gen);

            bulletPosition = { randomNumber, 500 };

            // 다른 총알과의 겹침 여부 확인
            overlap = false;
            for (const auto& bullet : ub) {
                double dx = bulletPosition.x - bullet->position.x;
                double dy = bulletPosition.y - bullet->position.y;
                double distance = std::sqrt(dx * dx + dy * dy);
                if (distance < 100) {  // 겹칠 거리(예: 100) 설정
                    overlap = true;
                    break;
                }
            }
        } while (overlap);

        E_Bullet* bullet = new E_Bullet(bulletPosition, 0, 0, camera);
        bullet->setShape(RECTANGLE);
        bullet->falling = false;
        ub.push_back(bullet);
    }
}

void Elementalist::Bullet_Create2(Pattern* pattern) {
    int pos_x = static_cast<int>(camera.GetPosition().x);
    std::uniform_int_distribution<int> dist(0 + pos_x, Width - 100 + pos_x);

    for (int i = 0; i < 6; i++) {
        bool overlap = false;
        Math::vec2 bulletPosition;

        do {
            double randomNumber = dist(gen);

            bulletPosition = { randomNumber, 20 };

            overlap = false;
            for (const auto& bullet : db) {
                double dx = bulletPosition.x - bullet->position.x;
                double dy = bulletPosition.y - bullet->position.y;
                double distance = std::sqrt(dx * dx + dy * dy);
                if (distance < 100) {
                    overlap = true;
                    break;
                }
            }
        } while (overlap);

        E_Bullet* bullet = new E_Bullet(bulletPosition, 0, 0, camera);

        bullet->setShape(RECTANGLE2);
        db.push_back(bullet);
        burst = true;
    }
}

void Elementalist::Timer()
{
    if (pattern_delay == true)
    {
        pattern_delay_time += dt;
    }

    if (pattern_delay_time >= pattern_delay_check)
    {
        pattern_delay = false;
        pattern_delay_time = 0;
        currentPattern = nullptr;
    }

    if (burst == true) {
        burst_timer += dt;
    }

    if (burst_timer >= 1.5 && burst_timer < 4) {
        if (!musicisplayed) {
            musicisplayed = true;
            for (int i = static_cast<int>(db.size() - 1); i >= 0; i--) {
                db[i]->magic.PlayAnimation(0);
            }
            CS230::SoundEffect::B4_Inferno().Big_play();
        }
    }
    else {
        musicisplayed = false;
    }

    if (burst_timer >= 4) {
        for (int i = static_cast<int>(db.size() - 1); i >= 0; i--) {
            delete db[i];
            db.erase(db.begin() + i);
        }
        burst = false;
        burst_timer = 0;
    }

    if (is_casting == true) {
        casting_timer += dt;
    }

    if (casting_timer >= 3) {
        is_casting = false;
        casting_timer = 0;
    }
}

void Elementalist::ub_update() {
    for (int i = 0; i < ub.size(); i++) {
        if (ub[i]->position.y < 550 && ub[i]->falling == false) {
            ub[i]->position.y += 0.5;
        }

        if (ub[i]->position.y >= 550) {
            ub[i]->falling = true;
        }

        if (ub[i]->falling == true) {
            ub[i]->velocity.y -= 10;
            ub[i]->position += ub[i]->velocity;
        }
    }
}

void Elementalist::direction_check() {
    if (Garam.position.x > position.x + 50)
    {
        right_check = true;
        left_check = false;
    }
    else
    {
        right_check = false;
        left_check = true;
    }
}

void  Elementalist::Teleport() {
    double pos_x = camera.GetPosition().x;
    std::uniform_int_distribution<int> dist(0 + static_cast<int>(pos_x), Width - 100 + static_cast<int>(pos_x));
    int randomNumber = dist(gen);
    position.x = randomNumber;
}

void E_Bullet::reset()
{
     b_num_count = 0;

     spinning = true;
     positioning = false;
     targeting = false;
     chasing = false;
     falling = false;
     shapeType = ELLIPSE;
     x = 0;
     y = 0;

     direction = 0;
     b_num = 0;
     shooting_timer = 0;
     e_bullet_timer = 0;
     eb_angle = 0;
     angle = 0;
     player_x = 0;
     player_y = 0;
     ebul_x = 0;
     ebul_y = 0;

     diff_x = 0;
     diff_y = 0;
     magnitude = 0;
     normalized_diff_x = 0;
     normalized_diff_y = 0;

     position = { 0,0 };
}

void E_Bullet::Timer()
{
    if (lux.fly_check == true && lux.reload == false) {
        e_bullet_timer += dt;
    }

    if (e_bullet_timer > 0.5 && eb.size() < 8 && lux.reload == false) {
        eb.push_back(new E_Bullet({ lux.position.x + 50 , lux.position.y + 75  }, 0, b_num, camera));
        for (int j = 0; j < eb.size(); j++) {
            if (eb[j]->targeting == false) {
                eb[j]->player_x = Garam.position.x;
                eb[j]->player_y = Garam.position.y + 45;
                eb[j]->eb_angle = 45 * static_cast<double>(eb.size());
                eb[j]->ebul_x = eb[j]->position.x + 100 * cos(eb[j]->eb_angle * PI / 180.0);
                eb[j]->ebul_y = eb[j]->position.y + 100 * sin(eb[j]->eb_angle * PI / 180.0);;
                eb[j]->b_num = j;
                eb[j]->shapeType = ELLIPSE;
                eb[j]->targeting = true;
                soundCheck = true;
                if (soundCheck == true)
                {
                    CS230::SoundEffect::B4_Fireball().play();
                    soundCheck = false;
                }
            }
            
        }
        e_bullet_timer = 0;
    }

    if (lux.reload == true) {
        shooting_timer += dt;
    }


    if (shooting_timer > 0.2 && ebullet.b_num_count < 7) {
        ebullet.b_num_count += 1;
        for (int j = 0; j < eb.size(); j++) {
            eb[j]->player_x = Garam.position.x;
            eb[j]->player_y = Garam.position.y + 45;
        }
        shooting_timer = 0;
    }
}

void E_Bullet::draw(Math::TransformationMatrix camera_matrix)
{
    magic.PlayAnimation(0);
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    fire.Update();
    magic.Update();
    if (shapeType == ELLIPSE) {
        if (chasing == false) {
            fire.Draw2(Math::TranslationMatrix(Math::vec2{position.x + 100 * cos(eb_angle * PI / 180.0), position.y + 100 * sin(eb_angle * PI / 180.0)} ) * camera_matrix);
        }
        else {
            fire.Draw2(Math::TranslationMatrix(position) * camera_matrix);
        }
    }
    else if (shapeType == RECTANGLE) {
        rock.Draw(camera_matrix * Math::TranslationMatrix(position) + Math::TranslationMatrix(Math::ivec2{ 30 ,30 }));
    }
    else if (shapeType == RECTANGLE2) {
        magic.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ (int)position.x + 50 , (int)position.y + 500 })) * Math::ScaleMatrix({ scale, scale }));
    }
}

void Elementalist::bullet_chase()
{
    if (eb.size() >= 8) {
        lux.reload = true;
    }

    if (eb.size() <= 0 && lux.reload == true) {
        ebullet.eb_angle = 0;
        ebullet.shooting_timer = 0;
        ebullet.b_num_count = 0;
        lux.reload = false;
        fly_check = false;
    }

    if (lux.reload == true) {
        for (int i = 0; i < eb.size(); i++) {
            if (eb[i]->b_num == ebullet.b_num_count) {
                eb[i]->chasing = true;
            }
        }
    }  

    for (int i = 0; i < eb.size(); i++) {
        if (eb[i]->chasing == true) {
            eb[i]->angle = atan2(eb[i]->ebul_y - eb[i]->player_y, eb[i]->ebul_x - eb[i]->player_x);
            eb[i]->position.x -= eb[i]->speed * cos(eb[i]->angle);
            eb[i]->position.y -= eb[i]->speed * sin(eb[i]->angle);
        }
    }
}

void Elementalist::reset()
{
     hp = 70;
     teleport_range = 200;

     burst_timer = 0;
     pattern_delay_time = 0;
     pattern_delay_check = 2.5;
     casting_timer = 0;


     alive = true;
     burst = false;
     reload = false;
     fly_check = false;
     is_casting = false;
     right_check = false;
     left_check = false;
     jump_check = false;

     pattern_delay = false;

     position = { 600, 30 };
}

void Elementalist::draw(Math::TransformationMatrix camera_matrix)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y; 
    sprite.Update();
    if (right_check) {
        sprite.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 50,90 })) * Math::ScaleMatrix({ -scale, scale }));
    }
    else if (left_check) {
        sprite.Draw2((camera_matrix * object_matrix + Math::TranslationMatrix(Math::ivec2{ 50,90 })) * Math::ScaleMatrix({ scale, scale }));
    }
}

void Elementalist::draw_hp(Math::TransformationMatrix camera_matrix)
{
    double pos_x = camera.GetPosition().x;
    double pos_y = camera.GetPosition().y;
    set_outline_width(1);
    push_settings();
    set_fill_color(0, 0, 0);
    draw_rectangle(position.x - 20 - pos_x, position.y + 200 - pos_y, 140, 10);
    pop_settings();

    if (hp >= 0) {
        push_settings();
        set_fill_color(128, 0, 0);
        draw_rectangle(position.x - 20 - pos_x, position.y + 200 - pos_y, (hp * 2), 10);
        pop_settings();
    }
}


void Elementalist::player_hit()
{
    if (Garam.hit == false && Garam.hp >= 0) {
        Garam.hit = true;
        Garam.hp -= 10;
        if (right_check == true) {
            Garam.velocity = { 15, 3 };
            Garam.flipped = false;
        }
        else if (right_check == false) {
            Garam.velocity = { -15, 3 };
            Garam.flipped = true;

        }
    }
}

void Elementalist::attack(Pattern* pattern)
{
    for (int k = 0; k < eb.size(); k++)
    {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= eb[k]->position.x - 12.5 &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= eb[k]->position.x + 12.5 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= eb[k]->position.y + 12.5 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= eb[k]->position.y - 12.5
            )
        {
            player_hit();
        }
    }

    for (int i = 0; i < ub.size(); i++)
    {
        if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= ub[i]->position.x  &&
            Garam.position.x - Garam.GetFrameSize().x / 2.0 <= ub[i]->position.x + 60 &&
            Garam.position.y - Garam.GetFrameSize().y / 2.0 <= ub[i]->position.y + 60 &&
            Garam.position.y + Garam.GetFrameSize().y / 2.0 >= ub[i]->position.y 
            )
        {
            player_hit();
        }
    }

    for (int i = 0; i < db.size(); i++)
    {
        if (burst_timer >= 2 && burst_timer < 4) {
            if (Garam.position.x + Garam.GetFrameSize().x / 2.0 >= db[i]->position.x &&
                Garam.position.x - Garam.GetFrameSize().x / 2.0 <= db[i]->position.x + 100 &&
                Garam.position.y - Garam.GetFrameSize().y / 2.0 <= db[i]->position.y + 1000 &&
                Garam.position.y + Garam.GetFrameSize().y / 2.0 >= db[i]->position.y
                )
            {
                player_hit();
            }
        }
    }
}