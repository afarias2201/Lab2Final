#include <iostream>
#include "AppAlquilerVehiculos.h"
#include "ClienteManager.h"
#include <locale.h>


using namespace std;

int main()
{
    setlocale(LC_ALL, "spanish");
    AppAlquilerVehiculos app;
    app.Ejecutar();
    return 0;
}
