## bomb

# <u>list functions</u>
``` shell
[...]
0x08048b20  phase_1
0x08048b48  phase_2
0x08048b98  phase_3
0x08048ca0  func4
0x08048ce0  phase_4
0x08048d2c  phase_5
0x08048d98  phase_6
[...]
```

# <u>phase1</u>
``` shell
Dump of assembler code for function phase_1:
   0x08048b20 <+0>:	push   %ebp
   0x08048b21 <+1>:	mov    %esp,%ebp
   0x08048b23 <+3>:	sub    $0x8,%esp
   0x08048b26 <+6>:	mov    0x8(%ebp),%eax
   0x08048b29 <+9>:	add    $0xfffffff8,%esp
   0x08048b2c <+12>:	push   $0x80497c0
   0x08048b31 <+17>:	push   %eax
   0x08048b32 <+18>:	call   0x8049030 <strings_not_equal>
   0x08048b37 <+23>:	add    $0x10,%esp
   0x08048b3a <+26>:	test   %eax,%eax
   0x08048b3c <+28>:	je     0x8048b43 <phase_1+35>
   0x08048b3e <+30>:	call   0x80494fc <explode_bomb>
   0x08048b43 <+35>:	mov    %ebp,%esp
   0x08048b45 <+37>:	pop    %ebp
   0x08048b46 <+38>:	ret    
End of assembler dump.
```
Check for <code>av[0]</code> being equal to
``` shell
(gdb) x/s 0x80497c0
0x80497c0:	"Public speaking is very easy."
```
## exploit 1
Public speaking is very easy.

# <u>phase2</u>
``` shell
Dump of assembler code for function phase_2:
   0x08048b48 <+0>:	push   %ebp
   0x08048b49 <+1>:	mov    %esp,%ebp
   0x08048b4b <+3>:	sub    $0x20,%esp
   0x08048b4e <+6>:	push   %esi
   0x08048b4f <+7>:	push   %ebx
   0x08048b50 <+8>:	mov    0x8(%ebp),%edx
   0x08048b53 <+11>:	add    $0xfffffff8,%esp
   0x08048b56 <+14>:	lea    -0x18(%ebp),%eax
   0x08048b59 <+17>:	push   %eax
   0x08048b5a <+18>:	push   %edx
   0x08048b5b <+19>:	call   0x8048fd8 <read_six_numbers>
   0x08048b60 <+24>:	add    $0x10,%esp
   0x08048b63 <+27>:	cmpl   $0x1,-0x18(%ebp)
   0x08048b67 <+31>:	je     0x8048b6e <phase_2+38>
   0x08048b69 <+33>:	call   0x80494fc <explode_bomb>
   0x08048b6e <+38>:	mov    $0x1,%ebx
   0x08048b73 <+43>:	lea    -0x18(%ebp),%esi
   0x08048b76 <+46>:	lea    0x1(%ebx),%eax
   0x08048b79 <+49>:	imul   -0x4(%esi,%ebx,4),%eax
   0x08048b7e <+54>:	cmp    %eax,(%esi,%ebx,4)
   0x08048b81 <+57>:	je     0x8048b88 <phase_2+64>
   0x08048b83 <+59>:	call   0x80494fc <explode_bomb>
   0x08048b88 <+64>:	inc    %ebx
   0x08048b89 <+65>:	cmp    $0x5,%ebx
   0x08048b8c <+68>:	jle    0x8048b76 <phase_2+46>
   0x08048b8e <+70>:	lea    -0x28(%ebp),%esp
   0x08048b91 <+73>:	pop    %ebx
   0x08048b92 <+74>:	pop    %esi
   0x08048b93 <+75>:	mov    %ebp,%esp
   0x08048b95 <+77>:	pop    %ebp
   0x08048b96 <+78>:	ret    
End of assembler dump.
```
Call to <code>read_six_numbers</code>:
```shell
Dump of assembler code for function read_six_numbers:
   0x08048fd8 <+0>:	push   %ebp
   0x08048fd9 <+1>:	mov    %esp,%ebp
   0x08048fdb <+3>:	sub    $0x8,%esp
   0x08048fde <+6>:	mov    0x8(%ebp),%ecx
   0x08048fe1 <+9>:	mov    0xc(%ebp),%edx
   0x08048fe4 <+12>:	lea    0x14(%edx),%eax
   0x08048fe7 <+15>:	push   %eax
   0x08048fe8 <+16>:	lea    0x10(%edx),%eax
   0x08048feb <+19>:	push   %eax
   0x08048fec <+20>:	lea    0xc(%edx),%eax
   0x08048fef <+23>:	push   %eax
   0x08048ff0 <+24>:	lea    0x8(%edx),%eax
   0x08048ff3 <+27>:	push   %eax
   0x08048ff4 <+28>:	lea    0x4(%edx),%eax
   0x08048ff7 <+31>:	push   %eax
   0x08048ff8 <+32>:	push   %edx
   0x08048ff9 <+33>:	push   $0x8049b1b
   0x08048ffe <+38>:	push   %ecx
   0x08048fff <+39>:	call   0x8048860 <sscanf@plt>
   0x08049004 <+44>:	add    $0x20,%esp
   0x08049007 <+47>:	cmp    $0x5,%eax
   0x0804900a <+50>:	jg     0x8049011 <read_six_numbers+57>
   0x0804900c <+52>:	call   0x80494fc <explode_bomb>
   0x08049011 <+57>:	mov    %ebp,%esp
   0x08049013 <+59>:	pop    %ebp
   0x08049014 <+60>:	ret    
End of assembler dump.
```
This reads 6 inputs into an array. If less than 6 are read, the bomb explodes. The <code>phase_2()</code> calculated the factorial of numbers 1 to 6, then it compares the values to the input array.

