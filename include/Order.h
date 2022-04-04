#ifndef PROJETO1_DA_ORDER_H
#define PROJETO1_DA_ORDER_H

#include <ostream>

class Order {
public:
    Order(int VOLUME, int WEIGHT, int REWARD, int DURATION);
    int getVolume() const;
    int getWeight() const;
    int getReward() const;
    int getDuration() const;
    friend std::ostream& operator<<(std::ostream& os, const Order &o);
private:
    int VOLUME;
    int WEIGHT;
    int REWARD;
    int DURATION;
};

#endif //PROJETO1_DA_ORDER_H
