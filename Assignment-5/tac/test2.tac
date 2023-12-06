Initializing Symbol Tables
Starting Parser
type-specifier
new-table
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
Global Symbol Table:


==================================================================================================================
Symbol Table: Global                              Parent: NULL
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Nested Table        
------------------------------------------------------------------------------------------------------------------
main           function       temp                -                   0              main                
==================================================================================================================


==================================================================================================================
Symbol Table: main                                               Parent: ST.Global
------------------------------------------------------------------------------------------------------------------
Name           Type           Category            Initial Value       Size           Nested Table        
------------------------------------------------------------------------------------------------------------------
retValue       int            local               -                   4              -
t0             int            temp                0                   4              -
==================================================================================================================




=============================================================================================================
THREE ADDRESS CODE
-------------------------------------------------------------------------------------------------------------
1: function main:
2: t0 = 0
3: return t0
4: end main

=============================================================================================================

