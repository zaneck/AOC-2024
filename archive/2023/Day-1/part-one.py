def extract_first_digit(line) -> str:
    for e in range(len(line)):
        if line[e].isdigit():
            return line[e]


def extract_last_digit(line) -> str:
    for e in range(len(line) - 1, -1, -1):
        if line[e].isdigit():
            return line[e]


def read_sum(file: str) -> int:
    with open(file) as f:
        # for line in f:
        #     print( extract_first_digit(line), extract_last_digit(line), line)

        return sum(
            int(extract_first_digit(line) + extract_last_digit(line)) for line in f
        )

print("Part One")
print("example", read_sum("example-part-one.txt"))
print("test", read_sum("test.txt"))

