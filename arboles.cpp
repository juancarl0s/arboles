#include <stdio.h>  // DAVID MIJARES - JUAN CARLOS ANGEL - ALG. PROGRAMACION 2 - PROYECTO 2
#include <stdlib.h>		
#include <string.h>	
#include <conio.h>
#include <windows.h> 

#define TRUE 1
#define FALSE 0

typedef char string [20];

typedef struct lista_arbol
{
	int FE;    //factor de equilibrio
	int	valor;	
	string name;
	struct	lista_arbol *IZQ;	
	struct	lista_arbol *DER;

}lista_arbol;
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void imprimir_inorden(lista_arbol *arboll){//Imprime los NOMBRES de los arboles de forma ascendente (ya que el ABB esta en forma ascendente).
	if (arboll){
		imprimir_inorden(arboll->IZQ);
		printf("\n\n %s",arboll->name);    
		imprimir_inorden(arboll->DER);
	}
}


void imprimir_postorden(lista_arbol *arboll){//Imprime de ultim ola RAIZ
	if (arboll){
		imprimir_postorden(arboll->IZQ);
		imprimir_postorden(arboll->DER);    
		printf("\n\n %s",arboll->name);
	}
}




int es_raiz_del_arbol(int clave, lista_arbol *raiz){//Determina si la clave que ingresa el usuario es raiz del arbol
	if (clave == raiz->valor)
		return TRUE;

	return FALSE;
}



int es_hoja(lista_arbol *nodo){//Determina si el nodo es hoja
	if (!(nodo->IZQ) && !(nodo->DER))
		return TRUE;
	
	return FALSE;
}



int altura(lista_arbol *datos){
	
	int	altura_nodo=0; 
	int	altura_su_izq=0; 
	int altura_su_der=0;
	
	if (!datos)
		return -1;
	
	if (es_hoja(datos))
		return 0;
	else
	{
		altura_nodo=1;
		
		altura_su_izq = altura(datos->IZQ);
		altura_su_der = altura(datos->DER);
		
		if (altura_su_izq > altura_su_der)
			altura_nodo += altura_su_izq;
		else
			altura_nodo += altura_su_der;
	}
	
	return altura_nodo;
}



lista_arbol *buscar_arbol(int clave, lista_arbol *datos){//Busca una clave especifica en el arbol
	lista_arbol *aux;
	aux = datos;

	if (!aux)
		return NULL;

	else 
	{
		if (aux->valor != clave)
		{
			if (clave < aux->valor) 
			{
				if (aux->IZQ == NULL) 
					return NULL;
				else 
					aux = buscar_arbol(clave,aux->IZQ);
			}
			else 
			{
				if (aux->DER == NULL)
					return NULL;
				else 
					aux = buscar_arbol(clave,aux->DER);
			}
		}
	}
	
	return aux;
}





lista_arbol *buscar_arbol_string(string nombre, lista_arbol *datos){//Busca un nombre especifico en el arbol
	lista_arbol *aux;
	aux = datos;

	if (!aux)
		return NULL;
	else 
	{
		if ((strcmp(aux->name,nombre))!=0)
		{
			if ((strcmp(aux->name,nombre))==1) 
			{
				if (!aux->IZQ) 
					return NULL;
				else 
					aux = buscar_arbol_string(nombre,aux->IZQ);
			}
			else 
			{
				if (!aux->DER)
					return NULL;
				else 
					aux = buscar_arbol_string(nombre,aux->DER);
			}
		}
	}
	
	return aux;
}












int buscar_arbol_validar(int clave, lista_arbol *datos, int cont){//Busca una CLAVE especifica en el arbol. Utilizada para validar que no se repita
	lista_arbol *aux;
	aux = datos;

	if (!aux)
		return cont;

	else 
	{
		if (aux->valor != clave)
		{
			if (clave < aux->valor) 
			{
				if (aux->IZQ == NULL) 
					return cont;
				else 
					cont = buscar_arbol_validar(clave,aux->IZQ,1);
			}
			else 
			{
				if (aux->DER == NULL)
					return cont;
				else 
					cont = buscar_arbol_validar(clave,aux->DER,1);
			}
		}
	}
	
	return (cont=0);
}




