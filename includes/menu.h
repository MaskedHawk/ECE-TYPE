#ifndef _MENU_H_
#define _MENU_H_

/* include */
#include <allegro.h>
#include <stdio.h>

/* struct */
typedef struct element
{
  int X;
  int Y;
  BITMAP* bmp;
}t_element;

typedef struct menu
{
  element* arrow;
  element* menu;
  element* logo;
} t_menu;


#endif /* !_STUDENT_H_ */
