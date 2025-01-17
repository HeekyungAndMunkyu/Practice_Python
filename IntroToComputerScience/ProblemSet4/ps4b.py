from ps4a import *
import time


#
#
# Problem #6: Computer chooses a word
#
#
def compChooseWord(hand, wordList, n):
    """
    Given a hand and a wordList, find the word that gives
    the maximum value score, and return it.

    This word should be calculated by considering all the words
    in the wordList.

    If no words in the wordList can be made from the hand, return None.

    hand: dictionary (string -> int)
    wordList: list (string)
    n: integer (HAND_SIZE; i.e., hand size required for additional points)

    returns: string or None
    """
    # BEGIN PSEUDOCODE


    # Create a new variable to store the maximum score seen so far (initially 0)
    maxScore = 0
    # Create a new variable to store the best word seen so far (initially None)
    maxWord = None


    # For each word in the wordList
    for word in wordList:
        # If you can construct the word from your hand
        # (hint: you can use isValidWord, or - since you don't really need to test if the word is in the wordList - you can make a similar function that omits that test)
        if isValidWord(word, hand, wordList):
            # Find out how much making that word is worth
            wordScore = getWordScore(word, n)
            # If the score for that word is higher than your best score
            if wordScore > maxScore:
                # Update your best score, and best word accordingly
                maxScore = wordScore
                maxWord = word

    # return the best word you found.
    return maxWord

#
# Problem #7: Computer plays a hand
#
def compPlayHand(hand, wordList, n):
    """
    Allows the computer to play the given hand, following the same procedure
    as playHand, except instead of the user choosing a word, the computer
    chooses it.

    1) The hand is displayed.
    2) The computer chooses a word.
    3) After every valid word: the word and the score for that word is
    displayed, the remaining letters in the hand are displayed, and the
    computer chooses another word.
    4)  The sum of the word scores is displayed when the hand finishes.
    5)  The hand finishes when the computer has exhausted its possible
    choices (i.e. compChooseWord returns None).

    hand: dictionary (string -> int)
    wordList: list (string)
    n: integer (HAND_SIZE; i.e., hand size required for additional points)
    """
    totalScore = 0

    while calculateHandlen(hand) > 0:

        # 1) The hand is displayed.
        print 'Current Hand:',
        displayHand(hand)

        # 2) The computer chooses a word.
        word = compChooseWord(hand, wordList, n)

        # 3) After every valid word: Tell the user how many points the word earned,
        #    and the updated total score, in one line followed by a blank line
        if word != None:
            totalScore += getWordScore(word, n)
            print '"%s" earned %d points. Total: %d points ' % (word, getWordScore(word, n), totalScore)
            print ''
            # Update the hand
            hand = updateHand(hand, word)
        else:
            break

    # 4)  The sum of the word scores is displayed when the hand finishes.
    print 'Total score: %d points.' % totalScore
    # 5)  The hand finishes when the computer has exhausted its possible
    # choices (i.e. compChooseWord returns None).

#
# Problem #8: Playing a game
#
#
def playGame(wordList):
    """
    Allow the user to play an arbitrary number of hands.

    1) Asks the user to input 'n' or 'r' or 'e'.
        * If the user inputs 'e', immediately exit the game.
        * If the user inputs anything that's not 'n', 'r', or 'e', keep asking them again.

    2) Asks the user to input a 'u' or a 'c'.
        * If the user inputs anything that's not 'c' or 'u', keep asking them again.

    3) Switch functionality based on the above choices:
        * If the user inputted 'n', play a new (random) hand.
        * Else, if the user inputted 'r', play the last hand again.

        * If the user inputted 'u', let the user play the game
          with the selected hand, using playHand.
        * If the user inputted 'c', let the computer play the
          game with the selected hand, using compPlayHand.

    4) After the computer or user has played the hand, repeat from step 1

    wordList: list (string)
    """

    #    Allow the user to play an arbitrary number of hands.
    n = HAND_SIZE
    hand = {}

    while True:

        # 1) Asks the user to input 'n' or 'r' or 'e'.

        answeredI = False
        userInput = None

        while answeredI == False:
            userInput = raw_input('Enter n to deal a new hand, r to replay the last hand, or e to end game: ')
            print ''

            if userInput == 'e':
                break
            elif userInput == 'r' and hand == {}:
                print 'You have not played a hand yet. Please play a new hand first!'
            elif userInput == 'n' or userInput == 'r':
                answeredI = True
            else:
                print 'Invalid command.'
                print ''

        # break out of the outer while loop to exit
        if userInput == 'e':
            break



        # 2) Asks the user to input a 'u' or a 'c'.

        answeredC = False
        control = None # will be assigned either 'u' or 'c'
        controlFunc = None # will be assigned either playHand or compPlayHand

        while answeredC == False:
            control = raw_input('Enter u to have yourself play, c to have the computer play: ')
            print ''

            if control == 'u':
                answeredC = True
                controlFunc = playHand
            elif control == 'c':
                answeredC = True
                controlFunc = compPlayHand
            else:
                print 'Invalid command.'
                print ''

        # 3) Switch functionality based on the above choices:

        # 3-1) new hand
        if userInput == 'n':
            hand = dealHand(n)
            controlFunc(hand, wordList, n)

        # 3-2) replay the last hand
        elif userInput == 'r':
            controlFunc(hand, wordList, n)





        # comp: new hand
#        elif userInput == 'n' and control == 'c':
#            hand = dealHand(n)
#            compPlayHand(hand, wordList, n)
        # comp: replay the last hand
#        elif userInput == 'r' and control == 'c':
#            if hand == {}:
#                print 'You have not played a hand yet. Please play a new hand first!'
#           else:
#                compPlayHand(hand, wordList, n)



#
# Build data structures used for entire session and play game
#
if __name__ == '__main__':
    wordList = loadWords()
    playGame(wordList)
