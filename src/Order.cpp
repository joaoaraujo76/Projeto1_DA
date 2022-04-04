#include "../include/Order.h"

using namespace std;

Order::Order(int VOLUME, int WEIGHT, int REWARD, int DURATION) {
    this->VOLUME=VOLUME;
    this->WEIGHT=WEIGHT;
    this->REWARD=REWARD;
    this->DURATION=DURATION;
}

int Order::getVolume() const{
    return VOLUME;
}

int Order::getWeight() const{
    return WEIGHT;
}

int Order::getReward() const{
    return REWARD;
}

int Order::getDuration() const {
    return DURATION;
}

ostream &operator<<(ostream &os, const Order &o) {
    os << o.getVolume() << " " << o.getWeight() << " " << o.getReward() << " " << o.getDuration() << endl;
    return os;
}