int buscar_arbol_validar_nombre(string nombre, lista_arbol *datos, int cont){ //Busca un NOMBRE especifico en el arbol. Utilizado para validar que no se repita
	lista_arbol *aux;
	aux = datos;

	if (!aux)
		return cont;

	else 
	{
		if ((strcmp(aux->name,nombre))!=0)
		{
			if ((strcmp(aux->name,nombre))==1) 
			{
				if (!aux->IZQ) 
					return cont;
				else 
					cont = buscar_arbol_validar_nombre(nombre,aux->IZQ,1);
			}
			else 
			{
				if (!aux->DER)
					return cont;
				else 
					cont = buscar_arbol_validar_nombre(nombre,aux->DER,1);
			}
		}
	}
	
	return (cont=0);
}






void rotacion_izqder(lista_arbol **avl, lista_arbol *equilibrio)
{
	lista_arbol *equilibrio_2 = equilibrio->DER;
	(*avl)->IZQ = equilibrio_2->DER;
	equilibrio_2->DER = (*avl);
	equilibrio->DER = equilibrio_2->IZQ;
	equilibrio_2->IZQ = equilibrio;
	
	if (equilibrio_2->FE == 1)
		equilibrio->FE = -1;
	else
		equilibrio->FE= 0;
		
	if (equilibrio_2->FE == -1)
		(*avl)->FE = 1;
		
	else
		(*avl)->FE=0;

	equilibrio_2->FE = 0;
	
	(*avl)=equilibrio_2;
}


void rotacion_derizq(lista_arbol **avl, lista_arbol *equilibrio)
{
	lista_arbol *equilibrio_2 = equilibrio->IZQ;
	(*avl)->DER = equilibrio_2->IZQ;
	equilibrio_2->IZQ = (*avl);
	equilibrio->IZQ = equilibrio_2->DER;
	equilibrio_2->DER = equilibrio;
	
	if (equilibrio_2->FE == 1)
		equilibrio->FE = -1;
	else
		equilibrio->FE = 0;
		
	if (equilibrio_2->FE == -1)
		(*avl)->FE = 1;
	else
		(*avl)->FE = 0;

	equilibrio_2->FE = 0;
	
	(*avl)=equilibrio_2;
}


void rotacion_izqizq(lista_arbol **avl, lista_arbol *equilibrio)
{
	(*avl)->IZQ = equilibrio->DER;
	equilibrio->DER = (*avl);
	
	if (equilibrio->FE == -1)
	{
		(*avl)->FE=0;
		equilibrio->FE = 0;
	}
	else
	{
		(*avl)->FE = 1;
		equilibrio->FE = 1;
	}

	(*avl)=equilibrio;

}



void rotacion_derder(lista_arbol **avl, lista_arbol *equilibrio)
{
	(*avl)->DER = equilibrio->IZQ;
	equilibrio->IZQ = (*avl);
	
	if (equilibrio->FE== 1)
	{
		(*avl)->FE = 0;
		equilibrio->FE = 0;
	}
	else
	{
		(*avl)->FE = -1;
		equilibrio->FE = -1;
	}
	
	(*avl)=equilibrio;
}






