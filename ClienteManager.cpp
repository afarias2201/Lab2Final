#include "ClienteManager.h"
#include <iostream>
#include <cstring>
#include <iomanip>
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

    if(!validarEmail(email)){
        cout << "El e-mail ingresado no es válido." << endl;
        return;
    }

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
        cout << endl;

        system("pause");

        MenuEditarCliente menuEditarCliente;
        menuEditarCliente.Mostrar(reg);

        if(!validarEmail(reg.getEmail())){
            cout << "Nuevo email no es válido. Modificación cancelada." << endl;
            return;
        }

        cout << endl << "Nuevo Registro:" << endl;
        Mostrar(reg);
        char confirmacion;
        cout << endl << "¿Desea continuar? (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion) == 'S'){
            if(_archivo.Guardar(reg, posicion)){
                cout << "Cliente modificado correctamente." << endl;
            }
            else{
                cout << "Error. No se pudo modificar el registro." << endl;
            }
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
        cout << left << setw(5) << reg.getID();
        cout << left << setw(13) << reg.getDNI();
        cout << left << setw(20) << reg.getApellidos();
        cout << left << setw(20) << reg.getNombres();
        cout << left << setw(15) << reg.getDomicilio();
        cout << left << setw(13) << reg.getTelefono();
        cout << left << setw(15) << reg.getEmail();
        cout << endl;
}
void ClienteManager::ListarTodos(){
    int cantidadRegistros = _archivo.contarRegistros();
    mostrarTituloClientes();
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
    mostrarTituloClientes();
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

bool ClienteManager::validarEmail(std::string email){
    int cantidadCaracteres = email.length();
    char* auxiliar = new char[cantidadCaracteres];
    strcpy(auxiliar, email.c_str());
    bool contieneArroba = false;
    bool contienePunto = false;
    for(int i=0; i<cantidadCaracteres; i++){
        if(auxiliar[i] == '@'){
            contieneArroba = true;
        }
    }
    for(int x=0; x<cantidadCaracteres; x++){
        if(auxiliar[x] == '.'){
            contienePunto = true;
        }
    }

    if(contienePunto && contieneArroba){
        return true;
    }
    else{
        return false;
    }
}

void ClienteManager::RecuperarRegistroEliminado(){
    int cantidadRegistros = _archivo.contarRegistros();
    string dni;
    cout << "Registros eliminados: " << endl;
    for(int i=0; i<cantidadRegistros; i++){
        Cliente cliente = _archivo.Leer(i);
        if(!cliente.getEstado()){
            Mostrar(cliente);
        }
    }
    cout << endl << "Ingrese el DNI del cliente a recuperar: ";
    cin >> dni;
    int posicion = _archivo.Buscar(dni);
    if(posicion == -1){
        cout << "Registro no encontrado" << endl;
        return;
    }
    Cliente reg = _archivo.Leer(posicion);
    if(!reg.getEstado()){
        cout << "Registro a recuperar: " << endl;
        Mostrar(reg);
        cout << endl << "¿Desea continuar? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            reg.setEstado(true);
            if(_archivo.Guardar(reg,posicion)){
                cout << "Registro recuperado correctamente." << endl;
            }
            else{
                cout << "Error al recuperar registro." << endl;
            }
        }
        else{
            cout << "Operación cancelada." << endl;
        }
    }
    else{
        cout << "El registro no se encuentra eliminado." << endl;
    }
}

void ClienteManager::mostrarTituloClientes(){
        cout << left << setw(5) << "ID";
        cout << left << setw(13) << "DNI";
        cout << left << setw(20) << "APELLIDOS";
        cout << left << setw(20) << "NOMBRES";
        cout << left << setw(15) << "DOMICILIO";
        cout << left << setw(13) << "TELEFONO";
        cout << left << setw(15) << "EMAIL";
        cout << endl << endl;
}
