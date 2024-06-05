#include "tabbcalendario.h"

TNodoABB::TNodoABB() {}

TNodoABB::TNodoABB(const TNodoABB &nodo)
{
    this->item = nodo.item;
    this->iz = nodo.iz;
    this->de = nodo.de;
}

TNodoABB::~TNodoABB()
{
    this->item.~TCalendario();
}

TNodoABB &
TNodoABB::operator=(const TNodoABB &nodo)
{
    if (this != &nodo)
    {
        (*this).~TNodoABB();
        this->item = nodo.item;
        this->iz = nodo.iz;
        this->de = nodo.de;
    }
    return *this;
}

void TABBCalendario::InordenAux(TVectorCalendario &calvector, int &posicion) const
{
    if (!this->EsVacio())
    {
        this->raiz->iz.InordenAux(calvector, posicion);
        calvector[posicion] = this->raiz->item;
        posicion += 1;
        this->raiz->de.InordenAux(calvector, posicion);
    }
}

void TABBCalendario::PreordenAux(TVectorCalendario &calvector, int &posicion) const
{
    if (!this->EsVacio())
    {
        calvector[posicion] = this->raiz->item;
        posicion += 1;
        this->raiz->iz.PreordenAux(calvector, posicion);
        this->raiz->de.PreordenAux(calvector, posicion);
    }
}
void TABBCalendario::PostordenAux(TVectorCalendario &calvector, int &posicion) const
{
    if (!this->EsVacio())
    {
        this->raiz->iz.PostordenAux(calvector, posicion);
        this->raiz->de.PostordenAux(calvector, posicion);
        calvector[posicion] = this->raiz->item;
        posicion += 1;
    }
}

void TABBCalendario::AuxiliarConstructor(const TABBCalendario &copia)
{
    if (copia.EsVacio())
    {
        this->raiz = NULL;
    }
    else
    {
        TNodoABB *aux = new TNodoABB();
        aux->item = copia.raiz->item;
        this->raiz = aux;
        this->raiz->iz.AuxiliarConstructor(copia.raiz->iz);
        this->raiz->de.AuxiliarConstructor(copia.raiz->de);
    }
}

TABBCalendario::TABBCalendario()
{
    this->raiz = NULL;
}

TABBCalendario::TABBCalendario(const TABBCalendario &arbol)
{
    AuxiliarConstructor(arbol);
}

TABBCalendario::~TABBCalendario()
{
    if (!EsVacio())
    {
        delete this->raiz;
        this->raiz = NULL;
    }
}

TABBCalendario &
TABBCalendario::operator=(const TABBCalendario &arbol)
{
    if (this != &arbol)
    {
        (*this).~TABBCalendario();
        AuxiliarConstructor(arbol);
    }
    return *this;
}

bool TABBCalendario::operator==(const TABBCalendario &arbol) const
{
    return this->Inorden() == arbol.Inorden();
}

bool TABBCalendario::EsVacio() const
{
    if (this->raiz == NULL)
    {
        return true;
    }
    return false;
}

bool TABBCalendario::Insertar(const TCalendario &calendario)
{
    if (this->Buscar(calendario))
    {
        return false;
    }
    if (this->EsVacio())
    {
        TNodoABB *nuevo = new TNodoABB();
        nuevo->item = calendario;
        this->raiz = nuevo;
    }
    else{
        if (calendario < this->raiz->item)
        {
            this->raiz->iz.Insertar(calendario);
        }
        else
        {
            this->raiz->de.Insertar(calendario);
        }
    }

    return true;
}

TCalendario TABBCalendario::getMayorIzquierda()
{
    TCalendario defecto;
    if (!EsVacio())
    {
        if (this->raiz->de.EsVacio())
        {
            return this->raiz->item;
        }
        else
        {
            return this->raiz->de.getMayorIzquierda();
        }
    }
    return defecto;
}

