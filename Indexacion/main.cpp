#include "ArbolB+.h"
#include "arbolB.h"
#include "AnalizadorLexico.h"
#include "AnalizadorSintactico.h"
//#include "Fichero.h"
#include "Tabla.h"


int main(){

/*	AnalizadorLexico lex;
	ifstream texto("texto.txt");
	
	char cadena[100];
	int longitud;

	while(!texto.eof()){
		texto.getline(cadena,100);
		 longitud = strlen(cadena);

		 if(longitud>0)
			lex.automata((string)cadena,longitud);
	}

	Nodo* temp = lex.almacen.inicio;
	//if(seleccionar(temp)){
	if(seleccionar(temp)){
		cout <<"sis es un sentencia permitida  ";
	}
	else
		cout<<"jajaja";

	/*string nombreIV= "BaseDatos/salarios-direccion.txt";
	FicheroIndice f2;
	if(!f2.crear(nombreIV,3,15)){
		cout<<"aja";
	}*/

//	Tabla tabla;
//	tabla.cargar("salarios");
//	tabla.insertar("salarios",cad);

	/*char cad[58];
	tabla.crearTabla("salarios",cad);*/

	/*tabla.cargar("salarios");
	tabla.insertar("salarios",cad);*/

	//char cadena[80];
	//tabla.seleccionar("salarios","apellido",cadena);

	//tabla.crearIndice(1);

	//char cad[58];
	//tabla.crearTabla("salarios",cad);

	//tabla.insertar("salarios",cad);

	//tabla.seleccionar("pagos",cad);

	ArbolB a(4);

	bClaves b = {12,"abel"};

	a.insertar(b);

	bClaves b2 = {12,"stive"};

	a.insertar(b2);
	bClaves b3 = {12,"marco"};

	a.insertar(b3);
	bClaves b4 = {12,"jose"};

	a.insertar(b4);
	bClaves b5 = {12,"carlos"};

	a.insertar(b5);
	bClaves b6 = {12,"maria"};

	a.insertar(b6);

	bClaves b1 = {12,"abel"};

	a.insertar(b1);

	a.mostrarArbol();


	char c;
	cin>>c;

	return 0;

}
