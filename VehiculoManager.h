#ifndef VEHICULOMANAGER_H
#define VEHICULOMANAGER_H
#include "Vehiculo.h"
#include "VehiculoArchivo.h"
#include <string>


class VehiculoManager
{
    public:
        void Cargar();
        void Editar();
        void Eliminar();
        void Mostrar(Vehiculo reg);
        void ListarTodos();
        int Buscar(std::string nroPatente);
        void ListarxPatente();
        void VehiculoIngresaTaller();
        void VehiculoRetiroDeTaller();

    private:
        VehiculoArchivo _archivo = VehiculoArchivo("vehiculo.dat");
};

#endif // VEHICULOMANAGER_H
