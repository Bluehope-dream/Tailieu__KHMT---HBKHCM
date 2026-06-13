import pytest
from solution import (
    square, get_odds, get_lengths, remove_none, even_indices,
    product, add, create_pairs, double, identity, result,
    NOT, tru, fls, SUCC, fact, process, compose, debug,
    MULT, fib, curry
)

# 1. square
def test_square_1(): assert square(2) == 4
def test_square_2(): assert square(0) == 0
def test_square_3(): assert square(-3) == 9

# 2. get_odds
def test_get_odds_1(): assert get_odds([1,2,3]) == [1,3]
def test_get_odds_2(): assert get_odds([2,4]) == []
def test_get_odds_3(): assert get_odds([5]) == [5]
def test_get_odds_4(): assert get_odds([]) == []
def test_get_odds_5(): assert get_odds([1,2,3,4,5,6,7,8,9,10]) == [1,3,5,7,9]

# 3. get_lengths
def test_get_lengths_1(): assert get_lengths(["a","bb"]) == [1,2]
def test_get_lengths_2(): assert get_lengths([]) == []
def test_get_lengths_3(): assert get_lengths(["abc"]) == [3]
def test_get_lengths_4():
    assert get_lengths(
        ["apple","banana","cat","dog","elephant","hi","python","code","lambda","function"]
    ) == [5,6,3,3,8,2,6,4,6,8]

# 4. remove_none
def test_remove_none_1(): assert remove_none([1,None,2]) == [1,2]
def test_remove_none_2(): assert remove_none([None,None]) == []
def test_remove_none_3(): assert remove_none([3]) == [3]
def test_remove_none_4():
    assert remove_none([
        1, None, 2, 3, None,
        4, 5, None, 6, 7,
        None, 8, 9, 10, None
    ]) == [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# 5. even_indices
def test_even_indices_1(): assert even_indices([1,2,3,4]) == [1,3]
def test_even_indices_2(): assert even_indices([10]) == [10]
def test_even_indices_3(): assert even_indices([]) == []
def test_even_indices_4():
    assert even_indices([
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15
    ]) == [1, 3, 5, 7, 9, 11, 13, 15]

# 6. product
def test_product_1(): assert product([1,2,3]) == 6
def test_product_2(): assert product([]) == 1
def test_product_3(): assert product([5]) == 5
def test_product_4():
    assert product([
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10
    ]) == 3628800

# 7. add
def test_add_1(): assert add(1)(2) == 3
def test_add_2(): assert add(5)(0) == 5
def test_add_3(): assert add(-1)(1) == 0

# 8. create_pairs
def test_pairs_1(): assert create_pairs([1,2],["a","b"]) == [(1,"a"),(2,"b")]
def test_pairs_2(): assert create_pairs([],[]) == []
def test_pairs_3(): assert create_pairs([1],["x"]) == [(1,"x")]
def test_pairs_4():
    assert create_pairs([
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15
    ], [
        "a", "b", "c", "d", "e",
        "f", "g", "h", "i", "j",
        "k", "l", "m", "n", "o"
    ]) == [
        (1, "a"), (2, "b"), (3, "c"), (4, "d"), (5, "e"),
        (6, "f"), (7, "g"), (8, "h"), (9, "i"), (10, "j"),
        (11, "k"), (12, "l"), (13, "m"), (14, "n"), (15, "o")
    ]

# 9. double
def test_double_1(): assert double(5) == 10
def test_double_2(): assert double(0) == 0
def test_double_3(): assert double(-2) == -4

# 10. identity
def test_identity_1(): assert identity(1) == [[1]]
def test_identity_2(): assert identity(2) == [[1,0],[0,1]]
def test_identity_3(): assert identity(3)[0][0] == 1
def test_identity_4():
    assert identity(5) == [
        [1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0],
        [0, 0, 1, 0, 0],
        [0, 0, 0, 1, 0],
        [0, 0, 0, 0, 1]
    ]

# 11. result
def test_result_1(): assert result == 7

# 12. NOT
def test_not_1(): assert NOT(tru)("T")("F") == "F"
def test_not_2(): assert NOT(fls)("T")("F") == "T"
def test_not_3(): assert NOT(tru)(1)(0) == 0

# 13. SUCC
def test_succ_1():
    ZERO = lambda f: lambda x: x
    assert SUCC(ZERO)(lambda x: x+1)(0) == 1

def test_succ_2():
    ZERO = lambda f: lambda x: x
    assert SUCC(SUCC(ZERO))(lambda x: x+1)(0) == 2

def test_succ_3():
    ZERO = lambda f: lambda x: x
    assert SUCC(ZERO)(lambda x: x*2)(1) == 2

# 14. fact
def test_fact_1(): assert fact(5) == 120
def test_fact_2(): assert fact(0) == 1
def test_fact_3(): assert fact(3) == 6

# 15. process
def test_process_1(): assert process([-1,2,-3,4]) == [4,16]
def test_process_2(): assert process([]) == []
def test_process_3(): assert process([1]) == [1]

# 16. compose
def test_compose_1():
    f=lambda x:x+1; g=lambda x:x*2
    assert compose(f,g)(5) == 11

def test_compose_2():
    f=lambda x:x-1; g=lambda x:x+1
    assert compose(f,g)(0) == 0

def test_compose_3():
    f=lambda x:x*3; g=lambda x:x
    assert compose(f,g)(2) == 6

# 17. debug (không assert print)
def test_debug_1():
    @debug
    def f(x): return x+1
    assert f(1) == 2

def test_debug_2():
    @debug
    def f(x,y): return x+y
    assert f(2,3) == 5

def test_debug_3():
    @debug
    def f(): return 10
    assert f() == 10

def test_debug_4(capsys):
    @debug
    def add(a, b):
        return a + b

    result = add(1, 2)

    captured = capsys.readouterr()

    assert result == 3
    assert "Calling" in captured.out

# 18. MULT
def test_mult_1():
    ONE = lambda f: lambda x: f(x)
    TWO = lambda f: lambda x: f(f(x))
    assert MULT(ONE)(TWO)(lambda x:x+1)(0) == 2

def test_mult_2():
    ZERO = lambda f: lambda x: x
    ONE = lambda f: lambda x: f(x)
    assert MULT(ZERO)(ONE)(lambda x:x+1)(0) == 0

def test_mult_3():
    ONE = lambda f: lambda x: f(x)
    assert MULT(ONE)(ONE)(lambda x:x+1)(0) == 1

# 19. fib
def test_fib_1():
    f=fib()
    assert [next(f) for _ in range(3)] == [0,1,1]

def test_fib_2():
    f=fib()
    next(f); next(f)
    assert next(f) == 1

def test_fib_3():
    f=fib()
    assert next(f) == 0

# 20. curry
def test_curry_1():
    @curry
    def add(a,b): return a+b
    assert add(1)(2) == 3

def test_curry_2():
    @curry
    def mul(a,b): return a*b
    assert mul(2)(3) == 6

def test_curry_3():
    @curry
    def sub(a,b): return a-b
    assert sub(5)(2) == 3