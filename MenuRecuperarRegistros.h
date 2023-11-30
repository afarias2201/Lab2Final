#ifndef MENURECUPERARREGISTROS_H
#define MENURECUPERARREGISTROS_H
#include "ReservaManager.h"
#include "VehiculoManager.h"
#include "ClienteManager.h"
#include "MarcaManager.h"


class MenuRecuperarRegistros
{
    public:
        void Mostrar();
    private:
        VehiculoManager _managerVehiculo;
        ClienteManager _managerCliente;
        ReservaManager _managerReserva;
        MarcaManager _managerMarca;
};

#endif // MENURECUPERARREGISTROS_H
