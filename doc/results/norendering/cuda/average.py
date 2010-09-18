

if __name__=="__main__":
	outputFilename = "output.dat"
	averages = []
	fileSuffixes = ['2', '4', '8', '16', '32', '64', '128', '256', '448']
	for fileSuffix in fileSuffixes:
		fileName = 'CollisionDetectionTimes_%s.csv' % fileSuffix
		f = open(fileName, 'r')
		accum = 0
		numLines = 0
		for line in f:
			val = float(line)
			accum = accum + val 
			numLines = numLines+1
		average = (accum / numLines)
		averages.append(average)
	outputFile = open(outputFilename, 'w')
	i = 0
	for average in averages:
		outputFile.write(fileSuffixes[i] + ' ')
		outputFile.write(str(average) + '\n')
		i = i + 1
