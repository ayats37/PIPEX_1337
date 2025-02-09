# **Pipex**

## **Overview**  
**Pipex** is a project that replicates the behavior of Unix pipelines (`|`) using **C** and system calls. It allows processing of input through multiple commands, mimicking how commands are piped in a Unix shell.

This project is part of the **42 curriculum**, focusing on **process management**, **file descriptor manipulation**, and **inter-process communication**.

## **Features**
- Simulates **Unix pipelines** (`cmd1 | cmd2`)
- Handles **input** and **output redirection**
- Manages errors like **invalid commands**, **permission issues**, and **missing files**
- **Bonus**: Supports multiple pipes (`cmd1 | cmd2 | cmd3`) and **here_doc** mode

## **System Calls Used**
- `pipe()` – Creates pipes between processes
- `fork()` – Creates child processes
- `dup2()` – Redirects file descriptors
- `execve()` – Executes commands
- `waitpid()` – Synchronizes processes

## **Project Structure**
```bash
pipex/
├── Makefile
├── pipex.c
├── pipex.h
├── utils.c
├── error_handling.c
├── README.md
├── libft/  (if used)
└── bonus/  (if bonus part is implemented)
