from copy import copy, deepcopy


class FragileDict(object):
    """docstring"""
    inside_context = False

    def __init__(self, data={}, _lock=True):
        self._data = deepcopy(data)
        self._lock = _lock

    def __enter__(self):
        self.inside_context = True
        self.data_tmp = copy(self._data)
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.inside_context = False
        if exc_value:
            self._data = copy(self.data_tmp)
            del self.data_tmp
            print("Exception has been suppressed.")
        self._data = deepcopy(self._data)
        return True

    def __getitem__(self, key):
        if key not in self._data:
            raise KeyError(key)
            return
        return self._data[key]

    def __setitem__(self, key, item):
        if self.inside_context:
            self._data[key] = copy(item)
        elif not self._lock:
            self._data[key] = copy(item)
        else:
            raise RuntimeError("Protected state")

    def __contains__(self, key):
        return key in self._data


if __name__ == "__main__":
    d = FragileDict({'key': 5})

    with d:
        d['key'] = 6
        d['ord'] = 7

    print(d['key'])
    print(d['ord'])
