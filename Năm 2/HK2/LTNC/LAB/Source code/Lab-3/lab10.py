from __future__ import annotations

from dataclasses import dataclass
from typing import Any, Callable, Dict, Generic, Iterable, Optional, Tuple, TypeVar


A = TypeVar("A")
B = TypeVar("B")
C = TypeVar("C")


# ============================================================
# 10-Question Consolidated Lab (Challenge)
# Sources: lab.py, linked_list_lambda_merge_sort.py, curry_howard_challenge.py
# ============================================================


# Q1
ChurchBool = Callable[[Any], Callable[[Any], Any]]


def church_true(x: Any) -> Callable[[Any], Any]:
    return lambda y: x


def church_false(x: Any) -> Callable[[Any], Any]:
    return lambda y: y


def church_not(b: ChurchBool) -> ChurchBool:
    """Q1: Implement Church boolean negation."""
    # TODO: Return the Church-encoded negation of b.
    # Write your answer below this comment.
    return lambda x : lambda y : b(y)(x)
    


def from_church_bool(b: ChurchBool) -> bool:
    return b(True)(False)



def compose(f: Callable[[B], C], g: Callable[..., B]) -> Callable[..., C]:
    """Q2: Implement variadic composition: f(g(*args, **kwargs))."""
    # TODO: Return a new function that accepts the arguments for g,
    # then applies f to the result of g.
    # Write your answer below this comment.
    
    def composer (*args,**kwargs):
        return f(g(*args,**kwargs))

    return composer 

# Q3
def map_recursive(fn: Callable[[A], B], xs: list[A]) -> list[B]:
    """Q3: Implement recursive map without loops."""
    # TODO: Recursively apply fn to every element of xs.
    # Do not use loops for this question.   
    # Write your answer below this comment.
    
    if xs == []:
        return []

    return [fn(xs[0])] + map_recursive(fn, xs[1:])


# Q4
def fix(f: Callable[[Callable[..., Any]], Callable[..., Any]]) -> Callable[..., Any]:
    """Q4: Implement eager fixed-point combinator (Z-style)."""
    # TODO: Implement a fixed-point combinator that works in eager Python.
    # It should support recursive functions through self-application.
    # Write your answer below this comment.
    return (lambda x: f(lambda *args: x(x)(*args)))(
           lambda x: f(lambda *args: x(x)(*args)))


# Q5
class Type:
    pass


@dataclass(frozen=True)
class TInt(Type):
    pass


@dataclass(frozen=True)
class TBool(Type):
    pass


@dataclass(frozen=True)
class TFun(Type):
    arg: Type
    ret: Type


class Expr:
    pass


@dataclass(frozen=True)
class Var(Expr):
    name: str


@dataclass(frozen=True)
class Lam(Expr):
    param: str
    param_type: Type
    body: Expr


@dataclass(frozen=True)
class App(Expr):
    fn: Expr
    arg: Expr


@dataclass(frozen=True)
class IntLit(Expr):
    value: int


@dataclass(frozen=True)
class BoolLit(Expr):
    value: bool


@dataclass(frozen=True)
class If(Expr):
    cond: Expr
    then_branch: Expr
    else_branch: Expr


@dataclass(frozen=True)
class Add(Expr):
    left: Expr
    right: Expr


@dataclass(frozen=True)
class Sub(Expr):
    left: Expr
    right: Expr


@dataclass(frozen=True)
class Mod(Expr):
    left: Expr
    right: Expr


@dataclass(frozen=True)
class IsZero(Expr):
    value: Expr


TypeEnv = Dict[str, Type]


