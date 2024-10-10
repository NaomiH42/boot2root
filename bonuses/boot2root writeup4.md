# Bonus - secret_phrase

There is an additional unused function in the `bomb` binary:

``` shell
(gdb) i func
...
0x08048ee8  secret_phase
...
```

Let's disassemble:

``` asm
(gdb) disas secret_phase 
Dump of assembler code for function secret_phase:
   0x08048ee8 <+0>:	push   %ebp
   0x08048ee9 <+1>:	mov    %esp,%ebp
   0x08048eeb <+3>:	sub    $0x14,%esp
   0x08048eee <+6>:	push   %ebx
   0x08048eef <+7>:	call   0x80491fc <read_line>
   0x08048ef4 <+12>:	push   $0x0
   0x08048ef6 <+14>:	push   $0xa
   0x08048ef8 <+16>:	push   $0x0
   0x08048efa <+18>:	push   %eax
   0x08048efb <+19>:	call   0x80487f0 <__strtol_internal@plt>
   0x08048f00 <+24>:	add    $0x10,%esp
   0x08048f03 <+27>:	mov    %eax,%ebx
   0x08048f05 <+29>:	lea    -0x1(%ebx),%eax
   0x08048f08 <+32>:	cmp    $0x3e8,%eax
   0x08048f0d <+37>:	jbe    0x8048f14 <secret_phase+44>
   0x08048f0f <+39>:	call   0x80494fc <explode_bomb>
   0x08048f14 <+44>:	add    $0xfffffff8,%esp
   0x08048f17 <+47>:	push   %ebx 
   0x08048f18 <+48>:	push   $0x804b320
   0x08048f1d <+53>:	call   0x8048e94 <fun7>
   0x08048f22 <+58>:	add    $0x10,%esp
   0x08048f25 <+61>:	cmp    $0x7,%eax
   0x08048f28 <+64>:	je     0x8048f2f <secret_phase+71>
   0x08048f2a <+66>:	call   0x80494fc <explode_bomb>
   0x08048f2f <+71>:	add    $0xfffffff4,%esp
   0x08048f32 <+74>:	push   $0x8049820
   0x08048f37 <+79>:	call   0x8048810 <printf@plt>
   0x08048f3c <+84>:	call   0x804952c <phase_defused>
   0x08048f41 <+89>:	mov    -0x18(%ebp),%ebx
   0x08048f44 <+92>:	mov    %ebp,%esp
   0x08048f46 <+94>:	pop    %ebp
   0x08048f47 <+95>:	ret    
End of assembler dump.
```

Apart from knowing we need to satisfy the condition `number - 1 > 1000`, there are no specific input requirements mentioned here. Our focus is on the `phase_defused` function, which is repeated across the levels. We observe a check against a string (`austinpowers`), which is passed if the second word entered during phase 4 matches:

```
   0x0804955e <+50>:	push   $0x8049d09
   0x08049563 <+55>:	push   %ebx
   0x08049564 <+56>:	call   0x8049030 <strings_not_equal>


(gdb) x/s 0x8049d09
0x8049d09:	"austinpowers"
```

This way, we found an alternative method of defusing the `bomb` binary.
``` shell
$ ./bomb
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Public speaking is very easy.
Phase 1 defused. How about the next one?
1 2 6 24 120 720
That's number 2.  Keep going!
1 b 214
Halfway there!
9 austinpowers
So you got that one.  Try this one.
opekmq
Good work!  On to the next...
4 2 6 3 1 5
Curses, you've found the secret phase!
But finding it and solving it are quite different...
1001
Wow! You've defused the secret stage!
Congratulations! You've defused the bomb!
```
