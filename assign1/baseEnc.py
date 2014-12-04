#!/usr/bin/python

import base64
import sys

sys.argv.pop(0);
for thingo in sys.argv:
	decoded = thingo.decode("hex")
	base = base64.b64encode(decoded)
	print base

print "==DONE=="