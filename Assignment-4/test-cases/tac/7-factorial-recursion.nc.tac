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
M
next-instruction
primary-expression
postfix-expression
unary-expression
multiplicative-expression
primary-expression
postfix-expression
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
jump-statement
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
init-declarator
declaration
block-item
block-item-list
next-instruction
primary-expression
postfix-expression
unary-expression
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
factorial	function	NULL		(null)		0	0	factorial
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
Symbol Table: factorial							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
n	int	param		(null)		4	0	NULL
retValue	int	local		(null)		4	0	NULL
t2	int	temp		0		4	0	NULL
t3	int	temp		1		4	0	NULL
t4	int	temp		1		4	0	NULL
t5	int	temp		(null)		4	0	NULL
t6	int	temp		(null)		4	0	NULL
t7	int	temp		(null)		4	0	NULL

=============================================================================================================

=============================================================================================================
Symbol Table: main							 Parent: Global

-------------------------------------------------------------------------------------------------------------
Name	Type	Category	Initial Value	Size	Offset	Nested Table
-------------------------------------------------------------------------------------------------------------
retValue	int	local		(null)		4	0	NULL
n	int	local		5		4	0	NULL
t8	int	temp		5		4	0	NULL
r	int	local		(null)		4	0	NULL
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
12: function factorial:
13: t2 = 0
14: if n == t2 goto 17
15: goto 20
16: goto 26
17: t3 = 1
18: return t3
19: goto 26
20: t4 = 1
21: t5 = n - t4
22: param t5
23: t6 = call factorial, 1
24: t7 = n * t6
25: return t7
26: end factorial
27: function main:
28: t8 = 5
29: n = t8
30: param n
31: t9 = call factorial, 1
32: r = t9
33: param n
34: t10 = call printInt, 1
35: t11 = string("! = ")
36: param t11
37: t12 = call printStr, 1
38: param r
39: t13 = call printInt, 1
40: t14 = 0
41: return t14
42: end main

=============================================================================================================

