import array

# Declaration and Initialization
arr = array.array('i', [1, 2, 3, 4, 5]) # `i`는 Integer 타입을 나타낸다.
d_arr = [1, 2, 3, 4, 5]

# FindAll
def traverse_array(arr):
    for i in arr:
        print(i, end=" ")

traverse_array(arr)

# FindOne
def find_element(arr, length, key): 
    for i in range(length):
          # Return the index if key is found
        if arr[i] == key:
            return i
    # Return -1 if key is not found
    return -1 
    
print(find_element(arr, 5, 1))

# Insert
# 단, arr는 가변 배열(Dynamic Array)라고 가정한다.
def insert_element(arr, length, x, pos):
    arr.append(None)
    # shift elements to the right
    # which are on the right side of pos
    for i in range(length-1, pos-1, -1):
        arr[i + 1] = arr[i]

    arr[pos] = x

insert_element(d_arr, 5, 3, 1)
print(d_arr)

# Delete
def delete_element(arr, length, key):
    pos = find_element(arr, length, key)

    if pos == -1:
        print("해당 요소가 없습니다.")
        return length
    
    for i in range(pos, length - 1):
        arr[i] = arr[i + 1]
    
    return length - 1

print(delete_element(arr, 5, 3))
print(arr)