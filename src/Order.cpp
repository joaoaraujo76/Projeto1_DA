#include "../include/Order.h"

using namespace std;

int Order::order_nID = 0;


Order::Order(int VOLUME, int WEIGHT, int REWARD, int DURATION, bool express, bool shipped) {
    this->VOLUME=VOLUME;
    this->WEIGHT=WEIGHT;
    this->REWARD=REWARD;
    this->DURATION=DURATION;
    this->express = express;
    this->shipped = shipped;
    ID = generateID();
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


int Order::getID() const {
    return ID;
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

int Order::generateID() {
    order_nID++;
    return order_nID;
}
