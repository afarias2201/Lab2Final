#include "DisponibilidadFlota.h"
#include <cstring>
#include "Vehiculo.h"
#include "VehiculoManager.h"
#include "ReservaManager.h"
#include <iostream>
#include <iomanip>

void DisponibilidadFlota::generarDisponibilidad()
{
    VehiculoManager vehiculoManager;
    int cantidadVehiculos = vehiculoManager.contarVehiculosActivos();

    DisponibilidadFlota* vecDispo;
    vecDispo = new DisponibilidadFlota[cantidadVehiculos];
    if(vecDispo == nullptr)
    {
        std::cout << "Error de memoria." << std::endl;
        return;
    }

    for (int i=0; i<cantidadVehiculos; i++)
    {
        Vehiculo* vVehiculo;
        vVehiculo = new Vehiculo[cantidadVehiculos]; //Se genera un vector dinamico de vehiculos
        if(vVehiculo == nullptr)
        {
            std::cout << "Error de memoria." << std::endl;
        }

        vehiculoManager.cargarVectorVehiculosActivos(vVehiculo, cantidadVehiculos);     //Se carga el vector de vehiculos con los vehiculos activos

        vecDispo[i].vehiculo.setPatente(vVehiculo[i].getPatente());
        vecDispo[i].vehiculo.setMarca(vVehiculo[i].getMarca());
        vecDispo[i].vehiculo.setModelo(vVehiculo[i].getModelo());                       //Se le settea los datos del vehiculo
        vecDispo[i].vehiculo.setAnioProduccion(vVehiculo[i].getAnioDeProduccion());
        vecDispo[i].vehiculo.setTipo(vVehiculo[i].getTipo());

        ReservaManager reservaManager;
        int cantidadReservasPorPatente = reservaManager.contarReservasxPatentes(vVehiculo[i].getPatente());
        if(cantidadReservasPorPatente != 0)
        {
            Reserva* reservasConMismaPatente;
            reservasConMismaPatente = new Reserva[cantidadReservasPorPatente]; //Se genera un vector dinamico de reservas
            if(reservasConMismaPatente == nullptr)
            {
                std::cout << std::endl << "Error en memoria dinamica." << std::endl;
                return;
            }

            reservaManager.CargarVectorPorNroPatente(vVehiculo[i].getPatente(), cantidadReservasPorPatente, reservasConMismaPatente); //Se carga el vector de reservas con las reservas con la patente del vehiculo de turno
            if(!validarSiEstaDisponibleHoy(fechaDeConsulta, reservasConMismaPatente, cantidadReservasPorPatente)) //Se valida  si el vehiculo esta alquilado el dia de la fecha de consulta
            {
                vecDispo[i].setEstadoVehiculoDispo(1); //Se le asigna estado "Alquilado"
            }
            else if(validarSiEstaDisponibleHoy(fechaDeConsulta, reservasConMismaPatente, cantidadReservasPorPatente) || cantidadReservasPorPatente == 0)
            {
                vecDispo[i].setEstadoVehiculoDispo(0); //Se le asigna estado "Disponible" si no esta alquilado el dia de la fecha o no existen reservas con esa patente
            }
            delete[] reservasConMismaPatente;
        }
        else if(vVehiculo[i].getEnTaller())
        {
            vecDispo[i].setEstadoVehiculoDispo(2); //Se le asigna el estado "En taller" si esta ingresado en taller
        }
        delete[] vVehiculo;
    }
    Mostrar(vecDispo, cantidadVehiculos); //Se muestra la dispo pasando el vector de vehiculos de la dispo y la cantidad de elementos

    delete[] vecDispo;
    system("pause");
}

