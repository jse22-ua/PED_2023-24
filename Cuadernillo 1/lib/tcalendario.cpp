#include "tcalendario.h"


const int TCalendario::NUMERODIAS[12]={
    31,28,31,30,31,30,31,31,30,31,30,31
    };

TCalendario::TCalendario()
{
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;
    this->mensaje = NULL;
}

bool TCalendario::esBisiesto(int year)
{
    if (year % 100 == 0)
    {
        return year % 400 == 0;
    }
    return year % 4 == 0;
}

bool TCalendario::CheckDate(int day, int month,int year)
{
    if (day <= 0 || day>31 || year<1900)
    {
        return false;
    }
    if(month<1 || month>12){
        return false;
    }
    if(month==4||month==6||month==9||month==11){
        if(day>30){
            return false;
        }
    }
    if(month==2){
        if(esBisiesto(year)){
            if(day>29){
                return false;
            }
        }
        else{
            if(day>28){
                return false;
            }
        }
    }
    return true;
    
}

TCalendario::TCalendario(int dia, int mes, int anyo, char *mens)
{
    if(CheckDate(dia,mes,anyo)){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;
        if(mens!=NULL){
            mensaje = new char[strlen(mens)+1];
            strcpy(mensaje,mens);
        }
        else{
            mensaje = mens;
        }
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
}

TCalendario::TCalendario(const TCalendario &cal)
{
    this->dia = cal.dia;
    this->mes = cal.mes;
    this->anyo = cal.anyo;
    if(cal.mensaje!=NULL){
        this->mensaje = new char[strlen(cal.mensaje)+1];
        strcpy(this->mensaje,cal.mensaje);
    }
    else{
        this->mensaje = cal.mensaje;
    }
}

TCalendario::~TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1990;
    mensaje =  NULL;
}

TCalendario &
TCalendario::operator=(const TCalendario &cal)
{
    if(this != &cal){
        (*this).~TCalendario();
        this->dia = cal.dia;
        this->mes = cal.mes;
        this->anyo = cal.anyo;
        if(cal.mensaje!=NULL){
            this->mensaje = new char[strlen(cal.mensaje)+1];
            strcpy(this->mensaje,cal.mensaje);
        }
        else{
            this->mensaje = cal.mensaje;
        }
    }
    return *this;
}

TCalendario
TCalendario::operator+(int days)
{   

    TCalendario copia(*this);
    int dias;
    if(days>0){
        while(days!=0){
            if(copia.mes==2 && esBisiesto(copia.anyo)){
                dias = 29;
            }
            else{
                dias = NUMERODIAS[copia.mes-1];
            }
            if(copia.dia+days>dias){
                int resto = dias - copia.dia + 1;
                copia.dia = 1;
                if(copia.mes!=12){
                    copia.mes += 1;
                }
                else{
                    copia.mes = 1;
                    copia.anyo += 1;
                }
                days -= resto;
            }
            else{
                copia.dia += days;
                days = 0;
            }
        }
    }
    return copia;
}

TCalendario
TCalendario::operator-(int days)
{
    TCalendario copia(*this);
    if(days>0){
        while(days!=0){
            if(days>=copia.dia){
                if(copia.mes==1 && copia.anyo==1900){
                    copia.dia = 1;
                    days =0;
                    if(copia.mensaje!=NULL){
                        delete[] copia.mensaje;
                        copia.mensaje = NULL;
                    }
                    
                }
                else{
                    if(copia.mes == 1){
                        copia.mes = 12;
                        copia.anyo -= 1;
                    }
                    else{
                        copia.mes -= 1;
                    }
                    if(copia.mes==2 && esBisiesto(copia.anyo)){
                        copia.dia = 29;
                    }
                    else{
                        copia.dia = NUMERODIAS[copia.mes-1];
                    }
    
                }

            }else{
                copia.dia -= days;
            }
        }
    }
    return copia;
}

TCalendario
TCalendario::operator++(int trampa)
{
    TCalendario temp(*this);
    int ultimodia;
    if(this->mes==2 && esBisiesto(this->anyo)){
        ultimodia=29;
    }
    else{
        ultimodia=NUMERODIAS[this->mes-1];
    }
    if(this->dia==ultimodia){
        if(this->mes==12){
            this->anyo+=1;
            this->mes = 1;
        }
        else{
            this->mes+=1;
        }
        this->dia=1;
        
    }
    else{
        this->dia+=1;
    }

    return temp;
}

