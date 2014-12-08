import base64
import binascii
import sys
import math

firstString = sys.argv[1]
secondString = sys.argv[2]

if len(firstString) == len(secondString):
	cumulativeDistance = 0
	print "hamming it up..."
	i = 0
	while i < len(firstString):
		#Right let's ham some ham.
		magicNumber = ord(firstString[i]) ^ ord(secondString[i])
		#Not the and. NAND! NAND GATES! STORE MAH DATAS BROO!
		#Ahem... sorry about that... so that should get me how many bits are *not* the same
		for j in range(0,8):
			cumulativeDistance = cumulativeDistance + (magicNumber>>j & 1)
		#so basically, for each byte, get each bit and add it's one ness to the total.
		i = i + 1
	print "ham dist is " + str(cumulativeDistance)
else:
	print "Well I guess you suck"