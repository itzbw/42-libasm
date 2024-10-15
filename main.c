#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>


 #define BOLD "\033[1m"
    #define GREEN "\033[32m"
    #define RED "\033[31m"
	#define YELLOW "\033[33m"
    #define NC "\033[0m"

	#define BUFFER_SIZE 1000


// nasm -f elf64 ft_strlen.s -o ft_strlen.o
// gcc -no-pie ft_strlen.o main.c -o test_main
// That flag is telling gcc not to make a position independent executable (PIE). 
// It just means that the code is position independent. 
// A result of PIE is that Address Space Layout Randomization (ASLR) can be enabled (these days the default for security reasons, which is why also PIE is the default these days).

extern int errno;

int ft_strlen(const char *str);
char *ft_strcpy(char *dest, const char *src);
ssize_t ft_write(int fd, const void *buf, size_t count);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);

void strlen_test() {
    printf(BOLD"\n--------------ft_strlen---------------\n"NC);
    char	*str[] = {
		"test12345",
		"1",
		"test",
		"",
		"\n",
		"zzzzzzzzzzzzzzzzzzzzzzzz hey",
	};

	int	numStrings = sizeof(str) / sizeof(str[0]);

	for (int i = 0; i < numStrings; i++) {
		int	expected = strlen(str[i]);
		int	result = ft_strlen(str[i]);

		printf(expected == result ? GREEN "OK" NC : RED "KO" NC);
		printf("\t strlen: %d\t ft_strlen: %d\n", expected, result);
	}
}

