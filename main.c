#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




// nasm -f elf64 ft_strlen.s -o ft_strlen.o
// gcc -no-pie ft_strlen.o main.c -o test_main
// That flag is telling gcc not to make a position independent executable (PIE). 
// It just means that the code is position independent. 
// A result of PIE is that Address Space Layout Randomization (ASLR) can be enabled (these days the default for security reasons, which is why also PIE is the default these days).
extern int ft_strlen(const char *str);
extern char *ft_strcpy(char *dest, const char *src);
ssize_t ft_write(int fd, const void *buf, size_t count);

void strlen_test() {
    printf("\n--------------ft_strlen---------------\n\n");
    const char *test_str1 = "Hello, World!";
    int length = ft_strlen(test_str1);
    printf("Length of '%s' is: %d\n", test_str1, length);
}

void		strcpy_test()
{
	printf("\n--------------ft_strcpy---------------\n\n");

	char str1[] = "Brigitte";
	char str2[] = "Bruno";

	printf("str1: %s\n", str1);
	ft_strcpy(str1, str2);
	printf("str1: %s\n", str1);
}

void	write_test()
{
	printf("\n--------------ft_write---------------\n\n");
	char buf[] = "Hello World\n";
	int fd = 1;
	int n = strlen(buf);
    // Test 1: Valid buffer
	errno = 0;
	printf("write() return value \t\t [%zd]\n", write(fd, buf, n));
	printf("ft_write() return value \t [%zd]\n", ft_write(fd, buf, n));
	printf("\n");
    // Test 2: Null buffer with zero length
	errno = 0;
	printf("write() return value \t\t [%zd]\n", write(fd, NULL, 0));
	printf("write() errno \t\t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
	errno = 0;
	printf("ft_write() return value \t [%zd]\n", ft_write(fd, NULL, 0));
	printf("ft_write() errno \t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
    // Test 3: Invalid file descriptor with NULL buffer
	errno = 0;
	printf("write() return value \t\t [%zd]\n", write(-1, NULL, 0));
	printf("write() errno \t\t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
	errno = 0;
	printf("ft_write() return value \t [%zd]\n", ft_write(-1, NULL, 0));
	printf("ft_write() errno \t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
}

int main () {
    strlen_test();
    strcpy_test();
    write_test();
    return 0;
}