#ifndef __TCALENDARIO__
#define __TCALENDARIO__
#include <iostream>
#include "string.h"

using namespace std;

class TCalendario{
    friend ostream &operator<<(ostream&, const TCalendario &);

    public:
        TCalendario();
        TCalendario(int dia, int mes, int anyo, char* mens);
        TCalendario(const TCalendario &);
        ~TCalendario();
        TCalendario &operator=(const TCalendario &);
        TCalendario operator+(int);
        TCalendario operator-(int);
        TCalendario operator++(int);
        TCalendario &operator++();
        TCalendario operator--(int);
        TCalendario &operator--();
        bool ModFecha(int,int,int);
        bool ModMensaje(char *);
        bool operator==(const TCalendario &);
        bool operator!=(const TCalendario &);
        bool operator>(const TCalendario &);
        bool operator<(const TCalendario &);
        bool Esvacio() const;
        int Dia() const;
        int Mes() const;
        int Anyo() const;
        char *Mensaje() const;


    private:
        int dia, mes, anyo;
        char* mensaje;
        bool esBisiesto(int);
        bool CheckDate(int, int,int);
        static const int NUMERODIAS[12];
};

#endif