void insertar_en_avl(lista_arbol *aux, lista_arbol **avl, int *conteo)
{
	lista_arbol *equilibrio=NULL;
	
	if (!(*avl)){
		(*avl) = (lista_arbol *)malloc(sizeof(lista_arbol));
		 aux->FE = 0;
		(*avl) = aux;
		(*avl)->DER = NULL;
		(*avl)->IZQ = NULL;
		(*conteo)=1;
	}
	else
	{
		if (*avl)
		{
			if(((*avl)->valor > aux->valor))
			{	
				insertar_en_avl(aux,&(*avl)->IZQ,&(*conteo));
				
				if (*conteo)
				{
					if((*avl)->FE==1)
					{
						(*avl)->FE=0;
						(*conteo)=0;
                    }
					else
					{
						if ((*avl)->FE == 0)
							(*avl)->FE=-1;
						else
						{
							equilibrio = (*avl)->IZQ;

							if (equilibrio->FE <= 0)
							{
								rotacion_izqizq(&(*avl),equilibrio);
								printf("\n\nEl Arbol Esta Equilibrado - POR I.I.\n\n");
								system("pause");
							}
						    else
							{
								rotacion_izqder(&(*avl),equilibrio);
								printf("\n\nEl Arbol Esta Equilibrado - POR I.D.\n\n");
							}

							(*conteo)=0;
                         }
					
					}				
				
				
				}//if del conteo
             

			}//if del valor
			
			else
			{
				if(((*avl)->valor < aux->valor))
				{
					insertar_en_avl(aux,&(*avl)->DER,&(*conteo));
				
					if (*conteo)
					{
						if((*avl)->FE==-1)
						{
							(*avl)->FE=0;
							(*conteo)=0;
						}
						else
						{
							if ((*avl)->FE == 0)
								(*avl)->FE=1;
						
							else
							{
								equilibrio = (*avl)->DER;

								if (equilibrio->FE >= 0)
								{
									rotacion_derder(&(*avl),equilibrio);
									printf("\n\nEl Arbol Esta Equilibrado - POR D.D.\n\n");
									system("pause");
								}
								else
									{
									rotacion_derizq(&(*avl),equilibrio);
									printf("\n\nEl Arbol Esta Equilibrado - POR D.I.\n\n");
									system("pause");
									}

								(*conteo)=0;
							}
									
						}
				
					}//if del conteo 2
             

				}//if del valor 2
			
			}
		
	
	
	
		}// if del avl
	
	}// del ELSE


}






lista_arbol *insertar_nodo_avl(int clave, string nombre, lista_arbol *avl)
{
	lista_arbol *aux_avl;
	aux_avl = NULL;
	int conteo=0;

	aux_avl = (lista_arbol *)malloc(sizeof(lista_arbol));
	aux_avl->valor = clave;
	strcpy(aux_avl->name,nombre);
	
	insertar_en_avl(aux_avl,&(avl),&(conteo));
	aux_avl = NULL;
	return(avl);

}



lista_arbol *insertar_arbol(int clave, lista_arbol *datos, string nombre){ //Inserta por CLAVE. SE DEBE CREAR UN INSERTAR, A PARTE DE ESTE, QUE INSERTE, EN UN ARBOL DISTINTO, POR NOMBRE. Me imagino que solo cambiamos las condiciones del "if" por STRCMP y ya
	
	lista_arbol *nuevo_dato;
	lista_arbol *aux;
	
	if (!(datos))
	{
		nuevo_dato = (lista_arbol *)malloc(sizeof(lista_arbol));
		nuevo_dato->valor = clave;
		strcpy(nuevo_dato->name,nombre);
		nuevo_dato->IZQ = NULL;
		nuevo_dato->DER = NULL;
		datos = nuevo_dato;
	}
	else
	{
		aux = datos;
		
		if (clave < datos->valor)
		{
			aux = insertar_arbol(clave,aux->IZQ,nombre);
			datos->IZQ = aux;
		}

		if (clave > datos->valor) 
		{
			aux = insertar_arbol(clave,aux->DER,nombre);
			datos->DER = aux;
		}
	}

	return datos;
}





