// Programación I - Primer Cuatrimestre de 2015
// Trabajo Práctico N°10: Recursividad y file I/O

// Ejercicio N°1
// Grupo N°2
// Integrantes:
// Cufaro, Gabriel Agustín
// De Ruschi, Agustin
// Luo, Leandro Adrian
// Michel, Bernardo

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
	int i=0;			//Variable utilizada para contadores

	int argtype[argc];		//Creo el arreglo cuyo contenido me indica que tipo de dato es cada argumento (0=nombre, 1=clave, 2=valor, 3=parametro)

	for(i=1;i<argc;i++)
	{
		if(*(argv[i])=='-')	//Si me encuentro con un guion, se trata de una opcion
		{
			if(i!=(argc-1))
			{
				argtype[i]=1;		//Indico que se trata de una clave
				argtype[i+1]=2;		//Indico que se trata de un valor

				if(*(argv[i+1])=='-')	//Verifico que no hayan dos claves consecutivas
				{
					printf("Hay dos opciones consecutivas sin un valor entre ellas.\n", i, i+1);
					return -1;
				}

				if(*(argv[i]+1)=='\0')	//Verifico que la clave tenga sentido
				{
					printf("Hay (por lo menos) una opcion invalida.\n",i);
					return -1;
				}

				i++;		//Me salteo el valor para que no quede como un parametro
			}
			else	//Si el ultimo argumento es una clave, esta no tiene valor
			{
				printf("La ultima opcion no tiene un valor asociado.\n");
				return -1;
			}
		}
		else			//Si no es una opcion, es un parametro
		{
			argtype[i]=3;
			printf("Este programa no admite parametros,\n");
			return -1;
		}
	}

	char* clave1="-order";
	char* clave2="-tol";
	char* clave3="-color";
	char* clave4="-report";

	int orden=4, tolerancia=4;								//valores del orden y tolerancia por defecto
	int red=255, green=0, blue=0;							//valores de los colores por defecto

	for(i=0;i<argc;i++)
	{
		if(argtype[i]==2)
		{
			if(mystr_compare(clave1, argv[i]))				//me fijo si esa calve es el orden
			{
				orden = getint(argv[i+1]);
				if(orden==-1)
				{
					printf("El valor del orden es invalido.\n");
					return -1;
				}
			}

			if(mystr_compare(clave2, argv[i]))				//me fijo si esa clave es la tolerancia
			{
				int tolerancia = getint(argv[i+1]);
				if(tolerancia==-1)
				{
					printf("El valor de la tolerancia es invalido.\n");
					return -1;
				}
			}

			if(mystr_compare(clave3, argv[i]))				//me fijo si esa clave es el color
			{
				if(checkcolor(argv[i+1]))
				{
					red=getR(argv[i+1]);
					green=getG(argv[i+1]);
					blue=getB(argv[i+1]);
				}
				else
				{
					printf("El valor del color es invalido.\n");
					return -1;
				}
			}
		}
	}

//Inicia la parte grafica

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   display = al_create_display(700, 700);
   
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }
 
   event_queue = al_create_event_queue();
   
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      return -1;
   }
   
   al_init_primitives_addon();
   
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_clear_to_color(al_map_rgb(255,255,255));
   
  
//   mipunto pA= {300,350+(3*12.5*sqrt(3))/2}; //punto de la izquierda del triángulo
//   mipunto pB= {350,350-(5*12.5*sqrt(3))/2}; //punto del medio del triángulo
//   mipunto pC= {400,350+(3*12.5*sqrt(3))/2}; //punto de la derecha del triángulo
   
//   mipunto pA1= {250,350+(3*25*sqrt(3))/2}; //punto de la izquierda del triángulo
//   mipunto pB1= {350,350-(5*25*sqrt(3))/2}; //punto del medio del triángulo
//   mipunto pC1= {450,350+(3*25*sqrt(3))/2}; //punto de la derecha del triángulo
   
//   mipunto pA2= {200,350+(3*37.5*sqrt(3))/2}; //punto de la izquierda del triángulo
//   mipunto pB2= {350,350-(5*37.5*sqrt(3))/2}; //punto del medio del triángulo
//   mipunto pC2= {500,350+(3*37.5*sqrt(3))/2}; //punto de la derecha del triángulo
   
   mipunto pA3= {100,350+(3*62.5*sqrt(3))/2}; //punto de la izquierda del triángulo
   mipunto pB3= {350,350-(5*62.5*sqrt(3))/2}; //punto del medio del triángulo
   mipunto pC3= {600,350+(3*62.5*sqrt(3))/2}; //punto de la derecha del triángulo
   
   MiCopoDeNieveKoch(pA3,pB3,pC3, tolerancia, al_map_rgb(red,green,blue)); 	//COLOR Y ORDEN AHORA VARIABLES
//   MiCopoDeNieveKoch(pA2,pB2,pC2, 3, al_map_rgb(0,255,0)); 
//   MiCopoDeNieveKoch(pA1,pB1,pC1, 2, al_map_rgb(0,0,255));
//   MiCopoDeNieveKoch(pA,pB,pC, 1, al_map_rgb(255,0,255));


   al_flip_display();
 
   while(1)
   {
      ALLEGRO_EVENT ev;
 
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      //al_clear_to_color(al_map_rgb(0,0,0));
      al_flip_display();
   }
 
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}






