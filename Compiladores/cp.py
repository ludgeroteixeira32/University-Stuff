stack = [None] * 40
top = -1
while(True):
    operation = input()
    if(operation == 'push'):
        numAux = input()
        num = int(numAux)
        top = top + 1
        stack[top] = num
    elif(operation == 'pop'):
        top = top - 1
    elif(operation == 'dup'): 
        num = stack[top]
        top = top + 1
        stack[top] = num
    elif(operation == 'swap'):
        num = stack[top]
        stack[top] = stack[top-1]
        stack[top-1] = num
    elif(operation == 'add'):
        a = stack[top]
        top = top - 1
        b = stack[top]
        stack[top] = a + b
    elif(operation == 'sub'):
        a = stack[top]
        top = top - 1
        b = stack[top]
        stack[top] = b - a
    elif(operation == 'mul'):
        a = stack[top]
        top = top - 1
        b = stack[top]
        stack[top] = a * b
    elif(operation == 'div'):
        a = stack[top]
        top = top - 1
        b = stack[top]
        stack[top] = b / a
    elif(operation == 'neg'):
        stack[top] = -stack[top]
    elif(operation == 'reset'):
        top = -1
    elif(operation == 'dump'):
	    for i in range(0, top + 1):

                print(stack[i])
    	    #    for x in stack:
    	    #        if x != None:
            
    elif(operation == 'print'):  
        print(stack[top])
    elif(operation == 'halt'):
        break
    elif(operation == 'read'):
        var = input()
        top = top +1
        stack[top] =  int(var)
    else:
        top = top + 1
        stack[top] = int(operation)