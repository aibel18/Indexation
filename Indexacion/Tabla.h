#include "Fichero.h"
#include "ArbolB.h"

void guardarCampo(FicheroIndice &f,nodoB* n,int &,int &j);
void guardar(FicheroIndice &f,nodoB *Act,int &,int&j);

class Tabla{
	RegistroDatos encabezado;
	string nombre;

	int ordenArbol;
public:
	void crearTabla(string, char*);
	bool cargar(string );
	void insertar(string, char*);
	void seleccionar(string,string, char*);
	void buscar(string, char*);
	void crearIndice(int);
};