#ifndef PROJETO1_DA_APP_H
#define PROJETO1_DA_APP_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <cmath>
#include "Van.h"
#include "Order.h"

class App {

private:
    std::string dataFolder = "../data/";
    std::vector<Order> orders;
    std::vector <Van> vans;
    std::vector <std::string> filesname = {"orders.txt", "vans.txt", "express_deliveries.txt"};
    int workTime = 8;
    int maxExpressDuration = 4;
public:
    App();
    ~App();
    void readFile(int file);
    void clearFile(std::fstream *file, const int FILE_NUM);
    void readVans();
    void readOrders();
    std::vector<std::string> readExpressOrders();
    void writeExpressOrders(int time, const std::vector<Order>& orders);
    void updateOrders();
    void loadData();
    void optimizeExpressDeliveries();
    std::vector<Van> &getVans();
    std::vector<Order> &getOrders() ;
    int getWorkingTime() const;
    void setWorkingTime(int workingTime);
    void setMaxExpressDuration(int maxExpressDuration);
};

#endif //PROJETO1_DA_APP_H