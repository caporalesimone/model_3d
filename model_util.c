// Libreria per la gestione del file contente il modello 3D

#include <stdio.h>
#include <allegro.h>
#include "model_util.h"
#include "3d_utils.h"

vertex *list_get_last_ptr (vertex *testa) {

	vertex *p;
	vertex *t;

	if (testa == NULL) 
		return NULL;
	for(p=testa,t=testa->next; t!=NULL; p=p->next,t=t->next);
	return p;
}

vertex *add_vertex(int x, int y, int z, vertex *modello) {

    vertex *vertice, *last_ptr;   
    
   	vertice = (vertex *)malloc(sizeof(vertex));
    vertice->x = x;
    vertice->y = y;
    vertice->z = z;
    vertice->next = NULL;		      
      
   	if (modello == NULL) { 
		modello = vertice; 
  	} else { 
        last_ptr = list_get_last_ptr(modello);
		last_ptr->next = vertice; 
  	}
  	
  	return modello;
}


vertex *load_model (char *filename, vertex *modello) {
   FILE *fp;
   char *line;
   int x,y,z;

   if ((fp = fopen(filename,"r"))==NULL) {
      allegro_message ("Errore nell'apertura del file %s [model_util.c]", filename);
      return NULL;
   }  

   while (fscanf(fp,"%d %d %d\n",&x,&y,&z) > 0) 
      modello = (vertex *)add_vertex(x,y,z,modello);
   fclose(fp);
 
   return modello; 
}

// Inizializzazione del modello 3D
vertex *init_model (vertex *modello) {
   
   const char filename[10] = "cubo.dat"; 

   if ((modello = (vertex *)load_model((char*)filename,modello)) == NULL){
      return NULL;
   }
     
   return modello;
}


// Crea la bitmap contenente il modello
/*void plot_modello (vertex *modello, BITMAP *bmp)
{  
     
   int x1,y1,x2,y2;

   while(modello) {
     x1 = modello->x;
     y1 = modello->y;
     if (modello->next != NULL){
        modello = modello->next;                
        x2 = modello->x;      
        y2 = modello->y;             
        fastline(bmp,x1,y1,x2,y2,makecol(255,255,255));
     } else {
       circle(bmp,x1,y1,20,makecol(0,0,255));
       modello = modello->next;
     }
   }
}
*/


void plot_modello (vertex *modello, BITMAP *bmp,double angleX, double angleY, double angleZ)
{
   int x1,y1,z1;
   int x2,y2,z2;
     
   init_3D();
   plot_axes(bmp, angleX, angleY, angleZ);
   
   int cnt=0;
   
   /*
   plot_3D_pixel (bmp,0, 0, 0,angleX,angleY,angleZ);
   plot_3D_pixel (bmp,0, 10, 0,angleX,angleY,angleZ);
   plot_3D_pixel (bmp,0, 10, 10,angleX,angleY,angleZ);
   plot_3D_pixel (bmp,0, 0, 10,angleX,angleY,angleZ);
   */
   
   while(modello) {
      cnt++;
      x1 = modello->x;
      y1 = modello->y;
      z1 = modello->z;
      
      //allegro_message("%d %d %d",x1,y1,z1);
      
      if (modello->next) {
        
        modello=modello->next;
        x2 = modello->x;
        y2 = modello->y;
        z2 = modello->z;
        //allegro_message("%d %d %d",x2,y2,z2);
        //plot_3D_pixel (bmp,x1, y1, z1,angleX,angleY,angleZ);
        //plot_3D_pixel (bmp,x2, y2, z2,angleX,angleY,angleZ);
        plot_3D_line (bmp,x1, y1, z1, x2, y2, z2,angleX,angleY,angleZ);
      } else {
             //cnt++;
        //plot_3D_pixel (bmp,x1, y1, z1,angleX,angleY,angleZ);
        modello = modello->next;
      }  
   }
     
     //allegro_message("%d",cnt);
     
}








