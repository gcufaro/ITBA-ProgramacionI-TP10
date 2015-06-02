/* 
 * File:   main.c
 * Author: Mercedes
 *
 * Created on 1 de junio de 2015, 23:55
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
/*
 * 
 */
typedef float mipunto[2];
int limite=3;
void MiAlgoritmoKoch(mipunto inicio,mipunto fin, int n);

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
   mipunto pA= {250,350+50*sqrt(3)};
   mipunto pB= {350,350-50*sqrt(3)};
   mipunto pC= {450,350+50*sqrt(3)};
   
   MiAlgoritmoKoch(pA,pC,3);
   MiAlgoritmoKoch(pC,pB,3);
   MiAlgoritmoKoch(pB,pA,3);

 
   //al_draw_line(250,350+50*sqrt(3),450,350+50*sqrt(3),al_map_rgb(255,0,0),2);
   //al_draw_line(250,350+50*sqrt(3),350,350-50*sqrt(3),al_map_rgb(255,0,0),2);
   //al_draw_line(350,350-50*sqrt(3),450,350+50*sqrt(3),al_map_rgb(255,0,0),2);
   
   al_flip_display();
 
   while(1)
   {
      ALLEGRO_EVENT ev;
 
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      al_clear_to_color(al_map_rgb(0,0,0));
      al_flip_display();
   }
 
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

void MiAlgoritmoKoch(mipunto inicio,mipunto fin, int n)
{
    if(n<=0)
    {
     al_draw_line(inicio[0],inicio[1],fin[0],fin[1],al_map_rgb(255,0,0),2);
        
    }else
    {
    mipunto puntoA= {inicio[0],inicio[1]};
    mipunto puntoB = {(2.0 * inicio[0]+fin[0])/3.0,(2.0 * inicio[1]+fin[1])/3.0 };
    mipunto puntoC = {(inicio[0]+fin[0])/2.0 - sqrt(3.0)/6.0 *(fin[1]-inicio[1]),
		       (inicio[1]+fin[1])/2.0 + sqrt(3.0)/6.0 *(fin[0]-inicio[0])};
    mipunto puntoD = {(inicio[0]+2.0 * fin[0])/3.0,(inicio[1]+2.0 *fin[1])/3.0 };
    mipunto puntoE = {fin[0],fin[1]};

    MiAlgoritmoKoch(puntoA, puntoB, n-1);
    MiAlgoritmoKoch(puntoB, puntoC, n-1);
    MiAlgoritmoKoch(puntoC, puntoD, n-1);
    MiAlgoritmoKoch(puntoD, puntoE, n-1);
    }
}


void MiCopoDeNieveKoch(mipunto punto1, mipunto punto2, mipunto punto3) //con errrores!
{  
   MiAlgoritmoKoch(punto1, punto2, limite);
   MiAlgoritmoKoch(punto2, punto3, limite);
   MiAlgoritmoKoch(punto3, punto1, limite);
} 