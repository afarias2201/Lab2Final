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
        int contarRegistros();
        Reserva Leer(int nroRegistro);
        int Buscar(int idReserva);

    private:
        std::string _nombreArchivo;
};

#endif // RESERVAARCHIVO_H
