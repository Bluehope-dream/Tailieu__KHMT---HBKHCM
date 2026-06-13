from lab10 import from_church_bool, church_false,church_not,church_true,map_recursive,compose,fix,type_of,ll_from_iterable,ll_to_list,merge_sorted_lists,merge_sort_linked, foldl,q5_curry

print(from_church_bool(church_true))
# True

print(from_church_bool(church_false))
# False

print(from_church_bool(church_not(church_true)))
# False

print(from_church_bool(church_not(church_false)))
# True

print(church_not(church_false)("left")("right"))
# left

print(church_not(church_true)("left")("right"))
# right
print(compose(lambda x: x + 1, lambda x: x * 2)(10))
print(map_recursive(lambda x: x * x, [1, 2, 3]))

print (map_recursive(lambda x: x+ 2020,[2 ,5,9,20]))

fact = fix(lambda rec: lambda n: 1 if n == 0 else n * rec(n - 1))
print(fact(5))
gcd = fix(
    lambda rec:
        lambda a, b:
            a if b == 0 else rec(b, a % b)
)

print(gcd(48, 18))




# print(type_of(Sub(IntLit(3), IntLit(2))))
# print(type_of(If(BoolLit(True), IntLit(1), BoolLit(False))))



a = ll_from_iterable([1, 3, 5])
b = ll_from_iterable([2, 4, 6])
print(ll_to_list(merge_sorted_lists(a, b)))
head = ll_from_iterable([4,2,9,1,2])

sorted_head = merge_sort_linked(head)

print(ll_to_list(sorted_head))


print(foldl(lambda acc, x: acc + x, 0, [1, 2, 3, 4]))


print(q5_curry(lambda p: f"{p[0]}:{p[1]}")("A")("B"))


