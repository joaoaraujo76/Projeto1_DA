#include "../include/Menu.h"

#include <iostream>

using namespace std;

Menu::~Menu() = default;

Menu::Menu(App &app): app(app) {}

int Menu::readInt() {
    int opt; string optstr;
    while (true){
        stringstream ss;
        ss << readStr(); ss >> opt;
        if(!ss.fail() && ss.eof() && opt>=0) break;
        cout << "Invalid input. Try a valid integer..." << endl;
    }
    cout << endl;
    return opt;
}

void Menu::waitForKey() {
    string str;
    cout << endl << "Press enter to continue..." << endl;
    getline(cin, str);
}

std::string Menu::readStr() {
    string str;
    cout << ": ";
    getline(cin, str);
    return str;
}

Menu *Menu::invalidInput() {
    cout << "Invalid input option!" << endl;
    return this;
}

MainMenu::MainMenu(App &app): Menu(app){}

void MainMenu::display(){
    cout << endl;
    cout << "Main Menu:" << endl;
    cout << "1 - Normal Orders management" << endl;
    cout << "2 - Express Orders management" << endl;
    cout << "3 - Ship orders" << endl;
    cout << "4 - Add/Remove Vans or Orders" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *MainMenu::nextMenu() {
    switch (readInt()) {
        case 1:
            return new NormalOrderMenu(app);
        case 2:
            return new ExpressOrderMenu(app);
        case 3:
            app.shipOrders();
            cout << "Done!" << endl;
            waitForKey();
            return this;
        case 4:
            return new AddRemoveItens(app);
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}

ExpressOrderMenu::ExpressOrderMenu(App &app): Menu(app){}

void ExpressOrderMenu::display(){
    cout << endl;
    cout << "Express Orders Menu:" << endl;
    cout << "1 - Minimize average express delivery time" << endl;
    cout << "2 - View Information" << endl;
    cout << "3 - Settings" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *ExpressOrderMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            app.optimizeExpressDeliveries();
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 2: {
            for(const string &line : app.readExpressOrdersData())
                cout << line << endl;
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 3: {
            return new ExpressSettingsMenu(app);
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

ExpressSettingsMenu::ExpressSettingsMenu(App &app): Menu(app){}

void ExpressSettingsMenu::display(){
    cout << endl;
    cout << "Express Orders Settings Menu:" << endl;
    cout << "1 - Change Working time (curr: " << app.getWorkingTime()/3600 << " hours)" << endl;
    cout << "2 - Change Max Express Delivery time (curr: " << app.getMaxExpressDuration()/60 << " minutes)" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *ExpressSettingsMenu::nextMenu() {
    int time;
    switch (readInt()) {
        case 1:{
            do{
                cout << "Please insert the new working time: ";
                time = readInt();
            } while (time > 24);
            app.setWorkingTime(time);
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 2:{
            cout << "Please insert the new Max Express Delivery time: ";
            time = readInt();
            app.setMaxExpressDuration(time);
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}

NormalOrderMenu::NormalOrderMenu(App &app) : Menu(app) {

}

void NormalOrderMenu::display() {
    cout << endl;
    cout << "Normal Orders Management:" << endl;
    cout << "1 - Min vans scenario" << endl;
    cout << "2 - Max profit scenario " << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *NormalOrderMenu::nextMenu() {
    switch (readInt()) {
        case 1:
            return new MinVansMenu(app);
        case 2:
            return new MaxProfitMenu(app);
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}

MinVansMenu::MinVansMenu(App &app) : Menu(app) {

}

void MinVansMenu::display() {
    cout << endl;
    cout << "Min Vans Scenario:" << endl;
    cout << "1 - Dispatch Orders to Vans" << endl;
    cout << "2 - See Information" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *MinVansMenu::nextMenu() {
    switch (readInt()) {
        case 1:
            app.dispatchOrdersToVans();
            cout << "Done!" << endl;
            waitForKey();
            return this;
        case 2: {
            for(const string &line : app.readEfficientVansData(App::MINVANSFILE))
                cout << line << endl;
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}

MaxProfitMenu::MaxProfitMenu(App &app) : Menu(app) {

}

void MaxProfitMenu::display() {
    cout << endl;
    cout << "Max Profit Scenario:" << endl;
    cout << "1 - Dispatch Orders to Vans" << endl;
    cout << "2 - See Information" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *MaxProfitMenu::nextMenu() {
    switch (readInt()) {
        case 1:
            cout << "Loading ..." << endl;
            app.maxProfitDispatch();
            cout << "Done!" << endl;
            waitForKey();
            return this;
        case 2: {
            for(const string &line : app.readEfficientVansData(App::PROFITVANSFILE))
                cout << line << endl;
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}

AddRemoveItens::AddRemoveItens(App &app) : Menu(app) {

}

void AddRemoveItens::display() {
    cout << endl;
    cout << "Management vans and orders" << endl;
    cout << "1 - Add Van" << endl;
    cout << "2 - Remove Van" << endl;
    cout << "3 - Add Order" << endl;
    cout << "4 - Remove Order" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *AddRemoveItens::nextMenu() {
    switch (readInt()) {
        case 1: {
            int w, v, c;
            cout << "Insert van max weight: ";
            w = readInt();
            cout << "Insert van max volume: ";
            v = readInt();
            cout << "Insert van cost: ";
            c = readInt();
            Van newVan(v, w, c);
            app.addVan(newVan);
            cout << "Van with ID=" << newVan.getID() << " inserted successfully" << endl;
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 2:{
            cout << "Insert the van id you want to remove: ";
            app.removeVan(readInt());
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 3:{
            int w, v, r, d;
            cout << "Insert order weight: ";
            w = readInt();
            cout << "Insert order volume: ";
            v = readInt();
            cout << "Insert order reward: ";
            r = readInt();
            cout << "Insert order duration: ";
            d = readInt();
            Order newOrder(v, w, r, d);
            app.addOrder(newOrder);
            cout << "Order with ID=" << newOrder.getID() << " inserted successfully" << endl;
            waitForKey();
            return this;
        }
        case 4: {
            cout << "Insert the order id you want to remove: ";
            app.removeOrder(readInt());
            cout << "Done!" << endl;
            waitForKey();
            return this;
        }
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}