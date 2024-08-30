import cs50

# get height when its an range of 1-8
height = 0
while (height < 1 or height > 8):
    height = cs50.get_int("Length: ")

# for loop that modifies string for every line then prints
for i in range(height):
    s = ""
    for j in range(height-i-1):
        s += ' '
    for h in range(i+1):
        s += '#'
    s += "  "
    for j in range(i+1):
        s += '#'
    print(s)