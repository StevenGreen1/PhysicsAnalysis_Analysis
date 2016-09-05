
red = []
green = []
blue = []

with open('RGB.txt','r') as f:
    for line in f:
        red.append( float(line.split()[0]) / 255 )
        green.append( float(line.split()[1]) / 255 )
        blue.append( float(line.split()[2]) / 255 )

string = 'static const float redArray[] = {'

for r in red[:-1]:
    string += str(r) + ', '
string += str(red[-1])

string += '}; \n'

string += 'static const float greenArray[] = {'

for g in green[:-1]:
    string += str(g) + ', '
string += str(green[-1])

string += '}; \n'

string += 'static const float blueArray[] = {'

for b in blue[:-1]:
    string += str(b) + ', '
string += str(blue[-1])

string += '}; \n'

print string
