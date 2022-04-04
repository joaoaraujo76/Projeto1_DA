#ifndef PROJETO1_DA_MENU_H
#define PROJETO1_DA_MENU_H

#include "App.h"

class Menu {
protected:
    App &app;
public:
    explicit Menu(App &app);
    virtual ~Menu();
    virtual void display()=0;
    virtual Menu *nextMenu()=0;
    int readInt();
    std::string readStr();
    void waitForKey();
    Menu *invalidInput();
};

class MainMenu: public Menu{
public:
    explicit MainMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class ExpressOrderMenu: public Menu{
public:
    explicit ExpressOrderMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class ExpressSettingsMenu: public Menu{
public:
    explicit ExpressSettingsMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};


#endif //PROJETO1_DA_MENU_H
