#ifndef MARCAMANAGER_H
#define MARCAMANAGER_H
#include "Marca.h"
#include "MarcaArchivo.h"
#include <string>


class MarcaManager
{
    public:
        void Cargar();
        void Eliminar();
        void Editar();
        void ListarTodos();
        void Mostrar(Marca reg);
        void RecuperarRegistroElimiando();

        void HacerCopiaSeguridad();
        void RestaurarCopiaSeguridad();

    private:
        MarcaArchivo _archivo = MarcaArchivo("marcas.dat");
        MarcaArchivo _archivobkp = MarcaArchivo("marcas.bkp");
        int generarIdMarca();
};

#endif // MARCAMANAGER_H
