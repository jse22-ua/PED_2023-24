#ifndef __TLISTACALENDARIO__
#define __TLISTACALENDARIO__
#include <iostream>
#include "tcalendario.h"

using namespace std;

class TNodoCalendario{
    friend TListaCalendario;
    friend TListaPos;
    public:
        TNodoCalendario();
        TNodoCalendario(const TNodoCalendario &);
        ~TNodoCalendario();
        TNodoCalendario& operator=(const TNodoCalendario&);
        
    private:
        TCalendario c;
        TNodoCalendario * siguiente;
};

class TListaPos{
    friend TListaCalendario;
    friend TNodoCalendario;
    public:
        TListaPos();
        TListaPos(const TListaPos &);
        ~TListaPos();
        TListaPos & operator=(const TListaPos &);
        bool operator==(const TListaPos &);
        bool operator!=(const TListaPos &);
        TListaPos Siguiente();
        bool EsVacia();
    private:
        TNodoCalendario *pos;
};

class TListaCalendario{
    friend TListaPos;
    friend TNodoCalendario;
    friend ostream& operator<<(ostream &, TListaCalendario&);
    public:
        TListaCalendario();
        TListaCalendario(const TListaCalendario &);
        ~TListaCalendario();
        TListaCalendario & operator=(const TListaCalendario &);
        bool operator==(const TListaCalendario&);
        TListaCalendario operator+(const TListaCalendario &);
        TListaCalendario operator-(const TListaCalendario &);
        bool Insertar(TCalendario &);
        bool Borrar(TCalendario &);
        bool Borrar(int, int, int);
        bool EsVacia() const;
        TCalendario Obtener(TListaPos &);
        bool Buscar(const TCalendario&) const;
        int Longitud() const;
        TListaPos Primera() const;
        TListaPos Ultima();
        TListaCalendario SumarSubl(int I_L1, int F_L1, TListaCalendario& L2, int I_L2,int F_L2);
        TListaCalendario ExtraerRango(int n1,int n2);
    private:
        TNodoCalendario *primero;

};

#endif