#ifndef H_AnalizadorS
#define H_AnalizadorS

#include <iostream>
#include <string>
#include "ListaDoble.h"

bool campos(Nodo *&temp){

	if(!temp->informacion.compare("*")){
		temp = temp->siguiente;
		return true;
	}
	while(temp != 0 && temp->token == IDE ){

		temp = temp->siguiente;
		if(temp !=0 && !temp->informacion.compare(","))
			temp = temp->siguiente;
		else
			return true;
	}
	temp = temp->anterior;
	return false;
}
bool camposP(Nodo *&temp){

	if(temp != 0 && !temp->informacion.compare("(")){
		temp = temp->siguiente;

		if(!temp->informacion.compare("*")){
			temp = temp->siguiente;
			return true;
		}
		while(temp != 0 && temp->token == IDE ){

			temp = temp->siguiente;
			if(temp !=0 && !temp->informacion.compare(","))
				temp = temp->siguiente;
			else
				if(!temp->informacion.compare(")")){
					temp = temp->siguiente;
						return true;
				}
		}
	}
	temp = temp->anterior;
	return false;
}
bool campos2(Nodo *&temp){

	while(temp != 0 && ( temp->token == CADE || temp->token == NUM )){

		temp = temp->siguiente;
		if(temp !=0 && !temp->informacion.compare(","))
			temp = temp->siguiente;
		else
			return true;
	}
	temp = temp->anterior;
	return false;
}

bool campos2P(Nodo *&temp){

	if(temp != 0 && !temp->informacion.compare("(")){
		temp = temp->siguiente;

		while(temp != 0 && ( temp->token == CADE || temp->token == NUM )){

			temp = temp->siguiente;
			if(temp !=0 && !temp->informacion.compare(","))
				temp = temp->siguiente;
			else
				if(!temp->informacion.compare(")")){
					temp = temp->siguiente;
					return true;
				}
		}
	}
	temp = temp->anterior;
	return false;
}
bool campoTamano(Nodo * & temp){

	if(temp != 0 && temp->token == IDE && temp->siguiente !=0 && temp->siguiente->token == RESER ){

		temp = temp->siguiente->siguiente;
		if(temp !=0 && !temp->informacion.compare("(") &&
			temp->siguiente !=0 && temp->siguiente->token == NUM &&
			temp->siguiente->siguiente !=0 && !temp->siguiente->siguiente->informacion.compare(")") ){
			
			temp = temp->siguiente->siguiente->siguiente;
			return true;
		}
	}
	
	return false;


}
bool campos3P(Nodo *&temp){

	if(temp != 0 && !temp->informacion.compare("(")){
		temp = temp->siguiente;

		while( campoTamano(temp) ){

			if(temp !=0 && !temp->informacion.compare(")") && temp->siguiente ==0){
				temp = temp->siguiente;
				return true;
			}
			if(temp!=0 && !temp->informacion.compare(",")){
				temp = temp->siguiente;
			}
		}
	}
	
	return false;
}
bool condicion(Nodo *&temp){

	if(!temp->informacion.compare("WHERE")){
		temp = temp->siguiente;
		if( temp!= 0 && temp->token == IDE && temp->siguiente !=0 && temp->siguiente->token == OpeC &&
			temp->siguiente->siguiente!=0 && (temp->siguiente->siguiente->token == CADE|| temp->siguiente->siguiente->token == NUM )){
				temp = temp->siguiente->siguiente->siguiente;

				return true;
		}
	}
	return false;
}
bool seleccionar(Nodo *& temp){

	if(!temp->informacion.compare("SELECT")){
		temp=temp->siguiente;

		if(campos(temp) && !temp->informacion.compare("FROM") ){

			temp = temp->siguiente;

			if(temp != 0 && temp->token  == IDE){
				temp = temp->siguiente;

				if(temp ==0)
					return true;

				if( condicion(temp))
					return true;
				else return false;
			}
			return false;
		}
	}
	return false;
}

bool insertar(Nodo *& temp){

	if(!temp->informacion.compare("INSERT") && !temp->siguiente->informacion.compare("INTO")){
		temp = temp->siguiente->siguiente;
		if(temp->token == IDE){
			temp = temp->siguiente;
			if(camposP(temp) && !temp->informacion.compare("VALUES")){
				temp = temp->siguiente;
				if(campos2P(temp))
					return true;			
			}
		}
	}

	return false;
}

bool crear(Nodo *& temp){

	if(!temp->informacion.compare("CREATE") && !temp->siguiente->informacion.compare("TABLE")){
		temp = temp->siguiente->siguiente;

		if(temp->token == IDE){
			temp = temp->siguiente;
			if(campos3P(temp) )
				return true;
		}
	}
	return false;
}

#endif