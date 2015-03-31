#include <allegro.h>
#include <stdio.h>
#include <string.h>

#define CASE_W 800/32
#define CASE_H 600/32

/* allegro init function */
void init_allegro()
{ 
  allegro_init();
  if ( install_sound( DIGI_AUTODETECT, MIDI_NONE, NULL) != 0 ) {

    allegro_message( "ERROR: %s", allegro_error );
  }
  install_keyboard();
  install_timer();
  install_mouse();
  
  set_color_depth(desktop_color_depth());
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600 - 24, 0, 0)!= 0)
  {
    allegro_message("prb gfx mode");
    allegro_exit();
    exit(EXIT_FAILURE);
  }
}

BITMAP * load_bmp_check(char *location)
{
  BITMAP *bmp;
  bmp = load_bitmap(location, NULL);

  if(!bmp)
  {
    allegro_message("can't load %s", location);
    exit(EXIT_FAILURE);
  }

  return(bmp);
}

int main()
{

  init_allegro();

  BITMAP* buffer;
  BITMAP* bloc;
  FILE* fichier;
  
  buffer = create_bitmap(800, 600-24);
  bloc = load_bmp_check("images/bloc.bmp");

  int test[CASE_W][CASE_H];
  memset(test, 0, sizeof(test));
  int x,y;
  int value;
  fichier = fopen("../map/map.lvl","r");

  for (y = 0; y<600/32; y++)
  {
    for (x = 0; x< 800 / 32; x++)
    {
      fscanf(fichier, "%d ",&test[x][y]);
      value= test[x][y];
      blit(bloc, buffer, (value % 100) * 32, (value / 100) * 32, x * 32, y *32, 32, 32);
    }
  }
  blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
  while(!key[KEY_ESC])
  {

  }
  
  return 0;
}
