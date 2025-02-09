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

# Pipex Hard Test Suite

These tests aim to challenge the `pipex` project with more complex scenarios, edge cases, and error handling.

## Tests

### **Advanced Tests**

1. **Test 1: Multiple commands with pipes and redirections (complex chain)**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep 'hello world'" "sort" "uniq" output.txt
     ```
   - Expected output: The content of `input.txt` should be processed through the following steps:
     1. `cat`: Output the content of `input.txt`.
     2. `grep 'hello world'`: Filter lines containing "hello world".
     3. `sort`: Sort the filtered lines.
     4. `uniq`: Remove duplicate lines.
   - Result: The unique sorted lines containing "hello world" should be written to `output.txt`.

2. **Test 2: Non-existent command in the middle of a pipe chain**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "nonexistentcommand" "grep hello" output.txt
     ```
   - Expected output: The command should fail after `nonexistentcommand` is reached, displaying an error message like `command not found`. `output.txt` should not be created.

3. **Test 3: Edge case with an empty input file**  
   - Command:  
     ```bash
     ./pipex empty.txt "cat" "grep hello" output.txt
     ```
   - Expected output: Since `empty.txt` is empty, no output should be written to `output.txt`, and the program should handle this gracefully without errors.

4. **Test 4: Input file with special characters (escaping)**  
   - Command:  
     ```bash
     ./pipex special_chars.txt "cat" "grep 'hello $world'" output.txt
     ```
   - Expected output: The program should correctly interpret `$world` as part of the string, and not expand it. The program should output lines containing "hello $world" to `output.txt`.

5. **Test 5: Pipe with both input and output redirection to non-existent files**  
   - Command:  
     ```bash
     ./pipex non_existent_file "cat" "grep hello" > "non_existent_output_file"
     ```
   - Expected output: It should fail with an error like `No such file or directory` for the input file. `non_existent_output_file` should not be created.

6. **Test 6: Multiple pipes with incorrect file permissions**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep hello" "sort" "uniq" > /root/output.txt
     ```
   - Expected output: It should return a permission error for writing to `/root/output.txt`, since the user likely does not have permission to write to that directory.

7. **Test 7: Handling invalid argument types for commands**  
   - Command:  
     ```bash
     ./pipex input.txt "cat" "grep" 123 "wc -l" output.txt
     ```
   - Expected output: It should return an error indicating that the argument `123` is invalid for `grep`.

8. **Test 8: Pipe with very large files**  
   - Command:  
     ```bash
     ./pipex large_input.txt "cat" "grep hello" "sort" "uniq" output.txt
     ```
   - Expected output: The program should handle large files (e.g., multiple gigabytes) without crashing. It should sort and output the unique lines containing "hello" to `output.txt`.

9. **Test 9: Command that generates large output (buffering test)**  
   - Command:  
     ```bash
     ./pipex large_input.txt "yes hello" "head -n 100000" output.txt
     ```
   - Expected output: The program should process the `yes` command to generate a large number of "hello" strings, pipe the output to `head -n 100000`, and write the first 100,000 "hello" lines to `output.txt`. Ensure no excessive memory usage or crashes.

10. **Test 10: Pipe and file redirection with special characters in filenames**  
    - Command:  
      ```bash
      ./pipex "input with spaces.txt" "grep hello" "wc -l" "output with spaces.txt"
      ```
    - Expected output: The program should correctly handle files with spaces in their names, properly redirect input and output, and count the lines with "hello" in `input with spaces.txt`, writing the result to `output with spaces.txt`.

11. **Test 11: Pipe with environment variables**  
    - Command:  
      ```bash
      export GREETING="hello"
      ./pipex input.txt "cat" "grep $GREETING" output.txt
      ```
   - Expected output: The `grep` command should match lines containing the value of the environment variable `GREETING`, which is "hello". It should write matching lines to `output.txt`.

12. **Test 12: Command chain with a mix of background and foreground processes**  
    - Command:  
      ```bash
      ./pipex input.txt "cat &" "grep hello" "wc -l" output.txt
      ```
   - Expected output: The `cat` command runs in the background while the rest of the pipe chain executes normally, counting the number of lines containing "hello" and writing the result to `output.txt`.

13. **Test 13: Pipe with command failures during multiple redirects**  
    - Command:  
      ```bash
      ./pipex input.txt "cat" "grep hello" "nonexistentcommand" output.txt
      ```
   - Expected output: The program should display an error due to the failure of the `nonexistentcommand` and should not create `output.txt`.

14. **Test 14: Large number of pipes**  
    - Command:  
      ```bash
      ./pipex input.txt $(for i in {1..1000}; do echo "cat"; done) output.txt
      ```
    - Expected output: The program should be able to handle a large number of pipes, properly redirecting each command and writing the output to `output.txt`.

### Conclusion

These advanced tests are designed to push the boundaries of the `pipex` implementation, checking for robust error handling, large file handling, correct processing of special characters, and more complex scenarios like handling environment variables and background processes. Ensure your code can handle these situations gracefully.
