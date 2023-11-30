#include "VehiculoManager.h"
#include "ReservaManager.h"
#include <algorithm>
#include "MenuEditarVehiculo.h"
#include "Fecha.h"
#include <iostream>
#include <iomanip>
#include "rlutil.h"
using namespace std;

void VehiculoManager::Cargar()
{
    string patente, modelo;
    int tipo, anioFabricacion, idMarca;
    float tarifaDiaria;
    MarcaManager managerMarca;
    Marca marca;

    cout << "Ingrese la información del nuevo Vehículo" << endl;
    cout << "Nro. de Patente: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    if(Buscar(patente) != -1)
    {
        cout << "El número de patente ya existe." << endl;
        cout << "No se ha grabado el nuevo registro." << endl;
        return;
    }
    cout << endl;
    managerMarca.ListarTodos();
    cout << "ID Marca: ";
    cin >> idMarca;

    //Validar que la marca exista
    if(_archivoMarca.Buscar(idMarca) == -1)
    {
        cout << "El id de Marca es inexistene. Operación cancelada." << endl;
        return;
    }
    marca = _archivoMarca.Leer(idMarca - 1);
    if(!marca.getActivo())
    {
        cout << "El id de Marca ha sido eliminado. Operación cancelada." << endl;
        return;
    }

    cout << "Modelo: ";
    cin >> modelo;
    cout << "Tipo (1- Gama baja, 2- Gama media, 3-Gama alta): ";
    cin >> tipo;
    if(tipo < 1 || tipo > 3)
    {
        cout << "Tipo no válido. Debe ser 1, 2 o 3." << endl;
        return;
    }
    cout << "Fabricación: ";
    cin >> anioFabricacion;
    cout << "Tarifa diaria: $";
    cin >> tarifaDiaria;

    Vehiculo reg;
    reg.setPatente(patente);
    reg.setModelo(modelo);
    reg.setIdMarca(idMarca);
    reg.setTipo(tipo);
    reg.setAnioProduccion(anioFabricacion);
    reg.setTarifaDiaria(tarifaDiaria);
    reg.setEnTaller(false);
    reg.setEstado(true);

    Mostrar(reg);
    char confirmacion;
    cout << endl << "Desea guardar el siguiente registro (S/N)?: " << endl;
    cin >> confirmacion;

    if(toupper(confirmacion) == 'S')
    {
        bool guardado = _archivo.Guardar(reg);
        if(guardado)
        {
            cout << "Registro guardado con satisfactoriamente";
        }
        else
        {
            cout << "Oops, Error. No se ha podido guardar el registro.";
        }
        cout << endl;
    }
    else
    {
        cout << "Carga de registro cancelada." << endl;
    }
}

void VehiculoManager::Editar()
{
    string patente;
    int posicion;

    ListarTodos();

    cout << endl << "Ingrese Nro. de patente a editar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);

    posicion = _archivo.Buscar(patente);
    Vehiculo reg = _archivo.Leer(posicion);
    if(reg.getEstado())
    {
        MenuEditarVehiculo menuEditorVehiculo;
        if(!reg.getEstado())
        {
            cout << "Vehiculo no encontrado." << endl;
            return;
        }
        cout << endl << "Registro a modificar: " << endl;
        Mostrar(reg);
        cout << endl << endl;
        system("pause");

        menuEditorVehiculo.Mostrar(reg);
        if(reg.getTipo() < 1 || reg.getTipo() > 3)
        {
            cout << "Gama de vehiculo incorrecta. Modificación cancelada." << endl;
            return;
        }

        int cantidadMarcas = _archivoMarca.contarRegistros();

        if(reg.getIDMarca() > cantidadMarcas || reg.getIDMarca() <= 0)
        {
            cout << "Marca de vehículo incorrecta. Modificación cancelada." << endl;
            return;
        }

        cout << "Nuevo registro: " << endl;
        Mostrar(reg);
        char confirmacion;
        cout << endl << "¿Está seguro de que desea guardar? (S/N):";
        cin >> confirmacion;

        if(toupper(confirmacion) == 'S'){
            if(_archivo.Guardar(reg, posicion))
            {
                cout << "Registro modificado satisfactoriamente." << endl;
            }
        }
        else{
            cout << "Registro no guardado. No se realizaron cambios." << endl;
        }
    }
    else
    {
        cout << "Registro no encontrado." << endl;
    }
}

