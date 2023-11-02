#include "ReservaManager.h"
#include "Vehiculo.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

void ReservaManager::Cargar()
{
    int id, numDniCliente;
    string patenteVehiculo;
    float importeAlquiler;
    int diaInicio, mesInicio, anioInicio, diaFin, mesFin, anioFin;

    cout << "Por favor, ingrese los datos de la reserva." << endl;
    cout << "-------------------------------------------" << endl;

    id = generarReservaId();
    cout << "ID a generar: " << id << endl;
    cout << "Patente del vehiculo a alquilar: ";
    cin >> patenteVehiculo;
    transform(patenteVehiculo.begin(), patenteVehiculo.end(), patenteVehiculo.begin(), ::toupper);

    int posicionRegistroVehiculo = _archivoVehiculo.Buscar(patenteVehiculo);
    Vehiculo regVehiculo;

    if(posicionRegistroVehiculo == -1)
    {
        cout << endl << "El vehiculo no existe." << endl;   //Valida que el vehiculo exista
        cout << "Carga de reserva cancelada." << endl;
        return;
    }
    else
    {
        regVehiculo = _archivoVehiculo.Leer(posicionRegistroVehiculo);
        if(!regVehiculo.getEstado())
        {
            cout << endl << "El vehiculo fue eliminado." << endl; //valida que el vehiculo no haya sido eliminado
            cout << "Carga de reserva cancelada." << endl;
            return;
        }
    }

    if(regVehiculo.getEnTaller())
    {
        cout << endl << "El vehiculo se encuentra en taller, no puede ser alquilado." << endl;  //Valida que el vehiculo no se encuentre en taller
        return;
    }

    cout << "Ingrese el numero de documento del cliente: ";
    cin >> numDniCliente;

    if(_archivoCliente.Buscar(numDniCliente) == -1)
    {
        cout << endl << "El cliente no existe." << endl;    //Valida que el cliente exista en la base de datos
        cout << "Carga de reserva cancelada." << endl;
        return;
    }

    cout << "Importe total de la reserva: $";
    cin >> importeAlquiler;
    cout << "Fecha de Inicio: ";
    cin >> diaInicio;
    cin >> mesInicio;
    cin >> anioInicio;
    cout << "Fecha de Fin: ";
    cin >> diaFin;
    cin >> mesFin;
    cin >> anioFin;

    Reserva reg;
    reg.setIdReserva(id);
    reg.setDocCliente(numDniCliente);
    reg.setPatenteVehiculo(patenteVehiculo);
    reg.setImporteAlquiler(importeAlquiler);
    reg.setFechaInicio(Fecha(diaInicio, mesInicio, anioInicio));
    reg.setFechaFin(Fecha(diaFin, mesFin, anioFin));
    reg.setEstado(true);

    //Se valida que la fecha de fin sea mayor a la fecha de inicio
    if(reg.getFechaFin() < reg.getFechaInicio())
    {
        cout << endl << "Error. La fecha de inicio no puede ser mayor a la fecha de fin." << endl;
        cout << "Carga de reserva cancelada" << endl;
        return;
    }

    //Se cuantan cuantas reservas hay con una misma patente
    int cantidadReservasConMismaPatente = contarReservasxPatentes(patenteVehiculo);

    //Si hay por lo menos una, se genera un vector dinamico de esas reservas
    if(cantidadReservasConMismaPatente != 0)
    {
        Reserva* reservasConMismaPatente;
        reservasConMismaPatente = new Reserva[cantidadReservasConMismaPatente];
        if(reservasConMismaPatente == nullptr)
        {
            cout << endl << "Error en memoria dinamica. Carga cancelada." << endl;
            return;
        }
        //Se validan si el vehiculo esta disponible en las fechas seleccionadas
        CargarVectorPorNroPatente(patenteVehiculo, cantidadReservasConMismaPatente, reservasConMismaPatente);
        //ordenarReservasPorFecha(reservasConMismaPatente, cantidadReservasConMismaPatente);
        if(!validarDisponibilidadVehiculo(reg.getFechaInicio(), reg.getFechaFin(), reservasConMismaPatente, cantidadReservasConMismaPatente))
        {
            cout << "El vehiculo no se encuentra disponible para las fechas indicadas. Carga canceladad." << endl;
            return;
        }
        delete []reservasConMismaPatente;
    }

    cout << endl;
    mostrarTituloReservas();
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

void ReservaManager::Eliminar()
{
    int id, posicion;

    cout << "Ingrese ID de reserva a eliminar: #";
    cin >> id;
    posicion = Buscar(id);
    if(posicion >= 0)
    {
        Reserva reg = _archivo.Leer(posicion);
        cout << "Registro a eliminar: " << endl;
        mostrarTituloReservas();
        Mostrar(reg);

        char confirmacion;
        cout << endl << "�Desea continuar. El registro sera elimiando (S/N): ";
        cin >> confirmacion;

        if(toupper(confirmacion) == 'S')
        {
            reg.setEstado(false);
            _archivo.Guardar(reg, posicion);
            cout << endl << "Reserva eliminada correctamente.";
        }
        else
        {
            cout << "No se han regitrado cambios." << endl;
        }
    }
    else
    {
        cout << "Registro no encontrado. No se han realizado cambios." << endl;
    }
}

void ReservaManager::Mostrar(Reserva reg)
{
    cout << left << setw(15) << reg.getIdReserva();
    cout << left << setw(25) << reg.getDocCliente();
    cout << left << setw(25) << reg.getPatenteVehiculo();
    cout << "$" << left << setw(25) << reg.getImporteAlquiler();
    cout << left << setw(20) << reg.getFechaInicio().toString();
    cout << left << setw(20) << reg.getFechaFin().toString() << endl << endl;
}

void ReservaManager::ListarTodos()
{
    ReservaManager::mostrarTituloReservas();

    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Reserva reg = _archivo.Leer(i);
        if(reg.getEstado()){
            Mostrar(reg);
        }
    }
    cout << endl;
}

