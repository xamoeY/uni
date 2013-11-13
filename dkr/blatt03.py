import math

for x in range(1, 9):
    a_k = 1/(math.pi*x) * (math.cos((math.pi*x)/4)-math.cos((2*math.pi*x)/4)+math.cos((3*math.pi*x)/4)-math.cos((5*math.pi*x)/4)+math.cos((6*math.pi*x)/4)-math.cos((7*math.pi*x)/4))
    b_k = 1/(math.pi*x) * (math.sin((2*math.pi*x)/4)-math.sin((math.pi*x)/4)+math.sin((5*math.pi*x)/4)-math.sin((3*math.pi*x)/4)+math.sin((7*math.pi*x)/4)-math.sin((6*math.pi*x)/4))
    h_k = math.sqrt(a_k**2 + b_k**2)
    print("k: {}, a_k: {}, b_k: {}, h_k: {}".format(x, a_k, b_k, h_k))

