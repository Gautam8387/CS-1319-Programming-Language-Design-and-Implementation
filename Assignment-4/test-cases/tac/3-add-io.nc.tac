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


==================================================================================================================
Symbol Table: Global                              Parent: NULL
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Offset         Nested Table        
------------------------------------------------------------------------------------------------------------------
printInt       int            function            -                   4              0              printInt            
readInt        int            function            -                   4              0              readInt             
printStr       char           function            -                   4              0              printStr            
main           int            function            -                   4              0              main                
==================================================================================================================


==================================================================================================================
Symbol Table: printInt                                           Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Offset         Nested Table        
------------------------------------------------------------------------------------------------------------------
x              int            param               -                   4              0              -
retValue       int            local               -                   4              0              -
==================================================================================================================



==================================================================================================================
Symbol Table: readInt                                            Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Offset         Nested Table        
------------------------------------------------------------------------------------------------------------------
n              *int           param               -                   4              0              -
retValue       int            local               -                   4              0              -
t0             int            temp                -                   4              0              -
==================================================================================================================



==================================================================================================================
Symbol Table: printStr                                           Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Offset         Nested Table        
------------------------------------------------------------------------------------------------------------------
s              *char          param               -                   4              0              -
retValue       char           local               -                   1              0              -
t1             char           temp                -                   1              0              -
==================================================================================================================



==================================================================================================================
Symbol Table: main                                               Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Offset         Nested Table        
------------------------------------------------------------------------------------------------------------------
retValue       int            local               -                   4              0              -
x              int            local               -                   4              0              -
y              int            local               -                   4              0              -
z              int            local               -                   4              0              -
t2             *int           temp                -                   4              0              -
t3             int            temp                -                   4              0              -
t4             *int           temp                -                   4              0              -
t5             int            temp                -                   4              0              -
t6             int            temp                -                   4              0              -
t7             int            temp                -                   4              0              -
t8             *char          temp                "+"                 4              0              -
t9             char           temp                -                   1              0              -
t10            int            temp                -                   4              0              -
t11            *char          temp                " = "               4              0              -
t12            char           temp                -                   1              0              -
t13            int            temp                -                   4              0              -
t14            int            temp                0                   4              0              -
==================================================================================================================




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
13: t2 = &x
14: param t2
15: t3 = call readInt, 1
16: t4 = &y
17: param t4
18: t5 = call readInt, 1
19: t6 = x + y
20: z = t6
21: param x
22: t7 = call printInt, 1
23: t8 = string("+")
24: param t8
25: t9 = call printStr, 1
26: param y
27: t10 = call printInt, 1
28: t11 = string(" = ")
29: param t11
30: t12 = call printStr, 1
31: param z
32: t13 = call printInt, 1
33: t14 = 0
34: return t14
35: end main

=============================================================================================================

