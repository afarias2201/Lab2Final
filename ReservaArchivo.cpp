#include "ReservaArchivo.h"

ReservaArchivo::ReservaArchivo(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ReservaArchivo::Guardar(Reserva reg){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if(p == nullptr){
        return false;
    }
    pudoEscribir = fwrite(&reg, sizeof(Reserva), 1, p);
    fclose(p);
    return pudoEscribir;
}

bool ReservaArchivo::Guardar(Reserva reg, int nroRegistro){
    bool pudoEscribir;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if(p == nullptr){
        return false;
    }
    fseek(p, nroRegistro * sizeof(Reserva), SEEK_SET);
    pudoEscribir = fwrite(&reg, sizeof(Reserva), 1, p);
    fclose(p);
    return pudoEscribir;
}

int ReservaArchivo::contarRegistros(){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return 0;
    }
        fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Reserva);
}

Reserva ReservaArchivo::Leer(int nroRegistro){
    Reserva reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return reg;
    }
    fseek(p, nroRegistro * sizeof(Reserva), SEEK_SET);
    fread(&reg, sizeof(Reserva), 1, p);
    fclose(p);
    return reg;
}

int ReservaArchivo::Buscar(int idReserva){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr){
    return -1;
    }
    int i = 0;
    Reserva reg;
    while(fread(&reg, sizeof(Reserva), 1, p)){
    if(reg.getIdReserva() == idReserva){
        fclose(p);
        return i;
    }
    i++;
    }
    fclose(p);
    return -1;
}
