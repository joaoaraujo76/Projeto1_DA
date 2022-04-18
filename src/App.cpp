#include "../include/App.h"

using namespace std;

App::App() = default;
App::~App() = default;


void App::readFile(int file) {
    switch (file) {
        case 0: readSettings(); break;
        case 1: readVans(); break;
        case 2: readOrders(); break;
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
    ofstream normalOrders(dataFolder + filesname[5]);
    ofstream expressOrders(dataFolder + filesname[2]);

    int volume, weight, reward, duration, id = 0;
    bool express;

    if(createFile(&ordersFile, 0))
        cerr << "Unable to open vans.txt" << endl;
    string info;
    getline(ordersFile, info); // trash

    while (ordersFile >> volume >> weight >> reward >> duration) {
        express = duration <= maxExpressDuration;
        Order order(id++, volume, weight, reward, duration, express, false);
        if(!express){
            normalOrders << order;
            normal_orders.push_back(order);
        }
        else{
            expressOrders << order;
            express_orders.push_back(order);
        }
    }
    expressOrders.close();
    normalOrders.close();
    ordersFile.close();
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

void App::optimizeExpressDeliveries() {
    resetOrders();
    int shippedExpressOrders = 0;
    int currTime = 0;
    sort(express_orders.begin(), express_orders.end(), [](Order &lhs, Order &rhs) {
        return lhs.getDuration() < rhs.getDuration();
    });
    if (express_orders.front().getDuration() > workTime)
        return writeExpressOrders(-1, 0, 0);
    for (Order &o: express_orders) {
        currTime += o.getDuration();
        if (currTime + o.getDuration() > workTime) {
            break;
        }
        currTime += o.getDuration();
        shippedExpressOrders++;
        o.setShipped();
    }
    if(shippedExpressOrders!=0)
        writeExpressOrders((int) (currTime / shippedExpressOrders), shippedExpressOrders, (int)round(((double)shippedExpressOrders / (double)express_orders.size()) * 100));
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
    expressOrdersFile << "Percentage of deliveries made: " << percentDeliveries << "%\n\n";

    sort(express_orders.begin(), express_orders.end(), [](Order &lhs, Order &rhs) {
        return lhs.isShipped() > rhs.isShipped();
    });

    for(Order &order : express_orders){
            expressOrdersFile << order;
    }
    expressOrdersFile.close();
}

void App::readExpressOrdersData() {
    ifstream expressOrdersFile;
    string data;
    expressOrdersFile.open(dataFolder + filesname[2]);
    if(!expressOrdersFile){
        cout << "No data available" << endl;
    }
    else{
        while (getline(expressOrdersFile, data))
        {
            cout << data << endl;
        }
    }
    expressOrdersFile.close();
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
    for(Order &order : express_orders){
        order.setExpress(order.getDuration() <= maxExpressDuration);
        order.setUnshipped();
    }
    for(Order &order : normal_orders){
        order.setExpress(order.getDuration() <= maxExpressDuration);
        order.setUnshipped();
    }
}

void App::nextExpressDay() {
    auto aux = express_orders;
    for (auto itr = express_orders.begin(); itr != express_orders.end(); itr++) {
        if ((*itr).isExpress())
            aux.erase(itr);
    }
}

void App::dispatchOrdersToVans() {
    vector<int> vanRemainVol(vans.size());
    vector<int> vanRemainWeight(vans.size());


    sort(normal_orders.begin(), normal_orders.end(), [](const Order &lhs, const Order &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) > (rhs.getVolume() * rhs.getWeight());
    });
    sort(vans.begin(), vans.end(), [](const Van &lhs, const Van &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) >= (rhs.getWeight() * rhs.getVolume());
    });

    int ordersLeft = 0;
    int vansNo = 0;
    int n = (int) normal_orders.size();

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < vansNo; j++) {
            if (vanRemainVol[j] >= normal_orders[i].getVolume() && vanRemainWeight[j] >= normal_orders[i].getWeight() && !normal_orders[i].isExpress()) {
                vanRemainVol[j] = vanRemainVol[j] - normal_orders[i].getVolume();
                vanRemainWeight[j] = vanRemainWeight[j] - normal_orders[i].getWeight();
                vans[j].add(normal_orders[i]);
                break;
            }
        }
        if (j == vansNo) {
            if (vansNo + 1 > vans.size()) {
                ordersLeft = n - i + 1;
                writeEfficientVans(vansNo,ordersLeft);
                return;
            }

            if(!getNormalOrders()[i].isExpress()){
                int vanVol = vans[vansNo].getVolume();
                int vanWeight = vans[vansNo].getWeight();
                vanRemainVol[vansNo] = vanVol - normal_orders[i].getVolume();
                vanRemainWeight[vansNo] = vanWeight - normal_orders[i].getWeight();
                vans[j].add(normal_orders[i]);
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
        EfficientVans << "Delivered all orders" << endl;
    }
    EfficientVans << "Used " << vansNo << "/" << vans.size() << " vans" << endl;
    EfficientVans << "Percent of vans used: " << percentVans << "%\n" << endl;
    EfficientVans << "Vans used and their orders:\n";

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

void App::clearOrdersFromVans() {
    for(int i = 0 ; i < vans.size(); i++){
        vans[i].get_belong_orders().clear();
    }
}

void App::readMinVansData() {
    string data;
    ifstream minVansFile;
    minVansFile.open(dataFolder + filesname[4]);
    if(!minVansFile){
        cout << "No data available" << endl;
    }
    else{
        while (getline(minVansFile, data))
        {
            cout << data << endl;
        }
    }
    minVansFile.close();
}

std::vector<Order> &App::getNormalOrders() {
    return normal_orders;
}

std::vector<Order> &App::getExpressOrders() {
    return express_orders;
}



