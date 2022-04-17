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
    std::vector <std::string> filesname = {"orders.txt", "vans.txt", "express_deliveries.txt", "settings.txt" };
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
    std::vector<std::string> readExpressOrdersData();
    void loadData();
    void saveData();
    void writeVans();
    void writeOrders();
    void writeSettings();
    void writeExpressOrders(int averageTime, size_t numDeliveries, int percentDeliveries);
    void saveFile(int file);
    void optimizeExpressDeliveries();
    void dispatchOrdersToVans();
    std::vector<Van> &getVans();
    std::vector<Order> &getOrders() ;
    int getWorkingTime() const;
    void setWorkingTime(int workTime);
    int getMaxExpressDuration();
    void setMaxExpressDuration(int maxExpressDuration);
    void resetOrders();
    void nextExpressDay();
};

#endif //PROJETO1_DA_APP_H