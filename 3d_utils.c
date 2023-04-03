/* Disegna i tre assi cartesiani */
#include <allegro.h>
#include "3d_utils.h"

double XO,YO;
int _ZOOM;    // Fattore di zoom

void init_3D (void) {
     XO = X_RES/2;
     YO = Y_RES/2;  
     _ZOOM = 6;    // Fattore di zoom   
}



void plot_axes(BITMAP *bmp, double angleX, double angleY, double angleZ){
     int r = 350;
     double x,y;

     /* Asse y */
     x=r*cos(angleY);
     y=r*sin(angleY);
     fastline(bmp,XO,YO,XO+x,YO-y,makecol32(255,255,255));
     fastline(bmp,XO,YO,XO-x,YO+y,makecol32(255,255,255));

     /* Asse x */
     x=r*cos(angleX);
     y=r*sin(angleX);
     fastline(bmp,XO,YO,XO+x,YO-y,makecol32(255,0,0));
     fastline(bmp,XO,YO,XO-x,YO+y,makecol32(255,0,0));
     
     /* Asse z */
     x=r*cos(angleZ);
     y=r*sin(angleZ);
     fastline(bmp,XO,YO,XO+x,YO-y,makecol32(0,255,0));
}


void from3D_to_2D (int x, int y, int z, 
               int *xp2D, int *yp2D, \
               double sinX, double cosX, \
               double sinY, double cosY, \
               double sinZ, double cosZ) { 

  double xp,yp;

  xp=(x * cosX + XO) + (y * cosY) + (z * cosZ);
  yp=(YO - x * sinX) - (y * sinY) - (z * sinZ);
 
  *xp2D = xp;
  *yp2D = yp;
}




/* Calcola e visualizza nella bitmap la funzione 3D */
void plot_3D_pixel (BITMAP *bmp, int x, int y, int z, double X_Angle, double Y_Angle, float Z_Angle)
{
 int xp2D,yp2D;    
 
 double sinX,cosX,sinY,cosY,sinZ,cosZ;
 
 int colore;

 sinX = sin(X_Angle) * (double)_ZOOM;
 cosX = cos(X_Angle) * (double)_ZOOM;
 sinY = sin(Y_Angle) * (double)_ZOOM;
 cosY = cos(Y_Angle) * (double)_ZOOM;
 sinZ = sin(Z_Angle) * (double)_ZOOM;
 cosZ = cos(Z_Angle) * (double)_ZOOM;

 from3D_to_2D(x,y,z,&xp2D,&yp2D,sinX,cosX,sinY,cosY,sinZ,cosZ);
 putpixel(bmp, xp2D, yp2D,makecol32(255,255,0));
 circle(bmp, xp2D, yp2D,6,makecol32(255,255,0));
       
}


void plot_3D_line (BITMAP *bmp, int x1, int y1, int z1, int x2, int y2, int z2,double X_Angle, double Y_Angle, float Z_Angle)
{
 int xp2D1,yp2D1;    
 int xp2D2,yp2D2;
  
 double sinX,cosX,sinY,cosY,sinZ,cosZ;
 
 int colore;

 sinX = sin(X_Angle) * (double)_ZOOM;
 cosX = cos(X_Angle) * (double)_ZOOM;
 sinY = sin(Y_Angle) * (double)_ZOOM;
 cosY = cos(Y_Angle) * (double)_ZOOM;
 sinZ = sin(Z_Angle) * (double)_ZOOM;
 cosZ = cos(Z_Angle) * (double)_ZOOM;

 from3D_to_2D(x1,y1,z1,&xp2D1,&yp2D1,sinX,cosX,sinY,cosY,sinZ,cosZ);
 from3D_to_2D(x2,y2,z2,&xp2D2,&yp2D2,sinX,cosX,sinY,cosY,sinZ,cosZ);
 
 fastline(bmp,xp2D1,yp2D1,xp2D2,yp2D2,makecol32(255,255,0));
       
}













