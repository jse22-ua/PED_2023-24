#include "tvectorcalendario.h"

TVectorCalendario::TVectorCalendario(){
    this->c = NULL;
    this->tamano = 0;

}

TVectorCalendario::TVectorCalendario(int tamano){
    if(tamano<=0){
        this->c = NULL;
        this->tamano = 0;
    }else{
        this->tamano = tamano;
        this->c = new TCalendario[tamano];
    }

}

TVectorCalendario::TVectorCalendario(const TVectorCalendario& copia){
    this->tamano = copia.tamano;
    if(copia.c == NULL){
        this->c= NULL;
    }
    else{
        this->c = new TCalendario[this->tamano];
        for(int i=0; i< this->tamano;i++){
            this->c[i] = copia.c[i];
        }
    }
    
}

TVectorCalendario::~TVectorCalendario(){
    delete[] this->c;
    this->c = NULL;
    this->tamano = 0;

}

TVectorCalendario& TVectorCalendario::operator=(const TVectorCalendario& copia){
    if(this != &copia){
        (*this).~TVectorCalendario();
        this->tamano = copia.tamano;
        if(copia.c == NULL){
            this->c= NULL;
        }
        else{
            this->c = new TCalendario[this->tamano];
            for(int i=0; i< this->tamano;i++){
                this->c[i] = copia.c[i];
            }
        }        

    }

    return *this;
}

bool
TVectorCalendario::operator==(const TVectorCalendario& otro) const{
    if(this->tamano!= otro.tamano){
        return false;
    }
    for(int i=0; i<this->tamano; i++){
        if(this->c[i]!=otro.c[i]){
            return false;
        }
    }
    return true;

}


bool 
TVectorCalendario::operator!=(const TVectorCalendario& otro) const{
    return !(*this == otro);
}

TCalendario&
TVectorCalendario::operator[](int position){
    if(position < 0 || position > this->tamano){
        return error;
    }
    return this->c[position - 1];
    
}

TCalendario
TVectorCalendario::operator[](int position) const{
    if(position < 0 || position > this->tamano){
        return error;
    }
    return this->c[position - 1];
}
int
TVectorCalendario::Tamano() const{
    return this->tamano;
}
int
TVectorCalendario::Ocupadas(){
    int contador = 0;
    if(this->tamano != 0){
        for(int i=0; i<this->tamano;i++){
            if(!this->c[i].Esvacio()){
                contador++;
            }
        }
    }
    return contador;

}

bool      
TVectorCalendario::ExisteCal(const TCalendario& cal){

    for(int i=0; i<this->tamano;i++){
        if(this->c[i]== cal){
            return true;
        }
    }
    return false;
}

void 
TVectorCalendario::MostrarMensajes(int dia,int mes,int year){
    char fi[] = "";
    TCalendario temp(dia ,mes, year,fi);
    cout << "[";
    if(temp!=error){
        if(this->tamano!=0){
            for(int i=0; i < this->tamano; i++){
                if(this->c[i]==temp || this->c[i]>temp){
                    cout << this->c[i];
                    if(i != this->tamano - 1){
                        cout << ", ";
                    }
                }
            }
        }

    }
    cout << "]" << endl;

}

bool
TVectorCalendario::Redimensionar(int tam){
    if(tam<=0 || tam==this->tamano){
        return false;
    }

    TVectorCalendario aux(tam);
    int bucle = this->tamano;
    if(tam<this->tamano){
        bucle = tam;
    }
    for(int i=0; i<bucle;i++){
        aux.c[i] = this->c[i];
    }

    (*this).~TVectorCalendario();
    *this = aux;
    return true;
    
}

ostream& operator<<(ostream& os,const TVectorCalendario& vc){
    os << "[";
    if(vc.tamano != 0){
        for(int i = 0; i< vc.tamano; i++){
            os<< "(" << i+1 << ") " << vc.c[i];
            if(i != vc.tamano - 1){
                os << ", ";
            }
        }
    }
    os << "]";
    return os;
}