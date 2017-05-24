# a python script to interact with exe
# to be completed for GUI

import subprocess
import tkinter
from tkinter import filedialog

def run(cmd, cin):
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    result = p.communicate(input=cin)
    return result[0].decode('UTF-8')

def getFilePath():
    root = tkinter.Tk()
    root.withdraw()
    path = filedialog.askopenfilename()
    root.destroy()
    return path

cmd = getFilePath()
keynum, recnum = 5, 50
cin = str(keynum) + " " + str(recnum)
result = run(cmd, cin.encode('UTF-8')).replace("\r", "").split("Python")


def make2DList(result):
    result = result.strip().split("\n")
    for i in range(len(result)):
        result[i] = result[i].split(" ")
        result[i] = list(filter(None, result[i]))
    return result

origin = make2DList(result[0])
radix = make2DList(result[1])
radixTime = result[2].strip()
merge = make2DList(result[3])
mergeTime = result[4].strip()
print(origin, radix, merge, radixTime, mergeTime)
# print(radixTime, mergeTime)
