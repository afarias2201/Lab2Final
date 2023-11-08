#ifndef CLIENTEARCHIVO_
#define CLIENTEARCHIVO_
#include "Cliente.h"
#include <iostream>


class ClienteArchivo
{
    public:
        ClienteArchivo(std::string nombreArchivo);
        bool Guardar(Cliente reg);
        bool Guardar(Cliente reg, int nroRegistro);
        bool Guardar(Cliente* clientes, int cantidadRegistros);
        int contarRegistros();
        Cliente Leer(int nroRegistro);
        void Leer(Cliente* clientes, int cantidadRegistros);
        int Buscar(std::string dniCliente);
        void Vaciar();

    private:
        std::string _nombreArchivo;
};

#endif // CLIENTEARCHIVO_
