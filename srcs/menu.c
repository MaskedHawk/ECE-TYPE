#include "../includes/menu.h"

/* allegro init function */
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

SAMPLE * load_wav_check(char *location)
{
  SAMPLE *music;
  music = load_wav(location);

  if(music == NULL)
  {
    allegro_message("can't load %s", location);
    exit(EXIT_FAILURE);
  }
  
  return(music);  
}
void draw_menu(BITMAP *buffer, t_menu *mainmenu, int i)
{
  /* darw logo and menu */
  draw_sprite(buffer, mainmenu->logo.bmp, mainmenu->logo.X, mainmenu->logo.Y);
  draw_sprite(buffer, mainmenu->menu.bmp, mainmenu->menu.X, mainmenu->menu.Y);
  draw_sprite(buffer, mainmenu->arrow.bmp, mainmenu->arrow.X, mainmenu->arrow.Y);
  
  blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
  
  clear_bitmap(buffer);
  
}


/* move arrow key */
int move_arrow(int arrowY, int i)
{
  arrowY += (32 * i);
  
  return(arrowY);
}

void scroll_background(BITMAP *buffer, BITMAP *bgImage, int i)
{

    draw_sprite(buffer, bgImage, 0 - i, 0);
    draw_sprite(buffer, bgImage, SCREEN_W - i, 0);
}    
int main()
{
  init_allegro();

  /* create t_menu var */
  t_menu *mainmenu;
  mainmenu = malloc(sizeof(t_menu));
  
  /* load bmp file into t_menu var*/
  mainmenu->menu.bmp = load_bmp_check("../images/text.bmp");
  mainmenu->logo.bmp = load_bmp_check("../images/logo.bmp");
  mainmenu->arrow.bmp = load_bmp_check("../images/arrow.bmp");

  /* set position into t_menu var*/
  mainmenu->arrow.X = (((SCREEN_W/2)-(mainmenu->menu.bmp->w/2))-20);
  mainmenu->arrow.Y = (((SCREEN_H/2)-(mainmenu->menu.bmp->h/2))+ 50);
  mainmenu->logo.X = ((SCREEN_W/2)-(mainmenu->logo.bmp->w/2));
  mainmenu->logo.Y = (((SCREEN_H/2)-(mainmenu->logo.bmp->h/2)) -100);
  mainmenu->menu.X = ((SCREEN_W/2)-(mainmenu->menu.bmp->w/2));
  mainmenu->menu.Y = (((SCREEN_H/2)-(mainmenu->menu.bmp->h/2))+ 50);
  
  
  BITMAP *bgImage = NULL;
  bgImage = load_bmp_check("../images/starBG.bmp");
  
  BITMAP *buffer = NULL;
  buffer = create_bitmap(800,600);
  clear_bitmap(buffer);

  SAMPLE *music;
  music = load_wav_check("../music/menu.wav");
  play_sample(music, 255, 128, 1000, 1);
  
  int choice = 0;
  int i = 0;
  
  while(!key[KEY_ENTER])
  {  
    scroll_background(buffer, bgImage, i);
    if(i >= 800) i = 0;
    
    /* draw menu */
    draw_menu(buffer, mainmenu, i);
    
    if(key[KEY_UP] && mainmenu->arrow.Y > mainmenu->menu.Y && i % 4 == 0)
      mainmenu->arrow.Y = move_arrow(mainmenu->arrow.Y, -1);
    if(key[KEY_DOWN] && mainmenu->arrow.Y < mainmenu->menu.Y + 50 && i % 4 == 0)
      mainmenu->arrow.Y = move_arrow(mainmenu->arrow.Y, 1);
    
    /* 50 HZ */
    rest(20);    
    i++;
  }
  /* transform arrowvalue into choice */
  choice = (mainmenu->arrow.Y -312 ) / 32;
  
  /* return choice */
  return (choice);
}END_OF_MAIN();
