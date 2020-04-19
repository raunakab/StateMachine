# Preface
A simple C++ library that provides abstractions to common operations that are performed on the Standard Library's std::vector data type.

# Introduction
Racket is a functional programming language which is a dialect of Lisp (which stands for LISt Processor).
Racket has support for very intuitive operations that can be performed on lists, such as length, map, andmap, ormap, foldl, etc.
These functions allow for simple function calls on lists to return a meaningful property about it.

This library aims to mimic Racket's list operators to work for the std::vector data type.
A comprehensive list of all the functions provided by this library will be provided further down this README.

# Purpose for Developing
A recent project required the usage of the Standard Library's Vector class.
While utilizing this data type, multiple operations needed to be performed on the vector, such as "Does this list contain x?", "I want to map every element in this vector to another data type.", etc.
As the project grew in size, a lot of code started being copied over and over again.

I thought that this would be the perfect usage for a library of functions which abstract away these requests into simple function calls.
For example, if I wanted to check if a vector contained an element, I would perform the falling function invocation:

	std::vector<int> myList = /* a vector of integers */;
	int const searchForMe = 5;
	bool const contains = Iterators<int>::contains(myList, searchForMe);

instead of doing the following over and over again:

	std::vector<int> myList = /* a vector of integers */;
	int const searchForMe = 5;
	typename std::vector<int>::iterator itr(myList.begin());
	for (; itr!=myList.end(); ++itr) if (searchForMe == *itr) /* do something */;

This provided multiple advantages, the primary two being increased readability and decoupled code.
Similarly, for more advanced operations, such as mappings, filtering, etc., will be require larger statements and logic.
Also, re-writing the same code over and over again will lead to errors, which then may require multiple lines to be edited due to one mistake being copy-pasted.

# Implementation
Since the std::vector is a templated data type, these functions provided by the library would also require to be templated.
Initially, all these functions were placed into a namespace, but namespaces cannot be templated.
Therefore, the functions were made static and placed into a class which had its default-constructor, copy-constructor, and destructor declared privately.
This was done becaues classes can be templated.
