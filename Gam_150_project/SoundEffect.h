/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  SoundEffect.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include <SFML/Audio.hpp>
#include <list>

inline float effectVolume = 25;
inline float musicVolume = 20;
inline float BigVolume = 80;

namespace CS230 {
    class SoundEffect {
    public:
        //static SoundEffect Gem();
        static SoundEffect& Landing();
        static SoundEffect& Jump();
        static SoundEffect& Portal();
        static SoundEffect& MeleeAttack();
        static SoundEffect& Item();
        static SoundEffect& Attacked();
        static SoundEffect& Attack();
        static SoundEffect& Dash();
        static SoundEffect& recovery1();
        static SoundEffect& recovery2();
        static SoundEffect& Weapon_change();
        static SoundEffect& FeildBGM();
        static SoundEffect& BossBGM();
        //Boss1
        static SoundEffect& B1_swing();
        static SoundEffect& B1_JumpAttack();
        //Boss2
        static SoundEffect& B2_pew();
        static SoundEffect& B2_baldosool();
        static SoundEffect& B2_swordBeam();
        static SoundEffect& B2_jump_Attack();
        //Boss3
        static SoundEffect& B3_Bbaeggom();
        static SoundEffect& B3_WormJump();
        //Boss4
        static SoundEffect& B4_Inferno();
        static SoundEffect& B4_Fireball();
        static SoundEffect& B4_Psychokinesis();





        SoundEffect(const std::string& path);
        void play();
        void Big_play();
        void loopplay();
        void stopAll();

    private:
        sf::SoundBuffer buffer;
        std::list<sf::Sound> sounds;
    };
}