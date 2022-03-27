#ifndef PROJETO1_DA_APP_H
#define PROJETO1_DA_APP_H

#include "string"
#include "vector"
#include "Van.h"
#include "Order.h"
#include "iostream"
#include <fstream>


class App {

public:
    std::string dataFolder = "../data/";
    std::vector<Order> orders;
    std::vector <Van> vans;
    std::vector <std::string> filesname = {"orders.txt", "vans.txt"};
public:
    App();
    ~App();
    void readFile(int file);
    void readVans();
    void readOrders();
    void loadData();
    std::vector<Van> &getVans();
    std::vector<Order> &getOrders();
};

#endif //PROJETO1_DA_APP_H
