"""
### TIME COMPLEXITY ###

On both iterative and recursive approaches, the time taken by the algorithm depends on the position of the searched element on the element axis created by the elements of the queried list.

BEST: the element is either outside the element axis, or right in the middle => Theta(1)
WORST: the element is at one of the lists ends => Theta(log(n))
AVERAGE: tree-based model => number of queried intervals based on the position of the element in the sorted array.

- the element at n/2 can be found using 1 comparision;
- the element at n/4 or 3n/4 can be found using 2 comparisons;
- the element at n/8, 3n/8, 5n/8 or 7n/8 can be found using 3 comparisons;
...

=> 1/n * sum_{k=0}^{[log2n]}{2^k(k+1)} = 1/n * (1 + 2 * 2 + 3 * 4 + ... + n * (log2n + 1)) =
   = nlog2n/n + 1/n, where nlog2n/n is dominant, thus the average complexity is Theta(logn)

=> O(logn)

### SPACE COMPLEXITY ###

Only constants are stored, thus resulting in Theta(1) additional space.
"""


def bin_search_iter(a: list, elem) -> int:
    l, r = 0, len(a)

    if r == 0:
        return -1

    if a[0] > elem or a[-1] < elem:
        return -1

    # r is right bound, l is left bound
    # r is exclusive, and l is inclusive
    while l <= r - 1:
        m = l + (r - l) // 2

        if a[m] == elem:
            return m

        if elem < a[m]:
            # r is exclusive, r is never reached
            r = m
        else:
            # l is inclusive, so we need to move it to the right
            l = m + 1

    return -1


def bin_search_rec(a: list, elem) -> int:
    if len(a) == 0:
        return -1

    if a[0] > elem or a[-1] < elem:
        return -1

    return bin_search_rec_helper(a, elem, 0, len(a))


def bin_search_rec_helper(a: list, elem, l: int, r: int) -> int:
    # r is right bound, l is left bound
    # r is exclusive, and l is inclusive
    if l > r - 1:
        return -1

    m = l + (r - l) // 2

    if a[m] == elem:
        return m

    if elem < a[m]:
        # r is exclusive, r is never reached
        return bin_search_rec_helper(a, elem, l, m)
    else:
        # l is inclusive, so we need to move it to the right
        return bin_search_rec_helper(a, elem, m + 1, r)


if __name__ == "__main__":
    a1 = [-7, -2, 0, 3, 7]
    a2 = [1]
    a3 = [1, 2, 3, 4, 5, 6]
    a4 = [1, 2]

    print(bin_search_rec(a1, 9), bin_search_iter(a1, 9))
    print(bin_search_rec(a2, 1), bin_search_iter(a2, 1))
    print(bin_search_rec(a3, 6), bin_search_iter(a3, 6))
    print(bin_search_rec(a3, 5), bin_search_iter(a3, 5))
    print(bin_search_rec(a4, 1), bin_search_iter(a4, 1))
