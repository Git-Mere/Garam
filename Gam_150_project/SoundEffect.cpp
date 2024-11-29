/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  SoundEffect.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "SoundEffect.h"


CS230::SoundEffect& CS230::SoundEffect::Landing()
{
    static SoundEffect Landing("Assets/Sound/Landing.wav");
    return Landing;
}

CS230::SoundEffect& CS230::SoundEffect::Jump()
{
    static SoundEffect Jump("Assets/Sound/JumpJump.wav");
    return Jump;
}

CS230::SoundEffect& CS230::SoundEffect::Portal()
{
    static SoundEffect Portal("Assets/Sound/Portal.wav");
    return Portal;
}

CS230::SoundEffect& CS230::SoundEffect::MeleeAttack()
{
    static SoundEffect MeleeAttack("Assets/Sound/sword_swing.wav");
    return MeleeAttack;
}

CS230::SoundEffect& CS230::SoundEffect::Item()
{
    static SoundEffect Item("Assets/Sound/Item.wav");
    return Item;
}

CS230::SoundEffect& CS230::SoundEffect::Attacked()
{
    static SoundEffect Attacked("Assets/Sound/Attacked.wav");
    return Attacked;
}
CS230::SoundEffect& CS230::SoundEffect::Attack()
{
    static SoundEffect Attack("Assets/Sound/Attack.wav");
    return Attack;
}

CS230::SoundEffect& CS230::SoundEffect::Dash()
{
    static SoundEffect Dash("Assets/Sound/Dash.wav");
    return Dash;
}

CS230::SoundEffect& CS230::SoundEffect::recovery1()
{
    static SoundEffect recovery1("Assets/Sound/recovery1.wav");
    return recovery1;
}

CS230::SoundEffect& CS230::SoundEffect::recovery2()
{
    static SoundEffect recovery2("Assets/Sound/recovery2.wav");
    return recovery2;
}

CS230::SoundEffect& CS230::SoundEffect::Weapon_change()
{
    static SoundEffect Weapon_change("Assets/Sound/Weapon_change.wav");
    return Weapon_change;
}

CS230::SoundEffect& CS230::SoundEffect::FeildBGM()
{
    static SoundEffect FeildBGM("Assets/Sound/bgm/FeildBGM.wav");
    return FeildBGM;
}

CS230::SoundEffect& CS230::SoundEffect::BossBGM()
{
    static SoundEffect BossBGM("Assets/Sound/bgm/BossBGM.wav");
    return BossBGM;
}

////////////////////////Boss1
CS230::SoundEffect& CS230::SoundEffect::B1_swing()
{
    static SoundEffect B1_swing("Assets/Sound/Batswing.wav");
    return B1_swing;
}

CS230::SoundEffect& CS230::SoundEffect::B1_JumpAttack()
{
    static SoundEffect B1_JumpAttack("Assets/Sound/Stun.wav");
    return B1_JumpAttack;
}


////////////////////////Boss2   
CS230::SoundEffect& CS230::SoundEffect::B2_pew()
{
    static SoundEffect B2_pew("Assets/Sound/pew.wav");
    return B2_pew;
}

CS230::SoundEffect& CS230::SoundEffect::B2_baldosool()
{
    static SoundEffect B2_baldosool("Assets/Sound/baldo.wav");
    return B2_baldosool;
}

CS230::SoundEffect& CS230::SoundEffect::B2_swordBeam()
{
    static SoundEffect B2_swordBeam("Assets/Sound/sword_beam.wav");
    return B2_swordBeam;
}

CS230::SoundEffect& CS230::SoundEffect::B2_jump_Attack()
{
    static SoundEffect B2_jump_Attack("Assets/Sound/JJikgi.wav");
    return B2_jump_Attack;
}

////////////////////////Boss3   
CS230::SoundEffect& CS230::SoundEffect::B3_Bbaeggom()
{
    static SoundEffect B3_Bbaeggom("Assets/Sound/Bbaeggom.wav");
    return B3_Bbaeggom;
}

CS230::SoundEffect& CS230::SoundEffect::B3_WormJump()
{
    static SoundEffect B3_WormJump("Assets/Sound/WormJump.wav");
    return B3_WormJump;
}

////////////////////////Boss4
CS230::SoundEffect& CS230::SoundEffect::B4_Inferno()
{
    static SoundEffect B4_Inferno("Assets/Sound/Inferno.wav");
    return B4_Inferno;
}

CS230::SoundEffect& CS230::SoundEffect::B4_Fireball()
{
    static SoundEffect B4_Fireball("Assets/Sound/Flame.wav");
    return B4_Fireball;
}

CS230::SoundEffect& CS230::SoundEffect::B4_Psychokinesis()
{
    static SoundEffect B4_Psychokinesis("Assets/Sound/Psychokinesis.wav");
    return B4_Psychokinesis;
}


CS230::SoundEffect::SoundEffect(const std::string& path)
{
    if (!buffer.loadFromFile(path))
        throw std::runtime_error("Failed to load sound file " + path);
}

void CS230::SoundEffect::play()
{
    // 더 이상 재생되지 않는 사운드 제거
    sounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });

    // 새 사운드 재생
    sounds.emplace_back();
    sounds.back().setBuffer(buffer);
    sounds.back().setVolume(effectVolume);
    sounds.back().play();
}

void CS230::SoundEffect::Big_play()
{
    // 더 이상 재생되지 않는 사운드 제거
    sounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });

    // 새 사운드 재생
    sounds.emplace_back();
    sounds.back().setBuffer(buffer);
    sounds.back().setVolume(BigVolume);
    sounds.back().play();
}

void CS230::SoundEffect::loopplay()
{
    // 더 이상 재생되지 않는 사운드 제거
    sounds.remove_if([](const sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; });

    // 새 사운드 재생
    sounds.emplace_back();
    sounds.back().setBuffer(buffer);
    sounds.back().setVolume(musicVolume);
    sounds.back().play();

    // 재생이 끝나면 다시 재생
    sounds.back().setLoop(true);
}

void CS230::SoundEffect::stopAll()
{
    for (auto& sound : sounds)
    {
        sound.stop();
    }
}