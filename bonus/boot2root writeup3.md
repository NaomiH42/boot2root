# bonus - dirtyc0w

After first getting into the server with ssh we can find the kernel version and find out current version is vulnerable to exploit dirtycow. By running our compiled binary, we create a new root user with our selected password. We can check it worked by looking at /etc/passwd file.
https://github.com/FireFart/dirtycow/blob/master/dirty.c

Running su firefart gives us root access, which we can make sure by id command.
