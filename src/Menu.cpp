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
    cout << "1 - Normal Orders management (not done)" << endl;
    cout << "2 - Express Orders management" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *MainMenu::nextMenu() {
    switch (readInt()) {
        case 1:
            return new NormalOrderMenu(app);
        case 2:
            return new ExpressOrderMenu(app);
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
    cout << "1 - Minimize average delivery time" << endl;
    cout << "2 - View Information" << endl;
    cout << "3 - Jump to next working day" << endl;
    cout << "4 - Settings" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *ExpressOrderMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            app.optimizeExpressDeliveries();
            return this;
        }
        case 2: {
            for(const string &line : app.readExpressOrders())
                cout << line << endl;
            return this;
        }
        case 3: {
            app.nextExpressDay();
            return this;
        }
        case 4: {
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
            return this;
        }
        case 2:{
            cout << "Please insert the new Max Express Delivery time: ";
            time = readInt();
            app.setMaxExpressDuration(time);
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
    cout << "1 - Dispatch orders to the vans " << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *NormalOrderMenu::nextMenu() {
    switch (readInt()) {
        case 1:
            app.dispatchOrdersToVans();
        case 0:
            return nullptr;
        default:
            return invalidInput();
    }
}
