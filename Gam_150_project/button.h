/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  button.h
Project:    Gam150 project - Garam
Author:     Seungheon Jeon, Sunghwan Lee, Jaeyong Lee, Jonghoon Kim
Created:    March 8, 2023
Updated:    June 10, 2023
*/
#pragma once
#include <string>

using namespace std;

class MadeButton
{
private:
    bool   onMouse   = false;
    bool   onPressed = false;
    bool   onClicked = false;
    string Btext;

public:
    double x{0.0}, y{0.0}, Width{0.0}, Height{0.0}, WidthDiv{0.0};
    int    r{0}, g{0}, b{0}, a{0}, scene{0};

    MadeButton(double x2, double y2, double Width2, double TextSize, int r2, int g2, int b2, int a2, string text,
               int scene2);

    void MadeColorButton();

    void MadeText();

    void SetRangeButton();


    void IMadeButton()
    {
        SetRangeButton();

        MadeColorButton();

        MadeText();
    };
};

void ButtonRange();