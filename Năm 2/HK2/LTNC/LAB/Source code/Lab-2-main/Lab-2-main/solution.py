from functools import reduce, partial

# 1
square = lambda x : x*x

# 2
def get_odds(nums):
    # TODO
    return [num for num in nums if num % 2 != 0]

# 3
def get_lengths(words):
    # TODO
    res = map (lambda word: len(word),words)
    return (list(res))

# 4
def remove_none(lst):
    # TODO
    return list(filter(None,lst))

# 5
def even_indices(lst):
    # TODO
    return [lst [i]  for i in range(len(lst)) if i% 2==0 ]
#-------------------------------------------------------------------------
# 6
from  functools import reduce, partial

def product(nums):
    # TODO
    return reduce (lambda x,y: x*y, nums,1)

# 7
# TODO
add = lambda a : lambda b: a+b

# 8
def create_pairs(l1, l2):
    # TODO
    res = zip(l1,l2)
    return list(res)

# 9
 # TODO
tmp = lambda x,y : x*y

double = partial (tmp,2)

# 10
def identity(n):
    # TODO
    return  [[1 if i ==j else 0 for j in range(n)] for i in range (n)]


# 11
result = (lambda  f: f(5))(lambda x: x+2)    # Tham số truyền vào là hàm nên mới có trị như vậy 

# 12

tru = lambda t: lambda f: t
fls = lambda t: lambda f: f
NOT = lambda a : a (fls) (tru)

# 13
# TODO
SUCC = lambda n : lambda f : lambda x: f(n(f)(x)) #n(f)(x) áp dụng n lần f lên x thêm 1 lần nữa f(n(f)(x))

# 14
def fact(n, acc=1):
    # TODO
    if n ==0:
        return acc
    return fact(n-1,acc*n)

# 15
def process(nums):
    # TODO
                                        #Iterable list
    return list (map(lambda x: x**2, filter(lambda x: x>0, nums)))
# 16
def compose(f, g):
    # TODO
    return lambda x: f(g(x))  # Bởi f và g đã được truyền lên  


# 17
def debug(func):
    # TODO
    
    
    def wrapper(*args,**kwargs):
        print("Calling")
        return func(*args,**kwargs)
    return wrapper

# 18
# MULT = \lambda m. \lambda n. \lambda f. m (n f)
MULT = lambda m : lambda n : lambda f : m((n)(f))

# 19
def fib():
    # TODO
    a,b = 0,1
    while True:
        yield a
        a,b = b, a+b
    
# 20
# def curry(func):
#     # TODO
#     def wrapper_function(*args, **kwargs):
#         return func(*args, **kwargs)
#     return wrapper_function

def curry(func):
    def curried(*args):
        
        if len(args) >= func.__code__.co_argcount:
            return func(*args)
        
        return lambda *next_args: curried(*(args + next_args))
    return curried