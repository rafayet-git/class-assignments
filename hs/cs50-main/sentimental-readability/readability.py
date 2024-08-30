from cs50 import get_string


# took code from my c assignment and translated it to python
def count_letters(txt):
    total = 0
    for i in range(len(txt)):
        value = ord(txt[i])
        if ((value < 91 and value > 64) or (value < 123 and value > 96)):
            total += 1
    return total


def count_words(txt):
    total = 1
    for i in range(len(txt)):
        if (txt[i] == ' '):
            total += 1
    return total


def count_sentences(txt):
    total = 0
    for i in range(len(txt)):
        value = ord(txt[i])
        if (value == 46 or value == 33 or value == 63):
            total += 1
    return total


text = get_string("text: ")
W = count_words(text)
L = (count_letters(text) / W) * 100 
S = (count_sentences(text) / W) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if (index < 1):
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print(f"Grade {index}")