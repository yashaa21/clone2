#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    struct dirent *de;  // Pointer for directory entry

    // Use the directory passed as an argument, else default to "."
    char *dir_name = (argc > 1) ? argv[1] : ".";

    // Open the directory
    DIR *dr = opendir(dir_name);

    if (dr == NULL) {
        printf("Could not open directory: %s\n", dir_name);
        return 1;
    }

    // Read and print all the files and directories
    while ((de = readdir(dr)) != NULL) {
        if (de->d_name[0] != '.')  // Skip hidden files like "." and ".."
            printf("%s  ", de->d_name);
    }

    closedir(dr);
    printf("\n");

    return 0;
}

