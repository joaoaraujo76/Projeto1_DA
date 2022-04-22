#ifndef PROJETO1_DA_VAN_H
#define PROJETO1_DA_VAN_H

#include <ostream>
#include <vector>
#include "Order.h"

class Van {
public:
    Van(int MAX_VOL, int MAX_WEIGHT, int COST, std::vector<Order>belong_orders = {});
    int getVolume() const;
    int getWeight() const;
    int getCost() const;
    int getID() const;
    void add(Order &o);
    std::vector <Order> get_belong_orders();
    void clearOrders();
    static void resetId();
    friend std::ostream& operator<<(std::ostream& os, const Van &o);
private:
    int ID;
    static int order_nID;
    int MAX_VOL;
    int MAX_WEIGHT;
    int COST;
    std::vector<Order> belong_orders;
    int generateID();
};



#endif //PROJETO1_DA_VAN_H
