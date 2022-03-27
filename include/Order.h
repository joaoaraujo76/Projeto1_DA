#ifndef PROJETO1_DA_ORDER_H
#define PROJETO1_DA_ORDER_H


class Order {
public:
    Order(int VOLUME, int WEIGHT, int REWARD, int DURATION);
    int getVolume();
    int getWeight();
    int getReward();
    int getDuration();
private:
    int VOLUME;
    int WEIGHT;
    int REWARD;
    int DURATION;
};

#endif //PROJETO1_DA_ORDER_H
