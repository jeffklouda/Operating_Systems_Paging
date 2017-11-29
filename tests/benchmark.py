import subprocess
import sys
import time
import re

#if len(sys.argv) < 1:
#    print "Please include test program as argument"
#    sys.exit

#args = sys.argv[1:len(sys.argv)]
args  = ["../bin/bs", "../bin/prime", "../bin/scan", "../bin/fibonacci"]
args_two = ["../bin/bubble", "../bin/insertion", "../bin/selection"]
commands = ["0 0 0 1", "8 64 0 1", "8 64 1 1", "8 64 2 1", " 8 64 3 1", "8 128 0 1", "8 128 1 1", "8 128 2 1", "8 128 3 1", "16 64 0 1", "16 64 1 1", "16 64 2 1", "16 64 3 1", "8 64 0 2", "8 64 1 2", "8 64 2 2", "8 64 3 2"]
commands_two = ["0 0 0 1", "8 64 0 1", "8 64 1 1", "8 64 2 1", " 8 64 3 1", "8 128 0 1", "8 128 1 1", "8 128 2 1", "8 128 3 1", "16 64 0 1", "16 64 1 1", "16 64 2 1", "16 64 3 1"]
new_commands = []

for index, arg in enumerate(args):
    for command in commands:
        new_commands.append(arg + " " + command)    
for index, arg in enumerate(args_two):
    for command in commands_two:
        new_commands.append(arg + " " + command)
print ('Command                |        Addrs|  Pages| VPNShift|VPNMask|    OffsetMask|Hits|  Misses')
for command in new_commands: 
    millis = float(time.time() * 1000)
    process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num1  = output[:index.start()]
    output = output[index.start():]
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num2  = output[:index.start()]
    output = output[index.start():]
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num3  = output[:index.start()]
    output = output[index.start():]
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num4  = output[:index.start()]
    output = output[index.start():]
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num5  = output[:index.start()]
    output = output[index.start():]
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num6  = output[:index.start()]
    output = output[index.start():]
    index = re.search("\d", output)
    output = output[index.start():]
    index = re.search("\n", output)
    num7  = output[:index.start()]
    output = output[index.start():]
    command = command.replace(" ", "|")
    #print('--------------------------------------------------------------------------------------------')
    print '{0: <31}'.format(command) + '| ' + '{0: <5}'.format(num1) + '| ' + '{0: <5}'.format(num2) + '| ' + '{0: <8}'.format(num3) + '| ' + '{0: <10}'.format(num4) + '| ' + '{0: <9}'.format(num5) + '| ' + '{0: <5}'.format(num6) + '| ' + '{0: <5}'.format(num7) 
    #print str(float(time.time() * 1000) - millis) + " :Milliseconds"

