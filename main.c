/* 
 * File:   main.c
 * Author: Mercedes
 *
 * Created on 1 de junio de 2015, 23:55
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

/*
 * 
 */

typedef float mipunto[2];
void MiAlgoritmoKoch(mipunto inicio, mipunto fin, int n, ALLEGRO_COLOR micolor1);
void MiCopoDeNieveKoch(mipunto punto1, mipunto punto2, mipunto punto3, unsigned 
                    int orden, ALLEGRO_COLOR micolor2);

int main(int argc, char** argv) {
 
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
   
   mipunto pA= {300,350+(3*12.5*sqrt(3))/2}; //punto de la izquierda del triángulo
   mipunto pB= {350,350-(5*12.5*sqrt(3))/2}; //punto del medio del triángulo
   mipunto pC= {400,350+(3*12.5*sqrt(3))/2}; //punto de la derecha del triángulo
   
   mipunto pA1= {250,350+(3*25*sqrt(3))/2}; //punto de la izquierda del triángulo
   mipunto pB1= {350,350-(5*25*sqrt(3))/2}; //punto del medio del triángulo
   mipunto pC1= {450,350+(3*25*sqrt(3))/2}; //punto de la derecha del triángulo
   
   mipunto pA2= {200,350+(3*37.5*sqrt(3))/2}; //punto de la izquierda del triángulo
   mipunto pB2= {350,350-(5*37.5*sqrt(3))/2}; //punto del medio del triángulo
   mipunto pC2= {500,350+(3*37.5*sqrt(3))/2}; //punto de la derecha del triángulo
   
   mipunto pA3= {100,350+(3*62.5*sqrt(3))/2}; //punto de la izquierda del triángulo
   mipunto pB3= {350,350-(5*62.5*sqrt(3))/2}; //punto del medio del triángulo
   mipunto pC3= {600,350+(3*62.5*sqrt(3))/2}; //punto de la derecha del triángulo
   
   MiCopoDeNieveKoch(pA3,pB3,pC3, 4, al_map_rgb(255,0,0)); 
   MiCopoDeNieveKoch(pA2,pB2,pC2, 3, al_map_rgb(0,255,0)); 
   MiCopoDeNieveKoch(pA1,pB1,pC1, 2, al_map_rgb(0,0,255));
   MiCopoDeNieveKoch(pA,pB,pC, 1, al_map_rgb(255,0,255));

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

void MiAlgoritmoKoch(mipunto inicio, mipunto fin, int n, ALLEGRO_COLOR micolor1)
{
    if(n<=0)
    {
        int n=0;
        for(n=0;n<50;n++)
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

void MiCopoDeNieveKoch(mipunto punto1, mipunto punto2, mipunto punto3, unsigned int orden, ALLEGRO_COLOR micolor2) //con errrores!
{  
   al_draw_filled_triangle(punto1[0], punto1[1], punto2[0], punto2[1], punto3[0], punto3[1], micolor2); 
            //relleno el triángulo inicial ya que no se contempla en el algoritmo por que solamente es con líneas
   
   MiAlgoritmoKoch(punto1, punto3, orden, micolor2);
   MiAlgoritmoKoch(punto3, punto2, orden, micolor2);
   MiAlgoritmoKoch(punto2, punto1, orden, micolor2);
} 