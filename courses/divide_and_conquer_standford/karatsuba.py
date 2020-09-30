# In this programming assignment you will implement one or more of the integer
# multiplication algorithms described in lecture.
# To get the most out of this assignment, your program should restrict itself
# to multiplying only pairs of single-digit numbers. You can implement the
# grade-school algorithm if you want, but to get the most out of the assignment
# you'll want to implement recursive integer multiplication and/or Karatsuba's algorithm.
# So: what's the product of the following two 64-digit numbers?
# 3141592653589793238462643383279502884197169399375105820974944592
# 2718281828459045235360287471352662497757247093699959574966967627
# [TIP: before submitting, first test the correctness of your program on some 
# small test cases of your own devising. Then post your best test cases to the 
# discussion forums to help your fellow students!]
# [Food for thought: the number of digits in each input number is a power of 2. 
# Does this make your life easier? Does it depend on which algorithm you're implementing?]
# The numeric answer should be typed in the space below. So if your answer is 1198233847, 
# then just type 1198233847 in the space provided without any space / commas / any other punctuation marks.
# (We do not require you to submit your code, so feel free to use any programming 
# language you want --- just type the final numeric answer in the following space.)
import math
import logging_user

counter = 0
def karatsuba(a,b):
	global counter
	counter = counter + 1
	# if(counter>20):
	# 	log.writeLog("Break recursion.")
		# return 0

	if(len(a)>1 and len(b)>1):
		base = 10
		n1 = len(a)
		n2 = len(b)
		n=min(n1,n2)
		m=math.floor(n/2)

		# Odd case
		if(len(a)%2==1):
			a_high = a[:-m]
			a_low  = a[-m:]
		else:
			a_high = a[:len(a)//2]
			a_low	 = a[len(a)//2:]
		
		# Odd case
		if(len(b)%2==1):
			log.writeLog("b is odd " + b[:-m], False)
			b_high = b[:-m]
			b_low  = b[-m:]
			log.writeLog("b: " + str(b), False)
			log.writeLog("a: " + str(a), False)
		else:
			b_high = b[:len(b)//2]
			b_low  = b[len(b)//2:]

		# Represent numbers as: x = x1*base^m + x0, where m=n/2(digits number)
		# x = (base<<m) * a_high + a_low
		# y = (base<<m) * b_high + b_low
		log.writeLog("m: " + str(m))
		log.writeLog("a: " + str(a))
		log.writeLog("b: " + str(b))
		log.writeLog("a_high: " + str(a_high))
		log.writeLog("a_low: " + str(a_low))
		log.writeLog("b_high: " + str(b_high))
		log.writeLog("b_low: " + str(b_low))
		# log.writeLog("len(a):" + len(a))
		# log.writeLog("len(b):" + len(b))
		if(len(b)==3 or len(a)==3):
			log.writeLog("LEN IS 3")
			log.writeLog(str(len(a)) + "  " +str(len(b)))
		log.writeLog("-------------------")
		# log.writeLog("first step")
		# First step
		# w2 = a_high * b_high
		w2 = karatsuba(a_high, b_high)
		log.writeLog("w2: " + str(w2))
		# log.writeLog("second step")
		# log.writeLog(a_low + b_low)	
		# Second step 
		# w0 = a_low * b_low
		w0 = karatsuba(a_low, b_low)
		log.writeLog("w0: " + str(w0))
		# log.writeLog("third step")
		# Third step 
		# w1 = (a_high + a_low) * (b_high + b_low) - w2 - w0
		a_w1 = str(int(a_high)+int(a_low))
		b_w1 = str(int(b_high)+int(b_low))
		log.writeLog("a_w1: " + str(a_w1) + " b_w1: " + str(b_w1))
		
		mid = karatsuba(a_w1, b_w1)
		log.writeLog("mid:" + str(mid) + " w2:" + str(w2) + " w0:" + str(w0))
		
		w1 = mid - w2 - w0
		log.writeLog("w1: " + str(w1))
		log.writeLog("m: " + str(m))
		
		result = (base**(2*m))*w2 + (base**(m))*w1 + w0
		log.writeLog("result:" + str(result) + "\n")

		# Log wrong results
		if(int(a)*int(b) != result):
			log.writeLog("a: " + str(a) + " b: " + str(b), True)
			log.writeLog("a x b = " + str(int(a)*int(b)), True)
			log.writeLog("karatsuba: " + str(result) + "\n", True)
		return result
	else: 
		return int(a)*int(b)


def main():
	a = "3141592653589793238462643383279502884197169399375105820974944592"
	b = "2718281828459045235360287471352662497757247093699959574966967627"
	# stolen_result = '8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184'
	# a = "123447"
	# b = "11"
	result = karatsuba(a,b)
	log.writeLog("*****************", True)
	# Result of Karatsuba algorithm
	log.writeLog(a + " x " + b + " = " + str(result), True)
	print(a + " x " + b + " = " + str(result))
	# Result of normal multiplication
	stolen_result = int(a) * int(b)
	print("Correct result = " + str(stolen_result))
	if(stolen_result==result):
		print("True")
	else:
		print("False")
	log.writeLog("*****************", True)

if __name__ == "__main__":
	# 2nd parameter: True->All logs; False->Only the one with True for writeLog()
	log = logging_user.Logging("karatsuba", True)
	# Disable all logs to file
	log.logOff()
	main()
