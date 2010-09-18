
if __name__=="__main__":
	file = open('CollisionDetectionTimes.csv', 'r')
	fileLines = file.readlines()
	accum = 0
	for line in fileLines:
		if(len(line) > 2):
			accum = accum + float(line)
	numLines = len(fileLines)
	if(numLines > 0):
		average = accum / numLines
		print("Average is : " + str(average))

		
