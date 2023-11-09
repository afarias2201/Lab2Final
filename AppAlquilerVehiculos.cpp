#include "AppAlquilerVehiculos.h"
#include <iostream>
using namespace std;

void AppAlquilerVehiculos::Ejecutar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "SISTEMA DE GESTION DE ALQUILER DE VEHÍCULOS" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "1 - RESERVAS" << endl;
        cout << "2 - VEHÍCULOS" << endl;
        cout << "3 - CLIENTES" << endl;
        cout << "4 - DISPONIBILIDAD DE VEHÍCULOS" << endl;
        cout << "5 - COPIAS DE SEGURIDAD Y RESTAURACIÓN DE DATOS" << endl;
        cout << "0 - CERRAR PROGRAMA" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _menuReserva.Mostrar();
            break;
        case 2:
            _menuVehiculos.Mostrar();
            break;
        case 3:
            _menuCliente.Mostrar();
            break;
        case 4:
            _dispoFlota.generarDisponibilidad();
            break;
        case 5:
            _menuCopiaRestauracion.Mostrar();
            break;
        case 0:
            return ;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        // system("pause");
    }
}
