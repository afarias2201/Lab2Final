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
        void VehiculoIngresaTaller();
        void VehiculoRetiroDeTaller();
        int contarVehiculosActivos();
        void cargarVectorVehiculosActivos(Vehiculo* vec, int cantidadElementos);

        void HacerCopiaSeguridad();
        void RestaurarCopiaDeSeguridad();

        //consultar
        void ListarxPatente();
        void ListarxGamaVehiculo();
        void ListarxMarca();
        void ListarxAnioProduccion();

        //Reporte

    private:
        VehiculoArchivo _archivo = VehiculoArchivo("vehiculo.dat");
        VehiculoArchivo _archivoBkp = VehiculoArchivo("vehiculo.bkp");
};

#endif // VEHICULOMANAGER_H
