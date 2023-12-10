#include "myl.h"
#include <unistd.h>
#include <stdlib.h>

/*
Function to print a string 
We will use the write system call to print the string to STDOUT
Reference: https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
*/
int printStr(char *str) {
    int len = 0;
    // Calculate the length of the string
    while (str[len] != '\0') {
        len++;
    }

    // Use the write system call to print the string to STDOUT
	// 1 is the file descriptor for STDOUT
    write(1, str, len);
    return len;
}


/*
Function to print an integer
We go through the following steps:
1. Allocate dynamic memory for a character array (string) to store the integer
2. Convert the integer to a character array (string) in reverse order
3. Reverse the string if it's a negative number
4. Use the write system call to print the integer string to STDOUT
5. Free the dynamically allocated memory
*/
int printInt(int num) {
    char *buffer;
    int index = 0;
	int bytes;

    buffer = (char *)malloc(100 * sizeof(char));
    if (buffer == NULL) {
        return ERR;
    }

    // Convert the integer to a character array (string) in reverse order
    if (num == 0) {
        buffer[index++] = '0';
    } 
	else {
        if (num < 0) {
            buffer[index++] = '-';
            num = -num;
        }

        while (num) {
            int digit = num % 10;
            buffer[index++] = (char)(digit + '0');
            num /= 10;
        }

        // Reverse the string if it's a negative number
        if (buffer[0] == '-') {
            int start = 1, end = index - 1;
            while (start < end) {
                char temp = buffer[start];
                buffer[start++] = buffer[end];
                buffer[end--] = temp;
            }
        } 
		else {
            // Reverse the string if it's a positive number
            int start = 0, end = index - 1;
            while (start < end) {
                char temp = buffer[start];
                buffer[start++] = buffer[end];
                buffer[end--] = temp;
            }
        }
    }
	// Calculate the number of bytes in the string
    bytes = index;

    // Use the write system call to print the integer string to STDOUT
    write(1, buffer, bytes);

    free(buffer);

    return bytes;
}

/*
A function to read an integer from STDIN
We go through the following steps:
1. Allocate dynamic memory for a character array (string) to store the integer
2. Read one character at a time from STDIN to the buffer
3. Check for invalid characters and set error flag if necessary
4. Convert the character array (string) to an integer
5. Free the dynamically allocated memory
*/
int readInt(int *error) {
    char buffer[1];
    char *numStr;
    int num = 0, len = 0, i;

    // Allocate dynamic memory for the numStr buffer
    numStr = (char *)malloc(20 * sizeof(char));

    if (numStr == NULL) {
        // Handle memory allocation failure
        *error = ERR;
        return 0;
    }

    while (1) {
        // Use the read system call to read one character from STDIN to buffer
        read(0, buffer, 1);

        if (buffer[0] == '\t' || buffer[0] == '\n' || buffer[0] == ' ') {
            break;
        } else if ((buffer[0] < '0' || buffer[0] > '9') && buffer[0] != '-') {
            // Set error flag if the character is not a digit or a minus sign
            *error = ERR;
        } else {
            // Store the digit character in the numStr array
            numStr[len++] = buffer[0];
        }
    }

    // Check for invalid length or empty input
    if (len > 9 || len == 0) {
        *error = ERR;
        free(numStr);  // Free the dynamically allocated memory before returning
        return 0;
    }

    // Convert the numStr array to an integer
    if (numStr[0] == '-') {
        if (len == 1) {
            // Set error flag if there is only a minus sign without digits
            *error = ERR;
            free(numStr);  // Free the dynamically allocated memory before returning
            return 0;
        }
        for (i = 1; i < len; i++) {
            if (numStr[i] == '-') {
                // Set error flag if there is more than one minus sign
                *error = ERR;
            }
            num *= 10;
            num += (int)(numStr[i] - '0');
        }
        // Make the number negative if the first character is a minus sign
        num = -num;
    } else {
        for (i = 0; i < len; i++) {
            if (numStr[i] == '-') {
                // Set error flag if there is a minus sign in the middle of the number
                *error = ERR;
            }
            num *= 10;
            num += (int)(numStr[i] - '0');
        }
    }
    // Free the dynamically allocated memory
    free(numStr);
    return num;
}