void DisponibilidadFlota::setPatenteDispo(std::string patente)
{
    vehiculo.setPatente(patente);
}
void DisponibilidadFlota::setModeloDispo(std::string modelo)
{
    vehiculo.setModelo(modelo);
}
void DisponibilidadFlota::setMarcaDispo(std::string marca)
{
    vehiculo.setMarca(marca);
}
void DisponibilidadFlota::setAnioProduccionDispo(int anio)
{
    vehiculo.setAnioProduccion(anio);
}
void DisponibilidadFlota::setTipoDispo(int tipo)
{
    vehiculo.setTipo(tipo);
}
void DisponibilidadFlota::setEstadoVehiculoDispo(int estadoVehiculo)
{
    if(estadoVehiculo == 0)
    {
        _estadoVehiculo = 0;
    }
    if(estadoVehiculo == 1)
    {
        _estadoVehiculo = 1;
    }
    if(estadoVehiculo == 2)
    {
        _estadoVehiculo = 2;
    }
}

std::string DisponibilidadFlota::getPatenteDispo() const
{
    return vehiculo.getPatente();
}
std::string DisponibilidadFlota::getModeloDispo() const
{
    return vehiculo.getModelo();
}
std::string DisponibilidadFlota::getMarcaDispo() const
{
    return vehiculo.getMarca();
}
int DisponibilidadFlota::getAnioProduccionDispo() const
{
    return vehiculo.getAnioDeProduccion();
}
std::string DisponibilidadFlota::getTipoDispo() const
{
    if(vehiculo.getTipo() == 1)
    {
        return "Gama baja";
    }
    else if(vehiculo.getTipo() == 2)
    {
        return "Gama media";
    }
    else
    {
        return "Gama Alta";
    }
}
std::string DisponibilidadFlota::getEstadoVehiculoDispo() const
{
    if(_estadoVehiculo == 0)
    {
        return "Disponible";
    }
    if(_estadoVehiculo == 1)
    {
        return "Alquilado";
    }
    if(_estadoVehiculo == 2)
    {
        return "En taller";
    }
}
bool DisponibilidadFlota::validarSiEstaDisponibleHoy(Fecha fechaHoy, Reserva* reserva, int cantidadElementos)
{
    for(int i=0; i<cantidadElementos; i++)
    {
        if(fechaHoy > reserva[i].getFechaInicio() && fechaHoy < reserva[i].getFechaFin())
        {
            return false;
        }
    }
    return true;
}

void DisponibilidadFlota::Mostrar(DisponibilidadFlota* vDispo, int cantidadElementos)
{
    std::cout << "DISPONIBILIDAD DE FLOTA DE VEHÍCULOS." << std::endl;
    std::cout << "Fecha de Ejecucion: " << fechaDeConsulta.toString() << std::endl << std::endl;

    // Ajusta la anchura de los campos y alinea a la izquierda
    std::cout
            << std::left << std::setw(15) << "Patente"
            << std::left << std::setw(15) << "Marca"
            << std::left << std::setw(15) << "Modelo"
            << std::left << std::setw(10) << "Año"
            << std::left << std::setw(15) << "Estado"
            << std::left << std::setw(15) << "Tipo" << std::endl << std::endl;

    for (int i = 0; i < cantidadElementos; i++)
    {
        // Ajusta la anchura de los campos y alinea a la izquierda
        std::cout
                << std::left << std::setw(15) << vDispo[i].getPatenteDispo()
                << std::left << std::setw(15) << vDispo[i].getMarcaDispo()
                << std::left << std::setw(15) << vDispo[i].getModeloDispo()
                << std::left << std::setw(10) << vDispo[i].getAnioProduccionDispo()
                << std::left << std::setw(15) << vDispo[i].getEstadoVehiculoDispo()
                << std::left << std::setw(15) << vDispo[i].getTipoDispo()
                << std::endl << std::endl;
    }
    /*
        std::cout << "Fecha de Ejecucion: " << fechaDeConsulta.toString() << std::endl << std::endl;
        for(int i=0; i<cantidadElementos; i++)
        {
            std::cout << vDispo[i].getPatenteDispo() << "   -   " << vDispo[i].getMarcaDispo() << "   -   " << vDispo[i].getModeloDispo() << "   -   " << vDispo[i].getAnioProduccionDispo() << "   -   " << vDispo[i].getEstadoVehiculoDispo() << "   -   " << vDispo[i].getTipoDispo() << std::endl << std::endl;
        }
    */
}
