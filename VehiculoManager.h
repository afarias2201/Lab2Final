#ifndef VEHICULOMANAGER_H
#define VEHICULOMANAGER_H
#include "Vehiculo.h"
#include "VehiculoArchivo.h"
#include "Marca.h"
#include "MarcaArchivo.h"
#include "MarcaManager.h"
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
        void RecuperarRegistroEliminado();

        void HacerCopiaSeguridad();
        void RestaurarCopiaDeSeguridad();

        //Reportes
        void generarDisponibilidad();

        //Consultar
        void ListarxPatente();
        void ListarxGamaVehiculo();
        void ListarxMarca();
        void ListarxAnioProduccion();

        //Listar
        void OrdenarxGama();
        void OrdenarxMarca();
        void OrdenarxAnioProduccion();

        //Reporte

    private:
        VehiculoArchivo _archivo = VehiculoArchivo("vehiculo.dat");
        VehiculoArchivo _archivoBkp = VehiculoArchivo("vehiculo.bkp");
        MarcaArchivo _archivoMarca = MarcaArchivo("marcas.dat");
        void ordenarVectorVehiculosxAnio(Vehiculo* vehiculos, int cantidadElementos);
        void ordenarVectorVehiculosxMarca(Vehiculo* vehiculos, int cantidadElementos);
        void mostrarTituloVehiculos();
};

#endif // VEHICULOMANAGER_H
