#ifndef RESERVAMANAGER_H
#define RESERVAMANAGER_H
#include "Reserva.h"
#include "ReservaArchivo.h"
#include "VehiculoArchivo.h"
#include "VehiculoManager.h"
#include <string>


class ReservaManager
{
    public:
        void Cargar();
        void Eliminar();
        void Mostrar(Reserva reg);
        void ListarTodos();
        int Buscar(int idReserva);
        void ListarxID();
        void CargarVectorPorNroPatente(std::string patente, int cantidadElementos, Reserva* vec);
        bool validarDisponibilidadVehiculo(Fecha fInicio, Fecha fFin, Reserva* vec, int cantidadElementos);

    private:
        ReservaArchivo _archivo = ReservaArchivo("reserva.dat");
        VehiculoArchivo _archivoVehiculo = VehiculoArchivo("vehiculo.dat");
        VehiculoManager _vehiculoManager;
        int generarReservaId();
        int contarReservasxPatentes(std::string patente);
};

#endif // RESERVAMANAGER_H
