from typing import Counter


def read_file(file: str) -> list[list[int]]:
    with open(file, "r") as f:
        return [[int(e) for e in line.strip().split(" ")] for line in f]


def strict_valid(elt: list[int]) -> bool:
    diff = elt[0] - elt[1]
    sign = "+" if elt[0] - elt[1] > 0 else "-"

    if abs(diff) > 3 or diff == 0:
        return False

    current = elt[1]
    for e in elt[2:]:
        new_diff = current - e
        new_sign = "+" if current - e > 0 else "-"

        if new_sign != sign or abs(new_diff) > 3 or new_diff == 0:
            return False

        current = e

    return True


def one_error_valid(elt: list[int]) -> bool:
    valid = strict_valid(elt)
    if not valid:
        for i in range(len(elt)):
            elt_cop = elt.copy()
            elt_cop.pop(i)
            if strict_valid(elt_cop):
                return True
    return valid


def score(result: list[bool]) -> int:
    return Counter(result)[True]


if __name__ == "__main__":
    elt = read_file("example.txt")
    result = [strict_valid(e) for e in elt]
    result_2 = [one_error_valid(e) for e in elt]
    print(score(result))
    print(score(result_2))

    elt = read_file("input.txt")
    result = [strict_valid(e) for e in elt]
    result_2 = [one_error_valid(e) for e in elt]
    print(score(result))
    print(score(result_2))
