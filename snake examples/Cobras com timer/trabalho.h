#ifndef __Main__
#define __Main__ 1
		
void teclado(unsigned char key, int x, int y);
void tecladoEspecial(int key, int x, int y);

void mouse(int button, int button_state, int x, int y );

void mouseMove(int x, int y );

void desenho(void);
void idle(void);

#endif	// __Main__