TCalendario &
TCalendario::operator++()
{
    int ultimodia;
    if(this->mes==2 && esBisiesto(this->anyo)){
        ultimodia=29;
    }
    else{
        ultimodia=NUMERODIAS[this->mes-1];
    }
    if(this->dia==ultimodia){
        if(this->mes==12){
            this->anyo+=1;
            this->mes = 1;
        }
        else{
            this->mes+=1;
        }
        this->dia=1;
    }
    else{
        this->dia+=1;
    }

    return *this;
}

TCalendario
TCalendario::operator--(int trampa)
{
    TCalendario temp(*this);
    if(this->dia==1){
        if(this->mes==1){
            if(this->anyo==1900){
                if(temp.mensaje!=NULL){
                    delete[] temp.mensaje;
                    temp.mensaje = NULL;
                }
                return temp;
            }
            this->anyo-=1;
            this->mes=12;
        }
        else{
            this->mes-=1;
        }
        if(this->mes==2 && esBisiesto(this->anyo)){
            this->dia = 29;
        }
        else{
            this->dia = NUMERODIAS[this->mes-1];
        }
        
    }
    else{
        this->dia-=1;
    }
    return temp;
}

TCalendario &
TCalendario::operator--()
{
    if(this->dia==1){
        if(this->mes==1){
            if(this->anyo==1900){
                if(this->mensaje!=NULL){
                    delete[] this->mensaje;
                    this->mensaje = NULL;
                }
                return *this;
            }
            this->anyo-=1;
            this->mes=12;
        }
        else{
            this->mes-=1;
        }
        if(this->mes==2 && esBisiesto(this->anyo)){
            this->dia = 29;
        }
        else{
            this->dia = NUMERODIAS[this->mes-1];
        }
        
    }
    else{
        this->dia-=1;
    }
    return *this;
}

bool TCalendario::ModFecha(int day, int month, int year)
{
    if(CheckDate(day,month,year)){
        dia = day;
        mes = month;
        anyo = year;
        return true;
    }
    return false;
    
}

bool TCalendario::ModMensaje(char* mensaje)
{
    if(mensaje!=NULL){
        if(this->mensaje!=NULL){
            delete[] this->mensaje;
        }
        this->mensaje = new char[strlen(mensaje)+1];
        strcpy(this->mensaje,mensaje);
    }
    else{
        this->mensaje = NULL;
    }
    return true;

    
}

bool TCalendario::operator==(const TCalendario &cal)
{
    if(this->anyo==cal.anyo&&this->mes==cal.mes&&this->dia==cal.dia){
        if(this->mensaje==NULL && cal.mensaje==NULL){
            return true;
        }
        if(strlen(this->mensaje)==0&&strlen(cal.mensaje)==0){
            return true;
        }
        if(strcmp(this->mensaje,cal.mensaje)==0){
            return true;
        }
    }
    return false;
}

bool TCalendario::operator!=(const TCalendario &cal)
{
    return !(*this==cal);

}

bool TCalendario::operator>(const TCalendario &cal)
{
    if(this->anyo>cal.anyo){
        return true;
    }
    if(this->anyo==cal.anyo && this->mes>cal.mes){
        return true;
    }
    if(this->anyo==cal.anyo && this->mes==cal.mes && this->dia>cal.dia){
        return true;
    }
    if(this->mensaje!=NULL){
        if(cal.mensaje==NULL){
            return true;
        }
        if(strcmp(this->mensaje,cal.mensaje)>0){
            return true;
        }
    }
    return false;

}

bool TCalendario::operator<(const TCalendario &cal)
{
    if(this->anyo<cal.anyo){
        return true;
    }
    if(this->anyo==cal.anyo && this->mes<cal.mes){
        return true;
    }
    if(this->anyo==cal.anyo && this->mes==cal.mes && this->dia<cal.dia){
        return true;
    }
    if(cal.mensaje!=NULL){
        if(this->mensaje==NULL){
            return true;
        }
        if(strcmp(this->mensaje,cal.mensaje)<0){
            return true;
        }
    }
    return false;
    
}

bool TCalendario::Esvacio() const
{
    if(this->dia==1&&this->mes == 1 && this->anyo==1900&&this->mensaje==NULL){
        return true;
    }
    return false;
}
int TCalendario::Dia() const
{
    return dia;
}
int TCalendario::Mes() const
{
    return mes;
}
int TCalendario::Anyo() const
{
    return anyo;
}
char *
TCalendario::Mensaje() const
{
    return mensaje;
}

ostream &operator<<(ostream &os, const TCalendario &c)
{
    if(c.dia<10){
        os << "0";
    }
    os << c.dia << "/";
    if(c.mes<10){
        os << "0";
    }
    os << c.mes << "/" << c.anyo << " \"";

    if(c.mensaje != NULL){
        os << c.mensaje;
    }
    os << "\"";

    return os;
}