#include "../include/Van.h"

using namespace std;

int Van::van_nID = 0;


Van::Van(int MAX_VOL, int MAX_WEIGHT, int COST, vector<Order> belong_orders) {
    ID=generateID();
    this->MAX_VOL=MAX_VOL;
    this->MAX_WEIGHT=MAX_WEIGHT;
    this->COST=COST;
    this->belong_orders=belong_orders;
}


int Van::getVolume() const {
    return MAX_VOL;
}

int Van::getWeight() const {
    return MAX_WEIGHT;
}

int Van::getCost() const {
    return COST;
}

int Van::getID() const {
    return ID;
}

ostream &operator<<(ostream &os, const Van &o) {
    int size = 8;
    os << setfill(' ') << setw(size) << o.getVolume() << setfill(' ') << setw(size + 4) << o.getWeight() << setfill(' ') << setw(size + 3) << o.getCost() << endl;
    return os;
}

void Van::add(Order &o) {
    belong_orders.push_back(o);
}

std::vector<Order> Van::get_belong_orders() {
    return belong_orders;
}

void Van::clearOrders() {
    belong_orders.clear();
}

void Van::resetId() {
    van_nID = 0;
}

int Van::generateID() {
    van_nID++;
    return van_nID;
}


