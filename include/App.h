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
#include <sstream>
#include "Van.h"
#include "Order.h"

class App {

private:
    std::string dataFolder = "../data/";
    std::vector<Order> orders;
    std::vector <Van> vans;
    std::vector <std::string> filesname = {"orders.txt", "vans.txt", "express_orders.txt", "settings.txt", "min_vans.txt", "normal_orders.txt", "profit_vans.txt", "express_deliveries.txt"};

    int workTime;
    int maxExpressDuration;
public:
    enum filesnumber {ORDERFILE, VANSFILE, EXPORDERSFILE, SETSFILE, MINVANSFILE, NORMALORDERSFILE, PROFITVANSFILE, OPTEXPORDERSFILE};

    App();
    ~App();
    void readFile(int file);
    bool clearFile(std::fstream *file, int FILE_NUM);
    bool createFile(std::fstream *file, int FILE_NUM);
    void readVans();
    void readOrders();
    void readSettings();
    bool emptyFile(std::fstream *file, int FILE_NUM);
    std::vector<std::string> readExpressOrdersData();
    std::vector<std::string> readEfficientVansData(filesnumber fileNo);
    void loadData();
    void saveData();
    void writeVans();
    void writeOrders();
    void writeNormalOrders();
    void writeExpressOrders();
    void writeSettings();
    void writeOptExpressOrders(int averageTime, size_t numDeliveries, int percentDeliveries);
    void writeEfficientVans(int vansNo, int ordersLeft);
    void writeProfitVans(int vansNo, int ordersLeft, int maxProfit);
    void saveFile(int file);
    void optimizeExpressDeliveries();
    void dispatchOrdersToVans();
    void maxProfitDispatch();
    int getWorkingTime() const;
    void setWorkingTime(int workTime);
    int getMaxExpressDuration() const;
    void setMaxExpressDuration(int maxExpressDuration);
    void resetOrders();
    void resetVans();
    void evaluateOrders();
    void shipOrders();
    void addOrder(Order &order);
    void addVan(Van &van);
    void removeOrder(int id);
    void removeVan(int id);
};

#endif //PROJETO1_DA_APP_H