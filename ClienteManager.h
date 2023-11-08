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
        int Buscar(std::string dni);
        void ListarxDNI();

        void HacerCopiaSeguridad();
        void RestaurarCopiaSeguridad();

    private:
        ClienteArchivo _archivo = ClienteArchivo("clientes.dat");
        ClienteArchivo _archivoBkp = ClienteArchivo("clientes.bkp");
        int generarIdCliente();
};

#endif // CLIENTEMANAGER_H
