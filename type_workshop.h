

#ifndef CODECRAFTSDK_TYPE_WORKSHOP_H
#define CODECRAFTSDK_TYPE_WORKSHOP_H
class type_workshop
{
private:
    int material_buy[8];//收购原材料数组，0表示不收购，1表示收购
    int material_produce[8];//生产物品数组，0表示生产，1表示不生产
    int produce_num;//具体生产物品的下标显示

public:
    type_workshop();
    virtual ~type_workshop();

    void set_type_workshop(int workType);
    int get_state_workshop(int workType);
};
#endif //CODECRAFTSDK_TYPE_WORKSHOP_H
