# get_next_line

A C function to read a line from a file descriptor, developed as part of the 42 school curriculum.

## Project Goals
- Create a function that reads a line from a file descriptor, returning one line at a time.
- Handle multiple file descriptors efficiently.
- Manage dynamic memory allocation for variable line lengths.
- Integrate into [libft](https://github.com/evandspr/libft) as a reusable utility.

## What I Learned
- **File I/O**: Understood how to use `read()` and manage buffers with `BUFFER_SIZE`.
- **Static Variables**: Learned to use static variables to preserve state across function calls.
- **Memory Management**: Improved skills in allocating and freeing memory dynamically.
- **Edge Cases**: Handled scenarios like empty files, large lines, and EOF.

## Bonus Features
- **Multiple File Descriptors**: Added support to read from several file descriptors simultaneously without mixing their buffers.
- **How I Did It**: Used an array of static buffers indexed by `fd` to keep track of each file descriptor’s reading state. This ensures that calling `get_next_line` on different `fd`s works independently.
- **Purpose**: Makes the function more versatile for real-world applications, like reading from multiple files or inputs at once.

## Files
- `get_next_line.c`: Main function with bonus logic for multiple `fd`s.
- `get_next_line_utils.c`: Helper functions for string manipulation.
- `get_next_line.h`: Header with prototypes.

## Usage
```c
#include "get_next_line.h"

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    line = get_next_line(fd1); // Reads from file1
    printf("File 1: %s", line);
    free(line);

    line = get_next_line(fd2); // Reads from file2
    printf("File 2: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```
**edesprez**

42 Student @ Paris
