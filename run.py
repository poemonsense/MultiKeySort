# a python script to interact with exe
# need to be completed for GUI

import subprocess
import tkinter
from tkinter import filedialog

def run(cmd, input):
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    result = p.communicate(input=data)
    return result[0].decode('UTF-8')

def getFilePath():
    root = tkinter.Tk()
    root.withdraw()
    path = filedialog.askopenfilename()
    root.destroy()
    return path

cmd = getFilePath()
data = b"sadojoidjoiqw"
print(run(cmd, data))