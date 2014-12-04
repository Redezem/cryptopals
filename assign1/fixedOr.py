import binascii
import sys

firstarg = sys.argv[1].decode("hex")
secondarg = sys.argv[2].decode("hex")
newArr = []

if len(firstarg) == len(secondarg):
	i = 0
	while i < len(firstarg):
		newArr.append(chr(ord(firstarg[i])^ord(secondarg[i])))
		#print firstarg[i], secondarg[i]
		i = i+1
	print binascii.hexlify(''.join(newArr))
else:
	print "Guess you're pretty shit then"