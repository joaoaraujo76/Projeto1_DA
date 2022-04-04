#include "include/App.h"

int main() {
    App app;
    app.loadData();
    app.optimizeExpressDeliveries();
    return 0;

    /*se quiserem testar a funcao ate podem apagar o ficheiro express..., ela cria um novo e escreve.
     * Para ja temos duas opcoes para mostrar na consola, ou metemos um field vector (que corresponderia ao aux_vector)
     * na app e so sacavamos e imprimiamos, ou entao faziamos um read file que retornava um vetor*/
}