int ReservaManager::Buscar(int idReserva)
{
    int cantidadRegistros = _archivo.contarRegistros();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Reserva reg = _archivo.Leer(i);
        if(idReserva == reg.getIdReserva())
        {
            return i;
        }
    }
    return -1;
}

void ReservaManager::ListarxID()
{
    int id, posicion;
    cout << "Ingrese ID de Reserva a buscar: ";
    cin >> id;
    cout << endl;

    ReservaManager::mostrarTituloReservas();

    posicion = _archivo.Buscar(id);
    if (posicion >= 0)
    {
        Reserva reg = _archivo.Leer(posicion);
        Mostrar(reg);
    }
    else
    {
        cout << endl << "ID de Reserva no encontrado." << endl << endl;
    }
}

int ReservaManager::generarReservaId()
{
    return _archivo.contarRegistros() + 1;
}

//Se cuentan las cantidad de reservas con la misma patente para validar existencias.
//Si existen reservar, se validar� las fechas de inicio y fin para corroborar que el vehiculo est� disponible
int ReservaManager::contarReservasxPatentes(std::string patente)
{
    int cantidadRegistrso = _archivo.contarRegistros();
    int cantidad = 0;
    for(int i=0; i<cantidadRegistrso; i++)
    {
        Reserva reg = _archivo.Leer(i);
        if(patente == reg.getPatenteVehiculo() && reg.getEstado())
        {
            cantidad++;
        }
    }
    return cantidad;
}

//Se carga el vector generado en el metodo "Cargar" a partir del numero de patente tipeado por el usuario
void ReservaManager::CargarVectorPorNroPatente(std::string patente, int cantidadElementos, Reserva* vec)
{
    int cantidadRegistros = _archivo.contarRegistros();
    int contador = 0;
    for(int i=0; i<cantidadElementos; i++)
    {
        for(int x=0; x<cantidadRegistros; x++)
        {
            Reserva reg = _archivo.Leer(x);
            if(patente == reg.getPatenteVehiculo() && reg.getEstado())
            {
                if (contador < cantidadElementos)
                {
                    vec[contador] = reg;
                    contador++; // Incrementa el contador para el siguiente elemento
                }
            }
        }
    }
}

