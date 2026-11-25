# README.md

Welcome to the Bluejay Compiler.

## Features

### Assertions

Assertions can be used to catch bugs. There are 3 kinds of assertions.

#### assert
Ordinary assertions declared using assert will flag an exception and continue to run code. You can disable assertions using --no-assert

#### staticassert
Assertions declared using staticassert will raise errors at compile time.

#### assume


### Format-strings
Format strings can append variables to strings at compile time. You can create them using the fstring operator. 

To append a variable, enclose it in "{}" brackets.

Format strings can only be used with variables.

Format-strings can be used in place of regular variadic printing functions. For example, instead of:

int age := 30;
std::println("My age is {}!", age);

You can do:

int age := 30;
string message = fstring("My age is {age}!");
std::println(msg);

Or, alternatively:

int age := 30;
std::println(fstring("My age is {age}!"));