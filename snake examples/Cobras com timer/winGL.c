#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined (__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "EstruturasDeDados.h"
#include "winGL.h"
#include "trabalho.h"
		
extern GLint	wLargura,
				wAltura;
				
extern int		xRes, 
				yRes;
				
float Cores[8][3] = { 	{0.0, 0.0, 0.0},
						{1.0, 0.0, 0.0},
						{0.0, 1.0, 0.0},
						{0.0, 0.0, 1.0},
						{1.0, 0.0, 1.0},
						{0.0, 1.0, 1.0},
						{1.0, 1.0, 0.0},
						{0.5, 0.5, 0.5} };
						
/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenhaLinha(tPonto P0, tPonto P1, eCor c) {
	
    glBegin(GL_LINES);
		glColor3fv(Cores[c]);
		glVertex2f(P0.x, P0.y);
		glVertex2f(P1.x, P1.y);
    glEnd();   
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenhaPonto(tPonto P, eCor c) {
	
	glColor3fv(Cores[c]);

    glBegin(GL_POINTS);
		glVertex2f(P.x, P.y);
    glEnd();   
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void desenhaCirculo(tPonto P0, float raio, int n, eCor c) {
	
#define GRAD2RAD(a)	(a) * M_PI / 180.0

int i;
tPonto p;
float teta = 360.0 / n;
	
	glColor3fv(Cores[c]);

    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(P0.x, P0.y);
    	for (i = 0.0 ; i <= 360.0 ; i += teta) {
    		p.x = P0.x + raio * cos(GRAD2RAD(i));	
    		p.y = P0.y + raio * sin(GRAD2RAD(i));	
    		glVertex2f(p.x, p.y);
    		}
    glEnd(); 
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void initOpenGL () {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void reshape (int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, w,  0.0, h);
}

/// ***********************************************************************
/// ** 
/// ***********************************************************************

void criaJanela(int argc, char** argv) {
	
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (wAltura, wLargura);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Jogo Snake - Estrutura de Dados");
}


/// ***********************************************************************
/// ** 
/// ***********************************************************************

void initEventos() {
	
    glutDisplayFunc(desenho);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	
	glutMainLoop();

}


