import collections
import math

"""In this problem, you will implement a bunch of short functions. The main purpose of this exercise is to familiarize yourself with Python, but as a bonus, the functions that you will implement will come in handy in subsequent homeworks.

Do not import any outside libraries (e.g. numpy). Only standard python libraries and/or the libraries imported in the starter code are allowed."""


############################################################
# Problem a

def findAlphabeticallyLastWord(text):
    """
    Given a string |text|, return the word in |text| that comes last
    alphabetically (that is, the word that would appear last in a dictionary).
    A word is defined by a maximal sequence of characters without whitespaces.
    You might find max() and list comprehensions handy here.
    """
    # BEGIN_YOUR_CODE (our solution is 1 line of code, but don't worry if you deviate from this)
    str = text.split()
    return max(str)
    
    # END_YOUR_CODE

############################################################
# Problem b

def euclideanDistance(loc1, loc2):
    """
    Return the Euclidean distance between two locations, where the locations
    are pairs of numbers (e.g., (3, 5)).
    """
    # BEGIN_YOUR_CODE (our solution is 1 line of code, but don't worry if you deviate from this)
    return math.dist(loc1, loc2);
    # END_YOUR_CODE

############################################################
# Problem c

def mutateSentences(sentence):
    """
    Given a sentence (sequence of words), return a list of all "similar"
    sentences.
    We define a sentence to be similar to the original sentence if
      - it as the same number of words, and
      - each pair of adjacent words in the new sentence also occurs in the original sentence
        (the words within each pair should appear in the same order in the output sentence
         as they did in the orignal sentence.)
    Notes:
      - The order of the sentences you output doesn't matter.
      - You must not output duplicates.
      - Your generated sentence can use a word in the original sentence more than
        once.
    Example:
      - Input: 'the cat and the mouse'
      - Output: ['and the cat and the', 'the cat and the mouse', 'the cat and the cat', 'cat and the cat and']
                (reordered versions of this list are allowed)
    """
    # BEGIN_YOUR_CODE (our solution is 17 lines of code, but don't worry if you deviate from this)
    words = sentence.split()
    sentences = []
    sentencePairs = []
    for i in enumerate(words):
        sentencePairs.append(words[i] + " " + words[i.index])
    
    return sentencePairs
    # END_YOUR_CODE

############################################################
# Problem d

def sparseVectorDotProduct(v1, v2):
    """
    Given two sparse vectors |v1| and |v2|, each represented as collections.defaultdict(float), return
    their dot product.
    You might find it useful to use sum() and a list comprehension.
    This function will be useful later for linear classifiers.
    Note: A sparse vector has most of its entries as 0
    The keys of the sparse vector can be any type. For example, an input could be {'a': 1.0, 'b': 2.0}
    """
    # BEGIN_YOUR_CODE (our solution is 4 lines of code, but don't worry if you deviate from this)
    mults = []
    for p in v1:
        mults.append(v1[p] * v2[p])
    return sum(mults)
    # END_YOUR_CODE

############################################################
# Problem e

def incrementSparseVector(v1, scale, v2):
    """
    Given two sparse vectors |v1| and |v2|, perform v1 += scale * v2.
    Do not modify v2 in your implementation.
    This function will be useful later for linear classifiers.
    """
    # BEGIN_YOUR_CODE (our solution is 2 lines of code, but don't worry if you deviate from this)
    for p in v1:
        v1[p] += scale * v2[p]
    # END_YOUR_CODE

############################################################
# Problem f

def computeLongestPalindromeLength(text):
    """
    A palindrome is a string that is equal to its reverse (e.g., 'ana').
    Compute the length of the longest palindrome that can be obtained by deleting
    letters from |text|.
    For example: the longest palindrome in 'animal' is 'ama' and it's length is 3.
    Your algorithm should run in O(len(text)^2) time.
    You should first define a recurrence before you start coding.
    """
    # BEGIN_YOUR_CODE (our solution is 14 lines of code, but don't worry if you deviate from this)
    # remove last letter until first == last
    start = 0
    end = text.len - 1;
    num = 0
    while (True):
        if (start == end):
            break
        elif (text[start:end][0] != text[start:end][-1]):
            end -= 1
        else:
            start += 1
            end -= 1
            num += 1
    return num
    # ENDi_YOUR_CODE
