#include "ArbolB+.h"
#include <iostream>
using namespace std;
bool nodoI::nodoLleno(int nEle){
	return (clavesUsadas==nEle);	
}

bool nodoI::nodoVacio(int nEle){
	return (clavesUsadas<nEle/2);
}

void nodoI::escribeNodo(){
	cout<<pagina<<"\t";
	for(int i=0;i<clavesUsadas;i++)
		cout<<claves[i]<<"  ";
	cout<<"\t\t";
	for(int j=0;j<clavesUsadas+1;j++)
		if((hijos[j]))
			cout<<(hijos[j])->pagina<<"  ";
	cout<<"\n";	
}