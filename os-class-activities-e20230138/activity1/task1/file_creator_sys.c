/* file_creator_sys.c */
#include <fcntl.h>   // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>  // write(), close()
#include <string.h>  // strlen()

int main() {
    // 1. Open/create "output.txt" using open()
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    // 2. Write "Hello from Operating Systems class!\n" using write()
    char *text = "Hello from Operating Systems class!\n";
    write(fd, text, strlen(text));
    
    // 3. Close the file using close()
    close(fd);
    
    // 4. Print "File created successfully!\n" to the terminal using write()
    char *msg = "File created successfully!\n";
    write(1, msg, strlen(msg));
    
    return 0;
}