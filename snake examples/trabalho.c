#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#if defined (__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "EstruturasDeDados.h"
#include "winGL.h"
		
int			wLargura 	= 500,
			wAltura 	= 500;
int			count		= 0;
			
tPonto		bolinha;
tPonto		cabeca;
tPonto		delta = { 2.0, 0.0 };
bool 		automatico = true;

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void tecladoEspecial(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP	: 	delta.y = 2.0; 
								delta.x = 0.0; 
								break;
		case GLUT_KEY_DOWN	: 	delta.y = -2.0; 
								delta.x = 0.0; 
								break;						
		case GLUT_KEY_LEFT	: 	delta.x = -2.0; 
								delta.y = 0.0; 
								break;
		case GLUT_KEY_RIGHT	: 	delta.x = 2.0; 
								delta.y = 0.0; 
								break;						
		}
	glutPostRedisplay();
}
				
/// ***********************************************************************
/// **
/// ***********************************************************************

void delay(int value ) {

	printf("Delay %d\n", count);
	count++;
	bolinha.x += 5;
	bolinha.y += 5;
	
	if (count < 20) { 
//		glutTimerFunc(500, delay, 0);
		glutPostRedisplay();
		}						
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {
	switch (key) {
		case 27		: 	exit(0);
						break;
						
		case 'n'	:	
		case 'N'	:	automatico = !automatico;
						break;
		case 'd'	:
		case 'D'	:	glutTimerFunc(500, delay, 0);
						count=0;
						break;
						
		}
	glutPostRedisplay();
}
		
/// ***********************************************************************
/// **
/// ***********************************************************************

void mouse(int button, int button_state, int x, int y ) {
	
	if 	(button_state == GLUT_DOWN ) {
		switch (button) {
			
			case GLUT_LEFT_BUTTON	: 	cabeca.x = x;
										cabeca.y = wLargura - y;
										break;
	
			case GLUT_RIGHT_BUTTON	:	bolinha.x = x;
										bolinha.y = wLargura - y;
										break;
			}
		glutPostRedisplay();
		}
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void idle() {
	
	cabeca.x += delta.x;
	if (cabeca.x > wLargura) 
		cabeca.x = 0;
	else 
		if (cabeca.x < 0) 
			cabeca.x = wLargura;
	cabeca.y += delta.y; 
	if (cabeca.y > wAltura) 
		cabeca.y = 0;
	else 
		if (cabeca.y < 0) 
			cabeca.y = wAltura;

	if ( (cabeca.x <= (bolinha.x + 10.0)) && (cabeca.y <= (bolinha.y + 10.0)) &&
		 (cabeca.x >= (bolinha.x - 10.0)) && (cabeca.y >= (bolinha.y - 10.0))) {
		bolinha.x = rand() % wLargura;
		bolinha.y = rand() % wAltura;
		}		
		
	glutPostRedisplay();
}							

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenho(void) {

int i;

    glClear(GL_COLOR_BUFFER_BIT); 
    
   	desenhaCirculo(cabeca, 15.0, 6, RED);
    
    desenhaCirculo(bolinha, 20.0, 15, BLUE);
		        	
    glutSwapBuffers();
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

int main(int argc, char** argv) {
	
int i;
	
	srand(time(NULL));
	
	bolinha.x = wLargura / 4.0f;
	bolinha.y = wAltura / 4.0f;

	cabeca.x = wLargura / 2.0f;
	cabeca.y = wAltura / 2.0f;
		
	criaJanela(argc, argv);
	
    initOpenGL();
    
    initEventos();
        
    return 0;   
}
