#include <allegro.h>
#include "model_util.h"
#include "3d_utils.h"

volatile int fps=0;
volatile int avg_fps=1;
volatile int last_fps=0;



void init();
void deinit();

void fps_timer()
{
        last_fps=fps;
        fps=0;
        avg_fps=(avg_fps*last_fps)/2;
}




int main() {
	init();

    vertex *modello = NULL;
    BITMAP *buffer;
    int update = 0;
    
    double X_Angle ;
    double Y_Angle ;
    double Z_Angle ;
   
   
    X_Angle = 05 * PI / 04;
    Y_Angle = 07 * PI / 04;
    Z_Angle = 01 * PI / 02;
     
    //X_Angle = 3*PI/4; // Asse Rosso
    //Y_Angle = 1*PI/4;   // Asse Bianco
    //Z_Angle = 0;  // Asse Verde
    
    
    
    
    buffer = create_bitmap(X_RES, Y_RES);
    

    if ((modello = (vertex *)init_model(modello)) == NULL) {
        allegro_message("Errore durante l'inizializzazione del modello 3D");
        allegro_message("fine");
		exit(-1);
	}

    clear(buffer);
    update = 1;

	while (!key[KEY_ESC]) {	
	  if (mouse_b & 1) {
         X_Angle += PI/400;
         Y_Angle += PI/400;
         //Z_Angle += PI/400;         
         update = 1;
      } 
      if (mouse_b & 2)  {
         X_Angle -= PI/400;
         Y_Angle -= PI/400;
         //Z_Angle -= PI/400;         
         update = 1;                          
      }
		
      if (key[KEY_PGUP])  {
         Z_Angle += PI/360;         
         update = 1;                          
      }
		
		
		
		
      if (update == 1) {

          clear_to_color(buffer,makecol32(0,0,0));      
          
          textprintf_ex(buffer, font, 10, 10, makecol(255,255,255),-1,"%dx%d", last_fps, avg_fps);
                                        
          plot_modello(modello,buffer,X_Angle, Y_Angle, Z_Angle);                                                                            
          
          fps++;
          //textout fps, avgfps, lastfps, etc//
          //textmode(makecol(0,0,0));
          //textprintf_ex(buffer,font,0,0,makecol(0,0,0),"FPS: %i  Average FPS: %i", last_fps, avg_fps);
           


          
          
          
          blit(buffer,screen,0,0,0,0,X_RES,Y_RES);  
          
          
          
          
          
          
          if(X_Angle > 2*PI) X_Angle=0;
          if(X_Angle < 0)    X_Angle=2*PI;
          if(Y_Angle > 2*PI) Y_Angle=0;
          if(Y_Angle < 0)    Y_Angle=2*PI;
          if(Z_Angle > 2*PI) Z_Angle=0;
          if(Z_Angle < 0)    Z_Angle=2*PI;
          
          update = 0;
      }		
	}
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = SCREEN_DEPTH;
	set_color_depth(depth);
	//res = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, X_RES, Y_RES, 0, 0);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, X_RES, Y_RES, 0, 0);
	
	
	
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	//install_timer();
    install_timer();
    install_int_ex(fps_timer,SECS_TO_TIMER(1));

	
	
	install_keyboard();
	install_mouse();
	
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
    show_mouse(screen);
	
}

void deinit() {
	clear_keybuf();
}
