#include "MenuCopiaYRestauracionDatos.h"

#include "MenuCliente.h"
#include <iostream>
using namespace std;

void MenuCopiaYRestauracionDatos::Mostrar(){
    int opc;
    while(true)
    {
        system("cls");
        cout << "------------------------------------------------------" << endl;
        cout << "----------COPIAS DE SEGURIDAD Y RESTAURACIÓN----------" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "1 - COPIA DE SEGURIDAD CLIENTES" << endl;
        cout << "2 - RESTAURAR COPIA DE SEGURIDAD CLIENTES" << endl << endl;
        cout << "3 - COPIA DE SEGURIDAD RESERVAS" << endl;
        cout << "4 - RESTAURAR COPIA DE SEGURIDAD RESERVAS" << endl << endl;
        cout << "5 - COPIA DE SEGURIDAD VEHÍCULOS" << endl;
        cout << "6 - RESTAURAR COPIA DE SEGURIDAD VEHÍCULOS" << endl << endl;
        cout << "7 - COPIA DE SEGURIDAD TODOS LOS ARCHIVOS" << endl;
        cout << "8 - RESTAURAR COPIA DE SEGURIDAD TODOS LOS ARCHIVOS" << endl << endl;
        cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        cout << endl <<"INGRESE UNA OPCION: ";
        cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _clienteManager.HacerCopiaSeguridad();
            break;
        case 2:
            _clienteManager.RestaurarCopiaSeguridad();
            break;
        case 3:
            _reservaManager.HacerCopiaSeguridad();
            break;
        case 4:
            _reservaManager.RestaurarCopiaSeguridad();
            break;
        case 5:
            _vehiculoManager.HacerCopiaSeguridad();
            break;
        case 6:
            _vehiculoManager.RestaurarCopiaDeSeguridad();
            break;
        case 7:
            _clienteManager.HacerCopiaSeguridad();
            _reservaManager.HacerCopiaSeguridad();
            _vehiculoManager.HacerCopiaSeguridad();
            break;
        case 8:
            _clienteManager.RestaurarCopiaSeguridad();
            _reservaManager.RestaurarCopiaSeguridad();
            _vehiculoManager.RestaurarCopiaDeSeguridad();
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        system("pause");
    }
}
