import time
import signal
from time import sleep


class TimeoutException(RuntimeError):
    def __init__(self, message=None):
        super().__init__(message)


def timeout(seconds_before_timeout):
    def decorate(f):
        def handler(signum, frame):
            raise TimeoutException()

        def new_f(*args, **kwargs):
            old = signal.signal(signal.SIGALRM, handler)
            old_time_left = signal.alarm(seconds_before_timeout)
            if 0 < old_time_left < seconds_before_timeout:  # never lengthen existing timer
                signal.alarm(old_time_left)
            start_time = time.time()
            try:
                result = f(*args, **kwargs)
            finally:
                if old_time_left > 0:  # deduct f's run time from the saved timer
                    old_time_left -= time.time() - start_time
                signal.signal(signal.SIGALRM, old)
                signal.alarm(old_time_left)
            return result

        return new_f

    return decorate


@timeout(0.5)
def func():
    sleep(0.1)


try:
    func()
except TimeoutException as e:
    print(e)
