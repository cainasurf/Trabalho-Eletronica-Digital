#ifndef __winGL__
#define __winGL__ 1

#include "EstruturasDeDados.h"

void desenhaPonto(tPonto P0, eCor c);
void desenhaCirculo(tPonto P0, float raio, int n, eCor c);
void desenhaLinha(tPonto P0, tPonto P1, eCor c);

void display(void);

void initOpenGL(void);

void reshape(int w, int h);

void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);

void criaJanela(int argc, char** argv);

void initEventos(void);

#endif

