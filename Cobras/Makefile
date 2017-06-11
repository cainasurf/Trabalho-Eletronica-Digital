.c.o:   $*.h
	g++ -c $*.c -Wno-deprecated

.cpp.o:	$*.h
	g++	-c $*.cpp -Wno-deprecated

all:	trabalho

trabalho:  trabalho.o winGL.o 
	g++ -o $@ $^ -framework OpenGL -framework GLUT

clean:
	rm *.o *.*~ *~ trabalho