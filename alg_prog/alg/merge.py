"""
    ### TIME COMPLEXITY ###

    The lists are passed only once, resulting in a merged list
    with or without duplicates.

    BEST = WORST = MEDIUM = Theta(n + m)

    ### SPACE COMPLEXITY ###

    The answer depends on the merging strategy: keeping or not keeping duplicates

    If duplicates are kept, Theta(n+m) additional space is required, as
    a new list with all the elements from the merged lists are created

    If duplicates aren't kept, the answer is a bit more complex. The amount of space
    needed by the program to merge the two lists depends on the amount of duplicates 
    contained in both lists. That is not easy to determine.

    BEST: every element in the first list is duplicated in the second list, resulting in O(n) space.
    WORST: no element is duplicated, resulting in O(n + m) space.
    AVERAGE: tricky, it depends on the amount of duplicates in both the first and second lists.

    Let's assume that a and b are our lists, of size n and m respectively. We assume that elements from both a and b are drawn from a universe U of size u, independently and uniformly, at a random rate.

    We want to compute the amount of elements x in U that appear in either a or b:
                
        E[X] = = E[sum(x in a or b, x in U)] = sum(E[x in a or b], x in U)
        P(x not in a) = (1 - 1/u)^n, P(x not in b) = (1 - 1/u)^m
        P(x not in a U b) = (1 - 1/u)^n * (1 - 1/u)^m = (1 - 1/u)^(n+m)
        E[X] = u * (1 - (1 - 1/u)^(n+m)), where 1 - (1 - 1/u)^(n+m) is 0 if x in U is not in a U b and 1 is x in U is in a U b.
    For u >> n + m, we can approximate (1 - 1/u)^(n+m) with e^-[(n+m)/u].
    The space complexity resulted is: Theta(u * (1 - (1 - 1/u)^(n+m)))

    The resulted space complexity, merge with no duplicates, is: O(u * (1 - (1 - 1/u)^(n+m)))
"""

def merge(a: list, b: list, keep_duplicates: bool = False) -> list | None:
    if sorted(a) != a or sorted(b) != b:
        return None

    i, j = 0, 0
    c = []

    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            if not keep_duplicates:
                if c and c[-1] == a[i]:
                    i += 1
                    continue
            c.append(a[i])
            i += 1
        else:
            if not keep_duplicates:
                if c and c[-1] == b[j]:
                    j += 1
                    continue
            c.append(b[j])
            j += 1

    for k in range(i, len(a)):
        if not keep_duplicates:
            if c and c[-1] == a[k]:
                continue
        c.append(a[k])

    for k in range(j, len(b)):
        if not keep_duplicates:
            if c and c[-1] == b[k]:
                continue
        c.append(b[k])

    return c
    
if __name__ == "__main__":
    a = [1, 2, 3, 5, 9, 12]
    b = [-3, -1, 2, 5, 15]
    print(merge(a, b))
    print(merge(a, b, True))
