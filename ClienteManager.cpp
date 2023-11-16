#include "ClienteManager.h"
#include <iostream>
using namespace std;
#include "MenuEditarCliente.h"

void ClienteManager::Cargar(){
    int id;
    string dni, nombres, apellidos, domicilio, telefono, email;

    cout << "Ingrese informacion del nuevo cliente." << endl;

    id = generarIdCliente();
    cout << "ID de cliente: " << id << endl;

    cout << "Nro. de DNI: ";
    cin >> dni;
    if(_archivo.Buscar(dni)!= -1){
        cout << "El nro. de DNI indicado ya existe." << endl;
        cout << "No se ha grabado el nuevo registro." << endl;
        return;
    }
    cout << "Nombres: ";
    cin.ignore();
    getline(cin, nombres);
    cout << "Apellidos: ";
    getline(cin, apellidos);
    cout << "Domicilio: ";
    getline(cin, domicilio);
    cout << "Telefono: ";
    getline(cin, telefono);
    cout << "E-mail: ";
    getline(cin, email);

    Cliente reg;
    reg.setID(id);
    reg.setDNI(dni);
    reg.setNombres(nombres);
    reg.setApellidos(apellidos);
    reg.setDomicilio(domicilio);
    reg.setTelefono(telefono);
    reg.setEmail(email);
    reg.setEstado(true);

    Mostrar(reg);
    char confirmacion;
    cout << endl << "Desea guardar el siguiente registro (S/N)?: " << endl;
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S'){
        bool guardado = _archivo.Guardar(reg);
        if(guardado){
            cout << "Registro guardado satisfactoriamente.";
        }
        else{
            cout << "Oops, Error. No se ha podido guardar el registro.";
        }
        cout << endl;
    }
    else {
        cout << "Carga de registro cancelada." << endl;
    }
}

void ClienteManager::Editar(){
    string dni;
    int posicion;
    cout << "Ingrese DNI del cliente a editar: ";
    cin >> dni;

    posicion = _archivo.Buscar(dni);
    if(posicion >= 0){
        Cliente reg = _archivo.Leer(posicion);
        cout << "Registro a modificar: " << endl;
        Mostrar(reg);
        MenuEditarCliente menuEditarCliente;
        menuEditarCliente.Mostrar(reg);
        if(_archivo.Guardar(reg, posicion)){
            cout << "Cliente modificado correctamente." << endl;
        }
        else{
            cout << "Error. No se pudo modificar el registro." << endl;
        }
    }
    else{
        cout << "Registro no encontrado." << endl;
    }
}

void ClienteManager::Eliminar(){
    string dni;
    int posicion;

    cout << "Ingrese nro. DNI a eliminar: ";
    cin >> dni;
    posicion = Buscar(dni);
    if(posicion >= 0){
        Cliente reg = _archivo.Leer(posicion);
        cout << "Registro a eliminar: " << endl;
        Mostrar(reg);

        char confirmacion;
        cout << endl << "¿Desea continuar. El registro sera eliminado (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion)== 'S'){
            reg.setEstado(false);
            _archivo.Guardar(reg, posicion);
            cout << endl << "Cliente eliminado correctamente.";
        }
        else{
            cout << "No se han realizado cambios." << endl;
        }
    }
    else{
        cout << "Registro no encontrado. No se han realizado cambios." << endl;
    }
}
void ClienteManager::Mostrar(Cliente reg){
    if(reg.getEstado()){
        cout << "---------------------------" << endl;
        cout << "ID: " << reg.getID() << endl;
        cout << "DNI: " << reg.getDNI() << endl;
        cout << "APELLIDOS: " << reg.getApellidos() << endl;
        cout << "NOMBRES: " << reg.getNombres() << endl;
        cout << "DOMICILIO: " << reg.getDomicilio() << endl;
        cout << "TELEFONO: " << reg.getTelefono() << endl;
        cout << "E-MAIL: " << reg.getEmail() << endl;
    }
}
void ClienteManager::ListarTodos(){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Cliente reg = _archivo.Leer(i);
        if(reg.getEstado()){
            Mostrar(reg);
        }
    }
    cout << endl;
}
int ClienteManager::Buscar(string dni){
    int cantidadRegistros = _archivo.contarRegistros();
    for (int i=0; i<cantidadRegistros; i++){
        Cliente reg = _archivo.Leer(i);
        if(dni == reg.getDNI()){
            return i;
        }
    }
    return -1;
}
void ClienteManager::ListarxDNI(){
    string dni;
    int posicion;

    cout << "Ingrese DNI a buscar: ";
    cin >> dni;
    posicion = _archivo.Buscar(dni);
    if(posicion >= 0){
        Cliente reg = _archivo.Leer(posicion);
        Mostrar(reg);
    }
    else{
        cout << "No se pudo encontrar el DNI indicado.";
        cout << endl;
    }
}

int ClienteManager::generarIdCliente(){
    return _archivo.contarRegistros() + 1;
}

void ClienteManager::ClientesOrdenadoAlfabeticamente(){
    int cantidadRegistros = _archivo.contarRegistros();

    Cliente* clientes;
    clientes = new Cliente[cantidadRegistros];
    if(clientes == nullptr){
        cout << "Error de memoria." << endl;
        return;
    }

    cargarVectorClientes(clientes, cantidadRegistros);
    OrdenarVectorClientesAlfabeticamente(clientes, cantidadRegistros);

    for(int i=0; i<cantidadRegistros; i++){
        if(clientes[i].getEstado()){
            Mostrar(clientes[i]);
        }
    }
    cout << endl;
    delete[] clientes;
}

void ClienteManager::cargarVectorClientes(Cliente* clientes, int cantidadRegistros){
    for(int i=0; i<cantidadRegistros; i++){
        Cliente reg = _archivo.Leer(i);
        clientes[i] = reg;
    }
}

void ClienteManager::OrdenarVectorClientesAlfabeticamente(Cliente* clientes, int cantidadRegistros){
    for(int i=0; i<cantidadRegistros; i++){
        for(int x=0; x<cantidadRegistros - 1; x++){
            if(clientes[x].getApellidos() > clientes[x+1].getApellidos()){
                Cliente aux = clientes[x];
                clientes[x] = clientes[x+1];
                clientes[x+1] = aux;
            }
        }
    }
}

void ClienteManager::HacerCopiaSeguridad(){
    int cantidadRegistros = _archivo.contarRegistros();
    Cliente *clientes = new Cliente[cantidadRegistros];
    if(clientes == nullptr){
        cout << "Falla al crear el backup." << endl;
        return;
    }

    _archivo.Leer(clientes, cantidadRegistros);
    _archivoBkp.Vaciar();

    if(_archivoBkp.Guardar(clientes, cantidadRegistros)){
        cout << "Backup creado satisfactoriamente." << endl;
    }
    else{
        cout << "Falla al crear backup." << endl;
    }
    delete[] clientes;
}
void ClienteManager::RestaurarCopiaSeguridad(){
    int cantidadRegistros = _archivoBkp.contarRegistros();
    Cliente* clientes = new Cliente[cantidadRegistros];
    if(clientes == nullptr){
        cout << "Falla al realizar backup." << endl;
        return;
    }

    _archivoBkp.Leer(clientes, cantidadRegistros);
    _archivo.Vaciar();

    if(_archivo.Guardar(clientes, cantidadRegistros)){
        cout << "Backup restaurado correctamente." << endl;
    }
    else{
        cout << "Falla al restaurar backup." << endl;
    }
    delete[] clientes;
}
