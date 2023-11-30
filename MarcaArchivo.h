#ifndef MARCAARCHIVO_H
#define MARCAARCHIVO_H
#include "Marca.h"


class MarcaArchivo
{
    public:
        MarcaArchivo(std::string nombreArchivo);
        bool Guardar(Marca reg);
        bool Guardar(Marca reg, int nroRegistro);
        bool Guardar(Marca* marcas, int cantidadRegistros);
        int contarRegistros();
        Marca Leer(int nroRegistro);
        void Leer(Marca* marcas, int cantidadRegistros);
        int Buscar(int idMarca);
        int Buscar(std::string nombre);
        void Vaciar();

    private:
        std::string _nombreArchivo;
};

#endif // MARCAARCHIVO_H
