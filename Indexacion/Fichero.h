#ifndef Fichero_H
#define Fichero_H

#include <fstream>
#include <String>
using namespace std;

void convertirNumero(int *numero,char* cadena);

class CampoDatos{
public:
	int longitud;
	char *valor;
	CampoDatos(){}
	CampoDatos(int longitud){
		this->longitud = longitud;

		valor = new char[longitud];
	
		for(int i=0;i<longitud;i++){
			valor[i] = 0;
		}
		valor [longitud] = '\0';
	}
	~CampoDatos(){
		valor =0;
	}

	void operator = (char *cadena){

		int longitud  = strlen(cadena);
		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
};

class RegistroDatos{
public:
	int longitudFija;
	int numeroCampos;
	CampoDatos* campos;

	RegistroDatos(){}
	RegistroDatos(int numC,int longitud){

		longitudFija = longitud ;
		numeroCampos = numC;
		campos = new CampoDatos[numC];
	}
	RegistroDatos(int numC,int longitud,char* cadena){

		longitudFija = longitud ;
		numeroCampos = numC;
		campos = new CampoDatos[numC];

		int longitudColumna=0;
		for(int i=0; i<numC;i++){

			convertirNumero(&longitudColumna ,cadena);
			cadena = cadena +sizeof(int);

			CampoDatos temp(longitudColumna);
			temp = cadena;//asignado el valor a temp
			
			añadir(i,temp);
			
			cadena = cadena + longitudColumna;
		}
	}

	void añadir(int i,CampoDatos campo){
		campos[i] = campo;
	}
	~RegistroDatos(){
		campos = 0;
	}
};

class FicheroDatos {
public: fstream f; // Stream para E/S al fichero
	unsigned int tamRegistro;
	int posInicial;
public:
	FicheroDatos();//{}
	FicheroDatos(string fdatos);
	FicheroDatos(string fdatos,int);

	bool abrir(string);

	bool crear(string fdatos,RegistroDatos);

	~FicheroDatos(); // Cierra el fichero
	void insertar(RegistroDatos &nuevoreg);
	void insertar(int ,int,RegistroDatos &nuevoreg);
	void leerRegistro(unsigned long pos, RegistroDatos &reg);
	void leerRegistro(unsigned long pos,char* cadena);
	void leerRegistro2(unsigned long pos,char* cadena);

	void leerTamaño(int &);
	void leerNumeroColumnas(int &);
	void leerEncabezado(int,char*);

	void eliminarRegistro(unsigned long pos);	
	void actualizar(unsigned long pos, const RegistroDatos &nuevoreg);
	void compactar(); // Eliminar físicamente los borrados
	void vaciar(); // Eliminar todos los registros
};

class Campo{
public:
	int direccion;
	int longitud;
	char *valor;
	Campo(){}
	Campo(int longitud,int direccion){
		this->longitud = longitud;
		this->direccion = direccion;
		valor = new char[longitud];
	
		for(int i=0;i<longitud;i++){
			valor[i] = 0;
		}
		valor [longitud] = '\0';
	}

	~Campo(){
		valor =0;
	}

	void operator = (char *cadena){

		int longitud  = strlen(cadena);
		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
	void operator = (const char *cadena){

		int longitud  = strlen(cadena);
		for(int i=0;i<longitud;i++){
			valor[i] = cadena[i];
		}
		valor[longitud] = '\0';
	}
};



class Registro{
public:
	int longitudFija;
	int numeroCampos;
	Campo* campos;
	int * hijos;

	Registro(){}
	Registro(int numC,int longitud){

		longitudFija = longitud;
		numeroCampos = numC;
		campos = new Campo[numC];
		hijos = new int[numC+1];
	}

	Registro(int numC,int longitudC,int longitud,char* cadena){

		longitudFija = longitud ;
		numeroCampos = numC;
		campos = new Campo[numC];
		hijos = new int[numC+1];

		int direccionC =0;
		for(int i=0; i<numC;i++){

			convertirNumero(&direccionC ,cadena);
			cadena = cadena +sizeof(int);

			Campo temp(longitudC,direccionC);
			temp = cadena; //asignando el valor a temp
			
			añadir(i,temp);
			
			cadena = cadena + longitudC;
		}
		int direccionH =0;
		for(int i=0; i<numC+1;i++){

			convertirNumero(&direccionH ,cadena);
			cadena = cadena +sizeof(int);

			hijos[i] = direccionH;			
		}
	}

	void añadir(int i,Campo campo){
		campos[i] = campo;
	}
	~Registro(){
		campos = 0;
	}
};

class FicheroIndice {
public: fstream f; // Stream para E/S al fichero
	unsigned int tamRegistro;
	unsigned int posInicial;
	
public:
	FicheroIndice(){}
	FicheroIndice(string fdatos,unsigned int );

	bool abrir(string);

	~FicheroIndice(); // Cierra el fichero

	bool crear(string fdatos,int,int);

	void leerEncabezado(int&,int&,int&);

	void insertar(Registro &nuevoReg);
	void insertar(int ,Registro &nuevoReg);
	void insertar(int posR,int posC,Registro &nuevoReg);
	void enter();
	//void leerRegistro(unsigned long pos, Registro *&reg,int);

	//lee el reistro indices con una posicion logica
	void leerRegistro(unsigned long pos, char*);

	//lee el registro con una posicion fisica
	void leerRegistro2(unsigned long pos, char*);
	void eliminarRegistro(unsigned long pos);
	void actualizar(unsigned long pos, const Registro &nuevoreg);
	void compactar(); // Eliminar físicamente los borrados
	void vaciar(); // Eliminar todos los registros
};

#endif