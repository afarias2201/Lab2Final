#ifndef APPALQUILERVEHICULOS_H
#define APPALQUILERVEHICULOS_H
#include "MenuVehiculos.h"
#include "MenuReserva.h"
#include "MenuCliente.h"
#include "DisponibilidadFlota.h"

class AppAlquilerVehiculos
{
    public:
        void Ejecutar();

    private:
        MenuVehiculos _menuVehiculos;
        MenuReserva _menuReserva;
        MenuCliente _menuCliente;
        DisponibilidadFlota _dispoFlota;
};

#endif // APPALQUILERVEHICULOS_H
