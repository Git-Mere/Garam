/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  button.cpp
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#include "button.h"
#include "SoundEffect.h"
#include <doodle/doodle.hpp>
#include <iostream>


using namespace doodle;

using namespace std;

constexpr int half{2};

extern std::vector<MadeButton> Button;
extern int bigstate;
enum Game;
void reset();

MadeButton::MadeButton(double x2, double y2, double Width2, double TextSize, int r2, int g2, int b2, int a2,
                        string text, int scene2)
{
    x      = x2;
    y      = y2;
    Width  = Width2;
    Height = TextSize;

    r = r2;
    g = g2;
    b = b2;
    a = a2;

    Btext = text;
    scene = scene2;
};

void MadeButton::SetRangeButton()
{
    double MX = get_mouse_x();
    double MY = get_mouse_y();


    if ((MX > x && MX < x + Width) && (MY > y && MY < y + Height))
    {
        onMouse = true;

        if (MouseIsPressed)
        {
            onPressed = true;
        }
        else
            onPressed = false;
    }
    else {
        onMouse = false;
    }
};

void MadeButton::MadeColorButton()
{
    if (onMouse)
    {
        if (onPressed)
        {
            set_fill_color(r, g / half, b / half, a);

        }
        else
            set_fill_color(r, g, b, a / half);
        draw_rectangle(x, y, Width, Height);

    }
    else {
        set_fill_color(r, g, b, a);

    }


};

void MadeButton ::MadeText()
{
    set_fill_color(255);
    set_font_size(Height / half);
    set_outline_color(0);
    draw_text(Btext, x, y);
}

void ButtonRange()
{
    double MX = get_mouse_x();
    double MY = get_mouse_y();

    for (int i = 0; i < Button.size(); i++)
    {
        if ((MX > Button[i].x && MX < Button[i].x + Button[i].Width) &&
            (MY > Button[i].y && MY < Button[i].y + Button[i].Height))
        {
            bigstate = Button[i].scene;
            CS230::SoundEffect::FeildBGM().stopAll();
            CS230::SoundEffect::BossBGM().stopAll();      
            CS230::SoundEffect::FeildBGM().loopplay();
            if (Button[i].scene == 1) {
                reset();
            }
        }
    }
}
