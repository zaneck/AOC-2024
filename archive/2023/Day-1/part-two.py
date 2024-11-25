digit_letters = [
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
]


def extract_number(line) -> dict:
    number = {}
    offset = 0
    while len(line) > 0:
        for i, d in enumerate(digit_letters):
            if line.startswith(d):
                number[offset] = i
                line = line[1:]
                offset += 1
                break
        if line[:1].isdigit():
            number[offset] = int(line[:1])
        line = line[1:]
        offset += 1
    return number


def read_sum(file: str) -> int:
    s = 0
    with open(file) as f:
        for line in f:
            numbers = extract_number(line)
            min_index = min(numbers.keys())
            max_index = max(numbers.keys())
            
            print(numbers[min_index], numbers[max_index], line)

            s += (numbers[min_index] * 10) + numbers[max_index]
    return s


print("Part two")
print("example", read_sum("example-part-two.txt"))
print("test", read_sum("test.txt"))
