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

# Pipex Test

This repository provides a set of tests for the `pipex` project to ensure its functionality under various conditions.

### 1. **Test 1: Basic Pipe Between Two Commands**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep hello" output.txt
     ```
   - Expected Output:  
     The contents of `input.txt` should be piped through `cat` and then filtered by `grep hello`, writing the result to `output.txt`.

### 2. **Test 2: Pipe with Input and Output Redirection**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "sort" output.txt
     ```
   - Expected Output:  
     The content of `input.txt` should be sorted and written to `output.txt`.

### 3. **Test 3: Pipe With Redirection of Error Output**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep nonexistent" output.txt 2> error.txt
     ```
   - Expected Output:  
     The program should handle the error gracefully, writing error messages to `error.txt`.

### 4. **Test 4: Pipe Between Two Commands with No Input File**  
   - Command:  
     ```bash
     ./pipex nonexistent_input.txt "cat" "sort" output.txt
     ```
   - Expected Output:  
     The program should handle the missing input file and print an appropriate error message without crashing.

### 5. **Test 5: Pipe With Empty Input File**  
   - Command:  
     ```bash
     ./pipex empty.txt "cat" "grep hello" output.txt
     ```
   - Expected Output:  
     No output should be written to `output.txt` since `empty.txt` is empty.

---

### 6. **Test 6: Multiple Commands with Pipes**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep hello" "sort" "uniq" output.txt
     ```
   - Expected Output:  
     The program should pipe the contents of `input.txt` through `cat`, filter lines with "hello", sort the lines, and remove duplicates. The final result should be written to `output.txt`.

### 7. **Test 7: Non-Existent Command in the Middle of a Pipe Chain**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "nonexistentcommand" "grep hello" output.txt
     ```
   - Expected Output:  
     The program should stop and display an error when encountering the `nonexistentcommand` and not proceed further in the pipe chain.

### 8. **Test 8: Pipe with Special Characters in Input**  
   - Command:  
     ```bash
     ./pipex special_chars.txt "cat" "grep 'hello $world'" output.txt
     ```
   - Expected Output:  
     The program should correctly interpret `$world` as part of the string and not expand it as a variable. It should match and output lines containing "hello $world".

### 9. **Test 9: Handling Multiple Redirections Simultaneously**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep hello" "sort" > output.txt 2> error.txt
     ```
   - Expected Output:  
     The program should correctly handle both the standard output and standard error redirections, placing the output into `output.txt` and errors into `error.txt`.

### 10. **Test 10: Missing Input File (Error Handling)**  
   - Command:  
     ```bash
     ./pipex nonexistent_file.txt "cat" "grep hello" output.txt
     ```
   - Expected Output:  
     The program should print an error message, indicating the missing input file and not attempt to create or write to `output.txt`.

### 11. **Test 11: Input File with Large Data (Performance)**  
   - Command:  
     ```bash
     ./pipex large_input.txt "cat" "grep hello" "sort" "uniq" output.txt
     ```
   - Expected Output:  
     The program should successfully handle large input files, process them through the pipes, and output the result to `output.txt`.

### 12. **Test 12: Multiple Pipes with Background Processes**  
   - Command:  
     ```bash
     ./pipex input.txt "cat &" "grep hello" "sort" output.txt
     ```
   - Expected Output:  
     The `cat` command should run in the background, and the rest of the chain should execute normally, producing the expected result in `output.txt`.

### 13. **Test 13: Invalid Command Argument**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep" "123" "wc -l" output.txt
     ```
   - Expected Output:  
     The program should detect the invalid argument `"123"` and return an appropriate error message.

### 14. **Test 14: Handling File Permissions Issues**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep hello" > /root/output.txt
     ```
   - Expected Output:  
     The program should fail due to a lack of permission to write to `/root/output.txt`, displaying an error message.

### 15. **Test 15: Pipe with Environment Variables**  
   - Command:  
     ```bash
     export GREETING="hello"
     ./pipex input.txt "cat" "grep $GREETING" output.txt
     ```
   - Expected Output:  
     The program should correctly handle environment variables and filter lines containing the value of `$GREETING`, which is "hello", writing the results to `output.txt`.
     
### 16. **Test 16: Command in Script**  
   - Command:  
     ```bash
     echo -e "#!/bin/bash\ncat input.txt | grep hello" > test_script.sh
     chmod +x test_script.sh
     ./pipex input.txt "./test_script.sh" output.txt
     ```
   - Expected Output:  
     The program should correctly execute the script `test_script.sh`, which contains a valid pipe, to process the contents of `input.txt` and write the result to `output.txt`. It should behave as if it were running the commands directly from the terminal.

### 17. **Test 17: Pipe Three Commands with Full Path (`/bin/cat`, `/usr/bin/grep`, `/bin/sort`)**
   - Command:  
     ```bash
     ./pipex input.txt "/bin/cat" "/usr/bin/grep hello" "/bin/sort" output.txt
     ```
   - Expected Output:  
     The contents of `input.txt` should be passed through `/bin/cat`, piped into `/usr/bin/grep hello` (filtering lines containing "hello"), and then piped into `/bin/sort`. The result should be written to `output.txt`.

---

## Conclusion

These tests cover both simple cases for basic functionality and more complex scenarios that challenge error handling, edge cases, performance, and environment variable handling. Make sure your implementation can handle all these tests without issues.