bool TABBCalendario::Borrar(const TCalendario &calendario)
{
    if (!this->Buscar(calendario))
    {
        return false;
    }
    else if (this->raiz->item == calendario)
    {
        if (this->raiz->de.EsVacio() && this->raiz->iz.EsVacio())
        {
            this->raiz = NULL;
            return true;
        }
        else if (!this->raiz->de.EsVacio() && this->raiz->iz.EsVacio())
        {
            this->raiz = this->raiz->de.raiz;
            return true;
        }
        else if (this->raiz->de.EsVacio() && !this->raiz->iz.EsVacio())
        {
            this->raiz = this->raiz->iz.raiz;
            return true;
        }
        else
        {
            TCalendario auxiliar = this->raiz->iz.getMayorIzquierda();
            this->raiz->item = auxiliar;
            this->raiz->iz.Borrar(auxiliar);
            return true;
        }
    }
    else
    {
        if (this->raiz->item < calendario)
        {
            return this->raiz->de.Borrar(calendario);
        }
        else
        {
            return this->raiz->iz.Borrar(calendario);
        }
    }
}

bool TABBCalendario::Buscar(const TCalendario &calendario) const
{
    if (this->EsVacio())
    {
        return false;
    }
    if (raiz->item == calendario)
    {
        return true;
    }
    return raiz->de.Buscar(calendario) || raiz->iz.Buscar(calendario);
}

TCalendario TABBCalendario::Raiz() const
{
    TCalendario defecto;
    if (this->EsVacio())
    {
        return defecto;
    }
    return this->raiz->item;
}

int TABBCalendario::Altura()
{
    if(this->EsVacio()){
        return 0;
    }
    return 1 + max(this->raiz->de.Altura(), this->raiz->iz.Altura());
}

int TABBCalendario::Nodos() const
{
    if(this->EsVacio()){
        return 0;
    }
    return 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
}

int TABBCalendario::NodosHoja()
{
    if(this->EsVacio()){
        return 0;
    }
    if (this->raiz->de.EsVacio() && this->raiz->iz.EsVacio())
    {
        return 1;
    }
    else
    {
        return this->raiz->de.NodosHoja() + this->raiz->iz.NodosHoja();
    }
}

TVectorCalendario
TABBCalendario::Inorden() const
{
    int posicion = 1;

    TVectorCalendario v(Nodos());
    InordenAux(v, posicion);
    return v;
}

TVectorCalendario
TABBCalendario::Preorden()
{
    int posicion = 1;

    TVectorCalendario v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorCalendario
TABBCalendario::Postorden()
{
    int posicion = 1;

    TVectorCalendario v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorCalendario
TABBCalendario::Niveles() const
{
    queue<TNodoABB*> cola;
    TVectorCalendario niveles(this->Nodos());
    if (!this->EsVacio())
    {
        int i = 1;
        cola.push(this->raiz);
        while (!cola.empty())
        {
            TNodoABB* este = cola.front();
            niveles[i] = este->item;
            cola.pop();

            if (!este->iz.EsVacio())
            {
                cola.push(este->iz.raiz);
            }
            if (!este->de.EsVacio())
            {
                cola.push(este->de.raiz);
            }
            i++;
        }
    }
    return niveles;
}

TABBCalendario
TABBCalendario::operator+(const TABBCalendario &otro)
{
    TABBCalendario copia(*this);
    TVectorCalendario inorden = otro.Inorden();

    for (int i = 0; i < inorden.Tamano(); i++)
    {
        copia.Insertar(inorden[i+1]);
    }

    return copia;
    
}

TABBCalendario
TABBCalendario::operator-(const TABBCalendario &otro)
{
    TABBCalendario copia;
    TVectorCalendario inorden = this->Inorden();

    for (int i = 0; i < inorden.Tamano(); i++)
    {
        if(!otro.Buscar(inorden[i+1])){
            copia.Insertar(inorden[i+1]);
        }
    }

    return copia;
}

ostream &
operator<<(ostream &os, const TABBCalendario &aux)
{
    os << aux.Niveles();
    return os;
}
