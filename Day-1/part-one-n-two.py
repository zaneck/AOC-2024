def by_line(file: str):
    with open(file, "r") as f:
        for line in f:
            yield line.strip().split("   ")


def two_list(file: str):
    l1 = []
    l2 = []
    for line in by_line(file):
        l1.append(line[0])
        l2.append(line[1])
    return sorted(l1), sorted(l2)


def similarity(l1, l2):
    count = {}
    res = 0

    for e in l2:
        count[e] = count.get(e, 0) + 1

    for e in l1:
        res += count.get(e, 0) * int(e)

    return res


def diff_sum(l1, l2):
    return sum([abs(int(x) - int(y)) for x, y in zip(l1, l2)])


if __name__ == "__main__":
    l1, l2 = two_list("example.txt")
    print(diff_sum(l1, l2))

    l1, l2 = two_list("input.txt")
    print(diff_sum(l1, l2))

    print(similarity(l1, l2))
