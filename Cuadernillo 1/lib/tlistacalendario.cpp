#include "tlistacalendario.h"

TNodoCalendario::TNodoCalendario(){
    this->siguiente = NULL;

}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &nodo ){
    this->siguiente = nodo.siguiente;
    this->c = nodo.c;
}

TNodoCalendario::~TNodoCalendario(){
    c.~TCalendario();
    this->siguiente = NULL;

}

TNodoCalendario& 
TNodoCalendario::operator=(const TNodoCalendario &nodo){
    if(this!=&nodo){
        (*this).~TNodoCalendario();
        this->c = nodo.c;
        this->siguiente = nodo.siguiente;
    }
}

TListaPos::TListaPos(){
    pos = NULL;

}

TListaPos::TListaPos(const TListaPos &tlpos){
    this->pos = tlpos.pos;
}

TListaPos::~TListaPos(){
    this->pos = NULL;
}

TListaPos&
TListaPos::operator=(const TListaPos &tlpos){
    if(this != &tlpos){
        (*this).~TListaPos();
        this->pos = tlpos.pos;
    }
}

bool 
TListaPos::operator==(const TListaPos &tlpos){
    if(this->pos == tlpos.pos){
        return true;
    }else{
        return false;
    }
}

bool 
TListaPos::operator!=(const TListaPos &tlpos){
    if(this->pos == tlpos.pos){
        return false;
    }else{
        return true;
    }
}

TListaPos 
TListaPos::Siguiente(){
    TListaPos siguientepos;
    if(this->pos!= NULL && this->pos->siguiente != NULL){
        siguientepos.pos  = this->pos->siguiente;
    }
    return siguientepos;
}

bool
TListaPos::EsVacia(){
    if(this->pos == NULL){
        return true;
    }
    return false;
}

TListaCalendario::TListaCalendario(){
    this->primero = NULL;
}

TListaCalendario::TListaCalendario(const TListaCalendario &copia){
    this->primero = NULL;
    TListaPos aux;
    aux = copia.Primera();
    while(!aux.EsVacia()){
        this->Insertar(aux.pos->c);
        aux = aux.Siguiente();
    }
}

TListaCalendario::~TListaCalendario(){
    TListaPos aBorrar, aux;
    aux = Primera();
    while(!aux.EsVacia()){
        aux = aBorrar;
        aux = aux.Siguiente();
        aBorrar.~TListaPos();
    }
    this->primero = NULL;
}

TListaCalendario& 
TListaCalendario::operator=(const TListaCalendario &tlc){
    if(this != &tlc){
        (*this).~TListaCalendario();
        TListaPos aux;
        if(!this->EsVacia()){
            this->primero = tlc.primero;
            aux = tlc.Primera();
            while(!aux.EsVacia()){
                this->Insertar(aux.pos->c);
                aux = aux.Siguiente();
            }
        }
    }

    return *this;
}

bool 
TListaCalendario::operator==(const TListaCalendario &comp){
    if(this->Longitud() != comp.Longitud()){
        return false;
    }
    TListaPos este = this->Primera();
    TListaPos elOtro = comp.Primera();
    while(!este.EsVacia()){
        if(este.pos->c != elOtro.pos->c){
            return false;
        }
        este = este.Siguiente();
        elOtro = elOtro.Siguiente();
    }
    return true;
}

TListaCalendario
TListaCalendario::operator+(const TListaCalendario &tlc){
    TListaCalendario *respuesta = new TListaCalendario(*this);
    TListaPos este;
    este = tlc.Primera();
    
    while(!este.EsVacia()){
        respuesta->Insertar(este.pos->c);
        este = este.Siguiente();
    }

    return (*respuesta);
}

TListaCalendario 
TListaCalendario::operator-(const TListaCalendario &tlc){
    TListaCalendario res;
    TListaPos este;
    este = this->Primera();

    while(!este.EsVacia()){
        if(!tlc.Buscar(este.pos->c)){
            res.Insertar(este.pos->c);
        }
        este = este.Siguiente();
    }

    return res;

}

bool 
TListaCalendario::Insertar(TCalendario &){

}

bool 
TListaCalendario::Borrar(TCalendario &){

}

bool 
TListaCalendario::Borrar(int, int, int){

}

bool 
TListaCalendario::EsVacia() const{
    if(this->primero == NULL){
        return true;
    }
    return false;
}

TCalendario
TListaCalendario::Obtener(TListaPos &){

}

bool 
TListaCalendario::Buscar(const TCalendario& cal)const{
    TListaPos aux = this->Primera();
    while(!aux.EsVacia()){
        if(aux.pos->c == cal){
            return true;
        }
        aux = aux.Siguiente();
    }
    return false;
}

int 
TListaCalendario::Longitud() const{
    int count = 0;
    TListaPos aux; 
    aux = this->Primera();
    if(!EsVacia()){
        while(!aux.EsVacia()){
            count += 1;
            aux = aux.Siguiente();
        }
    }
    return count;
}

TListaPos 
TListaCalendario::Primera() const{
}

TListaPos 
TListaCalendario::Ultima(){

}

TListaCalendario 
TListaCalendario::SumarSubl(int I_L1, int F_L1, TListaCalendario& L2, int I_L2,int F_L2){

}
TListaCalendario 
TListaCalendario::ExtraerRango(int n1,int n2){

}