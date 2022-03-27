#include "../include/Van.h"

Van::Van(int MAX_VOL, int MAX_WEIGHT, int COST) {
    this->MAX_VOL=MAX_VOL;
    this->MAX_WEIGHT=MAX_WEIGHT;
    this->COST=COST;
}

int Van::getVolume() {
    return MAX_VOL;
}

int Van::getWeight() {
    return MAX_WEIGHT;
}

int Van::getCost() {
    return COST;
}
