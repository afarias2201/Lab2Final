#ifndef RESERVAARCHIVO_H
#define RESERVAARCHIVO_H
#include "Reserva.h"
#include <string>


class ReservaArchivo
{
    public:
        ReservaArchivo(std::string nombreArchivo);
        bool Guardar(Reserva reg);
        bool Guardar(Reserva reg, int nroRegistro);
        bool Guardar(Reserva* reservas, int cantidadRegistros);
        int contarRegistros();
        Reserva Leer(int nroRegistro);
        void Leer(Reserva* reservas, int cantidadRegistros);
        int Buscar(int idReserva);
        void Vaciar();

    private:
        std::string _nombreArchivo;
};

#endif // RESERVAARCHIVO_H
