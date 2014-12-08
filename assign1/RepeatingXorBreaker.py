import base64
import binascii
import sys
import math

#--------------------------------------------------------------------------

def hammDist(firstString, secondString):
	if len(firstString) == len(secondString):
		cumulativeDistance = 0
		#print "hamming it up..."
		i = 0
		while i < len(firstString):
			#Right let's ham some ham.
			magicNumber = ord(firstString[i]) ^ ord(secondString[i])
			#Ahem... so that should get me how many bits are *not* the same
			for j in range(0,8):
				cumulativeDistance = cumulativeDistance + (magicNumber>>j & 1)
			#so basically, for each byte, get each bit and add it's one ness to the total.
			i = i + 1
		return cumulativeDistance
	else:
		print "Well I guess you suck. Hamming Dist cannot be calcuated."
		return 1000000 #ONE MILLION!

def GetKeyLikelyhood(secretStringLength, bigString):
	stringOne = bigString[0:secretStringLength]
	stringTwo = bigString[secretStringLength:(secretStringLength*2)]
	distance = hammDist(stringOne,stringTwo)
	distance = distance / secretStringLength
	#print "for distance " + str(secretStringLength) + " we get distance " + str(distance)
	return distance

def SplitToBlocks(blockSize,bigString):
	numberOfBlocks = len(bigString) / blockSize
	leftover = len(bigString) % blockSize

	bigArrayOfBlocks = []

	additionStr = ""
	i = 0
	j = 0
	while i < blockSize:
		while j < numberOfBlocks:
			additionStr = additionStr + bigString[j+(i*blockSize)]
			j = j + 1
		if leftover > blockSize:
			additionStr = additionStr + bigString[(blockSize*numberOfBlocks) + i]
		bigArrayOfBlocks.append(additionStr)
		i = i + 1

	return bigArrayOfBlocks

def SingleXorCracker(crackStr):
	splitChar = 0
	winnerChar = 0

	while splitChar < 128:
		splitArr = []
		scoreVal = 0
		for crack in crackStr:
			newchar = ord(crack)^splitChar
			if newchar == 32 or (newchar > 64 and newchar < 91) or (newchar > 96 and newchar < 123):
				scoreVal = scoreVal + 1
			splitArr.append(chr(newchar))
		if scoreVal >= len(crackStr)-1:  #magic numbers, oh joy...
			winnerChar = splitChar
		splitChar = splitChar + 1
	return chr(splitChar)

def XorProcess(content,codeWord):
	i = 0
	j = 0
	finalString = ""
	while i < len(content):
		while j < len(codeWord):
			if i >= len(content):
				break
			newcharacter = chr(ord(content[i]) ^ ord(codeWord[j]))
			finalString=finalString + newcharacter
			j = j+1
			i = i+1
		j = 0
	#hopefully, that works
	return finalString
#--------------------------------------------------------------------------


fileName = sys.argv[1]

f = open(fileName,"r")

key = 0
keyLikelihood = 1000000000000000 #Unrealistically large number

#we want the key with the smallest likelihood (what? Oh wait you're ranking by normalised hamming distance. Gotcha)

i = 0

fileContents = ""

for line in f:
	if line[:1] == '\n':
		fileContents = fileContents+(line[:-1])	
	else:
		fileContents = fileContents+line

fileContents = base64.b64decode(fileContents)

#print fileContents

for i in range(1,(len(fileContents)/2)):
	keyL = GetKeyLikelyhood(i,fileContents)
	if keyL < keyLikelihood:
		keyLikelihood = keyL
		key = i

print "Likely Key Length : " + str(key)

arrayOfBlocks = SplitToBlocks(key,fileContents)

#print arrayOfBlocks

finalKey = ""

for block in arrayOfBlocks:
	finalKey = finalKey + SingleXorCracker(block)

print "Key appears to be " + finalKey

finalStr = XorProcess(fileContents,finalKey)

print "Final message should be: " + finalStr