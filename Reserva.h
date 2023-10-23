#ifndef RESERVA_H
#define RESERVA_H
#include <string>
#include "Fecha.h"

class Reserva
{
    public:
        Reserva();
        Reserva(std::string patenteVehiculo, float importeAlquiler, Fecha fechaInicio, Fecha fechaFin, bool estado);
        int getIdReserva() const;
        int getDocCliente() const;
        std::string getPatenteVehiculo() const;
        float getImporteAlquiler() const;
        Fecha getFechaInicio() const;
        Fecha getFechaFin() const;
        bool getEstado() const;

        void setIdReserva(int idReserva);
        void setDocCliente (int numDoc);
        void setPatenteVehiculo(std::string patenteVehiculo);
        void setImporteAlquiler(float importeAlquiler);
        void setFechaInicio(Fecha fechaInicio);
        void setFechaFin(Fecha fechafin);
        void setEstado(bool estado);

    private:
        int _idReserva;
        int _numeroDocCliente;
        char _patenteVehiculo[10];
        float _importeAlquiler;
        Fecha _fechaInicio;
        Fecha _fechaFin;
        bool _estado;
};

#endif // RESERVA_H
