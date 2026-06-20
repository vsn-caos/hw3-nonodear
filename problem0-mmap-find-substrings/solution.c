#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Программе передаются два аргумента: имя файла и строка для поиска.
// Необходимо найти все вхождения строки в текстовом файле,
// используя отображение на память с помощью системного вызова mmap.
// На стандартный поток вывода вывести список всех позиций (с нуля),
// где встречается искомая строка, по одной на строку.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <search_string>\n", argv[0]);
        return 1;
    }

    // TODO: откройте файл, получите его размер через fstat,
    //       отобразите в память через mmap,
    //       найдите все вхождения argv[2] и выведите их позиции


    const char *filename = argv[1];
    const char *substr = argv[2];
    size_t sub_len = strlen(substr);

    if (sub_len == 0) return 0;
    
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    if (st.st_size == 0) {
        close(fd);
        return 0;
    }

    char *mdata = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mdata == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    for (off_t i = 0; i <= st.st_size - (off_t)sub_len; ++i) {
        if (memcmp(mdata + i, substr, sub_len) == 0) {
            printf("%ld\n", (long)i);
        }
    }

    munmap(mdata, st.st_size);
    close(fd);

    return 0;
}
