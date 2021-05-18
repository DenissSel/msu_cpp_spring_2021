def brackets(n):
    str = [""] * 2 * n
    if n > 0:
        yield from recur_brackets(str, 0, n, 0, 0)


def recur_brackets(str, pos, n, open, close):
    if close == n:
        ans = "".join(str)
        yield ans
        return
    else:
        if open < n:
            str[pos] = '('
            yield from recur_brackets(str, pos + 1, n,
                                      open + 1, close)
        if open > close:
            str[pos] = ')'
            yield from recur_brackets(str, pos + 1, n,
                                      open, close + 1)


if __name__ == "__main__":
    n = int(input())
    # brackets(n)
    for i in brackets(n):
        print(i)