//Validar si el vehiculo esta disponible para las fechas seleccionadas en el metodo "Cargar()"
bool ReservaManager::validarDisponibilidadVehiculo(Fecha fInicio, Fecha fFin, Reserva* vec, int cantidadElementos)
{
    for(int i=0; i<cantidadElementos; i++)
    {
        if(fInicio > vec[i].getFechaInicio() && fInicio < vec[i].getFechaFin() || fFin > vec[i].getFechaInicio() && fFin < vec[i].getFechaFin())
        {
            return false;
        }
    }
    return true;
}
//Validar si el vehiculo esta disponible para las fechas seleccionadas en el metodo "extenderReserva()"
bool ReservaManager::validarDisponibilidadVehiculoExtension(Fecha fInicio, Fecha nuevaFechaFin, Reserva* vec, int cantidadElementos)
{
    for(int i=0; i<cantidadElementos; i++)
    {
        if((nuevaFechaFin > vec[i].getFechaInicio() && nuevaFechaFin < vec[i].getFechaFin()) || (fInicio < vec[i].getFechaInicio() && nuevaFechaFin < vec[i].getFechaFin()))
        {
            return false;
        }
    }
    return true;
}

void ReservaManager::ListarxRangoDeImporte()
{
    float importeDesde, importeHasta;
    int cantidadRegistros = _archivo.contarRegistros();
    bool registroMostrado = false;

    cout << "Ingrese el importe m�nimo de la consulta: $";
    cin >> importeDesde;
    cout << "Ingrese el importe m�ximo de la consulta: $"; //Se ingresan los importes de la
    cin >> importeHasta;

    ReservaManager::mostrarTituloReservas();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Reserva reg = _archivo.Leer(i);
        if(importeDesde <= reg.getImporteAlquiler() && importeHasta >= reg.getImporteAlquiler())
        {
            Mostrar(reg);
            registroMostrado = true;
        }
    }

    if(registroMostrado)
    {
        cout << endl << "No existen registros con los par�metos ingresados." << endl;
    }
}

void ReservaManager::ListarxFechaDeInicioReserva()
{
    int dia, mes, anio;
    int cantidadRegistros = _archivo.contarRegistros();
    bool registroMostrado = false;

    cout << "Ingrese dia, mes y a�o de la fecha de inicio a consultar: ";
    cin >> dia;
    cin >> mes;
    cin >> anio;
    Fecha fechaConsulta(Fecha(dia, mes, anio));

    ReservaManager::mostrarTituloReservas();
    for(int i=0; i<cantidadRegistros; i++)
    {
        Reserva reg = _archivo.Leer(i);
        if(reg.getFechaInicio() == fechaConsulta)
        {
            Mostrar(reg);
            registroMostrado = true;
        }
    }
    if(!registroMostrado)
    {
        cout << endl << "No existen registros con los par�metos ingresados." << endl << endl;
    }
}

void ReservaManager::recaudacionxGama()
{
    int cantidadRegistros = _archivo.contarRegistros();
    float vAcuGamaVehiculo[3] {}; //Se declara vector para acumular los importes por gama
    Fecha fechaActual;
    int anioActual = fechaActual.getAnio();

    cout << "La recaudaci�n por gama del a�o actual " << anioActual << " fue la siguiente: " << endl << endl;

    for(int i=0; i<cantidadRegistros; i++)
    {
        Reserva reserva = _archivo.Leer(i);
        int posVehiculo = _archivoVehiculo.Buscar(reserva.getPatenteVehiculo());
        Vehiculo vehiculo = _archivoVehiculo.Leer(posVehiculo);
        if(vehiculo.getTipo() == 1 && reserva.getFechaInicio().getAnio() == anioActual) vAcuGamaVehiculo[0] += reserva.getImporteAlquiler();
        if(vehiculo.getTipo() == 2 && reserva.getFechaInicio().getAnio() == anioActual) vAcuGamaVehiculo[1] += reserva.getImporteAlquiler();
        if(vehiculo.getTipo() == 3 && reserva.getFechaInicio().getAnio() == anioActual) vAcuGamaVehiculo[2] += reserva.getImporteAlquiler();
    }

    cout << endl << "Recaudaci�n Gama Baja: " << vAcuGamaVehiculo[0] << endl;
    cout << endl << "Recaudaci�n Gama Media: " << vAcuGamaVehiculo[1] << endl;
    cout << endl << "Recaudaci�n Gama Alta: " << vAcuGamaVehiculo[2] << endl;
    cout << endl << endl;
}

