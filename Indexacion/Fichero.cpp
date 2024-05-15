#include "Fichero.h"

void convertirNumero(int *numero,char* cadena){

	int *numeros;
	numeros = (int*)(cadena);
	*numero = *numeros;

}

FicheroDatos::FicheroDatos(){
}
FicheroDatos::FicheroDatos(string fdatos){

	f.open(fdatos.c_str(),ios::in | ios::out);

	if (!f.is_open()){

		f.open(fdatos.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);
	}	
}
FicheroDatos::FicheroDatos(string fdatos,int l){

	tamRegistro = l;

	f.open(fdatos.c_str(),ios::in | ios::out);

	if (!f.is_open()){

		f.open(fdatos.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);
	}	
}

bool FicheroDatos::crear(string fdatos,RegistroDatos r){
	

	f.open(fdatos.c_str(),ios::in | ios::out);

	if (!f.is_open()){

		
		f.open(fdatos.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);

		f.seekp (0, ios::beg);

		tamRegistro = r.longitudFija+sizeof(int)*r.numeroCampos;

		f.write(reinterpret_cast<char *>(&tamRegistro), sizeof(int));
		f.write(reinterpret_cast<char *>(&r.numeroCampos), sizeof(int));

		for(int i=0;i<r.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&r.campos[i].longitud), sizeof(int));
			f.write(reinterpret_cast<char *>(r.campos[i].valor), r.campos[i].longitud);
		}

		f.write("\n",1);	
		
		f.close();
		return true;
	}
	

	return false;
}
bool FicheroDatos::abrir(string fdatos){

	f.open(fdatos.c_str(),ios::in | ios::out);

	if (f.is_open())
		return true;

	return false;
}
void FicheroDatos::insertar(RegistroDatos & nuevo){
	if(f.is_open()){
		f.seekp (0, ios::end);

		for(int i=0;i<nuevo.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&nuevo.campos[i].longitud), sizeof(int));
			f.write(reinterpret_cast<char *>(nuevo.campos[i].valor), nuevo.campos[i].longitud);
		}

		f.write("\n",1);		
	}	
}
void FicheroDatos::insertar(int posR,int posC,RegistroDatos & nuevo){
	if(f.is_open()){

		int pos=0;
		for(int i=0; i<posC;i++){
			pos =pos + nuevo.campos[i].longitud;
		}
		f.seekp ((nuevo.longitudFija+2)*posR +pos+posInicial, ios::beg);
		f.write(reinterpret_cast<char *>(nuevo.campos[posC].valor), nuevo.campos[posC].longitud);
	
	}	
}
void FicheroDatos::leerRegistro(unsigned long pos,char* cadena){
	if(f.is_open()){
		
		f.seekg ((tamRegistro+2)*pos+posInicial, ios::beg);
		f.read(reinterpret_cast<char *>(cadena), tamRegistro);
	}	
}
void FicheroDatos::leerRegistro2(unsigned long pos,char* cadena){
	if(f.is_open()){
		
		f.seekg (pos, ios::beg);
		f.read(reinterpret_cast<char *>(cadena), tamRegistro);
	}	
}
void FicheroDatos::leerRegistro(unsigned long pos,RegistroDatos & nuevo){
	if(f.is_open()){
		f.seekg ((nuevo.longitudFija +2)*pos+posInicial, ios::beg);
		f.read(reinterpret_cast<char *>(&nuevo), nuevo.longitudFija );
	}	
}

void FicheroDatos::leerTamano(int &tamano){
	if(f.is_open()){
		f.seekg (0, ios::beg);
		f.read(reinterpret_cast<char *>(&tamano), sizeof(int) );
	}	
}
void FicheroDatos::leerNumeroColumnas(int &columnas){
	if(f.is_open()){
		f.seekg (4, ios::beg);
		f.read(reinterpret_cast<char *>(&columnas), sizeof(int) );
	}	
}
void FicheroDatos::leerEncabezado(int tamano,char* cadena){
	if(f.is_open()){
		f.seekg (8, ios::beg);
		f.read(reinterpret_cast<char *>(cadena), tamano );
	}	
}
FicheroDatos::~FicheroDatos(){
	if(f.is_open())
		f.close();
}






//fichero indices--------------
FicheroIndice::FicheroIndice(string fdatos,unsigned int tam){

	f.open(fdatos.c_str(),ios::in | ios::out);
	tamRegistro = tam;

	if (!f.is_open()){
		f.open(fdatos.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);
	}	
}

