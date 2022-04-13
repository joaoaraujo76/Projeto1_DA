#ifndef PROJETO1_DA_VAN_H
#define PROJETO1_DA_VAN_H

#include <ostream>

class Van {
public:
    Van(int MAX_VOL, int MAX_WEIGHT, int COST);
    int getVolume() const;
    int getWeight() const;
    int getCost() const;
    friend std::ostream& operator<<(std::ostream& os, const Van &o);
private:
    int MAX_VOL;
    int MAX_WEIGHT;
    int COST;
};



#endif //PROJETO1_DA_VAN_H
