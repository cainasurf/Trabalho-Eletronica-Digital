#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
//********
#include <unistd.h> //usleep(10000);


#if defined (__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "EstruturasDeDados.h"
#include "trabalho.h"
#include "winGL.h"


#define VEL 15

int			wLargura 	= 500,
			wAltura 	= 500;
int 	count = 0;

//tPonto		bolinha;
tPonto		cabeca;
tPonto		delta = { VEL, 0.0 };

//*****************************
tNoCorpo head;
tCorpo		corpo;
eCor cor = YELLOW;
tfood *firstfood, *lastfood;

int b,g; bool gp = false;
bool check;


bool 		automatico = true;

/// ***********************************************************************
/// **
/// ***********************************************************************

void delay(long value) {
	int ii=0;

	while(ii<value)
		ii++;

}

/// ***********************************************************************
/// **
/// ***********************************************************************

void tecladoEspecial(int key, int x, int y) {


	if (g<8 && gp==true); //minimiza a possibilidade do usuário apertar duas setas adjascentes tao rapido
												//que faca com q a cobra ande no sentido contrário da mesma linha que estava andando
												//provocando a colisao da cabeca com o corpo, se existente

	else if (delta.x != 0){ //caso esteja andando em um sentido, só permite a mudanca de direcao, nao de sentido
	switch (key) {
		case GLUT_KEY_UP	: 	delta.y = VEL;
								delta.x = 0.0;
								gp=true;

								break;
		case GLUT_KEY_DOWN	: 	delta.y = -VEL;
								delta.x = 0.0;
								gp=true;

								break;
		}
	}
		else{
			switch (key) {
				case GLUT_KEY_LEFT	: 	delta.x = -VEL;
										delta.y = 0.0;
										gp=true;

										break;
				case GLUT_KEY_RIGHT	: 	delta.x = VEL;
										delta.y = 0.0;
										gp=true;

										break;
		}
	}

	glutPostRedisplay();
}


/// ***********************************************************************
/// **
/// ***********************************************************************

void teclado(unsigned char key, int x, int y) {
	int a=0;

	switch (key) {
		case 27		: 	exit(0);
						break;

		case 'n'	:
		case 'N'	:	automatico = !automatico;
						break;
		case 'd'	: 	printf("CHEAT ACTIVATED:\n" );
									printf("cresce 20...\n" );
									while(a<20){
									criaNo(cor);
									a++;
								}

					break;
		case 'w' : 	printf("CHEAT ACTIVATED:\n" );
								printf("apaga o ultimo segmento:\n" );
								deleteGRUPO(1);
					break;
}
	glutPostRedisplay();
}

/// ***********************************************************************
/// **
/// ***********************************************************************


void criaNo(eCor cir){
		tNoCorpo* NovoNo;

		NovoNo = (tNoCorpo*) malloc(sizeof(tNoCorpo));

		//primeira bola:
		if(corpo.numBolas == 0){
			corpo.inicio = NovoNo;
			corpo.fim = NovoNo;
			corpo.numBolas++;
			NovoNo->ant = &head;

			NovoNo->bola.x = NovoNo->ant->bola.x;
			NovoNo->bola.y = NovoNo->ant->bola.y;

			NovoNo->prox = NULL;

			NovoNo->collor = cir;
		}
		else{
			corpo.fim->prox = NovoNo;
			NovoNo->ant = corpo.fim;
			corpo.fim = NovoNo;
			corpo.numBolas++;

			NovoNo->bola.x = NovoNo->ant->bola.x;
			NovoNo->bola.y = NovoNo->ant->bola.y;

			NovoNo->prox = NULL;

			NovoNo->collor = cir;
		}


}

void deleteGRUPO(int d){
	tNoCorpo* auxg;
	int h=0;

	while(h<d && corpo.numBolas !=0){
		auxg = corpo.fim;
		corpo.fim = corpo.fim->ant; //ULTIMO SERA O PENULTIMO
		corpo.fim->prox = NULL; //ATERRO PROX DO ULTIMO
		free(auxg);
		corpo.numBolas--;
		h++;
	}

}

/// ***********************************************************************
/// **
/// ***********************************************************************

void criaFood(int balor){
	int jn=0;
	check = true;


	tfood* novafood;

	while (jn<balor){
		//define cor
		cor = static_cast<eCor>(rand() % 8);
		while (cor == GRAY || cor == BLACK)
		 cor = static_cast<eCor>(rand() % 8); //randomiza a cor diferente de cinza e preto(contraste c a cabeca)
		//cria elemento na lista food
		novafood = (tfood*) malloc(sizeof(tfood));

		if(jn==0){
			//encadeamento
			firstfood = novafood;
			lastfood = novafood;
			novafood->prox = NULL;
			//cor
			novafood->collor = cor;
			//coordenadas
			novafood->bolinha.x = rand() % wLargura;
			novafood->bolinha.y = rand() % wAltura;

			desenho();

		}
		else{
			lastfood->prox = novafood;
			novafood->prox = NULL;
			lastfood = novafood;
			//cor
			novafood->collor = cor;
			//coord
			novafood->bolinha.x = rand() % wLargura;
			novafood->bolinha.y = rand() % wAltura;

			desenho();
		}
		jn++;

		delay(200000000);

	}
}

