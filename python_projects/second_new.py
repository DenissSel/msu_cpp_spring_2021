def mergeSort(arr):
    # arr is a unique list that all levels in the recursion tree can access:

    def mergeSortRec(start, end):  # separate function that can take start/end indices
        if end - start > 1:
            middle = (start + end) // 2

            yield from mergeSortRec(start, middle)  # don't provide slice, but index range
            yield from mergeSortRec(middle, end)
            left = arr[start:middle]
            right = arr[middle:end]

            a = 0
            b = 0
            c = start

            while a < len(left) and b < len(right):
                if left[a] < right[b]:
                    arr[c] = left[a]
                    a += 1
                else:
                    arr[c] = right[b]
                    b += 1
                c += 1

            while a < len(left):
                arr[c] = left[a]
                a += 1
                c += 1

            while b < len(right):
                arr[c] = right[b]
                b += 1
                c += 1

            yield arr

    yield from mergeSortRec(0, len(arr))  # call inner function with start/end arguments


for i in mergeSort([6, 3, 8, 7, 4, 1, 2, 9, 5, 0]):
    print(i)