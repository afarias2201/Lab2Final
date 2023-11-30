#include "MenuEditarVehiculo.h"
#include <iostream>
using namespace std;
#include "rlutil.h"

Vehiculo MenuEditarVehiculo::Mostrar(Vehiculo& reg)
{
    system("cls");
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "--------------EDITAR VEHICULO------------" << endl;
    cout << "-----------------------------------------" << endl;
    rlutil::locate(4, 5);cout << "1 - MODELO" << endl;
    rlutil::locate(4, 6);cout << "2 - MARCA" << endl;
    rlutil::locate(4, 7);cout << "3 - TIPO" << endl;
    rlutil::locate(4, 8);cout << "4 - FABRICACION" << endl;
    rlutil::locate(4, 9);cout << "0 - CANCELAR" <<endl;
    cout << endl <<"INGRESE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    cout << endl;
    switch(opcion)
    {
    case 1:
    {
        string modelo;
        cout << "Ingrese nuevo modelo: ";
        cin >> modelo;
        reg.setModelo(modelo);
        return reg;
    }
    break;
    case 2:
    {
        int marca;
        cout << "Ingrese nueva marca: ";
        cin >> marca;
        reg.setIdMarca(marca);
        return reg;
    }
    break;
    case 3:
    {
        int tipo;
        cout << "Ingrese nuevo tipo de gama: ";
        cin >> tipo;
        reg.setTipo(tipo);
        return reg;
    }
    break;
    case 4:
    {
        int anioProduccion;
        cout << "Ingrese nuevo anio de produccion: ";
        cin >> anioProduccion;
        reg.setAnioProduccion(anioProduccion);
        return reg;
    }
    break;
    case 0:
        cout << "No se realizaron cambios." << endl;
        return reg;
        break;
    default:
        cout << "Opcion ingresada incorrecta. Intente nuevamente.";
             break;
    }

    system("cls");
}