void deletefood(tfood* f){
	tfood* auxf;
	auxf = firstfood;

	//caso a comida for a primeira
		if(auxf == f){
			firstfood = f->prox;
			free(f);
		}
		else{
			while(auxf->prox != f){ //acha o anterior ao f
				auxf = auxf->prox;
			}
			auxf->prox = f->prox;
			if(f->prox == NULL) //caso seja o ultimo, atualizo o lastfood
				lastfood = auxf;
				free(f);

		}

}

/// ***********************************************************************
/// **
/// ***********************************************************************
void idle() {
tNoCorpo* aux; //declaro aux
head.bola = cabeca; //atualizo tNoCorpo head


//cria GRUPO DE Food!!!!
	if(firstfood == NULL){
		if(check){ //se a ordem tiver certa, remove o grupo do corpo
			printf("PARABENS!!!!\n" );
			deleteGRUPO(b);
		}
		b++;
		criaFood(b);
	}
//******************************************
if(g==8){ //atualiza posicao da cobra a cada 8 ciclos

//andando em x
	aux = corpo.fim; //inicializo aux
	while(aux != NULL && aux!=&head){ //varre lista da cauda a cabeca
		aux->bola.x = aux->ant->bola.x;//o x do ponto será o x do anterior
		aux = aux->ant; //passa para o no anterior
	}
	cabeca.x += delta.x; //cabeca anda

//andando em y
	aux = corpo.fim;
	while(aux != NULL && aux!=&head ){
		aux->bola.y = aux->ant->bola.y;//
		aux = aux->ant;
	}
	cabeca.y += delta.y;

//******************************************
//orbit em x
	if (cabeca.x > wLargura)
		cabeca.x = 0;
	else
		if (cabeca.x < 0)
			cabeca.x = wLargura;

//orbit em y
	if (cabeca.y > wAltura)
		cabeca.y = 0;
	else
		if (cabeca.y < 0)
			cabeca.y = wAltura;

//******************************************
//colisao cabeca-bolinha
		tfood* cache; cache = firstfood;
		while (cache != NULL){
		if ( (cabeca.x <= (cache->bolinha.x + 10.0)) && (cabeca.y <= (cache->bolinha.y + 10.0)) &&
				 (cabeca.x >= (cache->bolinha.x - 10.0)) && (cabeca.y >= (cache->bolinha.y - 10.0))){

					 criaNo(cache->collor);
	  			 printf("numero de nos: %d\n", corpo.numBolas);

					 if(cache != lastfood){ //se a comida nao for a do topo -> ordem incorreta ->check é falso
					 		check = false;
							printf("COMEU A ERRADA :(\n" );
						}

					 deletefood(cache); //apaga comida do mapa

					 break;

				 }
				cache = cache->prox;
		}

//******************************************
//colisao cabeca corpo
	aux = corpo.fim;
	while (aux != NULL && aux !=corpo.inicio) {
		if ( (cabeca.x <= (aux->bola.x)) && (cabeca.y <= (aux->bola.y)) &&
		 (cabeca.x >= (aux->bola.x)) && (cabeca.y >= (aux->bola.y))) {
			 printf("          WASTED!           \n" );

			 exit(0);
		}
	aux = aux->ant;
	}
	g=0;
	gp=false;
}
g++;
	glutPostRedisplay();
}

/// ***********************************************************************
/// **
/// ***********************************************************************

void desenho(void) {

tNoCorpo* aux;

    glClear(GL_COLOR_BUFFER_BIT);

   	desenhaCirculo(cabeca, 12.5, 12, GRAY);

		//desenha COMIDINHAINHAZINHAS
		tfood* cache; cache = firstfood;
		while (cache != NULL){
			desenhaCirculo(cache->bolinha, 10.0, 15, cache->collor);
			cache = cache->prox;
		}

		//desenha corpo da bibora
		aux = corpo.inicio;
		if(corpo.numBolas != 0){
		while(aux != NULL ){
			//printf("chegou aqui\n");

			desenhaCirculo(aux->bola, 11, 15, aux->collor);
			aux = aux->prox;

		}
	}

    glutSwapBuffers();
}

/// ***********************************************************************
/// **
/// ***********************************************************************

int main(int argc, char** argv) {

int i;

	srand(time(NULL));

	b=2;

	cabeca.x = wLargura / 2.0f;
	cabeca.y = wAltura / 2.0f;

	head.bola = cabeca;
	head.ant = NULL;
	head.prox = corpo.inicio;

	corpo.inicio = NULL;
	corpo.numBolas = 0;

	g=0;
	criaJanela(argc, argv);

    initOpenGL();

    initEventos();

    return 0;
}
