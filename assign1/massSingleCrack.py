import sys

winnerString = []

lineNumber = 1

f = open(sys.argv[1],'r')

for line in f:
	if len(line) % 2 != 0:
		crackStr = line[:-1].decode("hex")
	splitChar = 0

	while splitChar < 128:
		splitArr = []
		scoreVal = 0
		for crack in crackStr:
			newchar = ord(crack)^splitChar
			if newchar == 32 or (newchar > 64 and newchar < 91) or (newchar > 96 and newchar < 123):
				scoreVal = scoreVal + 1
			splitArr.append(chr(newchar))
		if scoreVal >= len(crackStr)-1:  #magic numbers, oh joy...
			splitArr.append(" || ")
			splitArr.append(chr(splitChar))
			splitArr.append(" On Line ")
			splitArr.append(str(lineNumber))
			winnerString.append(''.join(splitArr))
		
		splitChar = splitChar + 1
	lineNumber = lineNumber + 1

print winnerString
