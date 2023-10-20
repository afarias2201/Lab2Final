#ifndef CLIENTEMANAGER_H
#define CLIENTEMANAGER_H
#include "Cliente.h"
#include "ClienteArchivo.h"
#include "string"

class ClienteManager
{
    public:
        void Cargar();
        void Editar();
        void Eliminar();
        void Mostrar(Cliente reg);
        void ListarTodos();
        int Buscar(int dni);
        void ListarxDNI();

    private:
        ClienteArchivo _archivo = ClienteArchivo("clientes.dat");
};

#endif // CLIENTEMANAGER_H
