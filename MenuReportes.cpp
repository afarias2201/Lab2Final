#include "MenuReportes.h"
#include <iostream>
using namespace std;
#include "rlutil.h"

void MenuReportes::Mostrar(){
     int opc;
    while(true)
    {
        system("cls");
        std::cout << "--------------------------------------------" << endl;
        std::cout << "---------------MENU DE REPORTES-------------" << endl;
        std::cout << "--------------------------------------------" << endl;
        rlutil::locate(4, 5); std::cout << "1 - RECAUDACION POR GAMA" << endl;
        rlutil::locate(4, 6); std::cout << "2 - RECAUDACION ANUAL" << endl;
        rlutil::locate(4, 7); std::cout << "3 - CANTIDAD RESERVAS POR MARCA" << endl;
        std::cout << endl <<"INGRESE UNA OPCION: ";
        std::cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _managerReservas.recaudacionxGama();
            break;
        case 2:
            _managerReservas.recaudacionAnual();
            break;
        case 3:
            _managerReservas.cantidadReservasxMarca();
            break;
        case 0:
            return;
            break;
        default:
            cout << "Opcion ingresada es incorrecta." << endl << "Intente nuevamente." << endl;
            break;
        }
        system("pause");
    }
}
