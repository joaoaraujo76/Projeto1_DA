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
    Van::resetId();
    fstream vansFile;
    int maxVol, maxWeight, cost;

    if(createFile(&vansFile,VANSFILE))
        cerr << "Unable to open vans.txt" << endl;
    string info;
    vansFile.close();

    ifstream file(dataFolder + filesname[VANSFILE]);
    getline(file, info);

    while (file >> maxVol >> maxWeight >> cost) {
        Van van(maxVol, maxWeight, cost);
        vans.push_back(van);
    }
    file.close();
}

void App::readOrders() {
    Order::resetId();
    fstream ordersFile;
    int volume, weight, reward, duration;
    string info;

    if(createFile(&ordersFile, ORDERFILE))
        cerr << "Unable to open orders.txt" << endl;
    ordersFile.close();

    ifstream file(dataFolder + filesname[ORDERFILE]);
    getline(file, info);

    while (file >> volume >> weight >> reward >> duration) {
        Order order(volume, weight, reward, duration);
        orders.push_back(order);
    }
    file.close();
    evaluateOrders();
}

void App::readSettings() {
    fstream settingsFile;
    createFile(&settingsFile, SETSFILE);
    if (emptyFile(&settingsFile, SETSFILE)) {
        settingsFile << "work time (hours) -10" << endl;
        settingsFile << "max express delivery duration (minutes) -4" << endl;
        settingsFile.close();
    }
    ifstream file(dataFolder + filesname[3]);
    string line;
    getline(file,line, '-');
    file >> workTime;
    setWorkingTime(workTime);
    getline(file,line, '-');
    file >> maxExpressDuration;
    setMaxExpressDuration(maxExpressDuration);
    file.close();
}

void App::optimizeExpressDeliveries() {
    resetOrders();
    int shippedExpressOrders = 0;
    int currTime = 0;
    sort(orders.begin(), orders.end(), [](Order &lhs, Order &rhs) {
        return lhs.getDuration() < rhs.getDuration();
    });
    if (orders.front().getDuration() > workTime)
        return writeOptExpressOrders(-1, 0, 0);
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
        writeOptExpressOrders((int) (currTime / shippedExpressOrders), shippedExpressOrders, (int)round(((double)shippedExpressOrders / (double)orders.size()) * 100));
}

void App::writeOptExpressOrders(int averageTime, size_t numDeliveries, int percentDeliveries) {
    fstream expressOrdersFile;
    clearFile(&expressOrdersFile,OPTEXPORDERSFILE);
    if(averageTime == -1){
        expressOrdersFile << "Impossible to deliver any order";
        expressOrdersFile.close();
        return;
    }
    expressOrdersFile << "Average time of each delivery: " << averageTime << "s" << endl;
    expressOrdersFile << "Number of deliveries:          " << numDeliveries << endl;
    expressOrdersFile << "Percentage of deliveries made: " << percentDeliveries << "%" << endl;
    expressOrdersFile <<  "id    volume   weight   reward   duration(s) \n";
    for(Order &order : orders){
        if(order.isShipped() && order.isExpress())
            expressOrdersFile << order.getID() << order << endl;
    }
    expressOrdersFile.close();
}

void App::writeOrders() {
    int counter = 0;
    fstream ordersFile;
    clearFile(&ordersFile,ORDERFILE);
    ordersFile << "   volume   weight   reward   duration(s) \n";
    for(Order &order : orders){
        counter++;
        if(counter == orders.size())
            ordersFile << order;
        else
            ordersFile << order << endl;
    }
    ordersFile.close();
}

std::vector<std::string> App::readExpressOrdersData() {
    const int NUM_LINES = 3;
    string info;
    vector<string> data;
    fstream expressOrdersFile;

    if(createFile(&expressOrdersFile,OPTEXPORDERSFILE)){
        data.emplace_back("No data available");
        expressOrdersFile.close();
        return data;
    }
    expressOrdersFile.open(dataFolder + filesname[OPTEXPORDERSFILE]);
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

void App::setMaxExpressDuration(int maxExpDuration) {
    this->maxExpressDuration = maxExpDuration*60;
    evaluateOrders();
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
        case 2: writeSettings(); break;
        default: break;
    }
}

void App::writeVans() {
    fstream vansFile;
    clearFile(&vansFile,VANSFILE);
    vansFile << "  maxVolume   maxWeight   cost \n";
    for(const Van &van : vans){
        vansFile << van;
    }
    vansFile.close();
}


void App::writeSettings() {
    fstream settingsFile;
    clearFile(&settingsFile,SETSFILE);
    settingsFile << "work time (hours) -" << workTime / 3600 << endl;
    settingsFile << "max express delivery duration (minutes) -" << maxExpressDuration / 60 << endl;
    settingsFile.close();
}


