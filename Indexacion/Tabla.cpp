#include "Tabla.h"
#include "ArbolB.h"
#include <iostream>

using namespace std;

void Tabla::crearTabla(string nombre, char * cadena){

	ordenArbol = 4;

	FicheroDatos f;

	string nombreV = "BaseDatos/"+nombre+".txt";

	if(f.abrir(nombreV)){
		cout<<"error la tabla ya existe";
	}
	else{
		CampoDatos cd1(8);
		cd1 = "nombre";
		CampoDatos cd2(20);
		cd2 = "apellido";
		CampoDatos cd3(15);
		cd3 = "direccion";
		CampoDatos cd4(15);
		cd4 = "sexo";

		RegistroDatos rd(4,58);

		rd.a�adir(0,cd1);
		rd.a�adir(1,cd2);
		rd.a�adir(2,cd3);
		rd.a�adir(3,cd4);
			
		if(f.crear(nombreV,rd)){

			FicheroIndice f2;//(cadena2,3*encabezado.campos[columna].longitud);
			string nombreIV;

			for(int i=0;i<rd.numeroCampos;i++){

				 nombreIV= "BaseDatos/"+nombre+"-"+rd.campos[i].valor+".txt";
				 if(!f2.crear(nombreIV,ordenArbol-1,rd.campos[i].longitud)){

					 cout<<"ubo algun error";
					 return ;
				 }
			}

			cout<<"se creo satisfactoriamente";
		}
	}
}

void Tabla::insertar(string nombre, char * cad){

	FicheroDatos f;

	string nombreV = "BaseDatos/"+nombre+".txt";

	if(f.abrir(nombreV)){

		int tama�o ;

		f.leerTama�o(tama�o);

		int columnas;

		f.leerNumeroColumnas(columnas);

		char *cade= new char[tama�o];
		f.leerEncabezado(tama�o,cade);
	
		f.tamRegistro = tama�o;
		f.posInicial = 10 +tama�o;

		RegistroDatos registro(columnas,tama�o);

		CampoDatos c1 (8);
		c1 = "mama";

		CampoDatos c2 (20);
		c2 = "mama";

		CampoDatos c3 (15);
		c3 = "cornelio";

		CampoDatos c4 (15);
		c4 = "cornelio";

		registro.a�adir(0,c1);
		registro.a�adir(1,c2);
		registro.a�adir(2,c3);
		registro.a�adir(3,c4);

		f.insertar(registro);

		cout<<"se inserto correctamente";
	}
	else{
		cout<<"el archivo no existe";
	}
}
bool Tabla::cargar(string nombre){

	this->nombre = nombre;

	FicheroDatos f;


	string nombreV = "BaseDatos/"+nombre+".txt";

	if(f.abrir(nombreV)){

		
		ordenArbol = 4;
		int tama�o ;
		f.leerTama�o(tama�o);

		int columnas;
		f.leerNumeroColumnas(columnas);

		char *cade= new char[tama�o];
		f.leerEncabezado(tama�o,cade);

		RegistroDatos temp (columnas,tama�o,cade);

		encabezado = temp;

		return true;

	}
	return false;
}
void Tabla::seleccionar(string nombre,string nombreC ,char *cadena){

	if(cargar(nombre)){

		
		string nombreV = "BaseDatos/"+nombre+"-"+nombreC+".txt";

		FicheroIndice f;
	char ca[88];
		if(f.abrir(nombreV)){
			int numeroColumna;
			int anchoColumna=0;
			int raiz=0;

			f.leerEncabezado(numeroColumna,anchoColumna,raiz);

			f.tamRegistro = numeroColumna * (anchoColumna+sizeof(int)) +(sizeof(int)*(numeroColumna+1));
			

			f.leerRegistro(7,ca);

			int *pos = (int *)ca;

			Registro reg(numeroColumna,anchoColumna,f.tamRegistro,ca);

			f.leerRegistro2(reg.hijos[1],ca);

			FicheroDatos ff;

			ff.abrir("BaseDatos/salarios.txt");

			int tama�o ;

		ff.leerTama�o(tama�o);

		int columnas;

		ff.leerNumeroColumnas(columnas);

		char *cade= new char[tama�o];
		ff.leerEncabezado(tama�o,cade);
	
		ff.tamRegistro = tama�o;
		ff.posInicial = 10 +tama�o;
				
		ff.leerRegistro2(*pos,ca);

		cout<<"";

		}

		
		
	
		/*f.tamRegistro = encabezado.longitudFija-encabezado.numeroCampos*(sizeof(int));
		f.posInicial = 10 +encabezado.longitudFija;

		f.leerRegistro(2,cadena);*/
	}

}

void Tabla::crearIndice(int columna){

	string nombreV = "BaseDatos/"+nombre+".txt";

	FicheroDatos f;
	if(f.abrir(nombreV)){

		f.tamRegistro = encabezado.longitudFija;

		f.posInicial = 10 +encabezado.longitudFija;
	
		ArbolB a(ordenArbol);
		bClaves t ;
		char caden[80];
	
		for(int i =0;!f.f.eof() ; i++){

			f.leerRegistro(i,caden);

			RegistroDatos temporal(encabezado.numeroCampos,f.tamRegistro,caden);

			t.registro = (temporal.longitudFija+2)*i+f.posInicial;//dando la direcion fisica al fichero de indicees
			t.valor = temporal.campos[columna].valor;

			a.insertar(t);
		}
		a.mostrarArbol();

		string cadena2 = "BaseDatos/"+nombre+"-"+encabezado.campos[columna].valor+".txt";

		FicheroIndice f2;

		if(f2.abrir(cadena2)){

			f2.tamRegistro = ((encabezado.campos[columna].longitud +sizeof(int))*(ordenArbol-1))+sizeof(int)*ordenArbol;

			f2.f.seekp (8, ios::beg);

			f2.f.write(reinterpret_cast<char *>(&a.raiz->page), sizeof(int));

			int ref = ordenArbol-1;
			guardar(f2,a.raiz,ref,encabezado.campos[columna].longitud);

		}

	}

}

void guardarCampo(FicheroIndice &f,nodoB* n,int &numeroC,int &tama�oC){

	Campo campo;
	Registro registro(numeroC,f.tamRegistro);
	int i;
	for(i=0;i<n->clavesUsadas;i++){
		campo = Campo(tama�oC,n->claves[i].registro);
		campo = n->claves[i].valor.c_str();

		registro.a�adir(i,campo);
	}

	for(int k=i;k<registro.numeroCampos;k++){
		campo = Campo(tama�oC,0);
		registro.a�adir(k,campo);
	}

	
	int j;
	for(j=0;j<n->clavesUsadas+1;j++){
		if(!n->hijos[j])
			break;
		registro.hijos[j] = n->hijos[j]->page*(f.tamRegistro+2);
		
	}

	for(int k=j;k<registro.numeroCampos+1;k++){
		registro.hijos[k] = 0;
	}

	f.insertar(n->page,registro);
}

void guardar(FicheroIndice &f,nodoB *Act,int &numeroC,int&j){
	int i;
	
	if(!Act)return;
	guardarCampo(f,Act,numeroC,j);

	for(i=0;i<=Act->clavesUsadas;i++)
		guardar(f,Act->hijos[i],numeroC,j);
}