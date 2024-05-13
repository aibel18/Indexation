#include <string>
using namespace std;
struct bClave{
	int valor;
	long registro;
};

class nodoI{
private:
	string *claves;
	nodoI **hijos;
	int clavesUsadas;
public:
	int pagina;
	nodoI(int orden){
		claves=new string[orden-1];
		hijos=new nodoI*[orden];
		clavesUsadas=0;

		for(int i=0;i<orden;i++)
			hijos[i]=0;
	}
	~nodoI(){

		delete []claves;
		delete []hijos;
		claves=0;
		hijos=0;
	}
	bool nodoLleno(int);
	bool nodoVacio(int);
	void escribeNodo();
	
	friend class ArbolB;

};

class ArbolBp{
private:
	nodoI *raiz;
	int orden;
	bool encontrarNodo(nodoI *,bClave&, int *);
public:
	ArbolBp(){
		raiz =0;
		cont=0;
	}
	ArbolBp(int nEle){
		orden=nEle;
		raiz=0;
		cont=0;
	}
	~ArbolBp(){
		eliminarArbol(raiz);
	}
	int cont;
	nodoI* get();
	nodoI* encontrar(bClave&,int *pos,nodoI*Nodo=0, bool r=true);
	void insertar(bClave&);
	void push(nodoI *,bClave&,int*,bClave *,nodoI **);
	void putLeaf(nodoI *,bClave,nodoI*,int);
	void dividirNodo(nodoI *Act,bClave &cl,nodoI *rd,int k,bClave *clMedian,nodoI **newnode);
	void mostrarArbol(nodoI *Act=0,bool r=true);

	void eliminarArbol(nodoI*);
	
};