int App::getMaxExpressDuration() const {
    return maxExpressDuration;
}

void App::resetOrders() {
    for(Order &order : orders){
        order.setUnshipped();
    }
}

void App::shipOrders() {
    for (auto itr = orders.begin(); itr != orders.end(); itr++) {
        if ((*itr).isShipped())
            orders.erase(itr--);
    }
    writeOrders();
}

void App::dispatchOrdersToVans() {
    vector<int> vanRemainVol(vans.size());
    vector<int> vanRemainWeight(vans.size());
    vector<Order> normalOrders;

    resetVans();
    resetOrders();

    for (auto &o : orders)
        if (!o.isExpress()) normalOrders.push_back(o);

    sort(normalOrders.begin(), normalOrders.end(), [](const Order &lhs, const Order &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) > (rhs.getVolume() * rhs.getWeight());
    });
    sort(vans.begin(), vans.end(), [](const Van &lhs, const Van &rhs) {
        return (lhs.getVolume() * lhs.getWeight()) >= (rhs.getWeight() * rhs.getVolume());
    });

    int ordersLeft = 0;
    int vansNo = 0;
    int n = (int) normalOrders.size();

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < vansNo; j++) {
            if (vanRemainVol[j] >= normalOrders[i].getVolume() && vanRemainWeight[j] >= normalOrders[i].getWeight() && !normalOrders[i].isExpress()) {
                vanRemainVol[j] = vanRemainVol[j] - normalOrders[i].getVolume();
                vanRemainWeight[j] = vanRemainWeight[j] - normalOrders[i].getWeight();
                for (auto &o : orders)
                    if (o.getID() == normalOrders[i].getID()) o.setShipped();
                normalOrders[i].setShipped();
                vans[j].add(normalOrders[i]);
                break;
            }
        }
        if (j == vansNo) {
            if (vansNo + 1 > vans.size()) {
                ordersLeft = n - i + 1;
                writeEfficientVans(vansNo, ordersLeft);
                return;
            }

            if(!normalOrders[i].isExpress()){
                int vanVol = vans[vansNo].getVolume();
                int vanWeight = vans[vansNo].getWeight();
                vanRemainVol[vansNo] = vanVol - normalOrders[i].getVolume();
                vanRemainWeight[vansNo] = vanWeight - normalOrders[i].getWeight();
                normalOrders[i].setShipped();
                for (auto &o : orders)
                    if (o.getID() == normalOrders[i].getID()) o.setShipped();
                vans[j].add(normalOrders[i]);
                vansNo++;
            }
        }
    }

    writeEfficientVans(vansNo, ordersLeft);
}