bool FicheroIndice::crear(string fdatos, int columnas, int tamanoC){
	
	f.open(fdatos.c_str(),ios::in | ios::out);

	if (!f.is_open()){
		
		f.open(fdatos.c_str(),ios::in | ios::out | ios::trunc);
		f.seekg (0, ios::beg);
		tamRegistro = (sizeof(int)+tamanoC)*columnas;

		f.write(reinterpret_cast<char *>(&columnas), sizeof(int));
		f.write(reinterpret_cast<char *>(&tamanoC), sizeof(int));

		int raiz;
		f.write(reinterpret_cast<char *>(&raiz), sizeof(int));

		f.write("\n",1);	
		
		f.close();
		return true;
	}

	return false;
}

bool FicheroIndice::abrir(string fdatos){

	f.open(fdatos.c_str(),ios::in | ios::out);

	if (f.is_open())
		return true;

	return false;
}

void FicheroIndice::insertar(Registro & nuevo){
	if(f.is_open()){

		f.seekp (14, ios::end);

		//f.write(reinterpret_cast<char *>(&nuevo.longitudFija), sizeof(int));
		
		for(int i=0;i<nuevo.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&nuevo.campos[i].direccion), sizeof(int));
			f.write(reinterpret_cast<char *>(nuevo.campos[i].valor), nuevo.campos[i].longitud);		
		}
		for(int i=0;i<nuevo.numeroCampos+1;i++){
			f.write(reinterpret_cast<char *>(&nuevo.hijos[i]), sizeof(int));
		}
		f.write("\n",1);		
	}	
}
void FicheroIndice::insertar(int posR,Registro & nuevo){
	if(f.is_open()){

		f.seekp ((nuevo.longitudFija+2)*posR+14, ios::beg);
		
		for(int i=0;i<nuevo.numeroCampos;i++){
			f.write(reinterpret_cast<char *>(&nuevo.campos[i].direccion), sizeof(int));
			f.write(reinterpret_cast<char *>(nuevo.campos[i].valor), nuevo.campos[i].longitud);		
		}
		for(int i=0;i<nuevo.numeroCampos+1;i++){
			f.write(reinterpret_cast<char *>(&nuevo.hijos[i]), sizeof(int));
		}
		f.write("\n",1);		
	}	
}
void FicheroIndice::insertar(int posR,int posC,Registro& nuevo){

	int pos=0;
	for(int i=0; i<posC;i++){
		pos =pos+ 4 + nuevo.campos[i].longitud;
	}

	f.seekp ((nuevo.longitudFija+2)*posR + pos +14, ios::beg);

	f.write(reinterpret_cast<char *>(&nuevo.campos[posC].direccion), sizeof(int));
	f.write(reinterpret_cast<char *>(nuevo.campos[posC].valor), nuevo.campos[posC].longitud);

}

void FicheroIndice::enter(){
	if(f.is_open()){
		f.seekp (0, ios::end);
		f.write("\n",1);		
	}	
}
void FicheroIndice::leerRegistro(unsigned long pos,char* cadena){
	if(f.is_open()){
		
		//f.seekg ((sizeof(int)*3+tamRegistro+2)*pos, ios::beg);
		f.seekg ((tamRegistro+2)*pos+14, ios::beg);
		//f.read(reinterpret_cast<char *>(cadena), sizeof(int)*4+tamRegistro);
		f.read(reinterpret_cast<char *>(cadena),tamRegistro);
	}	
}
void FicheroIndice::leerRegistro2(unsigned long pos,char* cadena){
	if(f.is_open()){
		
		f.seekg (pos+14, ios::beg);
		f.read(reinterpret_cast<char *>(cadena),tamRegistro);
	}	
}
void FicheroIndice::leerEncabezado(int &columnas,int &tamano,int &raiz){

	if(f.is_open()){
		f.seekg (0, ios::beg);
		f.read(reinterpret_cast<char *>(&columnas), sizeof(int) );
		f.seekg (4, ios::beg);
		f.read(reinterpret_cast<char *>(&tamano), sizeof(int) );
		f.seekg (8, ios::beg);
		f.read(reinterpret_cast<char *>(&raiz), sizeof(int) );
	}	
}

FicheroIndice::~FicheroIndice(){
	if(f.is_open())
		f.close();
}