void ReservaManager::recaudacionAnual()
{
    int anioConsulta;
    float recaudacionMensual[12] {};
    int cantidadRegistros = _archivo.contarRegistros();

    cout << "Por favor, ingrese a�o de consulta: ";
    cin >> anioConsulta;
    cout << endl << "La recaudacion del a�o " << anioConsulta << " es la siguiente: " << endl << endl;

    for(int i=0; i<cantidadRegistros; i++)
    {
        Reserva reserva = _archivo.Leer(i);
        if(reserva.getEstado() && reserva.getFechaInicio().getAnio() == anioConsulta)
        {
            recaudacionMensual[reserva.getFechaInicio().getMes() - 1] += reserva.getImporteAlquiler();
        }
    }

    for(int x=0; x<12; x++)
    {
        cout << "La recaudaci�n del mes " << x+1 << " fue de: $" << recaudacionMensual[x] << endl;
    }
    cout << endl;
}

void ReservaManager::mostrarTituloReservas()
{
    cout << left << setw(15) << "ID Reserva";
    cout << left << setw(25) << "Documento del cliente";
    cout << left << setw(25) << "Veh�culo alquilado";
    cout << left << setw(25) << "Importe del contrato";
    cout << left << setw(20) << "Fecha de Inicio";
    cout << left << setw(20) << "Fecha de Fin" << endl;
}

//Extiende la fecha fin de un contrato existente.
void ReservaManager::extenderReserva()
{
    int id, posicion;
    int dia, mes, anio;
    Fecha fechaHoy = Fecha();

    cout << "Extender reserva de un contrato." << endl;
    cout << endl << "Ingrese el ID de la reserva a extender: #";
    cin >> id;

    posicion = _archivo.Buscar(id); //Se bisca el id en cuestion
    if(posicion == -1)
    {
        cout << endl << "ID de reserva no existe. Operaci�n cancelada." << endl << endl;
        return;
    }
    cout << endl << "Registro seleccionado: " << endl << endl;
    Reserva reg = _archivo.Leer(posicion);

    mostrarTituloReservas();
    Mostrar(reg);

    if(fechaHoy > reg.getFechaFin())
    {
        cout << endl << "La reserva ya se inici� y se finaliz�. Genere una nueva reserva." << endl << endl;
        return;
    }

    cout << endl << "Ingrese nueva fecha de finalizacion de Reserva: ";
    cin >> dia;
    cin >> mes;
    cin >> anio;
    Fecha fechaExtension(dia, mes, anio);
    cout << endl << "Fecha seleccionada: " << fechaExtension.toString() << endl;

    if (fechaExtension < reg.getFechaFin())
    {
        cout << endl << "La fecha de extensi�n no puede ser menor a la fecha de fin original." << endl << endl;
        return;
    }

    int cantidadReservasConMismaPatente = contarReservasxPatentes(reg.getPatenteVehiculo());
    Reserva* ReservasMismaPatente;
    ReservasMismaPatente = new Reserva[cantidadReservasConMismaPatente];
    if (ReservasMismaPatente == nullptr)
    {
        cout << endl << "Error de memoria." << endl;
        return;
    }

    CargarVectorPorNroPatente(reg.getPatenteVehiculo(), cantidadReservasConMismaPatente, ReservasMismaPatente);
    ordenarReservasPorFecha(ReservasMismaPatente, cantidadReservasConMismaPatente);

    if(validarDisponibilidadVehiculoExtension(reg.getFechaInicio(), fechaExtension, ReservasMismaPatente, cantidadReservasConMismaPatente))
    {
        reg.setFechaFin(fechaExtension);
    }
    else
    {
        cout << endl << "El vehiculo no se encuentra disponible para la fecha de extensi�n" << endl;
        return;
    }

    mostrarTituloReservas();
    Mostrar(reg);
    cout << "Desea guardar el siguiente registro modificado (S/N): ";

    char confirmacion;
    cin >> confirmacion;
    if(toupper(confirmacion) == 'S')
    {
        if(_archivo.Guardar(reg, posicion))
        {
            cout << endl << "Registro modificado satisfactoriamente." << endl;
        }
        else
        {
            cout << endl << "Oops, error al modificar el registro. Cancelado." << endl;
        }
    }
    else
    {
        cout << "Operaci�n cancelada." << endl;
    }
    delete[] ReservasMismaPatente;
}

void ReservaManager::ordenarReservasPorFecha(Reserva* reservas, int cantidadElementos){
    for(int i=0; i<cantidadElementos; i++){
        for(int x=0; i<cantidadElementos - 1; i++){
            if(reservas[x=1].getFechaInicio() > reservas[x=1].getFechaInicio()){
                Reserva aux = reservas[x];
                reservas[x] = reservas[x+1];
                reservas[x+1] = aux;
            }
        }
    }
}
