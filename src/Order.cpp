#include "../include/Order.h"

Order::Order(int VOLUME, int WEIGHT, int REWARD, int DURATION) {
    this->VOLUME=VOLUME;
    this->WEIGHT=WEIGHT;
    this->REWARD=REWARD;
    this->DURATION=DURATION;
}

int Order::getVolume() {
    return VOLUME;
}

int Order::getWeight() {
    return WEIGHT;
}

int Order::getReward() {
    return REWARD;
}

int Order::getDuration() {
    return DURATION;
}
