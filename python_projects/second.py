import functools


def retry(check, n_attempts=5):
    def inner(func):
        @functools.wraps(func)
        def new_f(*args, **kwargs):
            if n_attempts:
                if n_attempts > 0:
                    for i in range(n_attempts):
                        inp = func(*args, **kwargs)
                        if check(inp):
                            return inp
                    raise RuntimeError("Expired number of retries")
                else:
                    inp = func(*args, **kwargs)
                    while not check(inp):
                        inp = func(*args, **kwargs)
                    return inp
            else:
                inp = func(*args, **kwargs)
                while not check(inp):
                    inp = func(*args, **kwargs)
                return inp

        return new_f

    return inner
