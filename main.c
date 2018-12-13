#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int size, sum = 0;
    struct stat s;
    unsigned long long limit;
    char *str;
    int pid;

    int fd = open ("input.txt", O_RDONLY);
    int status = fstat(fd, &s);
    size = s.st_size;

    str = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    int *shared = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    pid = fork();
    if (pid) {
        limit =  (unsigned long long) str + (size / 2);
        while (*((char*) limit) != '\n')
            limit++;
    } else {
        limit = (unsigned long long) str + size;
        str = str + (size / 2) + 1;

        while (*(str) != '+' && *(str) != '-')
            str++;
    }

    str--;
    while (str < limit) {
        int val = 0;
        int positive = *(++str) == '+';
        int digit = *(++str);

        do {
            val = val * 10 + digit - '0';
        } while ((digit = *(++str)) > '\n');

    	if (!positive) {
    		val = -val;
    	}

        sum += val;
    }

    if (pid) {
        wait(pid);
        sum += *shared;
        printf("%d\n", sum);
    } else {
        *shared = sum;
    }

    return 0;
}