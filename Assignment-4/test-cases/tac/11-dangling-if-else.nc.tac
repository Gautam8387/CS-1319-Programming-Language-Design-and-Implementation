Initializing Symbol Tables
Starting Parser
type-specifier
new-table
type-specifier
parameter-declaration
parameter-list
type-specifier
parameter-declaration
parameter-list
type-specifier
parameter-declaration
parameter-list
direct-declarator
declarator
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
jump-statement
statement
block-item
block-item-list
compound-statement
statement
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
jump-statement
statement
block-item
block-item-list
compound-statement
statement
selection-statement
statement
block-item
block-item-list
compound-statement
statement
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
jump-statement
statement
block-item
block-item-list
compound-statement
statement
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
jump-statement
statement
block-item
block-item-list
compound-statement
statement
selection-statement
statement
block-item
block-item-list
compound-statement
statement
selection-statement
statement
block-item
block-item-list
compound-statement
function-definition
external-declaration
translation-unit
type-specifier
new-table
direct-declarator
declarator
type-specifier
direct-declarator
declarator
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
initializer
init-declarator
declaration
block-item
block-item-list
next-instruction
type-specifier
direct-declarator
declarator
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
initializer
init-declarator
declaration
block-item
block-item-list
next-instruction
type-specifier
direct-declarator
declarator
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
initializer
init-declarator
declaration
block-item
block-item-list
next-instruction
type-specifier
direct-declarator
declarator
primary-expression
postfix-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
argument-expression-list
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
argument-expression-list
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
argument-expression-list
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
initializer
init-declarator
declaration
block-item
block-item-list
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
relational-expression
equality-expression
logical-AND-expression
logical-OR-expression
conditional-expression
assignment-expression
expression
jump-statement
statement
block-item
block-item-list
compound-statement
function-definition
external-declaration
translation-unit
Global Symbol Table:
=============================================================================================================
Symbol Table: Global							 Parent: NULL
-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
max	function	NULL		(null)		0	0	max
main	function	NULL		(null)		0	0	main

=============================================================================================================

=============================================================================================================
Symbol Table: max							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
a	int	param		(null)		4	0	NULL
b	int	param		(null)		4	0	NULL
c	int	param		(null)		4	0	NULL
retValue	int	local		(null)		4	0	NULL

=============================================================================================================

=============================================================================================================
Symbol Table: main							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
retValue	int	local		(null)		4	0	NULL
a	int	local		1		4	0	NULL
t0	int	temp		1		4	0	NULL
b	int	local		2		4	0	NULL
t1	int	temp		2		4	0	NULL
c	int	local		3		4	0	NULL
t2	int	temp		3		4	0	NULL
d	int	local		(null)		4	0	NULL
t3	int	temp		(null)		4	0	NULL
t4	int	temp		0		4	0	NULL

=============================================================================================================




=============================================================================================================
THREE ADDRESS CODE
-------------------------------------------------------------------------------------------------------------
1: function max:
2: if a > b goto 5
3: goto 12
4: goto 18
5: if a > c goto 8
6: goto 10
7: goto 11
8: return a
9: goto 18
10: return c
11: goto 18
12: if b > c goto 15
13: goto 17
14: goto 18
15: return b
16: goto 18
17: return c
18: end max
19: function main:
20: t0 = 1
21: a = t0
22: t1 = 2
23: b = t1
24: t2 = 3
25: c = t2
26: param a
27: param b
28: param c
29: t3 = call max, 3
30: d = t3
31: t4 = 0
32: return t4
33: end main

=============================================================================================================

