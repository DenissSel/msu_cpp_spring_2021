def solution1(str_given):
    return [str_given[n] * 4 for n in range(len(str_given))]


def solution2(str_given):
    return [str_given[n] * (n + 1) for n in range(len(str_given))]


def solution3(str_giv):
    return [n for n in str_giv if (bin(n)[2:].count('1') % 2 == 0)]


def solution4(mas):
    return [item for sublist in mas for item in sublist]


def solution5(n):
    return [(x, y, z) for x in range(1, n + 1) for y in range(x, n + 1)
            for z in range(y, n + 1) if x ** 2 + y ** 2 == z ** 2]


def solution6(mas):
    return [[item_plus + item for item_plus in mas[1]] for item in mas[0]]


def solution7(mas):
    return [[element[j] for element in mas] for j in range(len(mas[0]))]


def solution8(mas):
    return [[int(element) for element in el_str.split()] for el_str in mas]


def solution9(str_inp):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    return {alphabet[k]: k ** 2 for k in str_inp}


def solution10(mas):
    return {element.lower().capitalize() for element in mas
            if len(element) > 3}


solutions = {
    'solution1': solution1,
    'solution2': solution2,
    'solution3': solution3,
    'solution4': solution4,
    'solution5': solution5,
    'solution6': solution6,
    'solution7': solution7,
    'solution8': solution8,
    'solution9': solution9,
    'solution10': solution10,
}
if __name__ == "__main__":
    ans = solution9(range(0, 7))
    print(ans)
