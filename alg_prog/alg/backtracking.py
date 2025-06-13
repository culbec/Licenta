"""
### BACKTRACKING ###

Useful for problems where multiple solutions are possible.
Example: all groups of people of size k ordered by height

It involves three main steps:

1. space search: iterates through all possible combinations of a feature space;
    - e.g.: iterates over all persons from a given list;
2. ok condition: verifies if adding the current element to the solution is an ok option that can lead to the final solution;
    - e.g.: is the current person's height greater than the last one's?
3. solution: verifies if the current solution is a final solution; if so, we add it to the collection of solutions;
    - e.g.: we have k people? (the heights are ordered, part of candidate list)

This general algorithm can be applied to various problems as it can be extended by just only adjusting the `ok condition` and `solution` methods.
"""

# Finding permutations of k elements


def solution(curr: list, k: int) -> bool:
    return len(curr) == k and len(set(curr)) == k


def condition(curr: list, k: int) -> bool:
    return len(curr) < k


def backtrack(a: list, k: int, curr: list, finals: list) -> None:
    new_curr = curr[:]
    for x in a:
        new_curr.append(x)

        if solution(new_curr, k):
            finals.append(new_curr)

        if condition(new_curr, k):
            backtrack(a, k, new_curr, finals)
        new_curr = new_curr[:-1]


if __name__ == "__main__":
    f = []
    backtrack([1, 2, 3, 4, 5, 6], 3, [], f)
    print(f"Solutions: {f} | Size: {len(f)}")
