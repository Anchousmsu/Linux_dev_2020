import roman

with open('romantable.txt', 'w', encoding='utf-8') as f:
	for i in range(1, 101):
		f.write(str(i) + ' : ' + str(roman.toRoman(i)) + '\n')