void VehiculoManager::Eliminar()
{
    string patente;
    int posicion;
    ListarTodos();
    cout << endl << "Ingrese nro. de patente a eliminar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    posicion = Buscar(patente);
    if(posicion >= 0)
    {
        Vehiculo reg = _archivo.Leer(posicion);
        if(!reg.getEstado()){
            cout << "Registro ya eliminado." << endl;
            return;
        }

        cout << "Registro a eliminar: " << endl;
        Mostrar(reg);

        char confirmacion;
        cout << endl << "¿Desea continuar. El registro sera eliminado (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion)== 'S')
        {
            reg.setEstado(false);
            _archivo.Guardar(reg, posicion);
            cout << endl << "Vehiculo eliminado correctamente.";
        }
        else
        {
            cout << "No se han realizado cambios." << endl;
        }
    }
    else
    {
        cout << "Registro no encontrado. No se han realizado cambios." << endl;
    }
}

void VehiculoManager::Mostrar(Vehiculo reg)
{
    Marca marcaReg = _archivoMarca.Leer(reg.getIDMarca() - 1);
    cout << endl;
    cout << left << setw(15) << reg.getPatente();
    cout << left << setw(15) << marcaReg.getNombre();
    cout << left << setw(15) << reg.getModelo();
    if(reg.getTipo() == 1)
    {
        cout << left << setw(15) << "Gama baja";
    }
    else if(reg.getTipo() == 2)
    {
        cout << left << setw(15) << "Gama media";
    }
    else
    {
        cout << left << setw(15) << "Gama Alta";
    }
    cout << left << setw(10) << reg.getAnioDeProduccion();
    cout << left << setw(10) << reg.getTarifaDiaria();
    if(reg.getEnTaller())
    {
        cout << left << setw(12) << "Si";
    }
    else
    {
        cout << left << setw(12) << "No";
    }
}

void VehiculoManager::ListarTodos()
{
    int cantidadRegistros = _archivo.contarRegistros();
    mostrarTituloVehiculos();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Vehiculo reg = _archivo.Leer(i);
        if(reg.getEstado())
        {
            Mostrar(reg);
        }
    }
    cout << endl;
}

int VehiculoManager::Buscar(std::string nroPatente)
{
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Vehiculo reg = _archivo.Leer(i);
        if(nroPatente == reg.getPatente())
        {
            return i;
        }
    }
    return -1;
}

void VehiculoManager::ListarxPatente()
{
    string patente;
    int posicion;
    cout << "Ingrese nro. patente a buscar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    posicion = _archivo.Buscar(patente);

    mostrarTituloVehiculos();
    if(posicion >= 0)
    {
        Vehiculo reg = _archivo.Leer(posicion);
        Mostrar(reg);
    }
    else
    {
        cout << "Patente no encontrada.";
        cout << endl;
    }
    cout << endl;
}


//Metodos para modificar la propiedad "estado" un registro de Vehiculo
//Son metodos a parte del metodo "Editar" ya que, conceptualmente, el proceso es distinto.
void VehiculoManager::VehiculoIngresaTaller()
{
    ListarTodos();
    string patente;
    int posicion;

    cout << endl << "Ingrese Nro. de patente que ingresa a Taller: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);

    posicion = _archivo.Buscar(patente);
    if(posicion >= 0)
    {
        Vehiculo reg = _archivo.Leer(posicion);

        if(reg.getEnTaller())
        {
            cout << endl << "El vehiculo ya se encuentra en taller." << endl;
            return;
        }
        else if(!reg.getEstado())
        {
            cout << endl << "Vehiculo eliminado." << endl;
            return;
        }
        cout << "Vehiculo seleccionado: " << endl;

        mostrarTituloVehiculos();
        Mostrar(reg);

        cout << endl << "Corfirmar (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S')
        {
            reg.setEnTaller(true);
            _archivo.Guardar(reg, posicion);
            cout << "Vehiculo " << reg.getPatente() << " ingresado a taller. No estara disponible para alquilar." << endl;
        }
    }
    else
    {
        cout << "Registro no encontrado." << endl;
    }
}

