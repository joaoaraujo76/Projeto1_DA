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
    std::vector<Order> normal_orders;
    std::vector<Order> express_orders;
    std::vector <Van> vans;
    std::vector <std::string> filesname = {"orders.txt", "vans.txt", "express_orders.txt", "settings.txt", "min_vans.txt", "normal_orders.txt"};
    int workTime;
    int maxExpressDuration;
public:
    App();
    ~App();
    void readFile(int file);
    bool clearFile(std::fstream *file, int FILE_NUM);
    bool createFile(std::fstream *file, int FILE_NUM);
    void readVans();
    void readOrders();
    void readSettings();
    void readExpressOrdersData();
    void readMinVansData();
    void loadData();
    void saveData();
    void writeVans();
    void writeSettings();
    void writeExpressOrders(int averageTime, size_t numDeliveries, int percentDeliveries);
    void writeEfficientVans(int vansNo, int ordersLeft);
    void optimizeExpressDeliveries();
    void dispatchOrdersToVans();
    std::vector<Van> &getVans();
    std::vector<Order> &getNormalOrders() ;
    std::vector<Order> &getExpressOrders() ;
    int getWorkingTime() const;
    void setWorkingTime(int workTime);
    int getMaxExpressDuration();
    void setMaxExpressDuration(int maxExpressDuration);
    void resetOrders();
    void nextExpressDay();
    void clearOrdersFromVans();
};

#endif //PROJETO1_DA_APP_H