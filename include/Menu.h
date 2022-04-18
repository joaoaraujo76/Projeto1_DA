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

class NormalOrderMenu: public Menu{
public:
    explicit NormalOrderMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class ExpressSettingsMenu: public Menu{
public:
    explicit ExpressSettingsMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class MinVansMenu: public Menu{
public:
    explicit MinVansMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class MaxProfitMenu: public Menu{
public:
    explicit MaxProfitMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};


#endif //PROJETO1_DA_MENU_H
