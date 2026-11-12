#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "DatosMemCompartida.h"

using namespace std;

int main()
{
    // Abrimos el archivo de memoria compartida
    int fd_mem = open("memoria", O_RDWR);

    if (fd_mem < 0)
    {
        perror("Error al abrir memoria");
        return 1;
    }

    // Proyectamos el archivo en memoria
    DatosMemCompartida *datos = (DatosMemCompartida *) mmap(
        NULL,
        sizeof(DatosMemCompartida),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd_mem,
        0
    );

    if (datos == MAP_FAILED)
    {
        perror("Error en mmap");
        close(fd_mem);
        return 1;
    }

    close(fd_mem);

    cout << "BOT iniciado correctamente." << endl;

    // Bucle de control
    while (true)
    {
        float posicionPelota = datos->esfera.centro.y;
        float posicionRaqueta = (datos->raqueta1.y1 + datos->raqueta1.y2) / 2.0f;

        if (posicionPelota > posicionRaqueta + 0.2f)
        {
            datos->accion = 1;   // Subir
        }
        else if (posicionPelota < posicionRaqueta - 0.2f)
        {
            datos->accion = -1;  // Bajar
        }
        else
        {
            datos->accion = 0;   // Mantener posición
        }

        usleep(25000);
    }

    munmap(datos, sizeof(DatosMemCompartida));

    return 0;
}
