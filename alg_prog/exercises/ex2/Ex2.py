class B:
    def __init__(self, b: int):
        self.b = b

    def print(self):
        print(f"b = {self.b}")


class D(B):
    def __init__(self, b: int, d: str):
        super().__init__(b)
        self.d = d

    def print(self):
        print(f"b = {self.b} d = {self.d}")


def build_dict() -> dict[int, B]:
    o1 = B(8)
    o2 = D(5, "D5")
    o3 = B(-3)
    o4 = D(9, "D9")

    d = dict()
    d[8] = o1
    d[5] = o2
    d[-3] = o3
    d[9] = o4

    return d


def get_filtered_dict_b_greater_than_6(d: dict[int, B]) -> dict[int, B]:
    return {k: v for k, v in d.items() if isinstance(v, B) and v.b > 6}


"""
    Dictionary.put(dictionary^{io}, key^{i}, value^{i}): adauga perechea (key, value) in dictionar
    @param dictionary: dictionarul in care se adauga perechea
    @param key: cheia asociata valorii
    @param value: valoarea asociata cheii
    @pre: dictionary este un dictionar valid, nu exista deja o cheie cu valoarea key in dictionar
    @post: dictionarul contine perechea (key, value)
"""

"""
    Dictionary.get(dictionary^{i}, key^{i}, v^{o}): returneaza valoarea asociata cheii key in dictionar
    @param dictionary: dictionarul din care se obtine valoarea
    @param key: cheia pentru care se obtine valoarea
    @pre: dictionary este un dictionar valid, exista o cheie cu valoarea key in dictionar
    @post: v este valoarea asociata cheii key in dictionar
"""

"""
    Dictionary.size(dictionary^{i}, dim^{o}): returneaza numarul de perechi (cheie, valoare) din dictionar
    @param dictionary: dictionarul pentru care se obtine numarul de perechi
    @pre: dictionary este un dictionar valid
    @post: dim este numarul de perechi (cheie, valoare) din dictionar
"""

if __name__ == "__main__":
    d = build_dict()

    print("Initial dictionary:")
    for key, value in d.items():
        value.print()

    print("\nFiltered dictionary (b > 6):")
    filtered_dict = get_filtered_dict_b_greater_than_6(d)
    for key, value in filtered_dict.items():
        value.print()
