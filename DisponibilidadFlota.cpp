#include "DisponibilidadFlota.h"
#include <cstring>
#include "Vehiculo.h"
#include "VehiculoManager.h"
#include "ReservaManager.h"
#include <iostream>

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
        vVehiculo = new Vehiculo[cantidadVehiculos];
        if(vVehiculo == nullptr)
        {
            std::cout << "Error de memoria." << std::endl;
        }

        vehiculoManager.cargarVectorVehiculosActivos(vVehiculo, cantidadVehiculos);

        vecDispo[i].setPatenteDispo(vVehiculo[i].getPatente());
        vecDispo[i].setMarcaDispo(vVehiculo[i].getMarca());
        vecDispo[i].setModeloDispo(vVehiculo[i].getModelo());
        vecDispo[i].setAnioProduccionDispo(vVehiculo[i].getAnioDeProduccion());
        vecDispo[i].setTipoDispo(vVehiculo[i].getTipo());

        ReservaManager reservaManager;
        int cantidadReservasPorPatente = reservaManager.contarReservasxPatentes(vVehiculo[i].getPatente());
        if(cantidadReservasPorPatente != 0)
        {
            Reserva* reservasConMismaPatente;
            reservasConMismaPatente = new Reserva[cantidadReservasPorPatente];
            if(reservasConMismaPatente == nullptr)
            {
                std::cout << std::endl << "Error en memoria dinamica." << std::endl;
                return;
            }

            reservaManager.CargarVectorPorNroPatente(vVehiculo[i].getPatente(), cantidadReservasPorPatente, reservasConMismaPatente);
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
    Mostrar(vecDispo, cantidadVehiculos);
    delete[] vecDispo;
}

void DisponibilidadFlota::setPatenteDispo(std::string patente)
{
    strcpy(_patenteDispo, patente.c_str());
}
void DisponibilidadFlota::setModeloDispo(std::string modelo)
{
    strcpy(_modeloDispo, modelo.c_str());
}
void DisponibilidadFlota::setMarcaDispo(std::string marca)
{
    strcpy(_marcaDispo, marca.c_str());
}
void DisponibilidadFlota::setAnioProduccionDispo(int anio)
{
    _anioDeProduccionDispo = anio;
}
void DisponibilidadFlota::setTipoDispo(int tipo)
{
    _tipoDispo = tipo;
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
    return _patenteDispo;
}
std::string DisponibilidadFlota::getModeloDispo() const
{
    return _modeloDispo;
}
std::string DisponibilidadFlota::getMarcaDispo() const
{
    return _marcaDispo;
}
int DisponibilidadFlota::getAnioProduccionDispo() const
{
    return _anioDeProduccionDispo;
}
std::string DisponibilidadFlota::getTipoDispo() const
{
    if(_tipoDispo == 1)
    {
        return "Gama baja";
    }
    else if(_tipoDispo == 2)
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
    std::cout << "Fecha de Ejecucion: " << fechaDeConsulta.toString() << std::endl << std::endl;
    for(int i=0; i<cantidadElementos; i++)
    {
        std::cout << vDispo[i].getPatenteDispo() << "   -   " << vDispo[i].getMarcaDispo() << "   -   " << vDispo[i].getModeloDispo() << "   -   " << vDispo[i].getAnioProduccionDispo() << "   -   " << vDispo[i].getEstadoVehiculoDispo() << "   -   " << vDispo[i].getTipoDispo() << std::endl << std::endl;
    }
}
