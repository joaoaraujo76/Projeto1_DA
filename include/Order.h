#ifndef PROJETO1_DA_ORDER_H
#define PROJETO1_DA_ORDER_H

#include <ostream>

class Order {
public:
    Order(int VOLUME, int WEIGHT, int REWARD, int DURATION, bool express, bool shipped);
    int getVolume() const;
    int getWeight() const;
    int getReward() const;
    int getDuration() const;
    int getID() const;
    bool isExpress();
    void setShipped();
    bool isShipped();
    static void resetOrderIds();
    friend std::ostream& operator<<(std::ostream& os, const Order &o);
private:
    int ID;
    static int order_nID;
    int VOLUME;
    int WEIGHT;
    int REWARD;
    int DURATION;
    bool express;
    bool shipped;
    int generateID();
};
#endif //PROJETO1_DA_ORDER_H