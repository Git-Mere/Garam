/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  animation.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/

#pragma once
#include <vector>


class Animation {
public:
    Animation();
    Animation(const std::filesystem::path& animation_file);
    ~Animation();

    void Update();
    int CurrentFrame();
    void Reset();
    bool Ended();

private:
    enum class CommandType {
        PlayFrame,
        Loop,
        End,
    };

    class Command {
    public:
        virtual ~Command() {}
        virtual CommandType Type() = 0;
    };

    class End : public Command {
    public:
        virtual CommandType Type() override { return CommandType::End; }
    private:
    };

    class Loop : public Command {
    public:
        Loop(int loop_index);
        virtual CommandType Type() override { return CommandType::Loop; }
        int LoopIndex();
    private:
        int loop_index;
    };

    class PlayFrame : public Command {
    public:
        PlayFrame(int frame, double duration);
        virtual CommandType Type() override { return CommandType::PlayFrame; }
        void Update();
        bool Ended();
        void ResetTime();
        int Frame();
    private:
        int frame;
        double target_time;
        double timer;
    };

    int current_command;
    std::vector<Command*> commands;
    bool ended;
    PlayFrame* current_frame;
};

