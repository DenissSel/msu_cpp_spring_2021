def intervals_generator(lst, bound):
    i, j = 0, 0
    sum_ = 0
    yield 0, 2*len(lst)
    while True:
        try:
            if sum_ < bound:
                sum_ += lst[j]
                j += 1
            else:
                yield i, j
                sum_ -= lst[i]
                i += 1
        except IndexError:
            break


def smallest_sub_list(lst, bound):
    if not intervals_generator(lst, bound):
        return ''
    i, j = min(intervals_generator(lst, bound), key=lambda x: x[1] - x[0])
    if j - i > len(lst):
        return lst[0:0]
    return lst[i:j]


mas = list(map(int, input().split()))
N = int(input())
for element in smallest_sub_list(mas, N):
    print(element, end=' ')
