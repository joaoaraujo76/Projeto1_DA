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

/**
 * Main class with all the algorithms that solve the proposed scenarios
 */
class App {

private:
    std::string dataFolder = "../data/";
    std::vector<Order> orders;
    std::vector <Van> vans;
    std::vector <std::string> filesname = {"orders.txt", "vans.txt", "express_orders.txt", "settings.txt", "min_vans.txt", "normal_orders.txt", "profit_vans.txt", "express_deliveries.txt"};

    /** Keeps track of the work time in hours used in the third scenario (optimizeExpressDeliveries method) */
    int workTime;
    /** Defines the maximum duration of express orders used in the third scenario (optimizeExpressDeliveries method) */
    int maxExpressDuration;
public:
    enum filesnumber {ORDERFILE, VANSFILE, EXPORDERSFILE, SETSFILE, MINVANSFILE, NORMALORDERSFILE, PROFITVANSFILE, OPTEXPORDERSFILE};
    /**
     * App class default constructor
     */
    App();
    /**
     * App class default destructor
     */
    ~App();
    /**
     * Calls all the methods to read the files and load the program
     * @param file index number of the file in filesname vector
     */
    void readFile(int file);
    /**
     * Checks if the argument file exists and clears it, otherwise creates one file matching de FILE_NUM argument correspondent in the filesname
     * @param file fstream pointer file to clear
     * @param FILE_NUM index file number in the filesname vector
     * @return true if file exists or false otherwise
     */
    bool clearFile(std::fstream *file, int FILE_NUM);
    /**
     * Checks if the argument file exists and opens it in ios::app mode, otherwise creates one file matching de FILE_NUM argument correspondent in the filesname
     * @param file fstream pointer file to open
     * @param FILE_NUM index file number in the filesname vector
     * @return true if file exists or false otherwise
     */
    bool createFile(std::fstream *file, int FILE_NUM);
    /**
     * Reads Van objects from the vans text file and loads them in vans vector
     */
    void readVans();
    /**
     * Reads Order objects from the orders text file and loads them in orders vector
     */
    void readOrders();
    /**
     * Reads the settings from the settings text file and loads them in the program
     */
    void readSettings();
    /**
     * Checks if the file passed in the argument is empty
     * @param file fstream pointer file to check if it's empty
     * @param FILE_NUM index file number in filesname vector
     * @return true is file is empty or false otherwise
     */
    bool emptyFile(std::fstream *file, int FILE_NUM);
    /**
     * Reads express orders from the express orders file checking before if it exists, if not creates that file
     * @return vector with the order lines of the file
     */
    std::vector<std::string> readExpressOrdersData();
    /**
     * Reads vans from the file which number is passed in the argument fileNo checking before if it exists, if not creates that file
     * @param fileNo index file number in the filesname vector
     * @return vector with the order lines of the file
     */
    std::vector<std::string> readEfficientVansData(filesnumber fileNo);
    /**
     * Calls the methods to load all data files needed to the program run
     */
    void loadData();
    /**
     * Calls the methods to save all data produced by the program into the data files
     */
    void saveData();
    /**
     * Writes all vans information in the vans data file
     */
    void writeVans();
    /**
     * Writes all orders information in the orders data file
     */
    void writeOrders();
    /**
     * Writes the normal orders in the normal orders file, aggregating the matching id of those orders
     */
    void writeNormalOrders();
    /**
     * Writes the express orders in the express orders file, aggregating the matching id of those orders
     */
    void writeExpressOrders();
    /**
     * Writes the program actual settings in the settings file
     */
    void writeSettings();
    /**
     * Writes the express orders information and the results of the method that solve the third scenario with the express orders delivery into the express_delivery file
     * @param averageTime average time to deliver the express orders
     * @param numDeliveries number of express orders delivered
     * @param percentDeliveries percent of orders delivered
     */
    void writeOptExpressOrders(int averageTime, size_t numDeliveries, int percentDeliveries);
    /**
     * Writes the vans and its content orders into the min_vans file after running the dispatchOrdersToVans method
     * @param vansNo number of vans needed to dispatch the orders
     * @param ordersLeft orders left that could get into any van
     */
    void writeEfficientVans(int vansNo, int ordersLeft);
    /**
     * Writes the vans and their content orders into the profit_vans file after running the maxProfitDispatch method
     * @param vansNo number of vans needed to dispatch the orders
     * @param ordersLeft orders left that could get into any van
     * @param maxProfit maximum profit of the company in the shipped orders
     */
    void writeProfitVans(int vansNo, int ordersLeft, int maxProfit);
    void saveFile(int file);
    /**
     * Algorithm the solves the third scenario writing the results in the correspondent file
     */
    void optimizeExpressDeliveries();
    /**
     * Algorithm that solves the first scenario shipping the right orders into the vans and saving the results into the correspondent file
     * This is a bin packing algorithm variation
     */
    void dispatchOrdersToVans();
    /**
     * Algorithm that solves the second scenario shipping the right orders into the vans and saving the results into the correspondent file
     * This is a 0-1 knapsack algorithm variation with 2 constraint variables
     */
    void maxProfitDispatch();
    /**
     * Gets the work time attribute variable
     * @return work time attribute variable
     */
    int getWorkingTime() const;
    /**
     * Sets the work time attribute with the value passed in the argument
     * @param workTime work time in hours
     */
    void setWorkingTime(int workTime);
    /**
     * Gets the maximum duration of an express order
     * @return the value of the maxExpressDuration variable
     */
    int getMaxExpressDuration() const;
    /**
     * Sets the maximum duration of an express order with the value passed in the argument
     * @param maxExpressDuration maximum duration of an express order in seconds
     */
    void setMaxExpressDuration(int maxExpressDuration);
    /**
     * Sets all orders to unshipped state
     */
    void resetOrders();
    /**
     * Clears all the orders inside the vans
     */
    void resetVans();
    /**
     * Checks what other are express or normal and writes them into the the correspondent files
     */
    void evaluateOrders();
    /**
     * Ships the orders by clearing from the orders file the orders that where shipped in the last algorithm that was run
     */
    void shipOrders();
    /**
     * Adds an order to the orders vector
     * @param order Order object passed by reference
     */
    void addOrder(Order &order);
    /**
     * Adds a van to the vans vector
     * @param van Van object passed by reference
     */
    void addVan(Van &van);
    /**
     * Removes the van matching the id passed in the argument from the vans vector
     * @param id id number of the van to be removed
     */
    void removeOrder(int id);
    /**
     * Removes the order matching the id passed in the argument from the orders vector
     * @param id id number of the order to be removed
     */
    void removeVan(int id);
};

#endif //PROJETO1_DA_APP_H