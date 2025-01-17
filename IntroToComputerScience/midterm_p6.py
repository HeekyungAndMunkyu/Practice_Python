# recursive function
# don't use for or while loop


def laceStringsRecur(s1, s2):
    """
    s1 and s2 are strings.

    Returns a new str with elements of s1 and s2 interlaced,
    beginning with s1. If strings are not of same length,
    then the extra elements should appear at the end.
    """
#    def helpLaceStrings(s1, s2, out):
    def helpLaceStrings(s1, s2):
        if s1 == '':
            return s2
        if s2 == '':
            return s1
        else:
#            return s1[0] + s2[0] + helpLaceStrings(s1[1:], s2[1:], '')
            return s1[0] + s2[0] + helpLaceStrings(s1[1:], s2[1:])

    print 'helpLaceStrings(%s, %s, %s)' % (s1, s2, '')
#    return helpLaceStrings(s1, s2, '')
    return helpLaceStrings(s1, s2)


s1 = raw_input('string 1: ')
s2 = raw_input('string 2: ')

print laceStringsRecur(s1, s2)
