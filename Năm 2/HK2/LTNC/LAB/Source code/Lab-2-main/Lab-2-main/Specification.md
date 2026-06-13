# Programming Problem Set

---

## 1. Square Lambda Function
**Requirement:** Write a lambda function named **square** that takes a number and returns its square.

**Testcase:**
- **Test:** `print(square(5))`
- **Result:** `25`

---

## 2. Get Odds with List Comprehension
**Requirement:** Use **list comprehension** to write a function `get_odds(nums)` that returns the odd numbers from the list `nums`.

**Testcase:**
- **Test:** `print(get_odds([1, 2, 3, 4, 5]))`
- **Result:** `[1, 3, 5]`

---

## 3. Get Word Lengths with Map
**Requirement:** Write `get_lengths(words)` using **map()** to return a list of word lengths from `words`.

**Testcase:**
- **Test:** `print(get_lengths(['apple', 'banana']))`
- **Result:** `[5, 6]`

---

## 4. Remove None with Filter
**Requirement:** Use **filter()** to write `remove_none(lst)` that removes all `None` values from the list.

**Testcase:**
- **Test:** `print(remove_none([1, None, 2, None]))`
- **Result:** `[1, 2]`

## 5. Get Even Indices with Slicing
**Requirement:** Use **slicing** to write `even_indices(lst)` that returns the elements at even indices.

**Testcase:**
- **Test:** `print(even_indices([1, 2, 3, 4, 5]))`
- **Result:** `[1, 3, 5]`

---

## 6. Product of List with Reduce
**Requirement:** Use **reduce()** from `functools` to write `product(nums)` that computes the product of all numbers in the list. If the list is empty, return 1.

**Testcase:**
- **Test:** `print(product([1, 2, 3, 4]))`
- **Result:** `24`

---

## 7. Function Chain with Currying
**Requirement:** Use **currying** to create a function chain so that `add(a)(b)` returns `a + b`.

**Testcase:**
- **Test:** `print(add(5)(10))`
- **Result:** `15`

---

## 8. Create Paired Tuples with Zip
**Requirement:** Use **zip()** to write `create_pairs(l1, l2)` that returns a list of paired tuples from the two input lists.

**Testcase:**
- **Test:** `print(create_pairs([1, 2], ['a', 'b']))`
- **Result:** `[(1, 'a'), (2, 'b')]`

## 9. Create Partial Function
**Requirement:** Use **functools.partial** to create a new function `double` from `multiply(x, y) = x * y` by fixing `x = 2`.

**Testcase:**
- **Test:** `print(double(10))`
- **Result:** `20`

---

## 10. Identity Matrix with Nested List Comprehension
**Requirement:** Use **nested list comprehension** to write `identity( n )` that generates an `n`-by-`n` identity matrix.

**Testcase:**
- **Test:** `print(identity(2))`
- **Result:** `[[1, 0], [0, 1]]`

---

## 11. Evaluate Lambda Calculus Expression
**Requirement:** Evaluate the following Lambda Calculus expression in Python using nested anonymous functions: `(\lambda f. f(5)) (\lambda x. x + 2)`.

**Testcase:**
- **Test:** `print(result)`
- **Result:** `7`

---

## 12. Implement NOT in Lambda Calculus
**Requirement:** Implement **NOT** in Lambda Calculus. Given:
`tru = lambda t: lambda f: t`
`fls = lambda t: lambda f: f`
Write `NOT = lambda b: ...`

**Testcase:**
- **Test:** `print(NOT(tru)("T")("F"))`
- **Result:** `F`

## 13. Implement SUCC for Church Numerals
**Requirement:** Implement **SUCC** (successor) for Church numerals: `SUCC = \lambda n. \lambda f. \lambda x. f (n f x)`.

**Testcase:**
- **Test:** `ZERO = lambda f: lambda x: x; print(SUCC(ZERO)(lambda x: x+1)(0))`
- **Result:** `1`

---

## 14. Tail Recursive Factorial
**Requirement:** Write the factorial function `fact(n, acc=1)` using tail recursion to reduce memory usage and keep the function stateless.

**Testcase:**
- **Test:** `print(fact(5))`
- **Result:** `120`

---

## 15. Filter and Square with Map/Filter
**Requirement:** Write `process(nums)` to: filter positive numbers, then square them. Use **filter()** and **map()**.

**Testcase:**
- **Test:** `print(process([-1, 2, -3, 4]))`
- **Result:** `[4, 16]`

---

## 16. Function Composition
**Requirement:** Write `compose(f, g)` that returns the composition function `h(x) = f(g(x))`.

**Testcase:**
- **Test:** `f=lambda x:x+1; g=lambda x:x*2; print(compose(f,g)(5))`
- **Result:** `11`

## 17. Debug Decorator
**Requirement:** Write a **decorator** named `debug` that prints "Calling" before executing the wrapped function.

**Testcase:**
- **Test:**
  ```python
  @debug
  def add(a, b): return a + b
  print(add(1, 2))
  ```
- **Result:**
  ```text
  Calling
  3
  ```

---

## 18. Implement MULT for Church Numerals
**Requirement:** Implement **MULT** (multiplication) for Church numerals: `MULT = \lambda m. \lambda n. \lambda f. m (n f)`.

**Testcase:**
- **Test:** `ONE = lambda f: lambda x: f(x); TWO = lambda f: lambda x: f(f(x)); print(MULT(ONE)(TWO)(lambda x:x+1)(0))`
- **Result:** `2`

---

## 19. Fibonacci Generator
**Requirement:** Use a **generator** to create an infinite Fibonacci sequence (0, 1, 1, 2, 3, 5, ...). The state variables should only be updated inside the generator's `while True` loop.

**Testcase:**
- **Test:** `f=fib(); print([next(f) for _ in range(3)])`
- **Result:** `[0, 1, 1]`

---

## 20. General Curry Decorator
**Requirement:** Write a general **@curry** decorator that can transform any function with `n` parameters into a chain of curried functions.

**Testcase:**
- **Test:**
  ```python
  @curry
  def add(a, b): return a + b
  print(add(1)(2))
  ```
- **Result:** `3`