lista_arbol *insertar_arbol_por_nombre(int clave, lista_arbol *datos, string nombre){//inserta en un ABB
	
	lista_arbol *nuevo_dato;
	lista_arbol *aux;
	
	if (!(datos))
	{
		nuevo_dato = (lista_arbol *)malloc(sizeof(lista_arbol));
		nuevo_dato->valor = clave;
		strcpy(nuevo_dato->name,nombre);
		nuevo_dato->IZQ = NULL;
		nuevo_dato->DER = NULL;
		datos = nuevo_dato;
	}
	else
	{
		aux = datos;
		if ((strcmp(nombre,datos->name))==-1)
		{
			aux = insertar_arbol_por_nombre(clave,aux->IZQ,nombre);
			datos->IZQ = aux;
		}

		if ((strcmp(nombre,datos->name))==1) 
		{
			aux = insertar_arbol_por_nombre(clave,aux->DER,nombre);
			datos->DER = aux;
		}
	}

	return datos;
}





void equilibrar1(lista_arbol **avl, int *conteo)//hacia derecha
{
	lista_arbol *n1;
	
	if((*avl)->FE == -1)
	{
		(*avl)->FE=0;
		(*conteo)=0;
	}
			
	else
		if((*avl)->FE == 0)
		{
			(*avl)->FE=1;
		}
					
		else 
		{
			n1= (*avl)->DER;
			
			if (n1->FE >=0)
			{
				rotacion_derder(&(*avl),n1);
				(*conteo)=0;
			}
			else
				rotacion_derizq(&(*avl),n1);
			
			(*conteo)=0;
		}
}	





void equilibrar2(lista_arbol **avl, int *conteo)//hacia izquierda
{
	lista_arbol *n1;
	if((*avl)->FE == 0)
	{
		(*avl)->FE=-1;
		(*conteo)=0;
	}
	else
		if((*avl)->FE == 1)
		{
			(*avl)->FE = 0;
		}
		else 
		{
			n1 = (*avl)->IZQ;
		
				if (n1->FE <=0)
				{
					rotacion_izqizq(&(*avl),n1);
					(*conteo)=0;
				}
				else
					rotacion_izqder(&(*avl),n1);
			
			(*conteo)=0;	
		}
}






int menor_de_mayores(lista_arbol **avl, lista_arbol **t, int *conteo)
{
	if((*avl)->IZQ){
		return(menor_de_mayores(&(*avl)->IZQ,&(*t),&(*conteo)));
		equilibrar1(&(*avl),&(*conteo));
	}
	else
		*t = (*avl);
	    (*avl) = (*avl)->DER;
		(*conteo) = 1;
		if (*avl){
			equilibrar1(&(*avl),&(*conteo));
			equilibrar2(&(*avl),&(*conteo));
		}
		return((*t)->valor);
}




void eliminar_clave(lista_arbol **avl, int *conteo, int clave)
{

	string error;

	if(*avl)
	{
		if((*avl)->valor > clave)
		{
			eliminar_clave(&(*avl)->IZQ,&(*conteo),clave);
			
			if (altura((*avl)->DER)>altura((*avl)->IZQ))
				equilibrar1(&(*avl),&(*conteo));
			else if (altura((*avl)->IZQ)>altura((*avl)->DER))
				equilibrar2(&(*avl),&(*conteo));
		}
		else
			if((*avl)->valor < clave)
			{
				eliminar_clave(&(*avl)->DER,&(*conteo),clave);

			if (altura((*avl)->DER)>altura((*avl)->IZQ))
				equilibrar1(&(*avl),&(*conteo));
			else if (altura((*avl)->IZQ)>altura((*avl)->DER))
				equilibrar2(&(*avl),&(*conteo));
			
			}

			else
			{ //estoy en el nodo que quiero eliminar
			
				lista_arbol *aux_2 = *avl;
		
				if(!((*avl)->IZQ))
				{
					(*avl)=(*avl)->DER;
					delete(aux_2);
					(*conteo) = 1;
				}
				else
					if(!((*avl)->DER))
					{
						(*avl)=(*avl)->IZQ;
						delete(aux_2);
						(*conteo) = 1;
					}
					else
					{ //ambos hijos existen
						(*avl)->valor = menor_de_mayores(&(*avl)->DER,&(aux_2),&(*conteo));
						strcpy((*avl)->name,aux_2->name);
						if (altura((*avl)->DER)>altura((*avl)->IZQ))
							equilibrar1(&(*avl),&(*conteo));
						else if (altura((*avl)->IZQ)>altura((*avl)->DER))
							equilibrar2(&(*avl),&(*conteo));

						delete(aux_2);
					}
				
				printf("\n\n Se ha eliminado satisfactoriamente POR CLAVE.\n\n");
				system("pause");
			}
	} //end del if(avl)
}







