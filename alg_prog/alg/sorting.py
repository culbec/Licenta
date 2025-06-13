"""
### TIME COMPLEXITY ###

BEST = WORST = AVERAGE = Theta(n^2)

### SPACE COMPLEXITY ###

BEST = WORST = AVERAGE = Theta(1)
"""


def selection_sort(a: list, cond) -> list:
    n = len(a)

    # the ith element will be on its correct position after the second loop finishes
    for i in range(n - 1):
        for j in range(i + 1, n):
            if cond(a[i], a[j]):
                a[i], a[j] = a[j], a[i]

    return a


"""
    ### TIME COMPLEXITY ###

    BEST: list is already sorted, one pass: Theta(n)
    WORST: list is sorted in reverse order: Theta(n^2)
    AVERAGE: depends on the distance to the correct position of a misplaced element: Theta(N^2)
    
    (n-1) + (n-3) + (n-5) + ... + 0 + ... + (n-5) + (n-3) + (n-1) =
    = n * (n-2) * (1 + 3 + 5 + ... + n/2) = n^2 - (2 * n^2 / 4) = 
    = n^2 - n^2 / 2 = n^2/2

    Time complexity: O(n^2)

    ### SPACE COMPLEXITY ###
    Theta(1)
"""


def bubble_sort(a: list, cond) -> list:
    n = len(a)
    is_sorted = False

    while not is_sorted:
        is_sorted = True

        # we compare only adjacent elements and swap them accordingly
        # affects the 'is_sorted' state
        for i in range(n - 1):
            if cond(a[i], a[i + 1]):
                a[i], a[i + 1] = a[i + 1], a[i]
                is_sorted = False

    return a


"""
    ### TIME COMPLEXITY ###

    BEST: list is already sorted, one pass: Theta(n)
    WORST: list is sorted in reverse; for each element, we need to place it in the correct position:
    sum_{i=1}^{n}{sum_{j=1}^{i}{1}} = 1 + 2 + ... + n = n(n+1)/2 = Theta(n^2)
    AVERAGE: depends on the amount of swaps done by the second loop, therefore the relative ordering of a pair of elements in one specific iteration: Theta(n^2)

    Time complexity: O(n^2)

    ### SPACE COMPLEXITY ###
    Theta(1)
"""


def insertion_sort(a: list, cond) -> list:
    n = len(a)

    for i in range(1, n):
        # searching for the index of the element to its left
        # our goal is to pass the list backward and find the index of the element
        # if the we underflow the list, then the element is the first element in the list
        j, e = i - 1, a[i]

        # going left until the condition is not satisfied (misplaced elements)
        while j > -1 and not cond(e, a[j]):
            # we have a reference to the to be inserted element, this is safe
            a[j + 1] = a[j]
            # go left
            j -= 1

        # place the element in its place
        a[j + 1] = e

    return a


"""
    ### TIME COMPLEXITY ###
    
    The 'merge' method will run for 2 * n/2 = n iterations, as both arrays have half of the initial elements in almost all runs, only when the initial array's length is not even that doesn't happen.

    Theta(n * logn), proof below:

    Merging two arrays takes Theta(n+m) time, where n is the size of the first array and m is the size of the second array. As we are sorting halves each time, the complexity is Theta(n) * c

    T(n) = 2T(n/2) + c * n = 4T(n/4) + 2 * c * n = 8 * T(n/8) + 4 * c * n = ... = 2^k * T(n/2^k) + k * c * n
    The merge sort algorithm will execute until there is 1 element => n / 2^k = 1 => k = log2(n)
    => T(n) = n * T(1) + n * log2(n) => Theta(n * log2(n))

    Let n = 2^k

    T(2^k) = 2T(2^{k-1}) + 2^k
    2T(2^{k-1}) = 2^2T(2^{k-2}) + 2^k
    ...
    2^{k-1}T(2) = 2^kT(1) + 2^k
    2^kT(1) = 2^k

    => T(2^k) = k*2^k => T(n) = nlog2(n) => T(n) in Theta(nlog(n))
"""


def merge_sort(a: list, cond) -> list:
    # no need to sort an one element list or a null list
    if len(a) <= 1:
        return a

    # starting the sorting operation
    start, end = 0, len(a)
    return merge_sort_rec(a, start, end, cond)


def merge_sort_rec(a: list, start: int, end: int, cond) -> list:
    # 'start' and 'end' indicices indicate either an one element list or a null list
    # ### BASE CASE ###
    if end - start <= 1:
        return a[start:end]

    # Divide et Impera: splitting the list in half
    m = start + (end - start) // 2
    
    # retrieving the sorted left part
    left = merge_sort_rec(a, start, m, cond)
    # retrieveing the sorted right part
    right = merge_sort_rec(a, m, end, cond)
    # sorting the left and right parts
    # we already know their length based on the 'start', 'm' and 'end' indicies
    # we could've gotten their length, but this is more efficient
    return merge(left, right, m - start, end - m, cond)


def merge(a: list, b: list, n: int, m: int, cond) -> list:
    i, j, c = 0, 0, []

    while i < n and j < m:
        if cond(a[i], b[j]):
            c.append(b[j])
            j += 1
        else:
            c.append(a[i])
            j += 1

    c += [a[k] for k in range(i, n)]
    c += [b[k] for k in range(j, m)]

    return c


"""
    ### TIME COMPLEXITY ###
    
    BEST: Theta(nlogn)
    WORST: Theta(n^2)
    AVERAGE: Theta(nlogn)

    O(nlogn)
"""


def quick_sort(a: list, cond) -> list:
    # no need to sort an one element list or a null list
    if len(a) <= 1:
        return a

    # starting the sorting process
    return quick_sort_rec(a, 0, len(a), cond)


def quick_sort_rec(a: list, start: int, end: int, cond) -> list:
    # invalid indicies: either overflow or underflow of the list
    # ### BASE CASE ###
    if start >= end or start < 0:
        return a
    
    # partitionate the list
    # the element at position 'p' will be in its correct place
    p = partition(a, start, end, cond)

    # knowing that the element at position 'p' is in its correct position, we
    # just need to sort the elements left and right to it, because they aren't sorted
    quick_sort_rec(a, start, p, cond)
    quick_sort_rec(a, p + 1, end, cond)

    return a


def partition(a: list, start: int, end: int, cond) -> list:
    # similar to INSERTION SORT, we want a certain element to be in its correct position in the list
    # we chose the last element in the current subset
    i, piv = start, a[end - 1]

    # sorting the elements by the pivot: elements its left will all be lower, and elements its right will all be higher
    for j in range(start, end - 1):
        # condition based on pivot
        if cond(piv, a[j]):
            # swapping elements and increasing the end pivot index
            a[i], a[j] = a[j], a[i]
            i += 1

    # now we place the pivot in its correct position
    # the ith element did not satisfy the condition with the pivot, so the pivot is 'lower' than it
    a[i], a[end - 1] = a[end - 1], a[i]
    return i


if __name__ == "__main__":
    cond = lambda x, y: x > y

    print(selection_sort([3, 2, 2, 1, -1], cond))
    print(bubble_sort([3, 2, 2, 1, -1], cond))
    print(insertion_sort([3, 2, 2, 1, -1], cond))
    print(merge_sort([3, 2, 2, 1, -1], cond))
    print(quick_sort([3, 2, 2, 1, -1], cond))