## exploit 2
1 2 6 24 120 720

# <u>phase3</u>
``` shell
(gdb) disas phase_3
Dump of assembler code for function phase_3:
   0x08048b98 <+0>:	push   %ebp
   0x08048b99 <+1>:	mov    %esp,%ebp
   0x08048b9b <+3>:	sub    $0x14,%esp
   0x08048b9e <+6>:	push   %ebx
   0x08048b9f <+7>:	mov    0x8(%ebp),%edx
   0x08048ba2 <+10>:	add    $0xfffffff4,%esp
   0x08048ba5 <+13>:	lea    -0x4(%ebp),%eax
   0x08048ba8 <+16>:	push   %eax
   0x08048ba9 <+17>:	lea    -0x5(%ebp),%eax
   0x08048bac <+20>:	push   %eax
   0x08048bad <+21>:	lea    -0xc(%ebp),%eax
   0x08048bb0 <+24>:	push   %eax
   0x08048bb1 <+25>:	push   $0x80497de
   0x08048bb6 <+30>:	push   %edx
   0x08048bb7 <+31>:	call   0x8048860 <sscanf@plt>
   0x08048bbc <+36>:	add    $0x20,%esp
   0x08048bbf <+39>:	cmp    $0x2,%eax
   0x08048bc2 <+42>:	jg     0x8048bc9 <phase_3+49>
   0x08048bc4 <+44>:	call   0x80494fc <explode_bomb>
   0x08048bc9 <+49>:	cmpl   $0x7,-0xc(%ebp)
   0x08048bcd <+53>:	ja     0x8048c88 <phase_3+240>
   0x08048bd3 <+59>:	mov    -0xc(%ebp),%eax
   0x08048bd6 <+62>:	jmp    *0x80497e8(,%eax,4)
   0x08048bdd <+69>:	lea    0x0(%esi),%esi
   0x08048be0 <+72>:	mov    $0x71,%bl
   0x08048be2 <+74>:	cmpl   $0x309,-0x4(%ebp)
   0x08048be9 <+81>:	je     0x8048c8f <phase_3+247>
   0x08048bef <+87>:	call   0x80494fc <explode_bomb>
   0x08048bf4 <+92>:	jmp    0x8048c8f <phase_3+247>
   0x08048bf9 <+97>:	lea    0x0(%esi,%eiz,1),%esi
   0x08048c00 <+104>:	mov    $0x62,%bl
   0x08048c02 <+106>:	cmpl   $0xd6,-0x4(%ebp)
   0x08048c09 <+113>:	je     0x8048c8f <phase_3+247>
   0x08048c0f <+119>:	call   0x80494fc <explode_bomb>
   0x08048c14 <+124>:	jmp    0x8048c8f <phase_3+247>
   0x08048c16 <+126>:	mov    $0x62,%bl
   0x08048c18 <+128>:	cmpl   $0x2f3,-0x4(%ebp)
   0x08048c1f <+135>:	je     0x8048c8f <phase_3+247>
   0x08048c21 <+137>:	call   0x80494fc <explode_bomb>
   0x08048c26 <+142>:	jmp    0x8048c8f <phase_3+247>
   0x08048c28 <+144>:	mov    $0x6b,%bl
   0x08048c2a <+146>:	cmpl   $0xfb,-0x4(%ebp)
   0x08048c31 <+153>:	je     0x8048c8f <phase_3+247>
   0x08048c33 <+155>:	call   0x80494fc <explode_bomb>
   0x08048c38 <+160>:	jmp    0x8048c8f <phase_3+247>
   0x08048c3a <+162>:	lea    0x0(%esi),%esi
   0x08048c40 <+168>:	mov    $0x6f,%bl
   0x08048c42 <+170>:	cmpl   $0xa0,-0x4(%ebp)
   0x08048c49 <+177>:	je     0x8048c8f <phase_3+247>
   0x08048c4b <+179>:	call   0x80494fc <explode_bomb>
   0x08048c50 <+184>:	jmp    0x8048c8f <phase_3+247>
   0x08048c52 <+186>:	mov    $0x74,%bl
   0x08048c54 <+188>:	cmpl   $0x1ca,-0x4(%ebp)
   0x08048c5b <+195>:	je     0x8048c8f <phase_3+247>
   0x08048c5d <+197>:	call   0x80494fc <explode_bomb>
   0x08048c62 <+202>:	jmp    0x8048c8f <phase_3+247>
   0x08048c64 <+204>:	mov    $0x76,%bl
   0x08048c66 <+206>:	cmpl   $0x30c,-0x4(%ebp)
   0x08048c6d <+213>:	je     0x8048c8f <phase_3+247>
   0x08048c6f <+215>:	call   0x80494fc <explode_bomb>
   0x08048c74 <+220>:	jmp    0x8048c8f <phase_3+247>
   0x08048c76 <+222>:	mov    $0x62,%bl
   0x08048c78 <+224>:	cmpl   $0x20c,-0x4(%ebp)
   0x08048c7f <+231>:	je     0x8048c8f <phase_3+247>
   0x08048c81 <+233>:	call   0x80494fc <explode_bomb>
   0x08048c86 <+238>:	jmp    0x8048c8f <phase_3+247>
   0x08048c88 <+240>:	mov    $0x78,%bl
   0x08048c8a <+242>:	call   0x80494fc <explode_bomb>
   0x08048c8f <+247>:	cmp    -0x5(%ebp),%bl
   0x08048c92 <+250>:	je     0x8048c99 <phase_3+257>
   0x08048c94 <+252>:	call   0x80494fc <explode_bomb>
   0x08048c99 <+257>:	mov    -0x18(%ebp),%ebx
   0x08048c9c <+260>:	mov    %ebp,%esp
   0x08048c9e <+262>:	pop    %ebp
   0x08048c9f <+263>:	ret    
End of assembler dump.
```
This functions uses <code>scanf</code> and waits for 3 input parameters:
``` shell
(gdb) x/s 0x80497de
0x80497de:	"%d %c %d"
```
If the value is less than 0x2, the bomb defuses. The first integer has to be less than 0x7 - then there is a conditional check to have a correct input sequence:
``` shell
(gdb) p 0x0
$15 = 0
(gdb) printf "%c\n", 0x71
q
(gdb) p 0x309
$16 = 777
```
There are more combinations in the code, but this one is enough.

