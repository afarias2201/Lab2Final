#include <iostream>
#include "AppAlquilerVehiculos.h"
#include <locale.h>
#include "rlutil.h"

using namespace std;

int main()
{
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);
    setlocale(LC_ALL, "spanish");
    AppAlquilerVehiculos app;
    app.Ejecutar();
    return 0;
}
