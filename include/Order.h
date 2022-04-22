#ifndef PROJETO1_DA_ORDER_H
#define PROJETO1_DA_ORDER_H

#include <ostream>
#include <iomanip>

class Order {
public:
    Order(int VOLUME, int WEIGHT, int REWARD, int DURATION);
    int getVolume() const;
    int getWeight() const;
    int getReward() const;
    int getDuration() const;
    int getID() const;
    bool isExpress();
    void setExpress(bool express);
    void setShipped();
    void setUnshipped();
    bool isShipped();
    /**
     * Resets the orders id to zero
     */
    static void resetId();
    friend std::ostream& operator<<(std::ostream& os, const Order &o);
private:
    int ID;
    static int order_nID;
    int VOLUME;
    int WEIGHT;
    int REWARD;
    int DURATION;
    bool express;
    bool shipped;
    /**
     * Generates an id by incrementing the static order_nID variable
     * @return new unique id to the new order
     */
    int generateID();
};

#endif //PROJETO1_DA_ORDER_H