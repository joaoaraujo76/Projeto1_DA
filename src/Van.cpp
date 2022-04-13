#include "../include/Van.h"

using namespace std;

Van::Van(int MAX_VOL, int MAX_WEIGHT, int COST) {
    this->MAX_VOL=MAX_VOL;
    this->MAX_WEIGHT=MAX_WEIGHT;
    this->COST=COST;
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

ostream &operator<<(ostream &os, const Van &o) {
    os << o.getVolume() << " " << o.getWeight() << " " << o.getCost() << endl;
    return os;
}