def type_of(expr: Expr, env: TypeEnv | None = None) -> Type:
    """Q5: Implement type checker for Expr including Add/Sub/Mod/IsZero."""
    # TODO: Return the type of expr under env.
    # Handle literals, variables, lambdas, applications, if-expressions,
    # Add, Sub, Mod, and IsZero.
    # Raise TypeError when an expression is not well-typed.
    # Write your answer below this comment.
    if env is None: 
        env = {}

    if isinstance(expr,IntLit):
        return TInt()
    # Bool literial 

    if isinstance(expr,BoolLit):
        return TBool()
    
    if isinstance(expr,Var):
        if expr.name in env: 
            return env[expr.name]
        raise TypeError(f"Unbounded variable: {expr.name}")
    
    if isinstance(expr,Lam):
        new_env = env.copy()
        new_env[expr.param] = expr.param_type

        body_type = type_of(expr.body,new_env)
        return TFun(expr.param_type,body_type)
    
    # Application
    if isinstance(expr, App):
        fn_type = type_of(expr.fn, env)
        arg_type = type_of(expr.arg, env)

        if not isinstance(fn_type, TFun):
            raise TypeError("Trying to apply non-function")

        if fn_type.arg != arg_type:
            raise TypeError("Function argument type mismatch")

        return fn_type.ret
    
    # If
    if isinstance(expr, If):
        cond_type = type_of(expr.cond, env)

        if cond_type != TBool():
            raise TypeError("If condition must be boolean")

        then_type = type_of(expr.then_branch, env)
        else_type = type_of(expr.else_branch, env)

        if then_type != else_type:
            raise TypeError("If branches must have same type")

        return then_type


    # Add/Sub/Mod
    if isinstance(expr, (Add, Sub, Mod)):
        left_type = type_of(expr.left, env)
        right_type = type_of(expr.right, env)

        if left_type != TInt() or right_type != TInt():
            raise TypeError("Arithmetic operands must be integers")

        return TInt()

    # IsZero
    if isinstance(expr, IsZero):
        value_type = type_of(expr.value, env)

        if value_type != TInt():
            raise TypeError("IsZero expects integer")

        return TBool()

    raise TypeError("Unknown expression")

# Q6 + Q7
@dataclass
class Node:
    value: int
    next: Node | None = None


def ll_from_iterable(values: Iterable[int]) -> Node | None:
    head: Node | None = None
    tail: Node | None = None
    for v in values:
        n = Node(v)
        if head is None:
            head = n
            tail = n
        else:
            tail.next = n
            tail = n
    return head


def ll_to_list(head: Node | None) -> list[int]:
    out: list[int] = []
    cur = head
    while cur is not None:
        out.append(cur.value)
        cur = cur.next
    return out


def merge_sorted_lists(a: Node | None, b: Node | None) -> Node | None:
    """Q6: Merge two already sorted linked lists."""
    # TODO: Merge two sorted linked lists into one sorted linked list.
    # You may implement this recursively.
    # Write your answer below this comment.
    if a is None:
        return b

    if b is None:
        return a
    
    # chọn node nhỏ hơn
    if a.value <= b.value:
        a.next = merge_sorted_lists(a.next, b)
        return a
    else:
        b.next = merge_sorted_lists(a, b.next)
        return b


def merge_sort_linked(head: Node | None) -> Node | None:
    """Q7: Implement linked-list merge sort."""
    # TODO: Sort the linked list using merge sort.
    # Split the list, recursively sort each half, then merge them.
    # Write your answer below this comment.
    if not head  or not head.next :
        return head 

    # Xác định midpoint
    slow = head
    fast = head.next

    while fast is not None and fast.next is not None:
        slow = slow.next
        fast = fast.next.next

    # cắt list thành 2 nửa
    mid = slow.next
    slow.next = None

    # recursive sort
    left = merge_sort_linked(head)
    right = merge_sort_linked(mid)

    # merge lại
    return merge_sorted_lists(left, right)


# Q8 + Q9
@dataclass(frozen=True)
class Tree(Generic[A]):
    value: A
    left: Optional[Tree[A]] = None
    right: Optional[Tree[A]] = None


def foldl(fn: Callable[[B, A], B], init: B, xs: Iterable[A]) -> B:
    """Q8: Implement left fold for iterables."""
    # TODO: Traverse xs from left to right, updating the accumulator.
    # Start with init and repeatedly apply fn(acc, x).
    # Write your answer below this comment.
    acc = init

    for x in xs:
        acc = fn(acc, x)

    return acc


def fold_tree(leaf: B, node_fn: Callable[[A, B, B], B], t: Optional[Tree[A]]) -> B:
    """Q9: Implement structural fold over binary tree."""
    # TODO: Return leaf for an empty tree.
    # For a non-empty tree, recursively fold left and right subtrees,
    # then combine them with node_fn(value, left_result, right_result).
    # Write your answer below this comment.

    if t is None : 
        return leaf 

    left_branch = fold_tree(leaf, node_fn, t.left)
    right_branch = fold_tree(leaf,node_fn,t.right)

    return node_fn(t.value,left_branch,right_branch)


# Q10
def q5_curry(h: Callable[[Tuple[A, B]], C]) -> Callable[[A], Callable[[B], C]]:
    """Q10: Implement Curry-Howard currying: ((A,B)->C) -> A -> B -> C."""
    # TODO: Convert a function that takes one pair argument into
    # a curried function that takes a, then b.
    # Write your answer below this comment.
    return lambda a: lambda b : h ((a,b))