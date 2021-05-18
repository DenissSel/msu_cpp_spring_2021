import functools


def counter(func):  # a decorator to count calls
    @functools.wraps(func)
    def helper(*args, **kwargs):
        helper.ncalls += 1
        # print(helper.curr_depth)
        if helper.curr_depth == 0:
            helper.ncalls = 1
            helper.rdepth = 0
        helper.curr_depth += 1
        if helper.rdepth < helper.curr_depth:
            helper.rdepth = helper.curr_depth
        result = func(*args, **kwargs)

        helper.curr_depth -= 1

        return result

    helper.ncalls = 0
    helper.rdepth = 0
    helper.curr_depth = 0
    return helper


@counter
def func1(a):
    return a


if __name__ == "__main__":
    print(func1(4))
    print(func1.ncalls, func1.rdepth)

    func1(4)
    print(func1.ncalls, func1.rdepth)
