#ifndef __TLISTACALENDARIO__
#define __TLISTACALENDARIO__
#include <iostream>
#include "tcalendario.h"

using namespace std;

class TNodoCalendario{
    friend class TListaCalendario;
    friend class TListaPos;
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
    friend class TListaCalendario;
    friend class TNodoCalendario;
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
    friend class TListaPos;
    friend class TNodoCalendario;
    friend ostream& operator<<(ostream &,const TListaCalendario&);
    public:
        TListaCalendario();
        TListaCalendario(const TListaCalendario &);
        ~TListaCalendario();
        TListaCalendario & operator=(const TListaCalendario &);
        bool operator==(const TListaCalendario&);
        TListaCalendario operator+(const TListaCalendario &);
        TListaCalendario operator-(const TListaCalendario &);
        bool Insertar(const TCalendario &);
        bool Borrar(const TCalendario &);
        bool Borrar(TListaPos &);
        bool Borrar(int, int, int);
        bool EsVacia() const;
        TCalendario Obtener(const TListaPos &)const ;
        bool Buscar(const TCalendario&) const;
        int Longitud() const;
        TListaPos Primera() const;
        TListaPos Ultima() const;
        TListaCalendario SumarSubl(int I_L1, int F_L1, TListaCalendario& L2, int I_L2,int F_L2);
        TListaCalendario ExtraerRango(int n1,int n2);
    private:
        TNodoCalendario *primero;

};

#endif