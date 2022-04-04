#include "../include/App.h"

using namespace std;

App::App() = default;
App::~App() = default;


void App::readFile(int file) {
    switch (file) {
        case 0: readVans(); break;
        case 1: readOrders(); break;
        default: break;
    }
}

void App::loadData() {
    for (int file = 0; file < filesname.size(); file++){
        readFile(file);
    }
}

void App::readVans() {
    ifstream vansFile;
    int maxVol, maxWeight, cost;

    vansFile.open(dataFolder + filesname[1]);
    if (!vansFile.is_open()) {
        cerr << "Unable to open vans.txt";
        exit(1);
    }
    string info;

    getline(vansFile, info);

    while (vansFile >> maxVol >> maxWeight >> cost) {
        Van van(maxVol, maxWeight, cost);
        vans.push_back(van);
    }
    vansFile.close();
}

void App::readOrders() {
    ifstream ordersFile;
    int volume, weight, reward, duration;

    ordersFile.open(dataFolder + filesname[0]);
    if (!ordersFile.is_open()) {
        cerr << "Unable to open vans.txt";
        exit(1);
    }
    string info;

    getline(ordersFile, info);

    while (ordersFile >> volume >> weight >> reward >> duration) {
        Order order(volume, weight, reward, duration);
        orders.push_back(order);
    }
    ordersFile.close();
}

std::vector<Van> &App::getVans() {
    return vans;
}

std::vector<Order> &App::getOrders() {
    return orders;
}

void App::optimizeExpressDeliveries() {
    vector<Order> aux_orders;
    const int MAX_TIME = workTime * 3600;
    int currTime = 0;
    sort(orders.begin(), orders.end(), [](const Order &lhs, const Order &rhs) {
        return lhs.getDuration() < rhs.getDuration();
    });
    if(orders.front().getDuration() > MAX_TIME)
        return writeExpressOrders(-1, aux_orders);
    for(const Order &o : orders){
        aux_orders.push_back(o);
        currTime += o.getDuration();
        if(currTime > MAX_TIME){
            aux_orders.pop_back();
            return writeExpressOrders((int)(currTime/aux_orders.size()), aux_orders);
        }
    }
}

void App::writeExpressOrders(int time, const std::vector<Order>& currOrders) {
    ofstream ordersFile;
    ordersFile.open(dataFolder + filesname[2], ofstream::out | ofstream::trunc);
    if(!ordersFile.is_open()){
        ofstream ordersFile(dataFolder + filesname[2]);
        ordersFile.open(dataFolder + filesname[2], ofstream::out | ofstream::trunc);
    }
    if (!ordersFile.is_open()) {
        cerr << "Unable to open orders.txt";
        exit(1);
    }

    if(time == -1){
        ordersFile << "Impossible to deliver any order";
        ordersFile.close();
        return;
    }

    ordersFile << "Average time of each delivery: " << time << "s" << endl;
    ordersFile << "Number of deliveries:          " << currOrders.size() << endl;
    ordersFile << "Percentage of deliveries made: " << round(((double)currOrders.size() / (double)orders.size()) * 100) << "%" << endl;

    for(const Order &o : orders){
        ordersFile << o;
    }

    ordersFile.close();
}

int App::getWorkingTime() const {
    return workTime;
}

void App::setWorkingTime(int workingTime) {
    this->workTime = workingTime;
    optimizeExpressDeliveries();
}

std::vector<std::string> App::readExpressOrders() {
    const int NUM_LINES = 3;
    string info;
    vector<string> data;
    ifstream expressOrdersFile;

    expressOrdersFile.open(dataFolder + filesname[2]);
    if (!expressOrdersFile.is_open()) {
        cerr << "Unable to open vans.txt";
        exit(1);
    }

    for(int i = 0; i < NUM_LINES; i++){
        getline(expressOrdersFile, info);
        data.push_back(info);
    }
    expressOrdersFile.close();
    return data;
}