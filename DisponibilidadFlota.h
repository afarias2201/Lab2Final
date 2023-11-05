#ifndef DISPONIBILIDADFLOTA_H
#define DISPONIBILIDADFLOTA_H
#include "VehiculoArchivo.h"
#include "ReservaArchivo.h"
#include "Reserva.h"
#include <string>

//A partir del dia de la fecha, definido por el contructor de la clase Fecha, se genera una disponiblidad con el estado de todos los vehiculos registrados y activos

class DisponibilidadFlota
{
    public:
        void generarDisponibilidad();
        void Mostrar(DisponibilidadFlota* vDispo, int cantidadElementos);

        void setPatenteDispo(std::string patente);
        void setModeloDispo(std::string modelo);
        void setMarcaDispo(std::string marca);
        void setAnioProduccionDispo(int anio);
        void setTipoDispo(int tipo);
        void setEstadoVehiculoDispo(int estadoVehiculo);

        std::string getPatenteDispo() const;
        std::string getModeloDispo() const;
        std::string getMarcaDispo() const;
        int getAnioProduccionDispo() const;
        std::string getTipoDispo() const;
        std::string getEstadoVehiculoDispo() const;

    private:
        ReservaArchivo _archivoReserva = ReservaArchivo("reserva.dat");
        VehiculoArchivo _archivoVehiculo = VehiculoArchivo("vehiculo.dat");

        Fecha fechaDeConsulta = Fecha();
        Vehiculo vehiculo;
        /*
        char _patenteDispo[10];
        char _modeloDispo[10];
        char _marcaDispo[10];
        int _anioDeProduccionDispo;
        int _tipoDispo;
        */
        int _estadoVehiculo; // 0- Disponible, 1- Alquilado, 2- En taller
        bool validarSiEstaDisponibleHoy(Fecha fechaHoy, Reserva* reserva, int cantidadElementos);
        void cargarRegistrosDeLaDisponibilidad(DisponibilidadFlota* vecDispo, int cantidadVehiculos);
};

#endif // DISPONIBILIDADFLOTA_H
