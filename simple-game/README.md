# Belish
A programming language similar to human natural language expression  
_A programming language similar to English syntactic structure_

## Naming
Because this is a kind of programming language similar to English syntax, but with some ambiguity removed, the structure is rigorous, and then Berry(My favorite fruit) and English are spliced together, that is, Belish.

## Core idea
Subject predicate object structure.  
What's it meaning?  
### Subject
This is the action initiator, that is, the object that calls a function.  
### Predicate
This represents the action to be performed, that is, the function name.
### Object
This represents the object of an action operation, which is also the parameter of a function.
### Example
```
I say "Hello!".
```
`I` is the subject, `say` is the predicate, `"Hello!""` is the object.  
If we translate this code into JavaScript, it is written as follows:
```
I.say("Hello!");
```

```
my sister say "Hello,", "John!".
```
`My sister` is the subject, `say` is the predicate, `"Hello!""` is the object.  
If we translate this code into JavaScript, it is written as follows:
```
I.sister.say("Hello,", "John!");
```
