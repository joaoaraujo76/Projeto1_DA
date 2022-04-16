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

    getline(vansFile, info); // trash

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

    getline(ordersFile, info); //trash

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
        orders.pop_back();
        currTime += o.getDuration();
        if(currTime > MAX_TIME){
            aux_orders.pop_back();
            orders.push_back(o);
            return writeExpressOrders((int)(currTime/aux_orders.size()), aux_orders);
        }
    }
}

void App::writeExpressOrders(int time, const std::vector<Order>& currOrders) {
    fstream expressOrders;
    clearFile(&expressOrders,2);

    if(time == -1){
        expressOrders << "Impossible to deliver any order";
        expressOrders.close();
        return;
    }

    expressOrders << "Average time of each delivery: " << time << "s" << endl;
    expressOrders << "Number of deliveries:          " << currOrders.size() << endl;
    expressOrders << "Percentage of deliveries made: " << round(((double)currOrders.size() / (double)orders.size()) * 100) << "%" << endl;

    for(const Order &o : currOrders){
        expressOrders << o;
    }

    expressOrders.close();

    updateOrders();
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

void App::setMaxExpressDuration(int maxExpressDuration) {
    this->maxExpressDuration = maxExpressDuration;
}

void App::updateOrders() {
    fstream normalOrders;
    clearFile(&normalOrders,0);

    for(const Order &o : orders){
        normalOrders << o;
    }

    normalOrders.close();


}

void App::clearFile(fstream *file, const int FILE_NUM) {
    file->open(dataFolder + filesname[FILE_NUM], ofstream::out | ofstream::trunc);
    if(!file->is_open()){
        ofstream ordersFile(dataFolder + filesname[FILE_NUM]);
        ordersFile.open(dataFolder + filesname[2], ofstream::out | ofstream::trunc);
    }
    if (!file->is_open()) {
        cerr << "Unable to open orders.txt";
        exit(1);
    }
}
