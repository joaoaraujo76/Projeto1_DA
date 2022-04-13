#include "../include/Order.h"

using namespace std;

Order::Order(int VOLUME, int WEIGHT, int REWARD, int DURATION, bool express, bool shipped) {
    this->VOLUME=VOLUME;
    this->WEIGHT=WEIGHT;
    this->REWARD=REWARD;
    this->DURATION=DURATION;
    this->express = express;
    this->shipped = shipped;
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
    os << o.getVolume() << " " << o.getWeight() << " " << o.getReward() << " " << o.getDuration();
    return os;
}

bool Order::isExpress() {
    return express;
}

void Order::setShipped() {
    shipped = true;
}

void Order::setUnshipped() {
    shipped = false;
}

bool Order::isShipped() {
    return shipped;
}

void Order::setExpress(bool express) {
    this->express = express;
}
