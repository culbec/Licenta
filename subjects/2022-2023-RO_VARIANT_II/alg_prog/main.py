def binarySearchDecreasing(l: list, elem: int, start: int, end: int) -> int:
    if start >= end - 1:
        if len(l) == 0:
            return start
        elif elem < l[start]:
            return start + 1
        else:
            return start

    m = start + (end - start) // 2
    if elem == l[m]:
        return m
    elif elem < l[m]:
        return binarySearchDecreasing(l, elem, m, end)
    else:
        return binarySearchDecreasing(l, elem, start, m)


def circularPerm(text: str, k: int) -> str:
    if k <= 0 or k >= len(text):
        return text

    output = [c for c in text]
    n = len(text)
    for i in range(n):
        output[i] = text[((n - k) + i) % n]

    return "".join(output)


def isInorderTraversal(a: list) -> int | list:
    mapping = {}

    for i in range(len(a)):
        if a[i] != (i + 1):
            if (i + 1) < a[i]:
                mapping[(i + 1)] = a[i]
            else:
                mapping[a[i]] = i + 1

    return 0 if len(mapping) == 0 else [(k, v) for k, v in mapping.items()]


if __name__ == "__main__":
    l = [14, 12, 9, 5]
    start, end = 0, len(l)
    # assume 1-indexing
    print(binarySearchDecreasing(l, 15, start, end) + 1)
    print(binarySearchDecreasing(l, 11, start, end) + 1)
    print(binarySearchDecreasing(l, 12, start, end) + 1)

    text, k = "STRING", 2
    print(circularPerm(text, k))

    a = [3, 2, 1]
    print(isInorderTraversal(a))
