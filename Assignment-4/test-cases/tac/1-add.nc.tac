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
x	int	local		2		4	0	NULL
t2	int	temp		2		4	0	NULL
y	int	local		3		4	0	NULL
t3	int	temp		3		4	0	NULL
z	int	local		(null)		4	0	NULL
t4	int	temp		(null)		4	0	NULL
t5	int	temp		(null)		4	0	NULL
t6	*char	temp		"+"		4	0	NULL
t7	char	temp		(null)		1	0	NULL
t8	int	temp		(null)		4	0	NULL
t9	*char	temp		" = "		4	0	NULL
t10	char	temp		(null)		1	0	NULL
t11	int	temp		(null)		4	0	NULL
t12	int	temp		0		4	0	NULL

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
13: t2 = 2
14: x = t2
15: t3 = 3
16: y = t3
17: t4 = x + y
18: z = t4
19: param x
20: t5 = call printInt, 1
21: t6 = string("+")
22: param t6
23: t7 = call printStr, 1
24: param y
25: t8 = call printInt, 1
26: t9 = string(" = ")
27: param t9
28: t10 = call printStr, 1
29: param z
30: t11 = call printInt, 1
31: t12 = 0
32: return t12
33: end main

=============================================================================================================

