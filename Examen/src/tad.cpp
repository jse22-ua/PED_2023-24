#include <iostream>
#include "tabbcalendario.h"
#include "tcalendario.h"
#include "tlistacalendario.h"
#include "tvectorcalendario.h"

using namespace std;

int
main(void)
{
  TABBCalendario A; TListaCalendario L1,L2,L3; TVectorCalendario V; bool insertado;
  int resultado;
  TCalendario c;
  insertado = A.InsertarExamen(c,resultado);
  cout << resultado << endl;
  A.Clasificar(V,L1,L2,L3);
  cout << L1 << endl;
  cout << L2 << endl;
  cout << L3 << endl;
}
