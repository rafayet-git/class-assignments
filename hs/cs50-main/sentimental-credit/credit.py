import cs50


# gets the number needed to check for validity
def getmulti(num):
    nums = []
    total = 0
    i = len(num)-2
    # put every 2 number onto the list
    while (i >= 0):
        nums.append(num[i])
        i -= 2
    for j in range(len(nums)):
        h = int(nums[j])*2
        # check for number 10 or more, then it will convert to string then back to int to add to total
        if (h > 9):
            s = str(h)
            for t in s:
                total += int(t)
        else:
            total += h
    # add remaining digits to total
    i = len(num)-1
    while (i >= 0):
        total += int(num[i])
        i -= 2
    total = str(total)
    # return last digit
    return total[len(total) - 1]


def findcompany(num): 
    # check 1st letter for company
    if (num[0] == '3'):
        print("AMEX")
    elif (num[0] == '4'):
        print("VISA")
    elif (num[0] == '5'):
        print("MASTERCARD")
    else:
        print("INVALID")


# get height when its an range of 1-8
num = cs50.get_int("Number: ")
num = str(num)
if (len(num) < 3):
    print("INVALID")
else:
    if (getmulti(num) != '0'):
        print("INVALID")
    else:
        findcompany(num)

