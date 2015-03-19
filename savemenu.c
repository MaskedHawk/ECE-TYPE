
/* allegro init function */
void init_allegro()
{ 
  allegro_init();
  install_keyboard();
  install_timer();
  set_color_depth(desktop_color_depth());

  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
  {
    allegro_message("prb gfx mode");
    allegro_exit();
    exit(EXIT_FAILURE);
  }
  
}

/* move arrow key */
int move_arrow(int arrowY, int i)
{
  arrowY += (32*i);
  
  return(arrowY);
}

void draw_menu(int arrowX, int arrowY, int menuX, int menuY, int logoX, int logoY,
	       int i, BITMAP* logo, BITMAP* display, BITMAP* menu, BITMAP* arrow)
{
   /* darw logo and menu */
    draw_sprite(display, logo, logoX, logoY);
    draw_sprite(display, menu, menuX, menuY);
    draw_sprite(display, arrow, arrowX, arrowY);

    blit(display,screen,0,0,0,0,display->w,display->h);
    clear_bitmap(display);

    i+=1;
    if(i>=800) i=0;

}
int main()
{
  init_allegro(); 

  /*********
Need to be move into .h
*************************/
  BITMAP *bgImage = NULL;
  BITMAP *display = NULL;
  BITMAP *logo = NULL;
  BITMAP *menu =NULL;
  BITMAP *arrow =NULL;
/***********************************/
  int i;
  int choice = 0;
  
/* init display 
check if it can be in .h*/
  display = create_bitmap(800,600);
  clear_bitmap(display);

  menu = load_bitmap("images/text.bmp",NULL);
  logo = load_bitmap("images/logo.bmp",NULL);
  bgImage= load_bitmap("images/starBG.bmp",NULL);
  arrow= load_bitmap("images/arrow.bmp",NULL);

/* set position */
  int arrowX = (((SCREEN_W/2)-(menu->w/2))-20);
  int arrowY = (((SCREEN_H/2)-(menu->h/2))+ 50);
  int logoX = ((SCREEN_W/2)-(logo->w/2));
  int logoY = (((SCREEN_H/2)-(logo->h/2)) -100);
  int menuX = ((SCREEN_W/2)-(menu->w/2));
  int menuY = (((SCREEN_H/2)-(menu->h/2))+ 50);
  i = 0;
  while(!key[KEY_ESC])
  {
    /* scrolling background */
    draw_sprite(display, bgImage, 0 - i, 0);
    draw_sprite(display, bgImage, SCREEN_W - i, 0);

    /* draw menu */
    draw_menu(arrowX, arrowY, menuX, menuY, logoX, logoY,i , logo, display,menu,arrow);
    
    if(key[KEY_UP] && arrowY > menuY && i % 4 == 0)
      arrowY = move_arrow(arrowY, -1);
    if(key[KEY_DOWN] && arrowY < menuY + 50 && i % 4 == 0)
      arrowY = move_arrow(arrowY, 1);

    /* tmp tmp tmp tmp */
    /*******************/
    textprintf_ex(screen, font, 10, 10, makecol(255, 100, 200),-1, "%d", arrowY);
    /**************************/
    /* 50 HZ */
    rest(20);    
  }
  /* transform arrowvalue into choice */
  choice = (arrowY -312 ) / 32;

  /* return choice */
  return choice;
}END_OF_MAIN();
