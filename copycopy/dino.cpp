#include "dino.h"
#include <QDebug>

Dino::Dino() { }

Dino::Dino(int id, string name, string fam, int disc, double mass, int user_id)
{
    this->id = id;
    this->name = name;
    this->fam = fam;
    this->disc = disc;
    this->mass = mass;
    this->user_id = user_id;
}