void *menor_de_mayores_string(lista_arbol *abb, lista_arbol **t)
{
	if(abb->IZQ)
	{
		return(menor_de_mayores_string(abb->IZQ,&(*t)));
	}
	else
	{
		*t = abb;
		abb = abb->DER;
		return (*t);
	}
}





void eliminar_string(lista_arbol **abb, string nombre)
{
	string error;

	if(*abb)
	{
		if((strcmp((*abb)->name,nombre))==1)
		{
			eliminar_string(&(*abb)->IZQ,nombre);
		}
		else
			if ((strcmp((*abb)->name,nombre)==-1))
			{
				eliminar_string(&((*abb)->DER),nombre);
			}

			else
			{ //estoy en el nodo que quiero eliminar
			
				lista_arbol *aux_2 = *abb;
		
				if(!((*abb)->IZQ))
				{
					(*abb)=(*abb)->DER;
					delete(aux_2);
				}
				else
					if(!((*abb)->DER))
					{
						(*abb)=(*abb)->IZQ;
						delete(aux_2);
					}
					else
					{ //ambos hijos existen
						menor_de_mayores_string((*abb)->DER,&(aux_2));
						strcpy((*abb)->name,aux_2->name);
						delete(aux_2);
					}
				
				printf("\n\n Se ha eliminado satisfactoriamente POR NOMBRE.\n\n");
				system("pause");
			}
	} //end del if(avl)
}


void imprimir_niveles(lista_arbol *p, lista_arbol *aux, int n, int n2, int div, int space){ 
//space es donde comenzare a imprimir en la pantalla, en el nivel que se ejecute (ej: 40 si es una pantalla de 80 chars)
// div es la mitad del nivel en el que estoy
// n2 es el nivel q voy a imprimir, lo busco de arriba hacia abajo con n
	n++;

	if (n2 > (altura(aux) + 1))
		return;

	if (n == n2){
			char buffer [5];
			itoa (p->valor,buffer,10); // convierto el valor a string
			if (strlen(buffer)>1)
				gotoxy( (space-strlen(buffer)) ,n); // acomodo para poder imprimir en la pantalla (si valor tiene 1, 2, 3... chars)
			else
     			gotoxy(space,n);
			printf("%d",p->valor);
	}

	if (p->IZQ){
		imprimir_niveles(p->IZQ, aux, n, n2, div/2, space-(div/2));}
	if (p->DER){
		imprimir_niveles(p->DER, aux, n, n2, div/2, space+(div/2));}

	if (p == aux){
		n2++;
		printf("\n");
		imprimir_niveles(p, aux, 0, n2, 40, 40);}

}


