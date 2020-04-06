Q3 - Power series
=================

Overview
========

Representing functions as series
--------------------------------

Mathematical functions of one variable $x$ can often be expressed as a Maclaurin series:
$f_a(x) = \sum_{n=0}^{\infty} a_n x^n = a_0 + a_1 x + a_2 x^2 + ...$

In general the sequence of coefficients $a_0,a_1,a_2,...$ will be infinite,
and under certain conditions $f_a(x)$ converges on the true function value.

Series are available for a number of common functions:

- Constant $c$ : $a_0=c$, and $a_1,a_2,a_3,...$ are zero.

- Variable $x$ : $a_0=0$, $a_1=1$, and $a_2,a_3,a_4,...$ are zero.

- Sine $sin(x) = \sum^{\infty}_{n=0} \frac{(-1)^n}{(2n+1)!} x^{2n+1}$

Many other functions have [such expansions](https://en.wikipedia.org/wiki/Taylor_series#List_of_Maclaurin_series_of_some_common_functions).

Given a series $f_a(x)$ we can perform basic calculus on it:

- Differentiation: $f^\prime(x) = \sum_{n=0}^\infty a_{n+1} \left(n + 1\right) \left(x - c\right)^n$

- Integration: $\int f(x)\,dx &= C + \sum_{n=0}^\infty \frac{a_n \left(x - c\right)^{n+1}}{n + 1} $

Given two series $f_a(x)=\sum_{n=0}^{\infty} a_n x^n$ and $f_b(x)=\sum_{n=0}^{\infty} b_n x^n$
we can also perform basic arithmetic:

- Sum : $f_a(x) + f_b(x) = \sum_{n=0}^{\infty} (a_n+b_n) x^n$

- Product : $f_a(x) * f_b(x) = \sum_{n=0}^{\infty} \sum_{m=0}^{n} (a_m b_{m-n}) x^n$

Other operations such as division and function composition are possible, but the
formula for the coefficients is much more complicated.

Representing series as data-structures
--------------------------------------

A series is simply a mapping from an index $i$ to the coefficient $a_i$, 
so a series is naturally represented as an object with a member function
for returning coefficients at a given index.

The base-class `Series` in `series.hpp` is used to represent such a series,
and also includes methods for evaluating the series at a given value of $x$.
Any such evaluation must stop after a finite number of terms, so there
is an option to specify an absolute target tolerance, and to limit the total
number of terms.

Instances of `Series` may contain other series - for example if we add two
series together, the result will be a series that contains both series.
Whenever a series instance is built out of other series, it takes ownership
of the series, and is responsible for deleting it.

Functions and operations
------------------------

There are a number of declarations in `series_operations.hpp`,
which describe functions such as creating constants and variables,
and performing operations over them. The classes used to implement
these functions are not globally exposed, with only the `Series`
interface used.

For example, the function `series_make_constant` is used to create
a series representing a constant number. The actually implementation
is a class called `SeriesConstant`, but this is only declared in
the source file `series_constant.cpp` and is not globally declared.
The same pattern should be used for other operations and functions
over series, with classes implemented privately in source files,
and only accessible via the creation functions.

Parsing series
--------------

The function `series_parse` will take an expression in string form
and attempt to translate it into a series. The mini-language
uses a prefix form, where operators appear before arguments. White-space
is required between all components, and there is no error checking during parsing.

Examples of the series syntax are:

|  Mini-language               | Mathematical      |
|------------------------------|-------------------|
| `1.5`                        | $1.5$             |
| `x`                          | $x$               |
| `( * 3 x )`                  | $3 x$             |
| `( + ( * 3 x ) x )`          | $(3 x) + x$       |
| `( * x ( sin x ) )`          | $x sin(x)$        |
| `( * 3 ( sin x ) )`          | $3 sin(x)$        |
| `( + ( cos x ) ( sin x ) )`  | $cos(x) sin(x) $  |

The parser relies on the function `series_factory` to create instances
of different series - until each series is implement, it will not
be able to parse those types of series.

Tasks
=====

T1 - Evaluation (35%)
---------------------

### T1.1 - Optimising evaluate_truncated

The current implementation of `Series::evaluate_truncated` calls the
`pow` function many times, which is usually very expensive.

Rewrite `Series::evaluate_truncated` so that it only uses multiplication,
addition, and function calls to `Series::a`.

### T1.2 - Create a program that prints approximation changes

Write a program `print_approximation.cpp` which reads an
expression from `stdin` and prints the changing approximation
values as reported using `Series::evaluate_truncated`.

The program takes two optional command-line arguments:

1.  The value of $x$ at which to evaluate the function. If this is
    omitted, a default of $x=1$ should be chosen.
2.  The maximum $n^{max}$ to evaluate the function to. If omitted, this
    should default to $n^{max}=20$.

The output of the function should consist of four comma-separated
columns:

1. The value of $n$ passed to `evaluate_truncated`.
2. The value returned from `evaluate_truncated`.
3. The value of $a_n$.
4. The value of $a_n x^n$.

The first row printed should be for $n=0$, with the last
printed for $n=n^{max}$. In total $n^{max}+1$ rows should be
printed.

The default printing precision of `cout` is sufficient.

### T1.3 - Implement evaluate_to_tolerance 

The function `Series::evaluate_to_tolerance` is intended to keep
adding terms of the series until the error drops below some tolerance
`tol`. Ideally this would find the smallest value $T$ such
that $| \sum_{n=T}^{\infty} a_n x^n | < tol$, but this is very
difficult to prove.

Implement a method which stops evaluating terms when the
remaining absolute error is about `tol`. You should strike
an appropriate balance between uncertainty in the error
remaining and the number of terms evaluated. Simply
evaluating everything to 100000 terms is not appropriate.

If more than `max_n` terms are needed and the function
has not converged, then an error message should be 
printed to `cerr`, and the program terminated with `exit(1)`.


T2 - Series Functions (30%)
---------------------------

While it is not required, it is strongly recommended that you create
test code to check the values your functions produce.

### T2.1 - Implement Cos

Implement the function `series_cos`.

### T2.2 - Implement Sin

Implement the function `series_sin`.

### T2.3 - Implement cache

Implement the function `series_cache`.

This is not a mathematical operation, but an optimisation to avoid
recalculating coefficients multiple times.

T3 - Operations on series (35%)
-------------------------------

While it is not required, it is strongly recommended that you create
test code to check the values your operations produce.

### T3.1 - Implement sum

Implement the function `series_sum`.

### T3.2 - Implement product

Implement the function `series_product`.

### T3.3 - Implement integration

Implement the function `series_integral`.

### T3.4 - Create a definite integration program

Create a program `definite_integration.cpp` which
receives a series on `stdin`, and prints a numerical
estimate of the definite integral over the range $[a,b]$
to `stdout`.

The program should take three required command-line parameters:

1. The lower range $a$.
2. The upper range $b$.
3. A value $tol$ to pass to `evaluate_to_tolerance`.

