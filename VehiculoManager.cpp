#include "VehiculoManager.h"
#include <iostream>
#include <algorithm>
using namespace std;
#include "MenuEditarVehiculo.h"

void VehiculoManager::Cargar(){
    string patente, modelo, marca;
    int tipo, anioFabricacion;

    cout << "Ingrese la informacion del nuevo Vehiculo" << endl;
    cout << "Nro. de Patente: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    if(Buscar(patente) != -1){
        cout << "El numero de patente ya existe." << endl;
        cout << "No se ha grabado el nuevo registro." << endl;
        return;
    }
    cout << "Modelo: ";
    cin >> modelo;
    cout << "Marca: ";
    cin >> marca;
    cout << "Tipo (1- Gama baja, 2- Gama media, 3-Gama alta): ";
    cin >> tipo;
    if(tipo < 1 || tipo > 3){
        cout << "Tipo no valido. Debe ser 1, 2 o 3." << endl;
        return;
    }
    cout << "Fabricacion: ";
    cin >> anioFabricacion;

    Vehiculo reg;
    reg.setPatente(patente);
    reg.setModelo(modelo);
    reg.setMarca(marca);
    reg.setTipo(tipo);
    reg.setAnioProduccion(anioFabricacion);
    reg.setEnTaller(false);
    reg.setEstado(true);

    Mostrar(reg);
    char confirmacion;
    cout << endl << "Desea guardar el siguiente registro (S/N)?: " << endl;
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S'){
        bool guardado = _archivo.Guardar(reg);
        if(guardado){
            cout << "Registro guardado con satisfactoriamente";
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

void VehiculoManager::Editar(){
    string patente;
    int posicion;

    cout << "Ingrese Nro. de patente a editar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);

    posicion = _archivo.Buscar(patente);
    if(posicion >= 0){
        MenuEditarVehiculo menuEditorVehiculo;
        Vehiculo reg = _archivo.Leer(posicion);
        cout << "Registro a modificar: " << endl;
        Mostrar(reg);
        menuEditorVehiculo.Mostrar(reg);
        _archivo.Guardar(reg, posicion);
    }
    else{
        cout << "Registro no encontrado." << endl;
    }
}

void VehiculoManager::Eliminar(){
    string patente;
    int posicion;

    cout << "Ingrese nro. de patente a eliminar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    posicion = Buscar(patente);
    if(posicion >= 0){
        Vehiculo reg = _archivo.Leer(posicion);
        cout << "Registro a eliminar: " << endl;
        Mostrar(reg);

        char confirmacion;
        cout << endl << "¿Desea continuar. El registro sera eliminado (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion)== 'S'){
            reg.setEstado(false);
            _archivo.Guardar(reg, posicion);
            cout << endl << "Vehiculo eliminado correctamente.";
        }
        else{
            cout << "No se han realizado cambios." << endl;
        }
    }
    else{
        cout << "Registro no encontrado. No se han realizado cambios." << endl;
    }
}

void VehiculoManager::Mostrar(Vehiculo reg){
    cout << endl;
    cout << "Patente: " << reg.getPatente() << endl;
    cout << "Modelo: " << reg.getModelo() << endl;
    cout << "Marca: " << reg.getMarca() << endl;
    cout << "Tipo: ";
    if(reg.getTipo() == 1){
        cout << "Gama baja" << endl;
    }
    else if(reg.getTipo() == 2){
        cout << "Gama media" << endl;
    }
    else{
        cout << "Gama Alta" << endl;
    }
    cout << "Fabricacion: " << reg.getAnioDeProduccion() << endl;
    cout << "En Taller: ";
    if(reg.getEnTaller()){
        cout << "Si" << endl;
    }
    else{
        cout << "No" << endl;
    }
    cout << "ESTADO (PRUEBA): " << reg.getEstado();
    cout << endl;
}

void VehiculoManager::ListarTodos(){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Mostrar(_archivo.Leer(i));
    }
    cout << endl;
}

int VehiculoManager::Buscar(std::string nroPatente){
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Vehiculo reg = _archivo.Leer(i);
        if(nroPatente == reg.getPatente()){
            return i;
        }
    }
    return -1;
}

void VehiculoManager::ListarxPatente(){
    string patente;
    int posicion;
    cout << "Ingrese nro. patente a buscar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    posicion = _archivo.Buscar(patente);
    if(posicion >= 0){
        Vehiculo reg = _archivo.Leer(posicion);
        Mostrar(reg);
    }
    else{
        cout << "Patente no encontrada.";
        cout << endl;
    }
}


//Metodos para modificar la propiedad "estado" un registro de Vehiculo
//Son metodos a parte del metodo "Editar" ya que, conceptualmente, el proceso es distinto.
void VehiculoManager::VehiculoIngresaTaller(){
    string patente;
    int posicion;

    cout << "Ingrese Nro. de patente que ingresa a Taller: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);

    posicion = _archivo.Buscar(patente);
    if(posicion >= 0){
        Vehiculo reg = _archivo.Leer(posicion);

        if(reg.getEnTaller()){
            cout << endl << "El vehiculo ya se encuentra en taller." << endl;
            return;
        }
        else if(!reg.getEstado()){
            cout << endl << "Vehiculo eliminado." << endl;
            return;
        }
        cout << "Vehiculo seleccionado: " << endl;
        Mostrar(reg);

        cout << endl << "Corfirmar (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            reg.setEnTaller(true);
            _archivo.Guardar(reg, posicion);
            cout << "Vehiculo " << reg.getPatente() << " ingresado a taller. No estara disponible para alquilar." << endl;
        }
    }
    else{
        cout << "Registro no encontrado." << endl;
    }
}

void VehiculoManager::VehiculoRetiroDeTaller(){
    string patente;
    int posicion;

    cout << "Ingrese Nro. de patente que se retira de taller: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);

    posicion = _archivo.Buscar(patente);
    if(posicion >= 0){
        Vehiculo reg = _archivo.Leer(posicion);

        if(!reg.getEnTaller()){
            cout << endl << "El vehiculo no se encuentra en taller y está disponible para alquilar." << endl;
            return;
        }
        else if(!reg.getEstado()){
            cout << endl << "Vehiculo eliminado." << endl;
            return;
        }
        cout << "Vehiculo seleccionado: " << endl;

        Mostrar(reg);

        cout << endl << "Corfirmar (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            reg.setEnTaller(false);
            _archivo.Guardar(reg, posicion);
            cout << "Vehiculo " << reg.getPatente() << " retirado de taller. Está disponible para alquilar." << endl;
        }
    }
    else{
        cout << "Registro no encontrado." << endl;
    }
}

int VehiculoManager::contarVehiculosActivos(){
    int cantidad = 0;
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++){
        Vehiculo reg = _archivo.Leer(i);
        if(reg.getEstado()){
            cantidad++;
        }
    }
    return cantidad;
}

void VehiculoManager::cargarVectorVehiculosActivos(Vehiculo* vec, int cantidadElementos) {
    int cantidadRegistros = _archivo.contarRegistros();
    int indiceVec = 0; // Nuevo índice para controlar la asignación en vec

    for (int x = 0; x < cantidadRegistros && indiceVec < cantidadElementos; x++) {
        Vehiculo reg = _archivo.Leer(x);
        if (reg.getEstado()) {
            vec[indiceVec] = reg;
            indiceVec++; // Incrementa el índice en vec solo si se asigna un vehículo válido
        }
    }
}
