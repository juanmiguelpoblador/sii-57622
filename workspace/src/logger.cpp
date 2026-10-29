#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
ssize_t n;
    char buffer[1024];

  // Borrar FIFO por si existiera previamente
unlink("fifo");

/* Crear el FIFO */
if (mkfifo("fifo", 0666) < 0) {
    perror("No puede crearse el FIFO");
    return 1;
}

/* Abrir el FIFO */
fd = open("fifo", O_RDONLY);
if (fd < 0) {
    perror("No puede abrirse el FIFO");
    unlink("fifo");
    return 1;
}

/* Leer de la FIFO */
while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[n] = '\0';
    printf("%s", buffer);
    fflush(stdout);
}

if (n < 0) {
    perror("Error al leer de la FIFO");
}

/* Cerrar y eliminar el FIFO */
close(fd);
unlink("fifo");

return 0;

}
