#include "MenuEditarVehiculo.h"
#include <iostream>
using namespace std;

Vehiculo MenuEditarVehiculo::Mostrar(Vehiculo& reg)
{
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "--------------EDITAR VEHICULO------------" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "1 - MODELO" << endl;
    cout << "2 - MARCA" << endl;
    cout << "3 - TIPO" << endl;
    cout << "4 - FABRICACION" << endl;
    cout << "0 - CANCELAR" <<endl;
    cout << endl <<"INGRESE UNA OPCION: ";
    int opcion;
    cin >> opcion;
    switch(opcion)
    {
    case 1:
    {
        string modelo;
        cout << "Ingrese nuevo modelo: ";
        cin >> modelo;
        reg.setModelo(modelo);
        cout << endl << "Registro modificado correctamente." << endl;
        return reg;
    }
    break;
    case 2:
    {
        string marca;
        cout << "Ingrese nueva marca: ";
        cin >> marca;
        reg.setMarca(marca);
        cout << endl << "Registro modificado correctamente." << endl;
        return reg;
    }
    break;
    case 3:
    {
        int tipo;
        cout << "Ingrese nuevo tipo de gama: ";
        cin >> tipo;
        reg.setTipo(tipo);
        cout << endl << "Registro modificado correctamente." << endl;
        return reg;
    }
    break;
    case 4:
    {
        int anioProduccion;
        cout << "Ingrese nuevo anio de produccion: ";
        cin >> anioProduccion;
        reg.setAnioProduccion(anioProduccion);
        cout << endl << "Registro modificado correctamente." << endl;
        return reg;
    }
    break;
    case 0:
        cout << "No se realizaron cambios." << endl;
        return reg;
        break;
    }
    system("cls");
}
