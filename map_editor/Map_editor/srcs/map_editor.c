/*
From: Alexis Bollia <alexis@bollia.fr>
*/
#include <allegro.h>
#include <stdio.h>
#include <string.h>

#define CASE_W 1600/32
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
  clear_bitmap(screen);

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
void draw_cursor(BITMAP * buffer, int x, int y)
{
    rect(buffer, x, y, x+32, y+32, makecol(0, 255, 0));
}

void save_map(int map[CASE_W][CASE_H])
{
  int y;
  int x;

  FILE * fichier;
  char loc[] = "../map/map.lvl";
  fichier = fopen(loc,"w+");
  
  for (y = 0; y < CASE_H; y++)
  {
    for (x = 0; x < CASE_W; x++)
    {
      fprintf(fichier, "%d ", map[x][y]);
    }
    fprintf(fichier, "\n");
  }
  fclose(fichier);
}

int main()
{
  init_allegro();

  BITMAP* buffer;
  buffer = create_bitmap(800, 768);
  
  BITMAP* bloc;
  bloc = create_bitmap((CASE_W * 32), 600 - 24);
  clear_to_color(bloc, makecol(0, 0, 0));
  blit(bloc, buffer, 0, 0, 0, 0, bloc->w, bloc->h);
    
  BITMAP* select;
  select = load_bmp_check("images/bloc.bmp");
  blit(select, buffer, 0, 0, 0, 768 - 192, select->w, select->h);
  
  int selectX = 0;
  int selectY = 0;

  int x = 0;
  int y = 0;

  int blocx = 0;
/* map */
  int map[CASE_W][CASE_H];

  for (y = 0; y < CASE_H; y++)
  {
    for (x = 0; x < CASE_W; x++)
    {
      map[x][y] = 0;
    }
  }
  x=0;
  y = 0;
  while(!key[KEY_ESC])
  { 
    x = (mouse_x / 32) * 32 + blocx;
    y = (mouse_y / 32) * 32;
    
    draw_sprite(buffer, bloc, - blocx, 0 );
    if ((mouse_x / 32) < CASE_W && (mouse_y / 32) < CASE_H)
    {
      if (mouse_b & 1)
      {
	blit(select, bloc, (selectX) * 32, (selectY) * 32, x ,y ,32, 32);
	map[(x  / 32)][y / 32] = (selectY * 100) + selectX;
      }
    }

    if ( mouse_b & 1 && (mouse_y / 32) >= CASE_H)
    {
      selectY = (((mouse_y / 32) - CASE_H)) ;
      selectX = mouse_x / 32;
    }
/* test */
    textprintf_ex(buffer, font, 10, 10, makecol(255, 100, 200),
		  -1, "%d %d", (x  / 32) +(blocx/32), map[((x  / 32) + (blocx/32))][y / 32]);
/*******/
    
    draw_line(buffer, buffer->w, buffer->h);

/* cursor function */
    if(mouse_y < 576) draw_cursor(buffer, x - blocx, y);
    show_mouse(buffer);
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    if(key[KEY_RIGHT] && blocx < (bloc->w - 800))
    {
      blocx += 32;
      rest(10);
    }
    if(key[KEY_LEFT] && blocx != 0) blocx -= 32;
    rest(20);
  }
  save_map(map);
  for (y = 0; y < CASE_H; y++)
  {
    for (x = 0; x < CASE_W; x++)
    {
      printf("%d ",map[x][y]);
    }
    printf("\n");
  }

  return(0);

}END_OF_MAIN();
