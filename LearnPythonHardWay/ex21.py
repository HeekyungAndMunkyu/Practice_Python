# -*- coding: utf-8 -*-

def add(a, b):
	print "addition %d + %d" % (a, b)
	return a + b

def subtract(a, b):
	print "subtraction %d - %d" % (a, b)
	return a - b

def multiply(a, b):
	print "multiplification %d * %d" % (a, b)
	return a * b 
	
def divide(a, b):
	print "division %d / %d" % (a, b)
	return a / b


print "Let's do calculations only with functions!"


age = add(30, 5)
height = subtract(78, 4)
weight = multiply(90, 2)
iq = divide(100, 2)

print "age: %d, height: %d, weight: %d, iq: %d" % (age, height, weight, iq)


# bonus point questions
print "There is a problem."

what = add(age, subtract(height, multiply(weight, divide(iq, 2))))

print "result:", what, "Can you calculate by hands?"

calculation = age + (height - weight * (iq / 2))

print calculation

cal2 = divide(add(24, 34), subtract(100.0, 1023.0))

print cal2
