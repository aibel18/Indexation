#include "AnalizadorLexico.h"

char bancoOperadore[] = { '<' , '>' , '=' ,
							',' , ';' , '(' , ')','*'};

string bancoReservada[] = {"CREATE","DROP","SELECT","INSERT","UPDATE","DELETE","FROM","WHERE",
							"VALUES","INTO","ORDER","BY","TABLE","text","int"};

bool caracter(char carac){
	if( carac >= 'a' && carac <='z')
		return true;
	else
		return false;
}
bool caracterM(char carac){
	if( carac >= 'A' && carac <='Z')
		return true;
	else
		return false;
}
bool digito(char carac){
	if( carac >= '0' && carac <='9')
		return true;
	else
		return false;
}
AnalizadorLexico::AnalizadorLexico(){
	cargarReservadas();
	cargarOperadores();
}
AnalizadorLexico::~AnalizadorLexico(){
	almacen.eliminarLista(almacen.inicio);
}

void AnalizadorLexico::reiniciarAlmacen(){
	almacen.eliminarLista(almacen.inicio);
	almacen.inicio=0;
	almacen.final=0;
	almacen.numNodos =0;
}

void AnalizadorLexico::cargarReservadas(){
	int i=0;
	while(i < numRes){
		bancoReservadas[i] = bancoReservada[i];
		i++;
	}
}
void AnalizadorLexico::cargarOperadores(){

	int i=0;
	while(i < numOpe){
		bancoOperadores[i] = bancoOperadore[i];
		i++;
	}
}

void AnalizadorLexico::automata(string &cadena,int _largo){
	int i=0;
	int temp =0;
	int largo = _largo;
	string contenido;
	while(i<largo){

		temp = i;
		if(cadena[i]==' '|| cadena[i]=='\t')
			i++;	
		else if( buscaReservada(cadena,i)){
			contenido = cadena.substr(temp,i-temp);
			cout<<contenido<<"\t\t: es una palabra reservada\n";
			almacen.ingresar(contenido,RESER);
		}
		else if( buscaIdentificador(cadena,i) ){
			contenido = cadena.substr(temp,i-temp);
			cout<<contenido<<"  \t\t: es identificador\n";
			almacen.ingresar(contenido,IDE);
		}
			
		else if( buscaNumero( cadena,i ) ){
			contenido = cadena.substr(temp,i-temp);
			cout<<contenido<<"\t\t: es numero\n";
			almacen.ingresar(contenido,NUM);
		}
		else{
			if( int a =buscaOperador(cadena,i)){
				contenido = cadena.substr(temp,i-temp);
				cout<<contenido<<"\t\t: es un operador\t\t"<<a<<"\n";
				almacen.ingresar(contenido,a);
			}

			else if( buscaCadena(cadena,i) ){
				contenido = cadena.substr(temp,i-temp);
				
				cout<<contenido<<"\t\t: es una cadena decaracteres\n";
				almacen.ingresar(contenido,CADE);
			}
			
			else{
				contenido = cadena.substr(temp,i-temp);
				cout<<contenido<<"\t\t: no pertece a este lenguaje\n";
				i++;
			}
		}		
	}

}
bool AnalizadorLexico::automata2(string &cadena,int _largo){
	int i=0;
	int temp =0;
	int largo = _largo;
	string contenido;
	while(i<largo){

		temp = i;
		if(cadena[i]==' '|| cadena[i]=='\t')
			i++;	
		else if( buscaReservada(cadena,i)){
			contenido = cadena.substr(temp,i-temp);
			cout<<contenido<<"\t\t: es una palabra reservada\n";
			almacen.ingresar(contenido,RESER);
		}
		else if( buscaIdentificador(cadena,i) ){
			contenido = cadena.substr(temp,i-temp);
			cout<<contenido<<"  \t\t: es identificador\n";
			almacen.ingresar(contenido,IDE);
		}
			
		else if( buscaNumero( cadena,i ) ){
			contenido = cadena.substr(temp,i-temp);
			cout<<contenido<<"\t\t: es numero\n";
			almacen.ingresar(contenido,NUM);
		}
		else{
			if( int a =buscaOperador(cadena,i)){
				contenido = cadena.substr(temp,i-temp);
				cout<<contenido<<"\t\t: es un operador\t\t"<<a<<"\n";
				almacen.ingresar(contenido,a);
			}

			else if( buscaCadena(cadena,i) ){
				contenido = cadena.substr(temp,i-temp);
				
				cout<<contenido<<"\t\t: es una cadena decaracteres\n";
				almacen.ingresar(contenido,CADE);
			}
			
			else{
				contenido = cadena.substr(temp,i-temp);
				cout<<contenido<<"\t\t: no pertece a este lenguaje\n";
				i++;
				return false;
			}
		}		
	}
	return true;

}
bool AnalizadorLexico::buscaCadena(string &cadena,int &pos){
	
	int i= pos;

	int largo = cadena.size();

	if(cadena[pos] == 39){
		pos++;
		while( pos< largo ){

			if(cadena[pos] == 39){
				pos++;
				return true;
			}
			pos++;
		}
		pos = i;
		return false;
	}
	else{
		pos = i;
		return false;
	}
}
bool AnalizadorLexico::buscaNumero(string &cadena,int &pos){

	int i=pos;
	int contador =0;
	char temp = cadena[pos];
	while(digito(temp)){
		pos++;
		contador++;
		temp = cadena[pos];
	}
	if( temp == '.'){
		pos++;
		temp = cadena[pos];
		while(digito(temp)){
			pos++;
			temp = cadena[pos];
		}
	}
	if(contador>0)
		return true;
	else{
		pos = i;
		return false;
	}
}
bool AnalizadorLexico::buscaIdentificador(string &cadena,int &pos){

	int i=pos;
	if(caracter(cadena[pos]) || caracterM(cadena[pos]) || cadena[pos] == '_'){
		pos++;

		while( caracter(cadena[pos]) || caracterM(cadena[pos]) || digito(cadena[pos]) ){
			pos++;
		}
		return true;
	}
	else{
		pos = i;
		return false;
	}
}

bool AnalizadorLexico::buscaReservada(string &cadena,int &pos){
	
	int contador = pos;
	int largo = cadena.size();
	while(pos<largo){
		if(cadena[pos]== ' ' || cadena[pos] == '(' || cadena[pos] == ';' || cadena[pos] == '\0')
			break;
		pos++;
	}
	string temp = cadena.substr(contador,pos-contador);
	unsigned int j=0;
	while(j < temp.size() && ( caracterM(temp[j]) || caracter(temp[j]) ) )
			j++;

	if(j == temp.size()){
		int i=0;
		while( i< numRes ){

			if(!temp.compare(bancoReservadas[i]))
				 return true;
			i++;
		}
		pos = contador;
		return false;
		
	}
	else{
		pos = contador;

		return false;
	}
}

int AnalizadorLexico::buscaOperador(string &cadena,int &pos){

	int i=0;
	for(;i<numOpe;i++){

		if(cadena[pos] == bancoOperadores[i]){
			pos++;
			if(cadena[pos]== '=' ){

				if(i<2){
					pos++;
					return OpeC;
				}
				
			}
			else if(cadena[pos]== '>'){
				if(i<1){
					pos++;
					return OpeC;
				}
			}
			else if(i<3  ){
				return OpeC;
			}
			return OpeO;
		}
	}
	return false;

}