void VehiculoManager::VehiculoRetiroDeTaller()
{
    string patente;
    int posicion;
    ListarTodos();
    cout << endl << "Ingrese Nro. de patente que se retira de taller: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);

    posicion = _archivo.Buscar(patente);
    if(posicion >= 0)
    {
        Vehiculo reg = _archivo.Leer(posicion);
        if(!reg.getEstado()){
            cout << "Registro eliminado." << endl;
            return;
        }
        if(!reg.getEnTaller())
        {
            cout << endl << "El vehiculo no se encuentra en taller y está disponible para alquilar." << endl;
            return;
        }

        cout << "Vehiculo seleccionado: " << endl;

        mostrarTituloVehiculos();
        Mostrar(reg);

        cout << endl << "Corfirmar (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S')
        {
            reg.setEnTaller(false);
            _archivo.Guardar(reg, posicion);
            cout << "Vehiculo " << reg.getPatente() << " retirado de taller. Está disponible para alquilar." << endl;
        }
    }
    else
    {
        cout << "Registro no encontrado." << endl;
    }
}

/*
int VehiculoManager::contarVehiculosActivos()
{
    int cantidad = 0;
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Vehiculo reg = _archivo.Leer(i);
        if(reg.getEstado())
        {
            cantidad++;
        }
    }
    return cantidad;
}
*/

/*
void VehiculoManager::cargarVectorVehiculosActivos(Vehiculo* vec, int cantidadElementos)
{
    int cantidadRegistros = _archivo.contarRegistros();
    int indiceVec = 0; // Nuevo índice para controlar la asignación en vec

    for (int x = 0; x < cantidadRegistros && indiceVec < cantidadElementos; x++)
    {
        Vehiculo reg = _archivo.Leer(x);
        if (reg.getEstado())
        {
            vec[indiceVec] = reg;
            indiceVec++; // Incrementa el índice en vec solo si se asigna un vehículo válido
        }
    }
}
*/

void VehiculoManager::ListarxGamaVehiculo()
{
    int cantidadRegistros = _archivo.contarRegistros();
    int gamaVehiculo;
    bool registroMostrado = false;

    cout << "Ingrese tipo de vehiculo(1- Gama baja, 2- Gama media, 3-Gama alta): ";
    cin >> gamaVehiculo;
    cout << endl;
    mostrarTituloVehiculos();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Vehiculo reg = _archivo.Leer(i);
        if(gamaVehiculo == reg.getTipo() && reg.getEstado())
        {
            Mostrar(reg);
            registroMostrado = true;
        }
    }
    if(!registroMostrado)
    {
        cout << endl << "No existen registros con los parametos ingresados." << endl;
    }
    cout << endl << endl;
    system("pause");
}

void VehiculoManager::ListarxMarca()
{
    int cantidadRegistros = _archivo.contarRegistros();
    int marca;
    bool registroMostrado = false;

    MarcaManager managerMarca;
    managerMarca.ListarTodos();
    cout << "Ingrese ID de marca de vehiculos a consultar: ";
    cin >> marca;
    cout << endl;
    mostrarTituloVehiculos();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Vehiculo reg = _archivo.Leer(i);
        if(marca == reg.getIDMarca() && reg.getEstado())
        {
            Mostrar(reg);
            registroMostrado = true;
        }
    }
    if(!registroMostrado)
    {
        cout << endl << "No existen registros con los parametos ingresados." << endl;
    }
    cout << endl << endl;
    system("pause");
}

void VehiculoManager::ListarxAnioProduccion()
{

    int cantidadRegistros = _archivo.contarRegistros();
    int anio;
    bool registroMostrado = false;

    cout << "Ingrese año de produccion de vehiculos: ";
    cin >> anio;
    cout << endl;
    mostrarTituloVehiculos();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Vehiculo reg = _archivo.Leer(i);
        if(anio == reg.getAnioDeProduccion() && reg.getEstado())
        {
            Mostrar(reg);
            registroMostrado = true;
        }
    }
    if(!registroMostrado)
    {
        cout << endl << "No existen registros con los parametos ingresados." << endl;
    }
    cout << endl << endl;
    system("pause");
}

