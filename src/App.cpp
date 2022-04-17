#include "../include/App.h"

using namespace std;

App::App() = default;
App::~App() = default;


void App::readFile(int file) {
    switch (file) {
        case 0: readVans(); break;
        case 1: readOrders(); break;
        case 2: readSettings(); break;
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
    bool express;

    ordersFile.open(dataFolder + filesname[0]);
    if (!ordersFile.is_open()) {
        cerr << "Unable to open vans.txt";
        exit(1);
    }
    string info;

    getline(ordersFile, info); //trash

    while (ordersFile >> volume >> weight >> reward >> duration) {
        express = duration <= maxExpressDuration;
        Order order(volume, weight, reward, duration, express, false);
        orders.push_back(order);
    }
    ordersFile.close();
}

void App::readSettings() {
    ifstream settingsFile;
    settingsFile.open(dataFolder + filesname[3]);
    if (!settingsFile.is_open()) {
        ofstream settingFile(dataFolder + filesname[3]);
        settingFile << "work time (hours) -10 \n";
        settingFile << "max express delivery duration (minutes) -40";
    }
    settingsFile.open(dataFolder + filesname[3]);
    if (!settingsFile.is_open()) {
        cerr << "Unable to open settings.txt";
        exit(1);
    }
    string line;
    getline(settingsFile,line, '-');
    settingsFile >> workTime;
    setWorkingTime(workTime);
    getline(settingsFile,line, '-');
    settingsFile >> maxExpressDuration;
    setMaxExpressDuration(maxExpressDuration);
}

std::vector<Van> &App::getVans() {
    return vans;
}

std::vector<Order> &App::getOrders() {
    return orders;
}

void App::optimizeExpressDeliveries() {
    resetOrders();
    int shippedExpressOrders = 0;
    int currTime = 0;
    sort(orders.begin(), orders.end(), [](Order &lhs, Order &rhs) {
        return lhs.getDuration() < rhs.getDuration();
    });
    if (orders.front().getDuration() > workTime)
        return writeExpressOrders(-1, 0, 0);
    for (Order &o: orders) {
        if (!o.isExpress())
            continue;
        if(!(currTime+o.getDuration() > workTime)){
            shippedExpressOrders++;
            o.setShipped();
            currTime +=o.getDuration();
        }
        else{
          break;
        }
    }
    if(shippedExpressOrders!=0)
        writeExpressOrders((int) (currTime / shippedExpressOrders), shippedExpressOrders, round(((double)shippedExpressOrders / (double)orders.size()) * 100));
    writeOrders();
}

void App::writeExpressOrders(int averageTime, size_t numDeliveries, int percentDeliveries) {
    fstream expressOrdersFile;
    clearFile(&expressOrdersFile,2);
    if(averageTime == -1){
        expressOrdersFile << "Impossible to deliver any order";
        expressOrdersFile.close();
        return;
    }
    expressOrdersFile << "Average time of each delivery: " << averageTime << "s" << endl;
    expressOrdersFile << "Number of deliveries:          " << numDeliveries << endl;
    expressOrdersFile << "Percentage of deliveries made: " << percentDeliveries << "%" << endl;
    for(Order &order : orders){
        if(order.isShipped() && order.isExpress())
            expressOrdersFile << order << endl;
    }
    expressOrdersFile.close();
}

void App::writeOrders() {
    int counter = 0;
    fstream ordersFile;
    clearFile(&ordersFile,0);
    ordersFile << "volume peso recompensa duração(s) \n";
    for(Order &order : orders){
        counter++;
        if(!order.isExpress() && !order.isShipped()){
            if(counter == orders.size())
                ordersFile << order;
            else
                ordersFile << order << endl;
        }
    }
    ordersFile.close();
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
    if(data[0] == data[1]){
        data.pop_back();
        data.pop_back();
    }
    return data;
}

void App::setMaxExpressDuration(int maxExpressDuration) {
    this->maxExpressDuration = maxExpressDuration * 60;
}

void App::clearFile(fstream *file, int FILE_NUM) {
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

void App::saveData() {
    for (int file = 0; file < filesname.size(); file++){
        saveFile(file);
    }
}

void App::saveFile(int file) {
    switch (file) {
        case 0: writeVans(); break;
        case 1: writeOrders(); break;
        case 3: writeSettings(); break;
        default: break;
    }
}

void App::writeVans() {
    fstream vansFile;
    clearFile(&vansFile,1);
    vansFile << "volMax pesoMax custo \n";
    for(const Van &van : vans){
        vansFile << van;
    }
    vansFile.close();
}


void App::writeSettings() {
    fstream settingsFile;
    clearFile(&settingsFile,3);
    settingsFile << "work time (hours) -";
    settingsFile << workTime / 3600 << endl;
    settingsFile << "max express delivery duration (minutes) -";
    settingsFile << maxExpressDuration / 60;
    settingsFile.close();
}


int App::getMaxExpressDuration() {
    return maxExpressDuration;
}

void App::resetOrders() {
    for(Order &order : orders){
        order.setExpress(order.getDuration() <= maxExpressDuration);
        order.setUnshipped();
    }
}

void App::nextExpressDay() {
    auto aux = orders;
    for (auto itr = orders.begin(); itr != orders.end(); itr++) {
        if ((*itr).isExpress())
            aux.erase(itr);
    }
}

void App::dispatchOrdersToVans() {
    vector<int> vanRemainVol(vans.size());
    vector<int> vanRemainWeight(vans.size());

    int volVantotal = 0;
    int weightVanTotal = 0;
    for (auto &van: vans) {
        volVantotal += van.getVolume();
        weightVanTotal += van.getWeight();
    }
    int volVanMedium = (int) volVantotal / vans.size();
    int weightVanMedium = (int) weightVanTotal / vans.size();


    int volOrderTotal = 0;
    int weightOrderTotal = 0;
    for (auto &order: orders) {
        volOrderTotal += order.getVolume();
        weightOrderTotal += order.getWeight();
    }
    int volOrderMedium = (int) volOrderTotal / orders.size();
    int weightOrderMedium = (int) weightOrderTotal / orders.size();

    int ratioVol = volVanMedium / volOrderMedium;
    int ratioWeight = weightVanMedium / weightOrderMedium;


    sort(orders.begin(), orders.end(), [](const Order &lhs, const Order &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) > (rhs.getVolume() * rhs.getWeight());
    });
    sort(vans.begin(), vans.end(), [](const Van &lhs, const Van &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) >= (rhs.getWeight() * rhs.getVolume());
    });

    int vansNo = 0;
    int n = (int) orders.size();

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < vansNo; j++) {
            if (vanRemainVol[j] >= orders[i].getVolume() && vanRemainWeight[j] >= orders[i].getWeight()) {
                vanRemainVol[j] = vanRemainVol[j] - orders[i].getVolume();
                vanRemainWeight[j] = vanRemainWeight[j] - orders[i].getWeight();
                break;
            }
        }
        if (j == vansNo) {
            if (vansNo + 1 > vans.size()) {
                cout << "Not enough vans for all the orders" << endl;
                cout << "There were left " << n - i + 1 << " orders" << endl;
                return;
            }

            int vanVol = vans[vansNo].getVolume();
            int vanWeight = vans[vansNo].getWeight();
            vanRemainVol[vansNo] = vanVol - orders[i].getVolume();
            vanRemainWeight[vansNo] = vanWeight - orders[i].getWeight();
            vansNo++;
        }
    }
    cout << "Number of vans required: " << vansNo;
}

int App::getWorkingTime() const {
    return workTime;
}

void App::setWorkingTime(int workTime) {
    this->workTime = workTime*3600;
}