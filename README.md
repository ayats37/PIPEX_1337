# **Pipex**

## **Overview**
**Pipex** is a project that replicates the behavior of Unix pipelines (`|`) using **C** and system calls. It mimics the process of piping commands in a Unix shell, allowing data to flow from one process to another through pipes. This project is part of the **42 curriculum** and focuses on essential topics like **process management**, **file descriptor manipulation**, and **inter-process communication**.

In a Unix-like shell, you can chain commands using pipes, which allows the output of one command to be used as the input to another. **Pipex** aims to recreate this behavior with a C program that makes use of system calls such as `pipe()`, `fork()`, `dup2()`, `execve()`, and `waitpid()`.

## **Features**
- Simulates **Unix pipelines** (`cmd1 | cmd2`)
- Handles **input** and **output redirection** (`cmd1 > output.txt`)
- Manages errors like **invalid commands**, **permission issues**, and **missing files**
- **Bonus**: Supports multiple pipes (`cmd1 | cmd2 | cmd3`) and **here_doc** mode (reading input until a specific delimiter is encountered)
  
The project demonstrates how to manipulate file descriptors and manage multiple processes using C.

## **System Calls Used**
- **`pipe()`**: Creates a pipe to establish communication between processes.
- **`fork()`**: Creates child processes to execute commands.
- **`dup2()`**: Redirects file descriptors (standard input/output).
- **`execve()`**: Executes commands in the child processes.
- **`waitpid()`**: Waits for child processes to finish execution.

These system calls are fundamental for building **Pipex** and understanding **inter-process communication**.

## **Tests**

### **Mandatory Tests**  
These tests cover basic functionality such as piping between two commands, handling redirections, and checking for errors.

1. **Test 1: Pipe a simple command**  
   - Command:  
     ```sh
     ./pipex infile "cat" "grep hello" outfile
     ```
   - Expected output: It should pipe the contents of `infile` through `cat` and `grep hello`, writing the result to `outfile`.

2. **Test 2: Pipe between two commands with redirection**  
   - Command:  
     ```sh
     ./pipex input.txt "grep pipex" "wc -l" output.txt
     ```
   - Expected output: The number of times "pipex" appears in `input.txt` should be counted and written to `output.txt`.

3. **Test 3: Invalid command**  
   - Command:  
     ```sh
     ./pipex infile "invalidcommand" outfile
     ```
   - Expected output:  
     ```sh
     error: invalidcommand: command not found
     ```

4. **Test 4: Missing file**  
   - Command:  
     ```sh
     ./pipex nonexistentfile "ls" output.txt
     ```
   - Expected output:  
     ```sh
     error: nonexistentfile: No such file or directory
     ```

5. **Test 5: Redirecting output to a file**  
   - Command:  
     ```sh
     ./pipex input.txt "grep pipex" "sort" output.txt
     ```
   - Expected output: The contents of `input.txt` should be piped through `grep pipex` and `sort`, with the result written to `output.txt`.

### **Bonus Tests**  
These tests involve multiple pipes and the **here_doc** mode.

1. **Test 6: Multiple pipes**  
   - Command:  
     ```sh
     ./pipex infile "cmd1" "cmd2" "cmd3" outfile
     ```
   - Expected output:  
     ```sh
     < infile cmd1 | cmd2 | cmd3 > outfile
     ```
   - Multiple pipes should be used between `cmd1`, `cmd2`, and `cmd3`.

2. **Test 7: Here_doc mode**  
   - Command:  
     ```sh
     ./pipex here_doc "EOF" "cat" "grep pipex" output.txt
     ```
   - Expected output: The program should read from stdin until it encounters `EOF` and then execute `cat` and `grep pipex`.

3. **Test 8: Multiple pipes with redirection**  
   - Command:  
     ```sh
     ./pipex infile "grep pipex" "sort" "uniq" output.txt
     ```
   - Expected output: The contents of `infile` should be processed by `grep`, `sort`, and `uniq`, and the result should be written to `output.txt`.

4. **Test 9: Complex pipe with multiple commands and redirections**  
   - Command:  
     ```sh
     ./pipex input.txt "grep pipex" "wc -l" "sort" output.txt
     ```
   - Expected output: The program should process `input.txt` using `grep`, `wc -l`, and `sort`, and then write the result to `output.txt`.

5. **Test 10: Pipe with no input file**  
   - Command:  
     ```sh
     ./pipex "" "cat" "grep hello" outfile
     ```
   - Expected output:  
     ```sh
     error: No such file or directory
     ```

6. **Test 11: Pipe with no output file**  
   - Command:  
     ```sh
     ./pipex input.txt "cat" "grep hello" ""
     ```
   - Expected output: The program should handle the absence of the output file correctly.

### **Additional Manual Tests**  
- To manually test different scenarios, you can run various combinations of commands such as:
   ```sh
   ./pipex infile "ls -l" "wc -l" outfile
   ./pipex infile "cat" "grep hello" "wc -w" outfile

