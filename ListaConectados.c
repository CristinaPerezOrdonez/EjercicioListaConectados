#include <stdio.h>
#include <string.h>

typedef struct {
	char nombre[20];
	int socket;
} Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
} ListaConectados;

//La lista se pasa por referencia
int Pon (ListaConectados *lista, char nombre[20], int socket){
	//añade nuevo conectado y retorna 0 si okey o 0 si la lista ya estaba llena
	if(lista->num ==100)
		return -1;
	else
	{
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket=socket;
		lista->num++;
		return 0;
	}
}

int DameSocket(ListaConectados *lista, char nombre[20]){
	//Devuelve el socket o -1 si no lo ha encontrado en la lista
	//esquema de busqueda
	int i=0;
	int encontrado=0;
	while((i<lista->num)&& (!encontrado))
	{
		if(strcmp(lista->conectados[i].nombre,nombre)==0)
			encontrado=1;
		else
			i++;
	}
	if(encontrado)
		return lista->conectados[i].socket;
	else
		return -1;
}

int DamePosicion(ListaConectados *lista, char nombre[20]){
	//Devuelve el socket o -1 si no lo ha encontrado en la lista
	//esquema de busqueda
	int i=0;
	int encontrado=0;
	while((i<lista->num)&& (!encontrado))
	{
		if(strcmp(lista->conectados[i].nombre,nombre)==0)
			encontrado=1;
		else
			i++;
	}
	if(encontrado)
		return i;
	else
		return -1;
}

int Elimina (ListaConectados *lista, char nombre[20]){
	//Retorna 0 si se ha eliminado y -1 si el usuario no esta en la lista
	//lista ya es un puntero a la lista y por ello la pongo tal cual sin &
	int pos=DamePosicion (lista, nombre);
	if(pos==-1)
		return -1;
	else
	{
		int i;
		for(i=pos; i< lista->num-1; i++)
		{
			lista->conectados[i]=lista->conectados[i+1];
			//strcpy(lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			//lista->conectados[i].socket=lista->conectados[i+1].socket;
		}
		lista->num--;
		return 0;
	}
	
}

void DameConectados(ListaConectados *lista, char conectados[300]){
	//Pone en conectados los nombres de todos los conectados separados
	//por /. Primero pone el número de conectados
	//Ejemplo: "3/Pedro/Mayra/Luis"
	sprintf(conectados,"%d", lista->num);
	int i;
	for(i=0;i<lista->num;i++)
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);
	
}


void DameListaSockets (ListaConectados *lista, char conectados[300], char sockets[300]){
	//Escribe una funcion que recibe un vector de caracteres con 
	//los nombres de jugadores separados por barras y devuelve 
	//una cadena de caracteres con los sockets de cada uno de 
	//estos jugadores, separados por comas.
	char *p;
	char nombre[20];
	p=strtok(conectados,"/");
	int n=atoi(p);
	sprintf(sockets,"%d", n);
	p=strtok(NULL, "/");
	while(p!=NULL)
	{
		
		strcpy(nombre,p);
		int socket=DameSocket (lista, nombre);
		if(socket==-1)
			printf("No se ha podido añadir");
		else
		{
			sprintf(sockets, "%s,%d", sockets, socket);
		}
		p=strtok(NULL, "/");
		
	}
	
}

int main(int argc, char *argv[]) {
	ListaConectados miLista;
	miLista.num=0;
	
	//paso la lista por referencia y recojo el resultado
	int res=Pon(&miLista, "Juan", 5);
	if(res==-1)
		printf("La lista esta llena\n");
	else
		printf("Añadido a la lista\n");
	res=Pon(&miLista, "Laura", 3);
	if(res==-1)
		printf("La lista esta llena\n");
	else
		printf("Añadido a la lista\n");
	res=Pon(&miLista, "Ana", 1);
	if(res==-1)
		printf("La lista esta llena\n");
	else
		printf("Añadido a la lista\n");
	res=Pon(&miLista, "Carlos", 15);
	if(res==-1)
		printf("La lista esta llena\n");
	else
		printf("Añadido a la lista\n");
	res=Pon(&miLista, "Julian", 55);
	if(res==-1)
		printf("La lista esta llena\n");
	else
		printf("Añadido a la lista\n");
	
	int socket=DameSocket(&miLista, "Juan");
	if(socket==-1)
		printf("No está en la lista\n");
	else
		printf("El socket es %d\n", socket);
	
	//Se podria hacer igual pero con la función DamePosicion
	int pos=DamePosicion(&miLista, "Juan");
	if(pos==-1)
		printf("No esta en la lista\n");
	else
		printf("El socket del usuario es:%d\n", miLista.conectados[pos].socket);
	
	res = Elimina(&miLista, "Juan");
	if(res==-1)
		printf("No esta en la lista\n");
	else
		printf("Eliminado\n");
	
	pos=DamePosicion(&miLista, "Juan");
	if(pos==-1)
		printf("No esta en la lista\n");
	else
		printf("El socket del usuario es:%d\n", miLista.conectados[pos].socket);
	
	char misconectados[300];
	DameConectados(&miLista, misconectados);
	printf("Resultado: %s\n", misconectados);
	
	char *p;
	int n;
	p=strtok(misconectados,"/");
	n=atoi(p);
	int i;
	for(i=0;i<n;i++)
	{
		char nombre[20];
		p=strtok(NULL, "/");
		strcpy(nombre, p);
		printf("Conectado: %s\n", nombre);
	}
	
	char missockets[300];
	strcpy(misconectados, "3/Carlos/Julian/Ana");
	DameListaSockets(&miLista, misconectados, missockets);
	printf("Resultado: %s\n", missockets);
	
	return 0;
}

