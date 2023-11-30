#include "SubMenuListadosVehiculo.h"
#include <iostream>
using namespace std;

void SubMenuListadosVehiculo::Mostrar(){
        int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "--------------MENU DE VEHICULOS------------" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "1 - LISTAR VEHICULOS POR GAMA" << endl;
        cout << "2 - LISTAR VEHICULOS POR MARCA" << endl;
        cout << "3 - LISTAR VEHICULOS POR AÑO DE PRODUCCION" << endl;
        cout << "4 - LISTAR VEHICULOS ORDENADOS POR GAMA" << endl;
        cout << "5 - LISTAR VEHICULOS ORDENADOS POR Marca" << endl;
        cout << "6 - LISTAR VEHICULOS ORDENADOS POR AÑO DE PRODUCCIÓN" << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _manager.ListarxGamaVehiculo();
            break;
        case 2:
            _manager.ListarxMarca();
            break;
        case 3:
            _manager.ListarxAnioProduccion();
            break;
        case 4:
            _manager.OrdenarxGama();
            break;
        case 5:
            _manager.OrdenarxMarca();
            break;
        case 6:
            _manager.OrdenarxAnioProduccion();
            break;
        case 0:
            return ;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
    }
}
