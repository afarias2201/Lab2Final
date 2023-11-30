#ifndef MENUVEHICULOS_H
#define MENUVEHICULOS_H
#include "VehiculoManager.h"
#include "MenuMarcas.h"
#include "SubMenuListadosVehiculo.h"


class MenuVehiculos
{
    public:
        void Mostrar();

    private:
        VehiculoManager _manager;
        MenuMarcas _menuMarcas;
        SubMenuListadosVehiculo _menuListados;
};

#endif // MENUVEHICULOS_H
