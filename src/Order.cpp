#include "../include/Order.h"

using namespace std;

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
    string shipped;
    o.shipped? shipped = "True" : shipped = "False";
    os << "ID: " << o.getID() << " Vol: " << o.getVolume() << " Weight: " << o.getWeight() << " Reward: " << o.getWeight() << " Duration: " << o.getDuration() <<  " Shipped: "  << shipped << endl ;
    return os;
}

bool Order::isExpress() {
    return express;
}

void Order::setShipped() {
    shipped = true;
}

bool Order::isShipped() {
    return shipped;
}

void Order::resetOrderIds() {
    order_nID = 0;
}

int Order::generateID() {
    order_nID++;
    return order_nID;
}
