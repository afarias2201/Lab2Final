#ifndef VEHICULOARCHIVO_H
#define VEHICULOARCHIVO_H
#include "Vehiculo.h"
#include <string>

class VehiculoArchivo
{
    public:
        VehiculoArchivo(std::string nombreArchivo);
        bool Guardar(Vehiculo reg);                     //un solo registro
        bool Guardar(Vehiculo reg, int nroRegistro);    //registro editado
        bool Guardar(Vehiculo* vRegistros, int cantidadRegistros);
        int contarRegistros();
        Vehiculo Leer(int nroRegistro);
        void Leer(Vehiculo* vRegistros, int cantidadRegistros);
        int Buscar(std::string nroPatente);
        void Vaciar();

    private:
        std::string _nombreArchivo;
};

#endif // VEHICULOARCHIVO_H
