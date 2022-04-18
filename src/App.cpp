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
    fstream vansFile;
    int maxVol, maxWeight, cost, id = 0;

    if(createFile(&vansFile,1))
        cerr << "Unable to open vans.txt" << endl;
    string info;

    getline(vansFile, info); // trash

    while (vansFile >> maxVol >> maxWeight >> cost) {
        Van van(id++,maxVol, maxWeight, cost);
        vans.push_back(van);
    }
    vansFile.close();
}

void App::readOrders() {
    fstream ordersFile;
    int volume, weight, reward, duration, id = 0;
    bool express;

    for(int fileNum = 0; fileNum <=2; fileNum += 2){
        if(createFile(&ordersFile, fileNum) && fileNum == 0)
            cerr << "Unable to open orders.txt" << endl;
        string info;

        if(fileNum == 0)
            getline(ordersFile, info);
        else
            for(int times = 0; times < 3; times++){
                getline(ordersFile, info);
            }

        while (ordersFile >> volume >> weight >> reward >> duration) {
            express = duration <= maxExpressDuration;
            Order order(id++, volume, weight, reward, duration, express, false);
            orders.push_back(order);
        }
        ordersFile.close();
    }
}

void App::readSettings() {
    fstream settingsFile;
    if(clearFile(&settingsFile,3)){
        settingsFile << "work time (hours)-10\n";
        settingsFile << "max express delivery duration (minutes)-4";
    }
    settingsFile.close();
    settingsFile.open(dataFolder + filesname[3]);

    string line;
    getline(settingsFile,line, '-');
    settingsFile >> workTime;
    setWorkingTime(workTime);
    getline(settingsFile,line, '-');
    settingsFile >> maxExpressDuration;
    setMaxExpressDuration(maxExpressDuration);

    settingsFile.close();
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
        shippedExpressOrders++;
        o.setShipped();
        currTime += o.getDuration();
        if (currTime > workTime) {
            shippedExpressOrders--;
            o.setUnshipped();
            currTime -= o.getDuration();
            break;
        }
    }
    if(shippedExpressOrders!=0)
        writeExpressOrders((int) (currTime / shippedExpressOrders), shippedExpressOrders, (int)round(((double)shippedExpressOrders / (double)orders.size()) * 100));
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

std::vector<std::string> App::readExpressOrdersData() {
    const int NUM_LINES = 3;
    string info;
    vector<string> data;
    fstream expressOrdersFile;

    if(createFile(&expressOrdersFile,2)){
        data.push_back("No data available");
        expressOrdersFile.close();
        return data;
    }

    for(int i = 0; i < NUM_LINES; i++){
        getline(expressOrdersFile, info);
        data.push_back(info);
    }
    expressOrdersFile.close();
    if(data[0].empty()) {
        data.clear();
        data.emplace_back("No data available");
    }
    return data;
}

void App::setMaxExpressDuration(int maxExpressDuration) {
    this->maxExpressDuration = maxExpressDuration * 60;
}

bool App::clearFile(fstream *file, int FILE_NUM) {
    bool exists = true;
    file->open(dataFolder + filesname[FILE_NUM], ofstream::out | ofstream::trunc);
    if(!file->is_open()){
        fstream newFile(dataFolder + filesname[FILE_NUM]);
        file = &newFile;
        newFile.open(dataFolder + filesname[FILE_NUM], ofstream::out | ofstream::trunc);
        exists = false;
        if (!newFile.is_open()) {
            cerr << "Unable to open file";
            exit(1);
        }
    }
    return exists;
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


    sort(orders.begin(), orders.end(), [](const Order &lhs, const Order &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) > (rhs.getVolume() * rhs.getWeight());
    });
    sort(vans.begin(), vans.end(), [](const Van &lhs, const Van &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) >= (rhs.getWeight() * rhs.getVolume());
    });

    int ordersLeft;
    int vansNo = 0;
    int n = (int) orders.size();

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < vansNo; j++) {
            if (vanRemainVol[j] >= orders[i].getVolume() && vanRemainWeight[j] >= orders[i].getWeight() && !orders[i].isExpress()) {
                vanRemainVol[j] = vanRemainVol[j] - orders[i].getVolume();
                vanRemainWeight[j] = vanRemainWeight[j] - orders[i].getWeight();
                vans[j].add(orders[i]);
                break;
            }
        }
        if (j == vansNo) {
            if (vansNo + 1 > vans.size()) {
                ordersLeft = n - i + 1;
                writeEfficientVans(vansNo,ordersLeft);
                return;
            }

            if(!orders[i].isExpress()){
                int vanVol = vans[vansNo].getVolume();
                int vanWeight = vans[vansNo].getWeight();
                vanRemainVol[vansNo] = vanVol - orders[i].getVolume();
                vanRemainWeight[vansNo] = vanWeight - orders[i].getWeight();
                vans[j].add(orders[i]);
                vansNo++;
            }
        }
    }

    writeEfficientVans(vansNo,ordersLeft);
}


void App::writeEfficientVans(int vansNo, int ordersLeft) {
    fstream EfficientVans;
    clearFile(&EfficientVans,4);
    float percentVans = (float) vansNo / vans.size() * 100;
    if(ordersLeft > 0){
        EfficientVans << "Impossible to deliver all orders: " << ordersLeft << " orders left" << endl;
    }
    else{
        EfficientVans << "Delivered all "<< ordersLeft << "orders" << endl;
    }
    EfficientVans << "Used " << vansNo << "/" << vans.size() << " vans" << endl;
    EfficientVans << "Percent of vans used: " << percentVans << "%" << endl;
    EfficientVans << "Vans used and their orders:";

    for(int i = 0 ; i < vansNo; i++){
        EfficientVans << endl << "Van id: " <<  vans[i].getID() << " its orders: ";
        for(int j = 0 ; j < vans[i].get_belong_orders().size(); j++){
            EfficientVans << vans[i].get_belong_orders()[j].getID() << " ";
        }
    }
    EfficientVans.close();
}

int App::getWorkingTime() const {
    return workTime;
}

void App::setWorkingTime(int workTime) {
    this->workTime = workTime*3600;
}

bool App::createFile(std::fstream *file, int FILE_NUM) {
    bool created = false;
    file->open(dataFolder + filesname[FILE_NUM], ios::in);
    if(!file->is_open()){
        fstream newFile(dataFolder + filesname[FILE_NUM]);
        file = &newFile;
        newFile.open(dataFolder + filesname[FILE_NUM], ios::app);
        created = true;
        if (!newFile.is_open()) {
            cerr << "Unable to open file";
            exit(1);
        }
    }
    return created;
}

std::vector<std::string> App::readEfficientVansData() {
    const int NUM_LINES = 3;
    string info;
    vector<string> data;
    fstream expressOrdersFile;

    if(createFile(&expressOrdersFile,4)){
        data.push_back("No data available");
        expressOrdersFile.close();
        return data;
    }

    for(int i = 0; i < NUM_LINES; i++){
        getline(expressOrdersFile, info);
        data.push_back(info);
    }
    expressOrdersFile.close();
    if(data[0].empty()) {
        data.clear();
        data.emplace_back("No data available");
    }
    return data;
}


