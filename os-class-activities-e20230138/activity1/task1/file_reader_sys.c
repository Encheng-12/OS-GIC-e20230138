/* file_reader_sys.c */
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[256];
    
    // 1. Open "output.txt" for reading using open()
    int fd = open("output.txt", O_RDONLY);
    
    // 2 & 3. Read content into buffer in a loop and write to terminal (fd 1)
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }
    
    // 4. Close the file using close()
    close(fd);
    
    return 0;
}