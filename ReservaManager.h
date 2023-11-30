#ifndef RESERVAMANAGER_H
#define RESERVAMANAGER_H
#include "Reserva.h"
#include "ReservaArchivo.h"
#include "VehiculoArchivo.h"
#include "ClienteArchivo.h"
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
        void CargarVectorPorNroPatente(std::string patente, int cantidadElementos, Reserva* vec);
        bool validarDisponibilidadVehiculo(Fecha fInicio, Fecha fFin, Reserva* vec, int cantidadElementos);
        bool validarDisponibilidadVehiculoExtension(Fecha fInicio, Fecha nuevaFechaFin, Reserva* vec, int cantidadElementos);
        bool validarSiEstaDisponibleHoy(Fecha fechaHoy, Reserva* reserva, int cantidadElementos);
        int contarReservasxPatentes(std::string patente);
        void extenderReserva();
        void RecuperarRegistroEliminado();

        void HacerCopiaSeguridad();
        void RestaurarCopiaSeguridad();

        //consultas
        void ListarxID();
        void ListarxRangoDeImporte();
        void ListarxFechaDeInicioReserva();

        //Listados
        void ReservasOrdenadasxFechaInicio();
        void ReservasOrdenadasxImporte();

        //Reportes
        void recaudacionxGama();
        void recaudacionAnual();
        void cantidadReservasxMarca();

    private:
        ReservaArchivo _archivo = ReservaArchivo("reserva.dat");
        ReservaArchivo _archivoBkp = ReservaArchivo("reserva.bkp");
        VehiculoArchivo _archivoVehiculo = VehiculoArchivo("vehiculo.dat");
        ClienteArchivo _archivoCliente = ClienteArchivo("clientes.dat");
        VehiculoManager _vehiculoManager;
        int generarReservaId();
        void mostrarTituloReservas();
        void ordenarReservasPorFecha(Reserva* reservas, int cantidadElementos);
        void ordenarReservasPorImporte(Reserva* reservas, int cantidadElentos);
};

#endif // RESERVAMANAGER_H
