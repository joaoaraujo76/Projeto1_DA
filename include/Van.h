#ifndef PROJETO1_DA_VAN_H
#define PROJETO1_DA_VAN_H

#include <ostream>
#include <vector>
#include "Order.h"
#include <iomanip>

class Van {
public:
    Van(int MAX_VOL, int MAX_WEIGHT, int COST, std::vector<Order>belong_orders = {});
    int getVolume() const;
    int getWeight() const;
    int getCost() const;
    int getID() const;
    /**
     * Adds the order passed in the argument to the belong_orders vector
     * @param o Order object passed by reference
     */
    void add(Order &o);
    std::vector <Order> get_belong_orders();
    /**
     * Clear all orders from the belong_ordes vector
     */
    void clearOrders();
    /**
     * Resets the vans id to zero
     */
    static void resetId();
    friend std::ostream& operator<<(std::ostream& os, const Van &o);
private:
    int ID;
    static int van_nID;
    int MAX_VOL;
    int MAX_WEIGHT;
    int COST;
    std::vector<Order> belong_orders;
    /**
     * Generates an id by incrementing the static van_nID variable
     * @return new unique id to the new van
     */
    int generateID();
};



#endif //PROJETO1_DA_VAN_H
