#ifndef MENUCOPIAYRESTAURACIONDATOS_H
#define MENUCOPIAYRESTAURACIONDATOS_H
#include "ClienteManager.h"
#include "ReservaManager.h"
#include "VehiculoManager.h"
#include "MarcaManager.h"


class MenuCopiaYRestauracionDatos
{
    public:
        void Mostrar();

    private:
        ClienteManager _clienteManager;
        ReservaManager _reservaManager;
        VehiculoManager _vehiculoManager;
        MarcaManager _marcaManager;
};

#endif // MENUCOPIAYRESTAURACIONDATOS_H
