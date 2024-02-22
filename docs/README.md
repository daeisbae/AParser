# How to use the AParser scripting language
## Basic Arithmetics Operations
- Supports addition, negation, multiplication, and division calculation

Examples
```
./AParser                                            
>>> 1 + 1
2
>>> 1 - 1
0
>>> 251252 + 17204
268456
>>> 123 * 321
39483
>>> 10 / 2
5
```

## Variables
- Declared variable can't be redeclared, instead the value can be reassigned. Redeclaring the same value twice will throw an error! (This is intended)
- Variables can be used in arithmetic operations, variable declaration/assignment (ex. if a is declared as integer value 1, then `a + 1` will return 2 as an output)

### Declaring Variables
```
set <variable name> = <value>
```

Examples
```
./AParser
>>> set a = 1
1
>>> a
1
>>> set b = a + 12
13
>>> b
13
>>> a + b
14
>>> 
```

## Assigning Different Value to Variables
- Recursive assignment can be done (ex. `<variable name> = <variable name> = <new value to assign>`)

```
<variable name> = <new value to assign>
```

Examples
```
./AParser
>>> set a = 2
2
>>> a
2
>>> a = 4
4
>>> a + 1
5
>>> set b = 1
1
>>> b = a = 0
0
>>> a
0
>>> b
0
```