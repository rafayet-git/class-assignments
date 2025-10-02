#!/usr/bin/python

import random
import collections
import math
import sys
from util import *

############################################################
# Problem 3: binary classification
############################################################

############################################################
# Problem : feature extraction

def extractWordFeatures(x):
    """
    Extract word features for a string x. Words are delimited by
    whitespace characters only.
    @param string x:
    @return dict: feature vector representation of x.
    Example: "I am what I am" --> {'I': 2, 'am': 2, 'what': 1}
    """
    # BEGIN_YOUR_CODE (our solution is 4 lines of code, but don't worry if you deviate from this)
    splits = x.split()
    wordCount = {}
    for word in splits:
        if word in wordCount:
            wordCount[word] += 1
        else:
            wordCount[word] = 1

    return wordCount
    # END_YOUR_CODE

############################################################
# Problem: stochastic gradient descent

def learnPredictor(trainExamples, validationExamples, featureExtractor, numIters, eta):
    '''
    Given |trainExamples| and |validationExamples| (each one is a list of (x,y)
    pairs), a |featureExtractor| to apply to x, and the number of epochs to
    train |numIters|, the step size |eta|, return the weight vector (sparse
    feature vector) learned.

    You should implement stochastic gradient descent.

    Note: only use the trainExamples for training!
    You should call evaluatePredictor() on both trainExamples and validationExamples
    to see how you're doing as you learn after each epoch. Note also that the
    identity function may be used as the featureExtractor function during testing.
    '''
    weights = {}  # feature => weight
    # BEGIN_YOUR_CODE (our solution is 12 lines of code, but don't worry if you deviate from this)
    def predictor(x): # verbosePredict
        return 1 if dotProduct(featureExtractor(x), weights) >= 0 else -1 

    for e in range(numIters):
        for x, y in trainExamples:
            px = featureExtractor(x)
            margin = y * dotProduct(weights, px)
            if margin < 1: 
                increment(weights, eta * y, px)
                
        trainError = evaluatePredictor(trainExamples, predictor)
        devError = evaluatePredictor(validationExamples, predictor)
        print(f'epoch {e}: trainError={trainError:.2f} devError={devError:.2f}')
    # END_YOUR_CODE
    return weights

############################################################
# Problem : generate test case

def generateDataset(numExamples, weights):
    '''
    Return a set of examples (phi(x), y) randomly which are classified correctly by
    |weights|.
    '''
    random.seed(42)
    # Return a single example (phi(x), y).
    # phi(x) should be a dict whose keys are a subset of the keys in weights
    # and values can be anything (randomize!) with a nonzero score for the given weight vector.
    # y should be 1 or -1 as classified by the weight vector.

    # Note that the weight vector can be arbitrary during testing.
    def generateExample():
        # BEGIN_YOUR_CODE (our solution is 2 lines of code, but don't worry if you deviate from this)
        phi = {}

        num = random.randint(1, len(weights))
        subWeights = random.sample(list(weights.keys()), num)
        for w in subWeights:
            # (-1, 1)
            phi[w] = random.uniform(0, 1) * (1 if random.random() > 0.5 else -1)

        y = 1 if dotProduct(phi, weights) >= 0 else -1
        # END_YOUR_CODE
        return (phi, y)
    return [generateExample() for _ in range(numExamples)]

############################################################
# Problem : character features

def extractCharacterFeatures(n):
    '''
    Return a function that takes a string |x| and returns a sparse feature
    vector consisting of all n-grams of |x| without spaces mapped to their n-gram counts.
    EXAMPLE: (n = 3) "I like tacos" --> {'Ili': 1, 'lik': 1, 'ike': 1, ...
    You may assume that n >= 1.
    '''
    
    def extract(x):
        # BEGIN_YOUR_CODE (our solution is 6 lines of code, but don't worry if you deviate from this)
        x = ''.join(x.split())
        ngrams = {}

        for i in range(len(x) - n + 1):
            ng = x[i:i+n]
            if ng in ngrams:
                ngrams[ng] += 1
            else:
                ngrams[ng] = 1
        return ngrams
        # END_YOUR_CODE
    return extract