void VehiculoManager::HacerCopiaSeguridad()
{
    int cantidadRegistros = _archivo.contarRegistros();
    Vehiculo *vehiculos = new Vehiculo[cantidadRegistros];

    if(vehiculos == nullptr)
    {
        cout << "Falla al realizar el backup." << endl;
        return;
    }

    _archivo.Leer(vehiculos, cantidadRegistros);
    _archivoBkp.Vaciar();
    if(_archivoBkp.Guardar(vehiculos, cantidadRegistros))
    {
        cout << "Backup realizado correctamente." << endl;
    }
    else
    {
        cout << "Falla al realizar backup." << endl;
    }
    delete []vehiculos;
}

void VehiculoManager::RestaurarCopiaDeSeguridad()
{
    int cantidadRegistros = _archivoBkp.contarRegistros();
    Vehiculo *vehiculos = new Vehiculo[cantidadRegistros];

    if(vehiculos == nullptr)
    {
        cout << "Falla al restaurar backup." << endl;
        return;
    }

    _archivoBkp.Leer(vehiculos, cantidadRegistros);
    _archivo.Vaciar();

    if(_archivo.Guardar(vehiculos, cantidadRegistros))
    {
        cout << "Backup restaurado satisfactoriamente." << endl;
    }
    else
    {
        cout << "Falla al restaurar backup." << endl;
    }

    delete[] vehiculos;
}

void VehiculoManager::OrdenarxGama()
{
    int cantidadRegistros = _archivo.contarRegistros();

    mostrarTituloVehiculos();
    for(int i=1; i<=3; i++)
    {
        for(int x=0; x<cantidadRegistros; x++)
        {
            Vehiculo vehiculo = _archivo.Leer(x);
            if(vehiculo.getTipo() == i && vehiculo.getEstado())
            {
                Mostrar(vehiculo);
            }
        }
    }
    cout << endl;
    system("pause");
}

void VehiculoManager::OrdenarxMarca()
{
    int cantidadRegistros = _archivo.contarRegistros();
    Vehiculo* vehiculos = new Vehiculo[cantidadRegistros];
    if(vehiculos == nullptr)
    {
        cout << "Error de memoria." << endl;
        return;
    }

    _archivo.Leer(vehiculos, cantidadRegistros);
    ordenarVectorVehiculosxMarca(vehiculos, cantidadRegistros);

    mostrarTituloVehiculos();
    for(int i=0; i<cantidadRegistros; i++)
    {
        if(vehiculos[i].getEstado())
        {
            Mostrar(vehiculos[i]);
        }
    }
    cout << endl;
    delete[] vehiculos;
    system("pause");
}
void VehiculoManager::OrdenarxAnioProduccion()
{
    int cantidadVehiculos = _archivo.contarRegistros();
    Vehiculo* vehiculos;
    vehiculos = new Vehiculo[cantidadVehiculos];
    if(vehiculos == nullptr)
    {
        cout << "Error de memoria." << endl;
        return;
    }

    _archivo.Leer(vehiculos, cantidadVehiculos);
    ordenarVectorVehiculosxAnio(vehiculos, cantidadVehiculos);

    mostrarTituloVehiculos();
    for(int i=0; i<cantidadVehiculos; i++)
    {
        if(vehiculos[i].getEstado())
        {
            Mostrar(vehiculos[i]);
        }
    }
    cout << endl;
    delete[] vehiculos;
    system("pause");
}

void VehiculoManager::ordenarVectorVehiculosxAnio(Vehiculo* vehiculos, int cantidadElementos)
{
    for(int i=0; i<cantidadElementos; i++)
    {
        for(int x=0; x<cantidadElementos - 1; x++)
        {
            if(vehiculos[x].getAnioDeProduccion() > vehiculos[x+1].getAnioDeProduccion())
            {
                Vehiculo aux = vehiculos[x];
                vehiculos[x] = vehiculos[x+1];
                vehiculos[x+1] = aux;
            }
        }
    }
}

void VehiculoManager::ordenarVectorVehiculosxMarca(Vehiculo* vehiculos, int cantidadElementos)
{
    for(int i=0; i<cantidadElementos; i++)
    {
        for(int x=0; x<cantidadElementos - 1; x++)
        {
            if(vehiculos[x].getIDMarca() > vehiculos[x+1].getIDMarca())
            {
                Vehiculo aux = vehiculos[x];
                vehiculos[x] = vehiculos[x+1];
                vehiculos[x+1] = aux;
            }
        }
    }
}

