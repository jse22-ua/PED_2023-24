#include "tavlcalendario.h"

TNodoAVL::TNodoAVL() {}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo)
{
    this->item = nodo.item;
    this->iz = nodo.iz;
    this->de = nodo.de;
}

TNodoAVL::~TNodoAVL()
{
    this->item.~TCalendario();
}

TNodoAVL &
TNodoAVL::operator=(const TNodoAVL &nodo)
{
    if (this != &nodo)
    {
        (*this).~TNodoAVL();
        this->item = nodo.item;
        this->iz = nodo.iz;
        this->de = nodo.de;
    }
    return *this;
}

void TAVLCalendario::InordenAux(TVectorCalendario &calvector, int &posicion) const
{
    if (!this->EsVacio())
    {
        this->raiz->iz.InordenAux(calvector, posicion);
        calvector[posicion] = this->raiz->item;
        posicion += 1;
        this->raiz->de.InordenAux(calvector, posicion);
    }
}

void TAVLCalendario::PreordenAux(TVectorCalendario &calvector, int &posicion) const
{
    if (!this->EsVacio())
    {
        calvector[posicion] = this->raiz->item;
        posicion += 1;
        this->raiz->iz.PreordenAux(calvector, posicion);
        this->raiz->de.PreordenAux(calvector, posicion);
    }
}
void TAVLCalendario::PostordenAux(TVectorCalendario &calvector, int &posicion) const
{
    if (!this->EsVacio())
    {
        this->raiz->iz.PostordenAux(calvector, posicion);
        this->raiz->de.PostordenAux(calvector, posicion);
        calvector[posicion] = this->raiz->item;
        posicion += 1;
    }
}

void TAVLCalendario::AuxiliarConstructor(const TAVLCalendario &copia)
{
    if (copia.EsVacio())
    {
        this->raiz = NULL;
    }
    else
    {
        TNodoAVL *aux = new TNodoAVL();
        aux->item = copia.raiz->item;
        this->raiz = aux;
        this->raiz->iz.AuxiliarConstructor(copia.raiz->iz);
        this->raiz->de.AuxiliarConstructor(copia.raiz->de);
    }
}

TAVLCalendario::TAVLCalendario()
{
    this->raiz = NULL;
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &arbol)
{
    AuxiliarConstructor(arbol);
}

TAVLCalendario::~TAVLCalendario()
{
    if (!EsVacio())
    {
        delete this->raiz;
        this->raiz = NULL;
    }
}

TAVLCalendario &
TAVLCalendario::operator=(const TAVLCalendario &arbol)
{
    if (this != &arbol)
    {
        (*this).~TAVLCalendario();
        AuxiliarConstructor(arbol);
    }
    return *this;
}

bool TAVLCalendario::operator==(const TAVLCalendario &arbol) const
{
    return this->Inorden() == arbol.Inorden();
}

bool TAVLCalendario::EsVacio() const
{
    if (this->raiz == NULL)
    {
        return true;
    }
    return false;
}

bool TAVLCalendario::Insertar(const TCalendario &calendario)
{
    if (this->Buscar(calendario))
    {
        return false;
    }
    if (this->EsVacio())
    {
        TNodoAVL *nuevo = new TNodoAVL();
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

TCalendario TAVLCalendario::getMayorIzquierda()
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

bool TAVLCalendario::Borrar(const TCalendario &calendario)
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

bool TAVLCalendario::Buscar(const TCalendario &calendario) const
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

TCalendario TAVLCalendario::Raiz() const
{
    TCalendario defecto;
    if (this->EsVacio())
    {
        return defecto;
    }
    return this->raiz->item;
}

int TAVLCalendario::Altura()
{
    if(this->EsVacio()){
        return 0;
    }
    return 1 + max(this->raiz->de.Altura(), this->raiz->iz.Altura());
}

int TAVLCalendario::Nodos() const
{
    if(this->EsVacio()){
        return 0;
    }
    return 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
}

int TAVLCalendario::NodosHoja()
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
TAVLCalendario::Inorden() const
{
    int posicion = 1;

    TVectorCalendario v(Nodos());
    InordenAux(v, posicion);
    return v;
}

TVectorCalendario
TAVLCalendario::Preorden()
{
    int posicion = 1;

    TVectorCalendario v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

TVectorCalendario
TAVLCalendario::Postorden()
{
    int posicion = 1;

    TVectorCalendario v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorCalendario
TAVLCalendario::Niveles() const
{
    queue<TNodoAVL*> cola;
    TVectorCalendario niveles(this->Nodos());
    if (!this->EsVacio())
    {
        int i = 1;
        cola.push(this->raiz);
        while (!cola.empty())
        {
            TNodoAVL* este = cola.front();
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


ostream &
operator<<(ostream &os, const TAVLCalendario &aux)
{
    os << aux.Inorden();
    return os;
}