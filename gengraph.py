import matplotlib.pyplot as plt
X=list();
Y=list();
with open("graph.txt",'r') as G:
	for line in G:
		x,y=line.split(' ')
		y=y[:len(y)-1]
		X.append(float(x))
		Y.append(float(y))
X.sort()
Y.sort()
plt.plot(X,Y)
plt.show()