void main(){

	lista_arbol *p;//arbol ABB, utilizado para imprimir de mayor a menor por nombre
	p = NULL;
	
	lista_arbol *a;//arbol AVL.
	a= NULL;
	
	
	int conteo = 0;
	int caso = 0;
	int salir = 0;
	int numero = 0;
	int validar = 0;//utilizada para validar si existe la clave o el nombre
	string error, nombre, pass;
	
	do
{
		system("cls"); 
		printf("\n         |---------------------------------------------------------|");
        printf("\n         |                                                         |");
        printf("\n         |        --------->	A R B O L E S   <---------         |");
        printf("\n         |                      * Main Menu *                      |");
        printf("\n         |                                                         |");
		printf("\n         |   * Seleccione :                                        |");
		printf("\n         |                                                         |");
        printf("\n         |   1- Insertar                                           |");
        printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |   2- Eliminar                                           |");
        printf("\n         |                                                         |");
		printf("\n         |                                                         |");
        printf("\n         |                                                         |");
		printf("\n         |   3- Buscar por CLAVE                                   |");
        printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |   4- Buscar por NOMBRE                                  |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |   5- Imprimir Claves (por niveles)                      |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |   6- Imprimir Nombres (ascendente)                      |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |   7- Salir del Programa                                 |");
		printf("\n         |                                                         |");
        printf("\n         |                                                         |");
		printf("\n         |                                                         |");
		printf("\n         |---------------------------------------------------------| \n\n");
	    
		scanf("%d", &caso);

        switch (caso)
		{
			case 1:
				system("cls");
				printf("\n\n WARNING: NO REPITA NI CLAVE NI NOMBRE. \n\n\n");
				printf("\n\n\n Ingrese la CLAVE que desea agregar al ARBOL.\n\n\n");
				scanf("%i",&numero);
				printf("\n\n\n Ingrese el NOMBRE que desea agregarle a la clave.\n\n\n");
				gets(error);
				scanf("%s",&nombre);
				validar=1;
				printf("\n\n\n\n");
				a=insertar_nodo_avl(numero,nombre,a);
				p=insertar_arbol_por_nombre(numero,p,nombre);
				system("pause");
			break;

            
			case 2:
				gets(error);
				printf("\n\n Ingrese la CLAVE y el NOMBRE QUE LO ACOMPANA.\n\n");
				printf("\n\n WARNING: debe ingresar EL PAR CORRECTO. De lo contrario PUEDE QUE ELIMINE INCORRECTAMENTE. \n\n");
				printf("\n CLAVE:\n");
				scanf("%i",&numero);
				printf("\n\n NOMBRE:\n");
				gets(error);
				gets(nombre);
				eliminar_clave(&a,&conteo,numero);				
				eliminar_string(&(p),nombre);
				system("pause");
			break;

            
			case 3:
				gets(error);
				system("cls");
				printf("\n\n\n Ingrese la CLAVE que desea BUSCAR.\n\n\n");
				scanf("%i",&numero);
				lista_arbol *aux;
				aux = buscar_arbol(numero,a);
				if (aux){
					printf("\n\n   CLAVE----> %i",aux->valor);
					printf("\n\n   NOMBRE---> %s",aux->name);
					if (aux->IZQ)
						printf("\n\n   HIJO-IZQ (CLAVE)---> %i",aux->IZQ->valor);
					else
						printf("\n\n   HIJO-IZQ (CLAVE)---> NO TIENE.");

					if (aux->DER)
						printf("\n\n   HIJO-DER (CLAVE)---> %i",aux->DER->valor);
					else
						printf("\n\n   HIJO-DER (CLAVE)---> NO TIENE.");
				
				}
				else
					printf("\n\n NO EXISTE ESA CLAVE EN LOS DATOS DEL ARBOL.");
				printf("\n\n");
				system("pause");
			break;

            
			case 4:
				gets(error);
				system("cls");
				printf("\n\n\n Ingrese el NOMBRE que desea BUSCAR.\n\n\n");
				scanf("%s",&nombre);
				lista_arbol *aux_N;
				aux_N = buscar_arbol_string(nombre,p);
				if (aux_N){
					printf("\n\n   CLAVE----> %i",aux_N->valor);
					printf("\n\n   NOMBRE---> %s\n\n",aux_N->name);
				}
				else
					printf("\n\n NO EXISTE ESE NOMBRE EN LOS DATOS DEL ARBOL.");
				printf("\n\n");
				system("pause");
			break;
			
			
			case 5:
				gets(error);
				printf("\n\n\n");
				system("CLS");
				imprimir_niveles(a, a, 0, 1, 40, 40);
				printf("\n\n\n\n\n");
				system("pause");
			break;
			
			
			case 6:
				gets(error);
				imprimir_inorden(p);
				printf("\n\n");
				system("pause");
			break;
			
			
			case 7:
				gets(error);
				salir++;
			break;

	
		
		}
		
		system("cls");
		
	}while(salir == 0);







system("pause");
}
