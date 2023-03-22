#include "type_workshop.h"
using namespace std;

type_workshop::type_workshop()
{
    for (int i = 0; i < 8; ++i) {
        material_buy[i] = 0;
        material_produce[i] = 0;
    }
    produce_num = 0;
}

void type_workshop::set_type_workshop(int workType)
{
    switch (workType > 0 && workType <= 9) {
        case 1:
            material_produce[1] = 1;
            produce_num = 1;
        case 2:
            material_produce[2] = 1;
            produce_num = 2;
        case 3:
            material_produce[3] = 1;
            produce_num = 3;
        case 4:
            material_buy[1] = material_buy[2] = 1;
            material_produce[4] = 1;
            produce_num = 4;
        case 5:
            material_buy[1] = material_buy[3] = 1;
            material_produce[5] = 1;
            produce_num = 5;
        case 6:
            material_buy[2] = material_buy[3] = 1;
            material_produce[6] = 1;
            produce_num = 6;
        case 7:
            material_buy[4] = material_buy[5] = material_buy[6] = 1;
            material_produce[7] = 1;
            produce_num = 7;
        case 8:
            material_buy[7] = 1;
        case 9:
            for (int i = 1; i <= 7; ++i) {
                material_buy[i] = 1;
            }
    }
}
int type_workshop::get_state_workshop(int itemType)
{
    if(material_buy[itemType] == 1)
        return 1;
}
type_workshop::~type_workshop() = default;

