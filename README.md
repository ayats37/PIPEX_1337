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


