import operator
from functools import reduce
from itertools import islice


def solution1(mas):
    return list(map(lambda s:
                    int(''.join(list(filter(lambda x:
                                            x in '0123456789', s)))[::-1]),
                    mas))


def solution2(mas):
    return list(map(lambda x: x[0] * x[1], list(mas)))


def solution3(str_given):
    return list(filter(lambda x:
                       x % 6 == 0 or x % 6 == 2 or x % 6 == 5, str_given))


def solution4(mas):
    return list(filter(lambda x: bool(x), mas))


def solution5(mas):
    return list(map(lambda x:
                    operator.__setitem__(x,
                                         'square', x['length'] * x['width']),
                    mas))


def solution6(mas):
    return list(map(lambda x: {'name': x['name'],
                               'width': x['width'],
                               'length': x['length'],
                               'square': x['width'] * x['length']}, mas))


def solution7(mas):
    return set(reduce(set.intersection, [set(item) for item in mas]))


def solution8(mas):
    d = {}
    list(map(lambda x: operator.__setitem__(d, x, (d.get(x) or 0) + 1), mas))
    return d


def solution9(mas):
    return list(map(lambda x: x['name'],
                    list(filter(lambda s: s['gpa'] > 4.5, mas))))


def solution10(mas):
    return list(filter(lambda x: sum(
        list(map(lambda s: int(s), list(islice(x, 0, len(x), 2))))) == sum(
        list(map(lambda s: int(s), list(islice(x, 1, len(x),
                                               2))))), mas))


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
    ans = solution1(['12', '25.6', '84,02', '  69-91'])
    print(ans)
    ans = solution2(zip(range(2, 5), range(3, 9, 2)))
    print(ans)
    ans = solution3(range(20))
    print(ans)
    ans = solution4(['', 25, None, 'python', 0.0, [], ('msu', '1755-01-25')])
    print(ans)
    students = [
        {'name': 'Alina', 'gpa': 4.57},
        {'name': 'Sergey', 'gpa': 5.0},
        {'name': 'Nastya', 'gpa': 4.21},
        {'name': 'Valya', 'gpa': 4.72},
        {'name': 'Anton', 'gpa': 4.32},
    ]

    ans = solution9(students)
    print(ans)
    ans = solution10(['165033', '477329', '631811',
                      '478117', '475145', '238018', '917764', '394286'])
    print(ans)
    ans = solution7([{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}])
    print(ans)
    rooms = [
        {"name": "комната1", "width": 2, "length": 4},
        {"name": "комната2", "width": 2.5, "length": 5.6},
        {"name": "кухня", "width": 3.5, "length": 4},
        {"name": "туалет", "width": 1.5, "length": 1.5},
    ]
    ans = solution6(rooms)
    ans = solution8([1, 2, 1, 1, 3, 2, 3, 2, 4, 2, 4])
    print(ans)
