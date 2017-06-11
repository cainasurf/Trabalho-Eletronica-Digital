#ifndef __EstruturasDeDados__
#define __EstruturasDeDados__ 1

typedef enum 	{	BLACK,
					RED,
					GREEN,
					BLUE,
					MAGENTA,
					CIAN,
					YELLOW,
					GRAY
				} eCor;

typedef struct {	float x;
					float y;
			   } tPonto;

// ******************************************
//ESTRUTURA CORPO DA COBRA
typedef struct No {tPonto bola;
					struct No* ant;
					struct No* prox;
					eCor collor;
				} tNoCorpo;
typedef struct {
					tNoCorpo* inicio;
					tNoCorpo* fim;
					int numBolas;
					} tCorpo;
// ****************************************
//ESTRUTURA DA COMIDA
typedef struct food {tPonto bolinha;
					struct food* prox;
					eCor collor;
				} tfood;
// ****************************************


#endif		// __EstruturasDeDados__
