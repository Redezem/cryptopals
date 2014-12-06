import sys
import binascii

fileName = sys.argv[1]
codeWord = sys.argv[2]

finalString = ""

opendFile = open(fileName,"r")

fileContents = ""

for line in opendFile:
	fileContents = fileContents+line 

i = 0
j = 0

while i < len(fileContents):
	while j < len(codeWord):
		if i >= len(fileContents):
			break
		newcharacter = chr(ord(fileContents[i]) ^ ord(codeWord[j]))
		finalString=finalString + newcharacter
		j = j+1
		i = i+1
	j = 0
#hopefully, that works

finalString = binascii.hexlify(finalString)

print "resulting in " + finalString

exitfile = open("exit.txt","w")

exitfile.write(finalString)