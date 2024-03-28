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
        this->c = nodo.c;
        this->siguiente = nodo.siguiente;
    }
    return (*this);
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
        this->pos = tlpos.pos;
    }
    return (*this);
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
        aBorrar = aux;
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

        if(!tlc.EsVacia()){
            TNodoCalendario *auxiliar = new TNodoCalendario();
            auxiliar->c = tlc.primero->c;
            this->primero = auxiliar;
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
    TListaCalendario& respuesta = (*this);
    TListaPos este;
    este = tlc.Primera();
    
    while(!este.EsVacia()){
        respuesta.Insertar(este.pos->c);
        este = este.Siguiente();
    }

    return respuesta;
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
TListaCalendario::Insertar(const TCalendario &cal){
    TNodoCalendario *nuevo = new TNodoCalendario();
    nuevo->c = cal;
    if(this->Buscar(cal)){
        return false;
    }
    if(this->EsVacia()){
        this->primero = nuevo;
        return true;
    }
    TNodoCalendario *anterior = new TNodoCalendario();
    TListaPos aux;
    aux = this->Primera();
    anterior = aux.pos;
    while(!aux.EsVacia()){
        if(nuevo->c < aux.pos->c){
            nuevo->siguiente = anterior;
            if(aux.pos == this->Primera().pos){
                this->primero = nuevo;
            }
            else{
                anterior->siguiente = nuevo;
                nuevo->siguiente = aux.pos;
            }
            return true;
            
        }
        else{
            if(aux.pos->siguiente == NULL){
                aux.pos->siguiente = nuevo;
                return true;
            }
        }
        anterior = aux.pos;
        aux = aux.Siguiente();
    }
    return false;

}

bool 
TListaCalendario::Borrar(const TCalendario &cal){
    if(!this->Buscar(cal)){
        return false;
    }
    TNodoCalendario *este = new TNodoCalendario();
    TNodoCalendario *antes = new TNodoCalendario();
    TListaPos aux;

    aux = this->Primera();
    antes = aux.pos;
    while(!aux.EsVacia()){
        if(aux.pos->c == cal){
            este = aux.pos;
            if(cal == this->primero->c){
                this->primero = this->primero->siguiente;
                delete este;
            }else{
                antes->siguiente = este->siguiente;
                delete este;
            }
            return true;
        }

        antes = aux.pos;
        aux = aux.Siguiente();
    }

    return false;
    

}

bool 
TListaCalendario::Borrar(TListaPos &tpos){
    if(tpos.EsVacia()){
        return false;
    }
    return Borrar(tpos.pos->c);
}

bool 
TListaCalendario::Borrar(int day, int month, int year){
    TCalendario cal(day,month,year, (char*) "");
    TCalendario auxiliar;
    TNodoCalendario *este = new TNodoCalendario();
    TListaPos aux;
    int count = 0;
    aux = this->Primera();
    while(!aux.EsVacia()&&aux.pos->c<cal){
        if(aux.pos->c < cal){
            count +=1;
            auxiliar = aux.pos->c;
            aux = aux.Siguiente();
            this->Borrar(auxiliar);
        }else{
            aux = aux.Siguiente();  
        }
    }
    if(count== 0){
        return false;
    }
    return true;
}

bool 
TListaCalendario::EsVacia() const{
    if(this->primero == NULL){
        return true;
    }
    return false;
}

TCalendario
TListaCalendario::Obtener(const TListaPos &tpos) const{
    TListaPos aux = this->Primera();
    TCalendario cal;
    while(!aux.EsVacia()){
        if(aux == tpos){
            cal = tpos.pos->c;
            return cal;
        }
        aux = aux.Siguiente();
    }
    return cal;
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
    TListaPos primerPos;
    if(this->EsVacia()){
        return primerPos;
    }
    primerPos.pos = this->primero;
    return primerPos;
}

TListaPos 
TListaCalendario::Ultima() const{
    TListaPos ultimaPos, auxiliar; 
    if(this->EsVacia()){
        return ultimaPos;
    }
    ultimaPos = this->Primera();
    auxiliar = ultimaPos.Siguiente();
    while(!auxiliar.EsVacia()){
        ultimaPos = ultimaPos.Siguiente();
        auxiliar = ultimaPos.Siguiente();
        
    }
    return ultimaPos;
}

TListaCalendario 
TListaCalendario::SumarSubl(int I_L1, int F_L1, TListaCalendario& L2, int I_L2,int F_L2){
    TListaCalendario suma;
    if(I_L1<=F_L1){
        int fpos = F_L1;
        int ipos = I_L1;
        if(F_L1>this->Longitud()){
            fpos = this->Longitud();
        }
        if(I_L1<=0){
            ipos = 1;
        }
        TListaPos aux;
        aux = this->Primera();
        for(int i=1;i<=fpos;i++){
            if(i>=ipos){
                suma.Insertar(aux.pos->c);
            }
            aux = aux.Siguiente();
        }
    }
    if(I_L2<=F_L2){
        int fpos2 = F_L2;
        int ipos2 = I_L2;
        if(F_L2>L2.Longitud()){
            fpos2 = L2.Longitud();
        }
        if(I_L2<=0){
            ipos2 = 1;
        }
        TListaPos aux2;
        aux2 = L2.Primera();
        for(int i=1;i<=fpos2;i++){
            if(i>=ipos2){
                suma.Insertar(aux2.pos->c);
            }
            aux2 = aux2.Siguiente();
        }
    }
    return suma;

}

TListaCalendario 
TListaCalendario::ExtraerRango(int n1,int n2){
    TListaCalendario lista;
    if(n1>n2){
        return lista;
    }
    int ipos = n1;
    int fpos = n2;
    if(n1<=0){
        ipos = 1;
    }
    if(n2>this->Longitud()){
        fpos = this->Longitud();
    }
    TListaPos aux;
    aux = this->Primera();
    for (int i = 1; i < fpos; i++)
    {
        if(i>=ipos){
            lista.Insertar(aux.pos->c);
            this->Borrar(aux.pos->c);
        }
        aux = aux.Siguiente();
    }
    return lista;
}

ostream& operator<<(ostream &os,const TListaCalendario& cal){
    TListaPos aux;
    aux = cal.Primera();
    os << "<";

    while(!aux.EsVacia()){
        os << cal.Obtener(aux);
        if(aux != cal.Ultima()){
            os << " ";
        }
        aux = aux.Siguiente();
    }
    os << ">";
    return os;
}