void VehiculoManager::generarDisponibilidad()
{
    Fecha fechaHoy = Fecha(); //Crea un objeto fecha. Se construye con la fecha del sistema operativo.
    int cantidadVehiculos = _archivo.contarRegistros();
    ReservaManager managerReservas;

    //Se crea un vector dinamico de vehiculos y se los carga con los registros del archivo.
    Vehiculo* vehiculoParaDisponibilidad;
    vehiculoParaDisponibilidad = new Vehiculo[cantidadVehiculos];
    if(vehiculoParaDisponibilidad == nullptr)
    {
        cout << "Error de memoria." << endl;
        return;
    }
    _archivo.Leer(vehiculoParaDisponibilidad, cantidadVehiculos);
    mostrarTituloVehiculos();
    cout << "ESTADO";
    for(int i=0; i<cantidadVehiculos; i++)
    {
        string estadoDisponibilidad; //Variable auxiliar para mostrar el estado del vehiculo al generar la disponibilidad.
        int cantReservasPorPatente = managerReservas.contarReservasxPatentes(vehiculoParaDisponibilidad[i].getPatente());
        Reserva* reservasConMismaPatente;
        reservasConMismaPatente = new Reserva[cantReservasPorPatente];
        if(reservasConMismaPatente == nullptr)
        {
            cout << "Error de memoria en reservas." << endl;
            return;
        }

        managerReservas.CargarVectorPorNroPatente(vehiculoParaDisponibilidad[i].getPatente(), cantReservasPorPatente, reservasConMismaPatente);

        if(managerReservas.validarSiEstaDisponibleHoy(fechaHoy, reservasConMismaPatente, cantReservasPorPatente))
        {
            estadoDisponibilidad = "Disponible";
        }
        else
        {
            estadoDisponibilidad = "Alquilado";
        }

        if(vehiculoParaDisponibilidad[i].getEnTaller())
        {
            estadoDisponibilidad = "No Disponible";
        }
        delete[] reservasConMismaPatente;

        Mostrar(vehiculoParaDisponibilidad[i]);
        cout << estadoDisponibilidad;
    }
    delete[] vehiculoParaDisponibilidad;
    cout << endl << endl;
    system("pause");
}

void VehiculoManager::RecuperarRegistroEliminado(){
    int cantidadRegistros = _archivo.contarRegistros();
    string patente;
    cout << "Los siguientes vehículos fueron eliminados: " << endl << endl;
    for(int i=0; i<cantidadRegistros; i++){
        Vehiculo vehiculo = _archivo.Leer(i);
        if(!vehiculo.getEstado()){
            Mostrar(vehiculo);
        }
    }
    cout << endl << endl << "Ingrese número de patente a recuperar: ";
    cin >> patente;
    transform(patente.begin(), patente.end(), patente.begin(), ::toupper);
    int posicion = _archivo.Buscar(patente);
    if(posicion == -1){
        cout << "Vehículo no encontrado" << endl;
        return;
    }
    Vehiculo reg = _archivo.Leer(posicion);
    if(!reg.getEstado()){
        cout << "Registro a recuperar:" << endl;
        Mostrar(reg);
        cout << endl << "¿Desea continuar? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        if(toupper(confirmacion) == 'S'){
            reg.setEstado(true);
            if(_archivo.Guardar(reg, posicion)){
                cout << "Registro recuperado correctamente" << endl;
            }
            else{
                cout << "Error al recuperar registro" << endl;
                return;
            }
        }
        else{
            cout << "Operación cancelada" << endl;
            return;
        }
    }
    else{
        cout << "El registro no se encuentra eliminado." << endl;
    }
}

void VehiculoManager::mostrarTituloVehiculos(){
    cout << left << setw(15) << "PATENTE";
    cout << left << setw(15) << "MARCA";
    cout << left << setw(15) << "MODELO";
    cout << left << setw(15) << "GAMA";
    cout << left << setw(10) << "AÑO";
    cout << left << setw(10) << "TARIFA";
    cout << left << setw(12) << "EN TALLER";
}
