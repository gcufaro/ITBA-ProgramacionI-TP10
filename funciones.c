#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

/*
 * 
 */

#include "funciones.h"


void MiAlgoritmoKoch(mipunto inicio, mipunto fin, int n, ALLEGRO_COLOR micolor1)
{
    int loop=0;
    if(n<=0)
    {
        for(loop=0;loop<1;loop++)
        {
            al_flip_display();
        }
     al_draw_line(inicio[0], inicio[1], fin[0], fin[1], al_map_rgb(0,0,0), 2);  //linea de contorno de la figura
    }else
    {
        
    mipunto puntoA= {inicio[0],inicio[1]};
    mipunto puntoB = {(2.0 * inicio[0]+fin[0])/3.0,(2.0 * inicio[1]+fin[1])/3.0 };
    mipunto puntoC = {(inicio[0]+fin[0])/2.0 - sqrt(3.0)/6.0 *(fin[1]-inicio[1]),
		       (inicio[1]+fin[1])/2.0 + sqrt(3.0)/6.0 *(fin[0]-inicio[0])};
    mipunto puntoD = {(inicio[0]+2.0 * fin[0])/3.0,(inicio[1]+2.0 *fin[1])/3.0 };
    mipunto puntoE = {fin[0],fin[1]};

    al_draw_filled_triangle(puntoB[0], puntoB[1], puntoC[0], puntoC[1], puntoD[0], 
                        puntoD[1], micolor1); //relleno el triangulo nuevo con un color
    
    MiAlgoritmoKoch(puntoA, puntoB, n-1, micolor1);
    MiAlgoritmoKoch(puntoB, puntoC, n-1, micolor1);
    MiAlgoritmoKoch(puntoC, puntoD, n-1, micolor1);
    MiAlgoritmoKoch(puntoD, puntoE, n-1, micolor1);
    }
}

void MiCopoDeNieveKoch(mipunto punto1, mipunto punto2, mipunto punto3, unsigned int orden, ALLEGRO_COLOR micolor2)
{  
   al_draw_filled_triangle(punto1[0], punto1[1], punto2[0], punto2[1], punto3[0], punto3[1], micolor2); 
            //relleno el triángulo inicial ya que no se contempla en el algoritmo por que solamente es con líneas
   
   MiAlgoritmoKoch(punto1, punto3, orden, micolor2);
   MiAlgoritmoKoch(punto3, punto2, orden, micolor2);
   MiAlgoritmoKoch(punto2, punto1, orden, micolor2);
} 

int mystr_compare (char* stringA, char* stringB)
{
	int strlen;											//longitud del primer string
	for(strlen=0; stringA[strlen]!='\0'; strlen++);	//recorro el string para saber su longitud
											

	int i;											//indice para recorer el string
	for(i=0; i<=strlen; i++)
		if(stringA[i]!=stringB[i])					//comparo strings caracter por caracter
			return 0;								//si alguno no coincide devuelvo 0

	return 1;										//si todos coinciden devuelvo 1
}

int getint (char* stringC)
{
	int i, x=0;										//indice para recorrer el string, variable entera
	for(i=0; stringC[i]!='\0'; i++)
	{
		if((stringC[i]>'9') || (stringC[i]<'1'))	//si algun caracter del string no es un numero, devuelvo -1
			return -1;
		else x = 10*x + (stringC[i]-'0');
	}
	return x;										//si todos son numeros, devuelvo el numero entero
}
			
int checkcolor (char* stringD)
{
	int i, comacont=0;								//indice para recorrer string y contador de comas
	for(i=0; stringD[i]!='\0'; i++)
	{
		if((stringD[i]>'9') || (stringD[i]<'0'))	//si algun caracter del string no es un numero o una coma,
		{
			if(stringD[i]==',')
				comacont++;
			else return 0;							//devuelvo 0
		}
	}

	if(comacont!=2)									//si no hay exactamente 2 comas, devuelvo 0
		return 0;

	else return 1;									//si hay exactamente 2 comas y el resto son numeros, devuelvo 1
}

int getR (char* stringE)
{
	int i, red=0;									//indice para recorrer el string, variable de color rojo
	for(i=0; stringE[i]!=','; i++)
		red = red*10+(stringE[i]-'0');

	if(red>255)
		return -1;									//si el valor es mayor a 255 devuelvo -1
	else return red;
}

int getG (char* stringF)
{
	int i, green=0;									//indice para recorrer el string, variable de color verde
	for(i=0; stringF[i]!=','; i++);
	i++;											//paso la primera coma (salteo la parte del rojo)

	for(i=i; stringF[i]!=','; i++)
		green = green*10+(stringF[i]-'0');

	if(green>255)
		return -1;									//si el valor es mayor a 255 devuelvo -1
	else return green;
}

int getB (char* stringG)
{
	int i, blue=0;									//indice para recorrer el string, variable de color azul
	for(i=0; stringG[i]!=','; i++);
	i++;
	for(i=i; stringG[i]!=','; i++);
	i++;											//paso la segunda coma (salteo la parte del rojo y del verde)

	for(i=i; stringG[i]!=','; i++)
		blue = blue*10+(stringG[i]-'0');

	if(blue>255)
		return -1;									//si el valor es mayor a 255 devuelvo -1
	else return blue;
}



