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
#define TEST_FILE "test_read.txt"

extern int errno;

// Function prototypes
size_t ft_strlen(const char *str);
char *ft_strcpy(char *dest, const char *src);
ssize_t ft_write(int fd, const void *buf, size_t count);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);

// Helper function to print test results
void print_result(const char *test_name, int condition) {
    printf("%s: %s\n", test_name, condition ? GREEN "OK" NC : RED "KO" NC);
}

// Test functions
void test_strlen(void) {
    printf(BOLD"\n----- Testing ft_strlen -----\n"NC);
    const char *test_strings[] = {"test12345", "1", "test", "", "\n", "zzzzzzzzzzzzzzzzzzzzzzzz hey"};
    
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        size_t expected = strlen(test_strings[i]);
        size_t result = ft_strlen(test_strings[i]);
        print_result(test_strings[i], expected == result);
        printf("  strlen: %zu, ft_strlen: %zu\n", expected, result);
    }
}

void test_strcpy(void) {
    printf(BOLD"\n----- Testing ft_strcpy -----\n"NC);
    const char *test_strings[] = {"brigitte", "bruno", "test123", "", "very loooooooooooooooooong string..."};
    
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
        char *res1 = strcpy(buf1, test_strings[i]);
        char *res2 = ft_strcpy(buf2, test_strings[i]);
        
        print_result(test_strings[i], strcmp(buf1, buf2) == 0 && (res1 - buf1) == (res2 - buf2));
        printf("  Original: %s, Copy: %s\n", buf1, buf2);
    }
}

void test_write(void) {
    printf(BOLD"\n----- Testing ft_write -----\n"NC);
    const char *test_string = "Hello, World!\n";
    ssize_t res1, res2;
    int saved_stdout = dup(STDOUT_FILENO);
    
    // Test valid write
    res1 = write(STDOUT_FILENO, test_string, strlen(test_string));
    res2 = ft_write(STDOUT_FILENO, test_string, strlen(test_string));
    print_result("Valid write", res1 == res2);
    
    // Test invalid fd
    errno = 0;
    res1 = write(-1, test_string, strlen(test_string));
    int errno1 = errno;
    errno = 0;
    res2 = ft_write(-1, test_string, strlen(test_string));
    int errno2 = errno;
    printf("errno1: %d | errno2: %d"  , errno1, errno2);
    print_result("Invalid fd", res1 == res2 && errno1 == errno2);
    
    
    // Restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
}

void test_strcmp(void) {
    printf(BOLD"\n----- Testing ft_strcmp -----\n"NC);
    const char *strings1[] = {"test", "1", "test", "", "zzz"};
    const char *strings2[] = {"test", "2", "test2", "", "zzz1"};
    
    for (size_t i = 0; i < sizeof(strings1) / sizeof(strings1[0]); i++) {
        int res1 = strcmp(strings1[i], strings2[i]);
        int res2 = ft_strcmp(strings1[i], strings2[i]);
        print_result("strcmp", (res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) || (res1 == 0 && res2 == 0));
        printf("  '%s' vs '%s': strcmp: %d, ft_strcmp: %d\n", strings1[i], strings2[i], res1, res2);
    }
}

void test_read(void) {
    printf(BOLD"\n----- Testing ft_read -----\n"NC);
    int fd = open(TEST_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening test file");
        return;
    }
    
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    ssize_t res1 = read(fd, buf1, BUFFER_SIZE - 1);
    lseek(fd, 0, SEEK_SET);
    ssize_t res2 = ft_read(fd, buf2, BUFFER_SIZE - 1);
    
    buf1[res1 > 0 ? res1 : 0] = '\0';
    buf2[res2 > 0 ? res2 : 0] = '\0';
    
    print_result("Valid read", res1 == res2 && strcmp(buf1, buf2) == 0);
    printf("  Read content: %s\n", buf2);
    
    close(fd);
    
    // Test invalid fd
    errno = 0;
    res1 = read(-1, buf1, BUFFER_SIZE);
    int errno1 = errno;
    errno = 0;
    res2 = ft_read(-1, buf2, BUFFER_SIZE);
    int errno2 = errno;
    print_result("Invalid fd", res1 == res2 && errno1 == errno2);
}

void test_strdup(void) {
    printf(BOLD"\n----- Testing ft_strdup -----\n"NC);
    const char *test_strings[] = {"test", "1", "0", "", "\0", "very long string..."};
    
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        char *res1 = strdup(test_strings[i]);
        char *res2 = ft_strdup(test_strings[i]);
        
        print_result(test_strings[i], res1 && res2 && strcmp(res1, res2) == 0);
        printf("  Original: %s, Duplicate: %s\n", test_strings[i], res2);
        
        free(res1);
        free(res2);
    }
}

int main(void) {
    test_strlen();
    test_strcpy();
    test_write();
    test_strcmp();
    test_read();
    test_strdup();
    return 0;
}