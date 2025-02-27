// #include <stdio.h>
// #include "ft_printf.h"

// int main(void)
// {
// 	// Basic tests
// 	ft_printf("Character = A and yours: %c:\n", 'A');
// 	ft_printf("String = 'Hello, World!' and yours: %s:\n", "Hello, World!");
// 	ft_printf("Integer = 42 and yours: %d:\n", 42);
// 	ft_printf("Unsigned Integer = 42 and yours: %u:\n", 42);
// 	ft_printf("Hexadecimal = 2a and yours: %x:\n", 42);
// 	ft_printf("Pointer = 0x12345678 and yours: %p:\n", (void*)0x12345678);
// 	// Edge cases
// 	ft_printf("Null string = (null) and yours: %s:\n", NULL);
// 	ft_printf("Zero = 0 and yours: %d:\n", 0);
// 	ft_printf("Negative number = -42 and yours: %d:\n", -42);
// 	ft_printf("Large number = 2147483647 and yours: %d:\n", 2147483647);
// 	ft_printf("Large unsigned number = 4294967295 and yours: %u:\n", 4294967295U);
// 	ft_printf("Hexadecimal with leading zeros = 0000002a and yours: %08x:\n", 42);
// 	ft_printf("Pointer to NULL = (nil) and yours: %p:\n", NULL);
// 	// Mixed format specifiers
// 	ft_printf("Mix: A string 42 42 2a 0x12345678 and yours: %c %s %d %u %x %p:\n", 'A', "string", 42, 42, 42, (void*)0x12345678);
// 	// Width and precision
// 	ft_printf("Width = '        42' and yours: %10d:\n", 42);
// 	ft_printf("Precision = '00042' and yours: %.5d:\n", 42);
// 	ft_printf("Width and precision = '     00042' and yours: %10.5d:\n", 42);
// 	ft_printf("Left-justified = '42        ' and yours: %-10d:\n", 42);
// 	// Special characters
// 	ft_printf("Percent sign = %% and yours: %%:\n");
// 	ft_printf("Newline = '\\n' and yours: \n:\n");
// 	ft_printf("Tab = '\\tEnd of tab' and yours: \tEnd of tab:\n");
// 	// Complex cases
// 	ft_printf("Complex mix: 'A string -42 4294967295 deadbeef (nil)' and yours: %c %s %d %u %x %p:\n", 'A', "string", -42, 4294967295U, 0xDEADBEEF, NULL);
// 	ft_printf("Width and precision with string = '     Hello' and yours: %10.5s:\n", "Hello, World!");
// 	ft_printf("Width and precision with string = 'Hello' and yours: %.5s:\n", "Hello, World!");
// 	ft_printf("Width and precision with string = '     Hello' and yours: %10.5s:\n", "Hello");
// 	// Edge cases with characters
// 	ft_printf("Null character = '\\0' and yours: %c:\n", '\0');
// 	ft_printf("Character with large width = '                                                 A' and yours: %50c:\n", 'A');
// 	ft_printf("Character with negative width = 'A                                                 ' and yours: %-50c:\n", 'A');
// 	int i = ft_printf("%o   %Q   %% %% %d  %s   %p   %p", -2147488, "Hel1lo", "kks", (void *)-2);
// 	ft_printf("\n\n%d", i);
// 	return 0;
// 	close (2);
// 	int count = ft_printf("hello");
// 	printf("\n%d\n", count);
// 	printf("Testing write(1, 0, 0) with stdout open:\n");
//     if (write(1, 0, 0) == -1) {
//         perror("Error writing to stdout");
//         return -1;
//     } else {
//         printf("Write to stdout succeeded\n");
//     }
//     // Close stdout and attempt the write again
//     printf("Testing write(1, 0, 0) with stdout closed:\n");
//     close(1);
//     if (write(1, 0, 0) == -1) {
//         perror("Error writing to stdout");
//         return -1;
//     } else {
//         printf("Write to stdout succeeded\n");
//     }
//     // Reopen stdout to /dev/null to avoid crashing the program
//     int fd = open("test.txt", O_WRONLY);
//     if (fd != -1) {
//         dup2(fd, 1);
//         close(fd);
//     }
//     printf("Testing write(1, 0, 0) with stdout redirected to /dev/null:\n");
//     if (write(1, 0, 0) == -1) {
//         perror("Error writing to stdout");
//         return -1;
//     } else {
//         printf("Write to stdout succeeded\n");
//     }
// 	//int i = ft_printf("%o   %s   %% %% %d  %s   %p   %p", 2147488, "Hel1lo", -2147488, "kks", (void *)-1, (void *)-1);
// 	return 0;
// }
// #include "ft_printf.h"
// int main(void)
// {
//     // Test ft_printf with signed integers
//     ft_printf("Testing ft_printf with signed integers:\n");
//     ft_printf("%d\n", 12345);
//     ft_printf("%d\n", -12345);
//     ft_printf("%d\n", 0);
//     // Test ft_printf with unsigned integers
//     ft_printf("Testing ft_printf with unsigned integers:\n");
//     ft_printf("%u\n", 12345);
//     ft_printf("%u\n", 4294967295); // Maximum value for unsigned int
//     ft_printf("%u\n", 0);
//     return 0;
// }
// #include "ft_printf.h"
// int main(void)
// {
//     // Test signed integers
//     ft_printf("Signed integers:\n");
//     ft_printf("%d\n", 12345);
//     ft_printf("%d\n", -12345);
//     ft_printf("%d\n", 0);
//     // Test unsigned integers
//     ft_printf("Unsigned integers:\n");
//     ft_printf("%u\n", 12345);
//     ft_printf("%u\n", 4294967295); // Maximum value for unsigned int
//     ft_printf("%u\n", 0);
//     // Test hexadecimal (lowercase)
//     ft_printf("Hexadecimal (lowercase):\n");
//     ft_printf("%x\n", 255);
//     ft_printf("%x\n", 4294967295);
//     // Test hexadecimal (uppercase)
//     ft_printf("Hexadecimal (uppercase):\n");
//     ft_printf("%X\n", 255);
//     ft_printf("%X\n", 4294967295);
//     // Test characters
//     ft_printf("Characters:\n");
//     ft_printf("%c\n", 'A');
//     ft_printf("%c\n", 'z');
//     // Test strings
//     ft_printf("Strings:\n");
//     ft_printf("%s\n", "Hello, world!");
//     ft_printf("%s\n", "");
//     // Test pointers
//     ft_printf("Pointers:\n");
//     int a = 42;
//     ft_printf("%p\n", &a);
//     // Test mixed format
//     ft_printf("Mixed format:\n");
//     ft_printf("Int: %d, Unsigned: %u, Hex: %x, Char: %c, String: %s, Pointer: %p\n", 12345, 12345, 255, 'A', "Hello", &a);
//     return 0;
// }
// #include "ft_printf.h"
// #include <stdio.h
// int main(){
// 	ft_printf("%p\n", "hello");
// 	printf("%ld\n", (unsigned long)"hello");
// 	printf("%p\n", NULL);
// }
// #include <unistd.h>
// #include <stdio.h>
// #include <assert.h>
// #include "ft_printf.h"
// int main() {
//     assert(write(1, "", 0) == 0);
//     ft_printf("Test case 1 passed: Writing zero bytes succeeded\n");  
//     const char *msg = "Hello, World!\n";
//     ssize_t bytes_written = write(1, msg, 14);
//     assert(bytes_written == 14);
//     ft_printf("Test case 2 passed: Writing a valid string succeeded\n");
//     assert(write(1, msg, 14) == -1);
//     ft_printf("Test case 3 passed: Writing to an invalid file descriptor failed as expected\n");
//     return 0;
// }
// #include "ft_printf.h"
// #include <libc.h>
// int main(){
// 	int i = ft_printf("%d     %c    ----- %u   %p .... %i -----____----- %x ---- %X", 3654, 'd', 3334, 62534, 8375, 53675, 9723);
// 	printf("\n%d\n", i);
// }