void App::writeEfficientVans(int vansNo, int ordersLeft) {
    fstream EfficientVans;
    clearFile(&EfficientVans,MINVANSFILE);
    float percentVans = (float) vansNo / (float)vans.size() * 100;
    if(ordersLeft > 0){
        EfficientVans << "Impossible to deliver all orders: " << ordersLeft << " orders left" << endl;
    }
    else{
        EfficientVans << "Delivered all orders" << endl;
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

void App::setWorkingTime(int workTm) {
    this->workTime = workTm*3600;
}

bool App::createFile(std::fstream *file, int FILE_NUM) {
    bool created = false;
    file->open(dataFolder + filesname[FILE_NUM]);
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
    file->close();
    return created;
}

std::vector<std::string> App::readEfficientVansData(filesnumber fileNo) {
    const int NUM_LINES = 3;
    string info;
    vector<string> data;
    fstream file;

    if(createFile(&file, fileNo)){
        data.emplace_back("No data available");
        file.close();
        return data;
    }
    file.open(dataFolder + filesname[fileNo]);
    for(int i = 0; i < NUM_LINES; i++){
        getline(file, info);
        data.push_back(info);
    }
    file.close();
    if(data[0].empty()) {
        data.clear();
        data.emplace_back("No data available");
    }
    return data;
}



void App::evaluateOrders() {
    for(Order &order : orders){
        order.setExpress(order.getDuration() <= maxExpressDuration);
    }
    writeExpressOrders();
    writeNormalOrders();
}

void App::writeNormalOrders() {
    fstream ordersFile;
    clearFile(&ordersFile, NORMALORDERSFILE);
    ordersFile << " id    volume   weight   reward   duration(s) \n";
    for(Order &order : orders){
        if(!order.isExpress()){
            ordersFile << setw(3) << order.getID() << " " << order << endl;
        }
    }
    ordersFile.close();
}

void App::writeExpressOrders() {
    fstream ordersFile;
    clearFile(&ordersFile,EXPORDERSFILE);
    ordersFile << " id    volume   weight   reward   duration(s) \n";
    for(Order &order : orders){
        if(order.isExpress()){
            ordersFile << setw(3) << order.getID() << " " << order << endl;
        }
    }
    ordersFile.close();
}

bool App::clearFile(std::fstream *file, int FILE_NUM) {
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

bool App::emptyFile(fstream *file, const int FILE_NUM) {
    file->open(dataFolder + filesname[FILE_NUM]);
    file->seekg(0, ios::end);
    if (file->tellg() == 0) {
        return true;
    }
    return false;
}

void App::maxProfitDispatch() {
    int maxProfit = 0, profit;
    int shippedOrdersNo = 0;
    int usedVans = 0;
    vector<Order> auxOrders;
    resetOrders();
    resetVans();

    for (auto &o : orders) auxOrders.push_back(o);
    sort(vans.begin(), vans.end(), [](const Van &lhs, const Van &rhs) {
        return (lhs.getCost() < rhs.getCost() || (lhs.getCost() == rhs.getCost() && lhs.getVolume()*lhs.getWeight() >= rhs.getVolume()*rhs.getWeight()));
    });

    for (auto& van : vans){
        int i, w, v;
        int W = van.getWeight();
        int V = van.getVolume();
        int n = (int) auxOrders.size();
        vector<int> ordersShipped;
        profit = -van.getCost();

        if (auxOrders.empty()) break;

        vector<vector<vector<int>>> K(n + 1, vector<vector<int>>(W + 1, vector<int>(V + 1, 0)));

        for(i = 1; i <= n; i++) {
            int weight = auxOrders[i - 1].getWeight();
            int volume = auxOrders[i - 1].getVolume();
            int reward = auxOrders[i - 1].getReward();
            for(w = 0; w <= W; w++) {
                for (v = 0; v <= V; v++){
                    K[i][w][v] = K[i-1][w][v];

                    if ((w >= weight) && (v >= volume) && (K[i][w][v] < K[i - 1][w - weight][v - volume] + reward)) {
                        K[i][w][v] = K[i-1][w - weight][v - volume] + reward;
                    }
                }
            }
        }

        while (n != 0) {
            if (K[n][W][V] != K[n - 1][W][V]) {
                W = W - auxOrders[n - 1].getWeight();
                V = V - auxOrders[n - 1].getVolume();
                profit += auxOrders[n - 1].getReward();
                ordersShipped.push_back(n-1);
            }
            n--;
        }

        if (profit > 0){
            for (auto index : ordersShipped){
                auto shippedOrder = auxOrders[index];
                int id = shippedOrder.getID();
                for (auto &o : orders){
                    if (o.getID() == id) o.setShipped();
                }
                van.add(shippedOrder);
            }
            for (auto index : ordersShipped)
                auxOrders.erase(auxOrders.begin() + index);
            maxProfit += profit;
            usedVans++;
            shippedOrdersNo += (int)ordersShipped.size();
        }
    }
    int ordersLeft = (int)orders.size() - shippedOrdersNo;
    writeProfitVans(usedVans, ordersLeft, maxProfit);
}

void App::resetVans() {
    for (auto van : vans){
        van.clearOrders();
    }
}

void App::writeProfitVans(int vansNo, int ordersLeft, int maxProfit) {
    fstream profitVans;
    clearFile(&profitVans, PROFITVANSFILE);
    profitVans << "Maximum profit is: " << maxProfit << endl;

    if(ordersLeft > 0) profitVans << "Impossible to deliver all orders: " << ordersLeft << " orders left" << endl;
    else profitVans << "Delivered all orders" << endl;

    profitVans << "Used " << vansNo << "/" << vans.size() << " vans" << endl;
    profitVans << "Vans used and their orders:";
    for(int i = 0 ; i < vansNo; i++){
        profitVans << endl << "Van id: " << vans[i].getID() << " its orders: ";
        for(int j = 0 ; j < vans[i].get_belong_orders().size(); j++){
            profitVans << vans[i].get_belong_orders()[j].getID() << " ";
        }
    }
    profitVans.close();
}

void App::addOrder(Order &order) {
    orders.push_back(order);
    writeOrders();
}

void App::addVan(Van &van) {
    vans.push_back(van);
    writeVans();
}

void App::removeOrder(int id) {
    for(auto itr = orders.begin(); itr != orders.end(); itr++){
        if ((*itr).getID() == id){
            orders.erase(itr);
            break;
        }
    }
    writeOrders();
}

void App::removeVan(int id) {
    for(auto itr = vans.begin(); itr != vans.end(); itr++){
        if ((*itr).getID() == id){
            vans.erase(itr);
            break;
        }
    }
    writeVans();
}

