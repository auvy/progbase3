#pragma once

#include <string>
#include <QMetaType>

using namespace std;
struct  Dino
{
    int id = 0;
    string name = "";
    string per = "";
    string fam = "";
    int disc = 0;
    double mass = 0.0;

    Dino();
    Dino(int id, string name, string per, string fam, int disc, double mass);
};
Q_DECLARE_METATYPE(Dino)
