#include "material.h"
using namespace std;

void material::set_type(int type)
{
    material::type = type;
}

int material::get_type() const
{
    return material::type;
}

void material::set_formulation()
{
    for (int i = 0; i < 8; ++i) {
        formulation[i] = 0;
    }
    if (material::get_type() == 4)
    {
        formulation[1] = formulation[2] = 1;
    }
    else if (material::get_type() == 5)
    {
        formulation[1] = formulation[3] = 1;
    }if (material::get_type() == 6)
    {
        formulation[3] = formulation[2] = 1;
    }if (material::get_type() == 7)
    {
        formulation[4] = formulation[5] = formulation[6] = 1;
    }
}

int* material::get_formulation() {
    return material::formulation;
}

void material::set_buy_price(double buy_price) {
    material::buy_price = buy_price;
}

double material::get_buy_price() const {
    return buy_price;
}

void material::set_primary_sell_price(double primary_sell_price) {
    material::primary_sell_price = primary_sell_price;
}

double material::get_primary_sell_price() const {
    return material::primary_sell_price;
}

material::material() {}

material::~material() = default;