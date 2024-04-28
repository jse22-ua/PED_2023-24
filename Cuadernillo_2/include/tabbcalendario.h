#ifndef __TABBCALENDARIO__
#define __TABBCALENDARIO__
#include <iostream>
#include <queue>
#include <algorithm>
#include "tcalendario.h"
#include "tvectorcalendario.h"

using namespace std;

class TNodoABB;

class TABBCalendario{
    friend class TNodoABB;
    friend ostream & operator<<(ostream&, const TABBCalendario&);
    public:
        TABBCalendario();
        TABBCalendario(const TABBCalendario &);
        ~TABBCalendario();
        TABBCalendario & operator=(const TABBCalendario&);
        bool operator==(const TABBCalendario &) const;
        bool EsVacio() const;
        bool Insertar(const TCalendario &);
        bool Borrar(const TCalendario &);
        bool Buscar(const TCalendario &)const;
        TCalendario Raiz() const;
        int Altura();
        int Nodos() const;
        int NodosHoja();
        TVectorCalendario Inorden() const;
        TVectorCalendario Preorden();
        TVectorCalendario Postorden();
        TVectorCalendario Niveles()const ;
        TABBCalendario operator+(const TABBCalendario &);
        TABBCalendario operator-(const TABBCalendario &);
    private:
        TNodoABB *raiz;
        void AuxiliarConstructor(const TABBCalendario&);
        TCalendario getMayorIzquierda();
        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;

};

class TNodoABB{
    friend class TABBCalendario;
    public:
        TNodoABB();
        TNodoABB(const TNodoABB &);
        ~TNodoABB();
        TNodoABB & operator=(const TNodoABB &);

    private:
        TCalendario item;
        TABBCalendario iz, de;
};


#endif