void		strcpy_test()
{
	printf(BOLD "\n---------ft_strcpy--------\n" NC);

	char	*str[] = {
		"brigitte",
		"bruno",
		"test123",
		"",
		"lalaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	};

	int	numStrings = sizeof(str) / sizeof(str[0]);

	for (int i = 0; i < numStrings; i++) {
		// Test return value
		char	buff[BUFFER_SIZE];

		void	*ref_ptr = strcpy(buff, str[i]);
		void	*test_ptr = ft_strcpy(buff, str[i]);
		printf(YELLOW "\n---------Test return valuey--------\n" NC);
		printf(ref_ptr == test_ptr ? GREEN "POINTER OK" NC : RED "POINTER KO" NC);
		printf("\tstrcpy: %p\tft_strcpy: %p\n", ref_ptr, test_ptr);

		// Test destination string
		char	ref_dest[BUFFER_SIZE];
		char	test_dest[BUFFER_SIZE];

		strcpy(ref_dest, str[i]);
		ft_strcpy(test_dest, str[i]);
		printf(YELLOW "\n---------Test destination string--------\n" NC);
		printf(strcmp(ref_dest, test_dest) == 0 ? GREEN "COPY OK" NC : RED "COPY KO" NC);
		printf("\t\tstrcpy: %s\tft_strcpy: %s\n", ref_dest, test_dest);
	}
}

void	write_test()
{
	printf(BOLD"\n--------------ft_write---------------\n\n"NC);
	char buf[] = "Hello World\n";
	int fd = 1;
	int n = strlen(buf);
    // Test 1: Valid buffer
	errno = 0;
	printf(BOLD"\nTest 1: Valid buffer\n\n"NC);
	printf("write() return value \t\t [%zd]\n", write(fd, buf, n));
	printf("ft_write() return value \t [%zd]\n", ft_write(fd, buf, n));
	printf("\n");
    // Test 2: Null buffer with zero length
	errno = 0;
	printf(BOLD"\nNull buffer with zero length\n\n"NC);
	printf("write() return value \t\t [%zd]\n", write(fd, NULL, 0));
	printf("write() errno \t\t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
	errno = 0;
	printf("ft_write() return value \t [%zd]\n", ft_write(fd, NULL, 0));
	printf("ft_write() errno \t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
    // Test 3: Invalid file descriptor with NULL buffer
	errno = 0;
	printf(BOLD"\nInvalid file descriptor with NULL buffer\n\n"NC);
	printf("write() return value \t\t [%zd]\n", write(-1, NULL, 0));
	printf("write() errno \t\t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
	errno = 0;
	printf("ft_write() return value \t [%zd]\n", ft_write(-1, NULL, 0));
	printf("ft_write() errno \t\t [%d] \t [%s]\n", errno, strerror(errno));
	printf("\n");
}

void strcmp_test () {


    printf(BOLD "\n-----------ft_strcmp----------\n" NC);



char	*strings1[] = {
		"test123456770797",
		"1",
		"test",
		"",
		"zzzzzzzz",
	};

	char	*strings2[] = {
		"test1234567",
		"2",
		"test2",
		"",
		"zzzz1zzz",
	};

	int	numStrings = sizeof(strings1) / sizeof(strings1[0]);

	for (int i = 0; i < numStrings; i++) {
		int	expected = strcmp(strings1[i], strings2[i]);
		int	result = ft_strcmp(strings1[i], strings2[i]);

		printf(BOLD "%s" NC " vs "BOLD "%s" NC"\n", strings1[i], strings2[i]);
		printf(expected == result ? GREEN "OK" NC : RED "KO" NC);
		printf("\t Expected: %d\tResult: %d\n\n", expected, result);
	}

}

void read_test(){
	printf("\n--------------ft_read---------------\n\n");

	printf(BOLD "\nTesting ft_read\n" NC);

	int fds[] = {
		-1,
		open("read.txt", O_RDONLY, 0644),
		10
	};

	int	numFds = sizeof(fds) / sizeof(fds[0]);

	// Test return value and errno
	for (int j = 0; j < numFds; j++) {
		errno = 0;
		char	ref_buf[BUFFER_SIZE];
		int	ref_ret = read(fds[j], ref_buf, BUFFER_SIZE);
		ref_buf[ref_ret == -1 ? 0 : ref_ret] = '\0';
		int	ref_errno = errno;
		lseek(fds[j], 0, SEEK_SET);	// Reset file pointer
		errno = 0;
		char	test_buf[BUFFER_SIZE];
		int	test_ret = ft_read(fds[j], test_buf, BUFFER_SIZE);
		test_buf[test_ret == -1 ? 0 : test_ret] = '\0';
		int	test_errno = errno;

		printf("\nfd: %d\t", fds[j]);
		printf(ref_ret == test_ret ? GREEN "RETURN OK" NC : RED "RETURN KO" NC);
		printf("\tExpected: %d\tResult: %d\n\t", ref_ret, test_ret);
		printf(ref_errno == test_errno ? GREEN "ERRNO OK" NC : RED "ERRNO KO" NC);
		printf("\tExpected: %d\tResult: %d\n\t", ref_errno, test_errno);
		printf(strcmp(ref_buf, test_buf) == 0 ? GREEN "COPY OK" NC : RED "COPY KO" NC);
		printf("\t\tExpected: %s\tResult: %s\n", ref_buf, test_buf);
	}
	printf("\n");
}

void	strdup_test(void)
{
	printf(BOLD "\nTesting ft_strdup\n" NC);

	const char	*strings[] = {
		"test",
		"1",
		"0",
		"",
		"\0",
		"lalaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	};


	int	numStrings = sizeof(strings) / sizeof(strings[0]);

	for (size_t i = 0; i < numStrings; i++) {
		char	*ref_ptr = strdup(strings[i]);
		char	*test_ptr = ft_strdup(strings[i]);



		printf(strcmp(ref_ptr, test_ptr) == 0 ? GREEN "COPY OK" NC : RED "COPY KO" NC);
		printf("\t\tExpected: %s\tResult: %s\n", ref_ptr, test_ptr);
		free(test_ptr);
		free(ref_ptr);
	}
}


int main () {
    strlen_test();
    strcpy_test();
    write_test();
    strcmp_test();
read_test();
	strdup_test();
    return 0;
}


