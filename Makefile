all:	IP.o Paquete.o Pagina.o Buffer.o MatrizInt.o MatrizDouble.o LectorArchivoTexto.o Router.o Admin.o Host.o Tabla.o Main.o
	g++ -Wall -g -o sim *.o

clean:
	rm *.o && rm sim

clear:
	rm *.log

IP.o:	IP.cpp
	g++ -g -c IP.cpp

Paquete.o:	Paquete.cpp
	g++ -g -c Paquete.cpp

Pagina.o:	Pagina.cpp
	g++ -g -c Pagina.cpp

Buffer.o:	Buffer.cpp
	g++ -g -c Buffer.cpp

MatrizInt.o: 	MatrizInt.cpp
	g++ -g -c MatrizInt.cpp

MatrizDouble.o:	MatrizDouble.cpp
	g++ -g -c MatrizDouble.cpp

LectorArchivoTexto.o:	LectorArchivoTexto.cpp
	g++ -g -c LectorArchivoTexto.cpp

Router.o:	Router.cpp
	g++ -g -c Router.cpp

Admin.o:	Admin.cpp
	g++ -g -c Admin.cpp

Host.o:	Host.cpp
	g++ -g -c Host.cpp

Tabla.o:	Tabla.cpp
	g++ -g -c Tabla.cpp

Main.o:	Main.cpp
	g++ -g -c Main.cpp
