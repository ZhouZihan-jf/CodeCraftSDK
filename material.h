//
// Created by huawei on 2023/3/22.
//

#ifndef CODECRAFTSDK_MATERIAL_H
#define CODECRAFTSDK_MATERIAL_H

class material
{
private:
    int type;//物品类型
    int formulation[8];//生产配方
    double buy_price;//购买价
    double primary_sell_price;//原始售出价
public:
    material();
    virtual ~material();

    void set_type(int type);
    int get_type() const;

    void set_formulation();
    int* get_formulation();

    void set_buy_price(double buy_price);
    double get_buy_price() const;

    void set_primary_sell_price(double primary_sell_price);
    double get_primary_sell_price() const;


};
#endif //CODECRAFTSDK_MATERIAL_H
