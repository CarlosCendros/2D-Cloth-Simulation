#Archivo que genera .exe y .o file
#Este documento servirá para futuros makefile
#Solo has de cambiar los nombres en .o y en .exe

#Asegurate que en la terminal, antes de poner el comando mingw32... pones la direccion exacta del archivo
#Para borrar el .exe y el .o escribir en la terminal "mingw32-make clean"
#cd C:\Users\ccend\OneDrive\Escritorio\C++\Cloth
all: compile link

compile:
	g++ -c main.cpp -I"C:\Users\ccend\OneDrive\Documentos\libraries_code\SFML\include" -DSFML_STATIC
link:
	g++ main.o -o main -L"C:\Users\ccend\OneDrive\Documentos\libraries_code\SFML\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lsfml-main -lopengl32 -lgdi32 -lwinmm -lfreetype -lFLAC -lopenal32 -lpthread -lsfml-system-s -lopenal32 -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg
clean:
	del main.o
	del main.exe