#ifndef APPALQUILERVEHICULOS_H
#define APPALQUILERVEHICULOS_H
#include "MenuVehiculos.h"
#include "MenuReserva.h"
#include "MenuCliente.h"
#include "MenuReportes.h"
#include "MenuCopiaYRestauracionDatos.h"
#include "DisponibilidadFlota.h"
#include "MenuRecuperarRegistros.h"

class AppAlquilerVehiculos
{
    public:
        void Ejecutar();

    private:
        MenuVehiculos _menuVehiculos;
        MenuReserva _menuReserva;
        MenuCliente _menuCliente;
        MenuReportes _menuReportes;
        MenuCopiaYRestauracionDatos _menuCopiaRestauracion;
        DisponibilidadFlota _dispoFlota;
        MenuRecuperarRegistros _menuRecuperarRegistros;
};

#endif // APPALQUILERVEHICULOS_H
