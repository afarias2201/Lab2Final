#include "MenuVehiculos.h"
#include <iostream>
using namespace std;

void MenuVehiculos::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "--------------MENU DE VEHICULOS------------" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "1 - CARGAR" << endl;
        cout << "2 - EDITAR" << endl;
        cout << "3 - ELIMINAR" << endl;
        cout << "4 - LISTADO DE VEHICULOS" << endl;
        cout << "5 - BUSCAR POR PATENTE" << endl;
        cout << "6 - INGRESO A TALLER" << endl;
        cout << "7 - RETIRO DE TALLER" << endl;
        cout << "8 - LISTAR VEHICULOS POR GAMA" << endl;
        cout << "9 - LISTAR VEHICULOS POR MARCA" << endl;
        cout << "10 - LISTAR VEHICULOS POR A�O DE PRODUCCION" << endl;
        cout << "11 - LISTAR VEHICULOS ORDENADOS POR GAMA" << endl;
        cout << "12 - LISTAR VEHICULOS ORDENADOS POR A�O DE PRODUCCI�N" << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _manager.Cargar();
            break;
        case 2:
            _manager.Editar();
            break;
        case 3:
            _manager.Eliminar();
            break;
        case 4:
            _manager.ListarTodos();
            break;
        case 5:
            _manager.ListarxPatente();
            break;
        case 6:
            _manager.VehiculoIngresaTaller();
            break;
        case 7:
            _manager.VehiculoRetiroDeTaller();
            break;
        case 8:
            _manager.ListarxGamaVehiculo();
            break;
        case 9:
            _manager.ListarxMarca();
            break;
        case 10:
            _manager.ListarxAnioProduccion();
            break;
        case 11:
            _manager.OrdenarxGama();
            break;
        case 12:
            _manager.OrdenarxAnioProduccion();
            break;
        case 0:
            return ;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        system("pause");
    }
}
