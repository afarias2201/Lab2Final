#ifndef APPALQUILERVEHICULOS_H
#define APPALQUILERVEHICULOS_H
#include "MenuVehiculos.h"
#include "MenuReserva.h"
#include "MenuCliente.h"

class AppAlquilerVehiculos
{
    public:
        void Ejecutar();

    private:
        MenuVehiculos _menuVehiculos;
        MenuReserva _menuReserva;
        MenuCliente _menuCliente;
};

#endif // APPALQUILERVEHICULOS_H
