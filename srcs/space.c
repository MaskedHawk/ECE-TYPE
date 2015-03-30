#include <allegro.h>

void init_allegro()
{ 
  allegro_init();
  if ( install_sound( DIGI_AUTODETECT, MIDI_NONE, NULL) != 0 ) {

    allegro_message( "ERROR: %s", allegro_error );
  }
  install_keyboard();
  install_timer();
  
  set_color_depth(desktop_color_depth());
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0)!= 0)
  {
    allegro_message("prb gfx mode");
    allegro_exit();
    exit(EXIT_FAILURE);
  }
}

/* check bitmap function */
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
void scroll_background(BITMAP *buffer, BITMAP *bgImage, int i)
{

    draw_sprite(buffer, bgImage, 0 - i, 0);
    draw_sprite(buffer, bgImage, SCREEN_W - i, 0);
}    

int main()
{

  init_allegro();
  
  BITMAP *bgImage = NULL;
  bgImage = load_bmp_check("../images/starBG.bmp");

  BITMAP *buffer = NULL;
  buffer = create_bitmap(800,600);
  clear_bitmap(buffer);

  int i = 0;
      while(!key[KEY_ENTER])
  {  
    scroll_background(buffer, bgImage, i);
    if(i >= 800) i = 0;
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    clear_bitmap(buffer);

    /* 50 HZ */
    rest(20);    
    i++;
  }
      return(0);
}END_OF_MAIN();
