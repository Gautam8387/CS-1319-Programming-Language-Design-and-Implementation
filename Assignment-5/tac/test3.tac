Initializing Symbol Tables
Starting Parser
type-specifier
new-table
type-specifier
parameter-declaration
parameter-list
type-specifier
pointer
parameter-declaration
parameter-list
direct-declarator
declarator
init-declarator
declaration
external-declaration
translation-unit
type-specifier
new-table
type-specifier
parameter-declaration
parameter-list
type-specifier
pointer
parameter-declaration
parameter-list
direct-declarator
declarator
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
type-specifier
direct-declarator
declarator
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
type-specifier
pointer
direct-declarator
declarator
init-declarator
declaration
block-item
block-item-list
next-instruction
unary-operator
primary-expression
postfix-expression
unary-expression
unary-expression
primary-expression
postfix-expression
unary-expression
multiplicative-expression
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
block-item
block-item-list
compound-statement
function-definition
external-declaration
translation-unit
Global Symbol Table:


==================================================================================================================
Symbol Table: Global                              Parent: NULL
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Nested Table        
------------------------------------------------------------------------------------------------------------------
func           function       temp                -                   0              func                
main           function       temp                -                   0              main                
==================================================================================================================


==================================================================================================================
Symbol Table: func                                               Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Nested Table        
------------------------------------------------------------------------------------------------------------------
a              int            param               -                   4              -
b              *int           param               -                   4              -
==================================================================================================================



==================================================================================================================
Symbol Table: main                                               Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Nested Table        
------------------------------------------------------------------------------------------------------------------
a              int            local               1                   4              -
t0             int            temp                1                   4              -
t1             int            temp                1                   4              -
t2             int            temp                -                   4              -
b              int            local               -                   4              -
t3             int            temp                1                   4              -
t4             int            temp                -                   4              -
c              int            local               -                   4              -
t5             int            temp                1                   4              -
t6             int            temp                -                   4              -
t7             int            temp                2                   4              -
t8             int            temp                -                   4              -
t9             int            temp                10                  4              -
t10            int            temp                -                   4              -
d              *int           local               -                   4              -
t11            int            temp                -                   4              -
t12            int            temp                -                   4              -
t13            int            temp                -                   4              -
==================================================================================================================




=============================================================================================================
THREE ADDRESS CODE
-------------------------------------------------------------------------------------------------------------
1: function func:
2: return
3: end func
4: function main:
5: t0 = 1
6: a = t0
7: t1 = 1
8: t2 = a + t1
9: a = t2
10: t3 = 1
11: t4 = t3 - a
12: b = t4
13: t5 = 1
14: t6 = t5 / b
15: c = t6
16: t7 = 2
17: t8 = c * t7
18: t9 = 10
19: t10 = t8 + t9
20: c = t10
21: t11 = *d
22: t12 = c * c
23: t13 = t12 % a
24: *d = t13
25: return
26: end main

=============================================================================================================

