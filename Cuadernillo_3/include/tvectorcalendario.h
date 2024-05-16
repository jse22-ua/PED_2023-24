#ifndef __TVECTORCALENDARIO__
#define __TVECTORCALENDARIO__
#include <iostream>
#include "tcalendario.h"

using namespace std;

class TVectorCalendario{
    friend ostream& operator<<(ostream&,const TVectorCalendario&);

    public:
        TVectorCalendario();
        TVectorCalendario(int);
        TVectorCalendario(const TVectorCalendario&);
        ~TVectorCalendario();
        TVectorCalendario& operator=(const TVectorCalendario&);
        bool operator==(const TVectorCalendario&) const;
        bool operator!=(const TVectorCalendario&) const;
        TCalendario& operator[](int);
        TCalendario operator[](int) const;
        int Tamano() const;
        int Ocupadas();
        bool ExisteCal(const TCalendario&);
        void MostrarMensajes(int,int,int);
        bool Redimensionar(int);


    private:
        TCalendario *c;
        int tamano;
        TCalendario error;

};

#endif