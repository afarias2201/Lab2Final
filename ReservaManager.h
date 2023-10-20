#ifndef RESERVAMANAGER_H
#define RESERVAMANAGER_H
#include "Reserva.h"
#include "VehiculoManager.h"
#include "ReservaArchivo.h"
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
        VehiculoManager _vehiculoManager;
        int generarReservaId();
        int contarReservasxPatentes(std::string patente);
};

#endif // RESERVAMANAGER_H