# exploit 3
0 q 777
- however, the README files shows us that 'b' is used, so the final exploit is "1 b 214".

# <u>phase4</u>
``` shell
Dump of assembler code for function phase_4:
   0x08048ce0 <+0>:	push   %ebp
   0x08048ce1 <+1>:	mov    %esp,%ebp
   0x08048ce3 <+3>:	sub    $0x18,%esp
   0x08048ce6 <+6>:	mov    0x8(%ebp),%edx
   0x08048ce9 <+9>:	add    $0xfffffffc,%esp
   0x08048cec <+12>:	lea    -0x4(%ebp),%eax
   0x08048cef <+15>:	push   %eax
   0x08048cf0 <+16>:	push   $0x8049808
   0x08048cf5 <+21>:	push   %edx
   0x08048cf6 <+22>:	call   0x8048860 <sscanf@plt>
   0x08048cfb <+27>:	add    $0x10,%esp
   0x08048cfe <+30>:	cmp    $0x1,%eax
   0x08048d01 <+33>:	jne    0x8048d09 <phase_4+41>
   0x08048d03 <+35>:	cmpl   $0x0,-0x4(%ebp)
   0x08048d07 <+39>:	jg     0x8048d0e <phase_4+46>
   0x08048d09 <+41>:	call   0x80494fc <explode_bomb>
   0x08048d0e <+46>:	add    $0xfffffff4,%esp
   0x08048d11 <+49>:	mov    -0x4(%ebp),%eax
   0x08048d14 <+52>:	push   %eax
   0x08048d15 <+53>:	call   0x8048ca0 <func4>
   0x08048d1a <+58>:	add    $0x10,%esp
   0x08048d1d <+61>:	cmp    $0x37,%eax
   0x08048d20 <+64>:	je     0x8048d27 <phase_4+71>
   0x08048d22 <+66>:	call   0x80494fc <explode_bomb>
   0x08048d27 <+71>:	mov    %ebp,%esp
   0x08048d29 <+73>:	pop    %ebp
   0x08048d2a <+74>:	ret    
End of assembler dump.
```
This functions scans for an integer and checks if it is a positive number.
``` shell
(gdb) x/s $0x8049808
Value can't be converted to integer.
```
Then is calls <code>func4</code> and checks if the return value is 0x37:
``` shell
(gdb) p 0x37
$17 = 55
```
Let's explore the function that is called:
``` shell
Dump of assembler code for function func4:
   0x08048ca0 <+0>:	push   %ebp
   0x08048ca1 <+1>:	mov    %esp,%ebp
   0x08048ca3 <+3>:	sub    $0x10,%esp
   0x08048ca6 <+6>:	push   %esi
   0x08048ca7 <+7>:	push   %ebx
   0x08048ca8 <+8>:	mov    0x8(%ebp),%ebx
   0x08048cab <+11>:	cmp    $0x1,%ebx
   0x08048cae <+14>:	jle    0x8048cd0 <func4+48>
   0x08048cb0 <+16>:	add    $0xfffffff4,%esp
   0x08048cb3 <+19>:	lea    -0x1(%ebx),%eax
   0x08048cb6 <+22>:	push   %eax
   0x08048cb7 <+23>:	call   0x8048ca0 <func4>
   0x08048cbc <+28>:	mov    %eax,%esi
   0x08048cbe <+30>:	add    $0xfffffff4,%esp
   0x08048cc1 <+33>:	lea    -0x2(%ebx),%eax
   0x08048cc4 <+36>:	push   %eax
   0x08048cc5 <+37>:	call   0x8048ca0 <func4>
   0x08048cca <+42>:	add    %esi,%eax
   0x08048ccc <+44>:	jmp    0x8048cd5 <func4+53>
   0x08048cce <+46>:	mov    %esi,%esi
   0x08048cd0 <+48>:	mov    $0x1,%eax
   0x08048cd5 <+53>:	lea    -0x18(%ebp),%esp
   0x08048cd8 <+56>:	pop    %ebx
   0x08048cd9 <+57>:	pop    %esi
   0x08048cda <+58>:	mov    %ebp,%esp
   0x08048cdc <+60>:	pop    %ebp
   0x08048cdd <+61>:	ret    
End of assembler dump.
```
Apparently a recursion is used to get a sum of [num - 0x1] and [num - 0x2] if the number passed to the function is greater than 1. Fibbonaci sequence!
``` shell
num[x] = num[x-1] + num[x-2]
```
The number that gives us a final product of 55 is 10. However, the function stops at index 1, so the last numbers used in sequence are not [0, 1]. Because of this, we substract 1 to get a final result of 9.

