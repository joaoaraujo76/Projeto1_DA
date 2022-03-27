#include "../include/App.h"

App::App() = default;
App::~App() = default;


void App::readFile(int file) {
    switch (file) {
        case 0: readVans(); break;
        case 1: readOrders(); break;
    }
}

void App::loadData() {
    for (int file = 0; file < filesname.size(); file++){
        readFile(file);
    }
}

void App::readVans() {
    std::ifstream vansFile;
    int maxVol, maxWeight, cost;

    vansFile.open(dataFolder + filesname[1]);
    if (!vansFile.is_open()) {
        std::cerr << "Unable to open vans.txt";
        exit(1);
    }
    std::string info;

    getline(vansFile, info);

    while (vansFile >> maxVol >> maxWeight >> cost) {
        Van van(maxVol, maxWeight, cost);
        vans.push_back(van);
    }
    vansFile.close();
}

void App::readOrders() {
    std::ifstream ordersFile;
    int volume, weight, reward, duration;

    ordersFile.open(dataFolder + filesname[0]);
    if (!ordersFile.is_open()) {
        std::cerr << "Unable to open vans.txt";
        exit(1);
    }
    std::string info;

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
