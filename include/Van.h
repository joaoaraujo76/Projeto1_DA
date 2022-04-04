#ifndef PROJETO1_DA_VAN_H
#define PROJETO1_DA_VAN_H


class Van {
public:
    Van(int MAX_VOL, int MAX_WEIGHT, int COST);
    int getVolume() const;
    int getWeight() const;
    int getCost() const;
private:
    int MAX_VOL;
    int MAX_WEIGHT;
    int COST;
};



#endif //PROJETO1_DA_VAN_H
