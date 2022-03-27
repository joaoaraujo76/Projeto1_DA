#ifndef PROJETO1_DA_VAN_H
#define PROJETO1_DA_VAN_H


class Van {
public:
    Van(int MAX_VOL, int MAX_WEIGHT, int COST);
    int getVolume();
    int getWeight();
    int getCost();
private:
    int MAX_VOL;
    int MAX_WEIGHT;
    int COST;
};



#endif //PROJETO1_DA_VAN_H
