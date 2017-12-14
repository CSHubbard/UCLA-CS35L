#!/usr/bin/python
#Cody Hubbard 004843389 - Lab3

import string
import sys
import locale
from optparse import OptionParser
				
def main():
	locale.setlocale(locale.LC_COLLATE, 'C')

	usage_msg = """%prog [OPTION]... FILE1 FILE2 Output three columns, containing lines only in FILE1, lines only in FILE2, and lines in both files."""

	parser = OptionParser(usage=usage_msg)
	parser.add_option("-1", action='store_true', dest="arg1", default=False, help="suppress first column of output")
	parser.add_option("-2", action='store_true', dest="arg2", default=False, help="suppress second column of output")
	parser.add_option("-3", action='store_true', dest="arg3", default=False, help="suppress third column of output")
	parser.add_option("-u", action='store_true', dest="argu", default=False, help="allow input of unsorted files")

	options, args = parser.parse_args(sys.argv[1:])

	inputfile1 = []
	inputfile2 = []
	
	if len(args) != 2:
		parser.error("wrong number of operands")
		
	if args[0] == "-":
		inputfile1 = sys.stdin.readlines()
	else:
		f = open(args[0], 'r')
		inputfile1 = f.readlines()
		f.close()
		
	if args[1] == "-":
		inputfile2 = sys.stdin.readlines()
	else:
		f = open(args[1], 'r')
		inputfile2 = f.readlines()
		f.close()

	output1 = []
	output2 = []
	output3half1 = []
	output3half2 = []
	output3 = []
		
	if options.argu==False:
	
	#I would check for sorted-ness around here if it was needed
	
		for x in inputfile1:
			if x in inputfile2:
				output3half1.append(x)
			else:
				output1.append(x)
		
		for x in output3half1:
				inputfile1.remove(x)
				inputfile2.remove(x)
				
		for x in output1:
				inputfile1.remove(x)
		
		for x in inputfile2:
			if x in inputfile1:
				output3half2.append(x)
			else:
				output2.append(x)
		
		for x in output3half2:
				inputfile1.remove(x)
				inputfile2.remove(x)
				
		for x in output2:
				inputfile2.remove(x)
				
		output3 = output3half1 + output3half2
		everyWord = sorted(output1+output2+output3)
		
		for x in everyWord:
			if options.arg1 == False:
				if x in output1:
					sys.stdout.write(x)
			
			if options.arg2 == False:
				if x in output2:
					if options.arg1 == False:
						sys.stdout.write("\t"+x)
					if options.arg1 == True:
						sys.stdout.write(x)
						
			if options.arg3 == False:
				if x in output3:
					if options.arg1 == False:
						if options.arg2 == False: 
							sys.stdout.write('\t'+'\t'+x)
						if options.arg2 == True:
							sys.stdout.write('\t'+x)
					if options.arg1 == True:
						if options.arg2 == False: 
							sys.stdout.write('\t'+x)
						if options.arg2 == True:
							sys.stdout.write(x)
							
			if "\n" not in x:
				sys.stdout.write('\n')

		
	if options.argu==True:
		for x in inputfile1:
			if x in inputfile2:
				output3.append(x)
		
		for x in output3:
				inputfile2.remove(x)

		
		for x in inputfile1:
			if x in output3:
			
				if options.arg1 == False:
					if options.arg2 == False:
						sys.stdout.write("\t"+"\t"+x)
					if options.arg2 == True:
						sys.stdout.write("\t"+x)

				if options.arg1 == True:
					if options.arg2 == False:
						sys.stdout.write("\t"+x)
					if options.arg2 == True:
						sys.stdout.write(x)
				
			else:
				if options.arg1 == False:
					sys.stdout.write(x)
					
			if "\n" not in x:
				sys.stdout.write('\n')
		
		if options.arg2 == False:
			for x in inputfile2:
				if options.arg1 == False:
					sys.stdout.write("\t"+x)
				if options.arg1 == True:
					sys.stdout.write(x)
				if "\n" not in x:
					sys.stdout.write('\n')
					
if __name__ == "__main__":
	main()
