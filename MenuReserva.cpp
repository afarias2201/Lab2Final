#include "MenuReserva.h"
#include <iostream>
using namespace std;

void MenuReserva::Mostrar(){
 int opc;
    while(true)
    {
        system("cls");
        std::cout << "--------------------------------------------" << endl;
        std::cout << "---------------MENU DE RESERVAS-------------" << endl;
        std::cout << "--------------------------------------------" << endl;
        std::cout << "1 - CARGAR" << endl;
        std::cout << "2 - ELIMINAR" << endl;
        std::cout << "3 - LISTADO DE RESERVA" << endl;
        std::cout << "4 - BUSCAR POR ID DE RESERVA" << endl;
        std::cout << "0 - VOLVER AL MENU PRINCIPAL" <<endl;
        std::cout << endl <<"INGRESE UNA OPCION: ";
        std::cin >> opc;
        system("cls");
        switch(opc)
        {
        case 1:
            _manager.Cargar();
            break;
        case 2:
            _manager.Eliminar();
            break;
        case 3:
            _manager.ListarTodos();
            break;
        case 4:
            _manager.ListarxID();
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
