#include "include/App.h"

int main() {
    App app;
    app.loadData();
    for(int i = 0; i < 5; i++){
        std::cout << app.getVans()[i].getCost() << std::endl; // testing
    }
}