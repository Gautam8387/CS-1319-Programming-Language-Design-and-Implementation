Initializing Symbol Tables
Starting Parser
type-specifier
new-table
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
type-specifier
new-table
type-specifier
pointer
parameter-declaration
parameter-list
direct-declarator
declarator
unary-operator
primary-expression
postfix-expression
unary-expression
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
type-specifier
new-table
type-specifier
pointer
parameter-declaration
parameter-list
direct-declarator
declarator
unary-operator
primary-expression
postfix-expression
unary-expression
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
type-specifier
new-table
direct-declarator
declarator
type-specifier
direct-declarator
declarator
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
primary-expression
postfix-expression
unary-operator
primary-expression
postfix-expression
unary-expression
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
expression
expression-statement
statement
block-item
block-item-list
next-instruction
primary-expression
postfix-expression
unary-expression
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
assignment-expression
expression
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
next-instruction
primary-expression
postfix-expression
unary-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
additive-expression
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
assignment-expression
expression
M
next-instruction
primary-expression
postfix-expression
unary-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
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
assignment-expression
expression
expression-statement
statement
iteration-statement
statement
block-item
block-item-list
next-instruction
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
expression-statement
statement
block-item
block-item-list
next-instruction
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
expression-statement
statement
block-item
block-item-list
next-instruction
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
expression-statement
statement
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
printInt	function	NULL		(null)		0	0	printInt
readInt	function	NULL		(null)		0	0	readInt
printStr	function	NULL		(null)		0	0	printStr
main	function	NULL		(null)		0	0	main

=============================================================================================================

=============================================================================================================
Symbol Table: printInt							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
x	int	param		(null)		4	0	NULL
retValue	int	local		(null)		4	0	NULL

=============================================================================================================

=============================================================================================================
Symbol Table: readInt							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
n	*int	param		(null)		4	0	NULL
retValue	int	local		(null)		4	0	NULL
t0	int	temp		(null)		4	0	NULL

=============================================================================================================

=============================================================================================================
Symbol Table: printStr							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
s	*char	param		(null)		4	0	NULL
retValue	char	local		(null)		1	0	NULL
t1	char	temp		(null)		1	0	NULL

=============================================================================================================

=============================================================================================================
Symbol Table: main							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
retValue	int	local		(null)		4	0	NULL
n	int	local		(null)		4	0	NULL
i	int	local		0		4	0	NULL
t2	int	temp		0		4	0	NULL
r	int	local		1		4	0	NULL
t3	int	temp		1		4	0	NULL
t4	*int	temp		(null)		4	0	NULL
t5	int	temp		(null)		4	0	NULL
t6	int	temp		1		4	0	NULL
t7	int	temp		1		4	0	NULL
t8	int	temp		(null)		4	0	NULL
t9	int	temp		(null)		4	0	NULL
t10	int	temp		(null)		4	0	NULL
t11	*char	temp		"! = "		4	0	NULL
t12	char	temp		(null)		1	0	NULL
t13	int	temp		(null)		4	0	NULL
t14	int	temp		0		4	0	NULL

=============================================================================================================




=============================================================================================================
THREE ADDRESS CODE
-------------------------------------------------------------------------------------------------------------
1: function printInt:
2: return x
3: end printInt
4: function readInt:
5: t0 = *n
6: return t0
7: end readInt
8: function printStr:
9: t1 = *s
10: return t1
11: end printStr
12: function main:
13: t2 = 0
14: i = t2
15: t3 = 1
16: r = t3
17: t4 = &n
18: param t4
19: t5 = call readInt, 1
20: t6 = 1
21: i = t6
22: if i <= n goto 28
23: goto 31
24: t7 = 1
25: t8 = i + t7
26: i = t8
27: goto 22
28: t9 = r * i
29: r = t9
30: goto 24
31: param n
32: t10 = call printInt, 1
33: t11 = string("! = ")
34: param t11
35: t12 = call printStr, 1
36: param r
37: t13 = call printInt, 1
38: t14 = 0
39: return t14
40: end main

=============================================================================================================