## exploit 4
9

# <u>phase5</u>
``` shell
Dump of assembler code for function phase_5:
   0x08048d2c <+0>:	push   %ebp
   0x08048d2d <+1>:	mov    %esp,%ebp
   0x08048d2f <+3>:	sub    $0x10,%esp
   0x08048d32 <+6>:	push   %esi
   0x08048d33 <+7>:	push   %ebx
   0x08048d34 <+8>:	mov    0x8(%ebp),%ebx
   0x08048d37 <+11>:	add    $0xfffffff4,%esp
   0x08048d3a <+14>:	push   %ebx
   0x08048d3b <+15>:	call   0x8049018 <string_length>
   0x08048d40 <+20>:	add    $0x10,%esp
   0x08048d43 <+23>:	cmp    $0x6,%eax
   0x08048d46 <+26>:	je     0x8048d4d <phase_5+33>
   0x08048d48 <+28>:	call   0x80494fc <explode_bomb>
   0x08048d4d <+33>:	xor    %edx,%edx
   0x08048d4f <+35>:	lea    -0x8(%ebp),%ecx
   0x08048d52 <+38>:	mov    $0x804b220,%esi
   0x08048d57 <+43>:	mov    (%edx,%ebx,1),%al
   0x08048d5a <+46>:	and    $0xf,%al
   0x08048d5c <+48>:	movsbl %al,%eax
   0x08048d5f <+51>:	mov    (%eax,%esi,1),%al
   0x08048d62 <+54>:	mov    %al,(%edx,%ecx,1)
   0x08048d65 <+57>:	inc    %edx
   0x08048d66 <+58>:	cmp    $0x5,%edx
   0x08048d69 <+61>:	jle    0x8048d57 <phase_5+43>
   0x08048d6b <+63>:	movb   $0x0,-0x2(%ebp)
   0x08048d6f <+67>:	add    $0xfffffff8,%esp
   0x08048d72 <+70>:	push   $0x804980b
   0x08048d77 <+75>:	lea    -0x8(%ebp),%eax
   0x08048d7a <+78>:	push   %eax
   0x08048d7b <+79>:	call   0x8049030 <strings_not_equal>
   0x08048d80 <+84>:	add    $0x10,%esp
   0x08048d83 <+87>:	test   %eax,%eax
   0x08048d85 <+89>:	je     0x8048d8c <phase_5+96>
   0x08048d87 <+91>:	call   0x80494fc <explode_bomb>
   0x08048d8c <+96>:	lea    -0x18(%ebp),%esp
   0x08048d8f <+99>:	pop    %ebx
   0x08048d90 <+100>:	pop    %esi
   0x08048d91 <+101>:	mov    %ebp,%esp
   0x08048d93 <+103>:	pop    %ebp
   0x08048d94 <+104>:	ret  
   ```
