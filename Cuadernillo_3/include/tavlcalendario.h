#ifndef __TAVLCALENDARIO__
#define __TAVLCALENDARIO__
#include <iostream>
#include <queue>
#include <algorithm>
#include "tcalendario.h"
#include "tvectorcalendario.h"

using namespace std;

class TNodoAVL;

class TAVLCalendario{
    friend class TNodoABB;
    friend ostream & operator<<(ostream&, const TAVLCalendario&);
    public:
        TAVLCalendario();
        TAVLCalendario(const TAVLCalendario &);
        ~TAVLCalendario();
        TAVLCalendario & operator=(const TAVLCalendario&);
        bool operator==(const TAVLCalendario &) const;
        bool operator!=(const TAVLCalendario &) const;
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
    private:
        TNodoAVL *raiz;
        void AuxiliarConstructor(const TAVLCalendario&);
        TCalendario getMayorIzquierda();
        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;

};

class TNodoAVL{
    friend class TAVLCalendario;
    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);

    private:
        TCalendario item;
        TAVLCalendario iz, de;
        int fe;
};


#endif