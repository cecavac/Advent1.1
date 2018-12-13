#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int size, sum = 0, value;
    struct stat s;
    char *limit;
    int ret;
    char *str;

    int fd = open ("input.txt", O_RDONLY);
    int status = fstat(fd, &s);
    size = s.st_size;

    str = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    limit = str + size;
    for (str = str; str < limit; str++) {
        int val = 0;
        int positive = *(str++) == '+';

        while (*str > '\n') {
            val = val * 10 + *(str++) - '0';
        }

    	if (positive) {
    		sum += val;
    	} else {
    		sum -= val;
    	}
    }

    printf("%d\n", sum);

    return 0;
}