This phase uses <code>strlen</code> if the input is equal to 6. Then, it modifies the input string by choosing a character from a reference string at a position of <code>str[i] & 0xf</code>. The final string is then compared against a password:
``` shell
(gdb) x/m 0x804b220
0x804b220:	"isrveawhobpnutfg"  --> reference string
(gdb) x/m 0x804980b
0x804980b:	"giants"                    --> password
```
Our task is to figure out what a string that chooses characters convertable to numbers in range 0-15 will look like. A simple C program will help:
``` shell
ffarkas@ffarkas:~/boot2root$ cc find_string.c -o giants
ffarkas@ffarkas:~/boot2root$ ./giants
char a matches s
char e matches a
char k matches n
char m matches t
char o matches g
char p matches i
char q matches s
char u matches a
```
This now gives us combinations:
``` shell
?????a
??e???
???k??
????m?
o?????
?p????
?????q
??u???
======
op(u/e)km(q/a)
======
opukmq
opukma
opekmq
opekma
```
Now we try which if these inputs successfuly passes.

# exploit 5
opekmq

# <u>phase6</u>
``` shell
Dump of assembler code for function phase_6:
   0x08048d98 <+0>:	push   %ebp
   0x08048d99 <+1>:	mov    %esp,%ebp
   0x08048d9b <+3>:	sub    $0x4c,%esp
   0x08048d9e <+6>:	push   %edi
   0x08048d9f <+7>:	push   %esi
   0x08048da0 <+8>:	push   %ebx
   0x08048da1 <+9>:	mov    0x8(%ebp),%edx
   0x08048da4 <+12>:	movl   $0x804b26c,-0x34(%ebp)
   0x08048dab <+19>:	add    $0xfffffff8,%esp
   0x08048dae <+22>:	lea    -0x18(%ebp),%eax
   0x08048db1 <+25>:	push   %eax
   0x08048db2 <+26>:	push   %edx
   0x08048db3 <+27>:	call   0x8048fd8 <read_six_numbers>
   0x08048db8 <+32>:	xor    %edi,%edi
   0x08048dba <+34>:	add    $0x10,%esp
   0x08048dbd <+37>:	lea    0x0(%esi),%esi
   0x08048dc0 <+40>:	lea    -0x18(%ebp),%eax
   0x08048dc3 <+43>:	mov    (%eax,%edi,4),%eax
   0x08048dc6 <+46>:	dec    %eax
   0x08048dc7 <+47>:	cmp    $0x5,%eax
   0x08048dca <+50>:	jbe    0x8048dd1 <phase_6+57>
   0x08048dcc <+52>:	call   0x80494fc <explode_bomb>
   0x08048dd1 <+57>:	lea    0x1(%edi),%ebx
   0x08048dd4 <+60>:	cmp    $0x5,%ebx
   0x08048dd7 <+63>:	jg     0x8048dfc <phase_6+100>
   0x08048dd9 <+65>:	lea    0x0(,%edi,4),%eax
   0x08048de0 <+72>:	mov    %eax,-0x38(%ebp)
   0x08048de3 <+75>:	lea    -0x18(%ebp),%esi
   0x08048de6 <+78>:	mov    -0x38(%ebp),%edx
   0x08048de9 <+81>:	mov    (%edx,%esi,1),%eax
   0x08048dec <+84>:	cmp    (%esi,%ebx,4),%eax
   0x08048def <+87>:	jne    0x8048df6 <phase_6+94>
   0x08048df1 <+89>:	call   0x80494fc <explode_bomb>
   0x08048df6 <+94>:	inc    %ebx
   0x08048df7 <+95>:	cmp    $0x5,%ebx
   0x08048dfa <+98>:	jle    0x8048de6 <phase_6+78>
   0x08048dfc <+100>:	inc    %edi
   0x08048dfd <+101>:	cmp    $0x5,%edi
   0x08048e00 <+104>:	jle    0x8048dc0 <phase_6+40>
   0x08048e02 <+106>:	xor    %edi,%edi
   0x08048e04 <+108>:	lea    -0x18(%ebp),%ecx
   0x08048e07 <+111>:	lea    -0x30(%ebp),%eax
   0x08048e0a <+114>:	mov    %eax,-0x3c(%ebp)
   0x08048e0d <+117>:	lea    0x0(%esi),%esi
   0x08048e10 <+120>:	mov    -0x34(%ebp),%esi
   0x08048e13 <+123>:	mov    $0x1,%ebx
   0x08048e18 <+128>:	lea    0x0(,%edi,4),%eax
   0x08048e1f <+135>:	mov    %eax,%edx
   0x08048e21 <+137>:	cmp    (%eax,%ecx,1),%ebx
   0x08048e24 <+140>:	jge    0x8048e38 <phase_6+160>
   0x08048e26 <+142>:	mov    (%edx,%ecx,1),%eax
   0x08048e29 <+145>:	lea    0x0(%esi,%eiz,1),%esi
   0x08048e30 <+152>:	mov    0x8(%esi),%esi
   0x08048e33 <+155>:	inc    %ebx
   0x08048e34 <+156>:	cmp    %eax,%ebx
   0x08048e36 <+158>:	jl     0x8048e30 <phase_6+152>
   0x08048e38 <+160>:	mov    -0x3c(%ebp),%edx
   0x08048e3b <+163>:	mov    %esi,(%edx,%edi,4)
   0x08048e3e <+166>:	inc    %edi
   0x08048e3f <+167>:	cmp    $0x5,%edi
   0x08048e42 <+170>:	jle    0x8048e10 <phase_6+120>
   0x08048e44 <+172>:	mov    -0x30(%ebp),%esi
   0x08048e47 <+175>:	mov    %esi,-0x34(%ebp)
   0x08048e4a <+178>:	mov    $0x1,%edi
   0x08048e4f <+183>:	lea    -0x30(%ebp),%edx
   0x08048e52 <+186>:	mov    (%edx,%edi,4),%eax
   0x08048e55 <+189>:	mov    %eax,0x8(%esi)
   0x08048e58 <+192>:	mov    %eax,%esi
   0x08048e5a <+194>:	inc    %edi
   0x08048e5b <+195>:	cmp    $0x5,%edi
   0x08048e5e <+198>:	jle    0x8048e52 <phase_6+186>
   0x08048e60 <+200>:	movl   $0x0,0x8(%esi)
   0x08048e67 <+207>:	mov    -0x34(%ebp),%esi
   0x08048e6a <+210>:	xor    %edi,%edi
   0x08048e6c <+212>:	lea    0x0(%esi,%eiz,1),%esi
   0x08048e70 <+216>:	mov    0x8(%esi),%edx
   0x08048e73 <+219>:	mov    (%esi),%eax
   0x08048e75 <+221>:	cmp    (%edx),%eax
   0x08048e77 <+223>:	jge    0x8048e7e <phase_6+230>
   0x08048e79 <+225>:	call   0x80494fc <explode_bomb>
   0x08048e7e <+230>:	mov    0x8(%esi),%esi
   0x08048e81 <+233>:	inc    %edi
   0x08048e82 <+234>:	cmp    $0x4,%edi
   0x08048e85 <+237>:	jle    0x8048e70 <phase_6+216>
   0x08048e87 <+239>:	lea    -0x58(%ebp),%esp
   0x08048e8a <+242>:	pop    %ebx
   0x08048e8b <+243>:	pop    %esi
   0x08048e8c <+244>:	pop    %edi
   0x08048e8d <+245>:	mov    %ebp,%esp
   0x08048e8f <+247>:	pop    %ebp
   0x08048e90 <+248>:	ret  
```
This phase takes 6 numbers as the input values. Apparently the numbers are stored in global variables <code>node[i]</code>:
``` shell
(gdb) x/m 0x804b26c
0x804b26c <node1>:	0x000000fd
```
Our task is to sort the nodes (each number we input represents the index of the node) so that we get a sequence in a descending order. We can display the value stored in the registers at the corresponding addresses using the <code>x/20x [addr]</code> syntax:
``` shell
0x804b26c <node1>:	0xfd	0x00	0x00	0x00	0x01	0x00	0x00	0x00
0x804b260 <node2>:	0xd5	0x02	0x00	0x00	0x02	0x00	0x00	0x00
0x804b254 <node3>:	0x2d	0x01	0x00	0x00	0x03	0x00	0x00	0x00
0x804b248 <node4>:	0xe5	0x03	0x00	0x00	0x04	0x00	0x00	0x00
0x804b23c <node5>:	0xd4	0x00	0x00	0x00	0x05	0x00	0x00	0x00
0x804b230 <node6>:	0xb0	0x01	0x00	0x00	0x06	0x00	0x00	0x00
```
We convert the hexadecimal values into decimal numbers:
``` shell
node | 2nd | 1st
1 - 253 - 0 -> position 5
2 - 213 - 2 -> position 2
3 - 45 - 1 -> position 4
4 - 229 - 3 -> position 1
5 - 212 - 0 -> position 6
6 - 176 - 1 -> position 3
```
## exploit 6
4 2 6 3 1 5

# <u>password</u>
``` shell
ffarkas@ffarkas:~/boot2root$ ./bomb 
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Public speaking is very easy.
Phase 1 defused. How about the next one?
1 2 6 24 120 720
That's number 2.  Keep going!
1 b 214
Halfway there!
9
So you got that one.  Try this one.
opekmq
Good work!  On to the next...
4 2 6 3 1 5
Congratulations! You've defused the bomb!
```
The README file says "NO SPACE IN THE PASSWORD (password is case sensitive)." - the final password is:
``` shell
Publicspeakingisveryeasy.126241207201b2149opekmq426315
```
Based on a Slack discussion, there is a mistake in the password and the two penultimate characters are swapped:
``` shell
Publicspeakingisveryeasy.126241207201b2149opekmq426135
```