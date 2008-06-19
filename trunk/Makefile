all:	IP.o Paquete.o Pagina.o Buffer.o MatrizInt.o MatrizDouble.o LectorArchivoTexto.o Router.o Admin.o Host.o Tabla.o Main.o
	g++ -Wall -g -o sim *.o

clean:
	rm *.o && rm sim

clearlogs:
	rm *.log

IP.o:	IP.cpp
	g++ -g -c IP.cpp -Wall

Paquete.o:	Paquete.cpp
	g++ -g -c Paquete.cpp -Wall

Pagina.o:	Pagina.cpp
	g++ -g -c Pagina.cpp -Wall

Buffer.o:	Buffer.cpp
	g++ -g -c Buffer.cpp -Wall

MatrizInt.o: 	MatrizInt.cpp
	g++ -g -c MatrizInt.cpp -Wall

MatrizDouble.o:	MatrizDouble.cpp
	g++ -g -c MatrizDouble.cpp -Wall

LectorArchivoTexto.o:	LectorArchivoTexto.cpp
	g++ -g -c LectorArchivoTexto.cpp -Wall

Router.o:	Router.cpp
	g++ -g -c Router.cpp -Wall

Admin.o:	Admin.cpp
	g++ -g -c Admin.cpp -Wall

Host.o:	Host.cpp
	g++ -g -c Host.cpp -Wall

Tabla.o:	Tabla.cpp
	g++ -g -c Tabla.cpp -Wall

Main.o:	Main.cpp
	g++ -g -c Main.cpp -Wall
