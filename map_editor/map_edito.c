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
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 768, 0, 0)!= 0)
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

void draw_line(BITMAP * buffer, int xmax, int ymax)
{
  int i;
  for(i = 32; i <= xmax; i+=32)
    vline(buffer, i, 0, ymax , makecol(0,0,0));
  for(i = 32; i <= ymax; i+=32)
    hline(buffer, 0, i, xmax, makecol(0,0,0));
}
void draw_rectangle(BITMAP * buffer, int x, int y)
{
    rect(buffer, x, y, x+32, y+32, makecol(0, 255, 0));
}

void save_map(int map[CASE_W][CASE_H])
{
  int y;
  int x;

  FILE * fichier;
  fichier = fopen("map.lvl","w+");
  for (y = 0; y<600/32; y++)
  {
    for (x = 0; x< 800 / 32; x++)
    {
      fprintf(fichier, "%d ", map[x][y]);
    }
      fprintf(fichier, "\n");
  }
  fclose( fichier );
}

int main()
{
  init_allegro();

  BITMAP* buffer;
  BITMAP* bloc;
  BITMAP* select;

  int selectX = 0;
  int selectY = 0;
  int x = 0;
  int y = 0;
  int test[CASE_W][CASE_H];
  
  memset(test, 0, sizeof(test));

  clear_bitmap(screen);

  buffer = create_bitmap(800, 768);
  bloc = create_bitmap(800, 600 - 24);
  select = load_bmp_check("images/bloc.bmp");
  clear_to_color(buffer, makecol(0, 0, 0));
  blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    
  while(!key[KEY_ESC])
  {
    x = (mouse_x / 32) * 32;
    y = (mouse_y / 32) * 32;
    clear_to_color(buffer, makecol(255, 255, 255));

    draw_sprite(buffer, bloc, 0, 0);
    
    blit(select, buffer, 0, 0, 0, 768 - 192, select->w, select->h);
    if ((mouse_x / 32) < CASE_W && (mouse_y / 32) < CASE_H)
    {
      if (mouse_b & 1)
      {
	blit(select, bloc, (selectX) * 32 ,(selectY) * 32, x ,y ,32, 32);
	test[x / 32][y / 32] = (selectY * 100) + selectX;
      }
    }
    if ( mouse_b & 1 && (mouse_y / 32) >= CASE_H)
    {
      selectY = (((mouse_y / 32) - CASE_H)) ;
      selectX = mouse_x / 32;
    }
    textprintf_ex(buffer, font, 10, 10, makecol(255, 100, 200),
		  -1, "%d", selectY);
    draw_line(buffer, buffer->w, buffer->h);
    if(mouse_y < 576) draw_rectangle(buffer, x, y);   
    show_mouse(buffer);  
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

    rest(20);
  }
  save_map(test);
  return(0);
}END_OF_MAIN();
