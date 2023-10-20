#ifndef VEHICULOARCHIVO_H
#define VEHICULOARCHIVO_H
#include "Vehiculo.h"
#include <string>

class VehiculoArchivo
{
    public:
        VehiculoArchivo(std::string nombreArchivo);
        bool Guardar(Vehiculo reg);
        bool Guardar(Vehiculo reg, int nroRegistro);
        int contarRegistros();
        Vehiculo Leer(int nroRegistro);
        int Buscar(std::string nroPatente);

    private:
        std::string _nombreArchivo;
};

#endif // VEHICULOARCHIVO_H
