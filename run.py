# a python script to interact with exe
# to be completed for GUI

import subprocess
from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
from tkinter.ttk import *
import xlwt, time

def run(runtime, cmd, cin):
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    result = p.communicate(input=cin)
    result = result[0].decode('UTF-8').replace("\r", "")
    return result

def getFilePath():
    root = Tk()
    root.withdraw()
    path = filedialog.askopenfilename()
    root.destroy()
    return path

def makecin(*args):
    result = ''
    for x in args:
        result += str(x) + " "
    return result.encode('UTF-8')

def make2DList(result):
    result = result.strip().split("\n")
    for i in range(len(result)):
        result[i] = result[i].split(" ")
        result[i] = list(filter(None, result[i]))
    return result

def makeResult(func, result):
    if func == 0:
        result = result.split("Python")
        origin = make2DList(result[0])
        radix = make2DList(result[1])
        radixTime = float(result[2].strip())
        merge = make2DList(result[3])
        mergeTime = float(result[4].strip())
        return [origin, radix, merge, radixTime, mergeTime]

def getCurrentTime():
    return time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(time.time()))

def writeToExcel(data, count):
    workbook = xlwt.Workbook()
    name = ["init", "radix", "merge"]
    for i in range(count):
        sheet = workbook.add_sheet(name[i])
        for row in range(len(data[i])):
            for col in range(len(data[i][row])):
                sheet.write(row, col, str(data[i][row][col]))
    time = getCurrentTime().replace(':','-').replace(' ','-')
    workbook.save("result-%s.xls" % time)

def analyse(result):
    result = result.strip().split('\n')
    for i in range(len(result)):
        result[i] = result[i].split(', ')
    radix, merge = 0, 0
    for record in result:
        radix += float(record[0])
        merge += float(record[1])
    radix /= len(result)
    merge /= len(result)
    return [radix, merge, merge / radix]

############
# GUI part #
############

class presentation(Frame):
    def __init__(self, master, data):
        self.frame = Frame(master)
        self.frame.pack()

        nameFrame = Frame(self.frame, padding=(5, 4))
        nameFrame.grid(row=0, column=1, columnspan=2)
        Label(nameFrame, text="多关键字排序", font='微软雅黑 16', anchor=CENTER).grid(row=0)

        Frame(self.frame, width='3').grid(column=0, rowspan=2)
        Frame(self.frame, width='3').grid(column=3, rowspan=2)

        keyFrame1 = Frame(self.frame, padding=(5, 4))
        keyFrame1.grid(row=1, column=1)
        keyFrame2 = Frame(self.frame, padding=(5, 4))
        keyFrame2.grid(row=1, column=2)
        self.keyLabel = Label(keyFrame1, text="关键字数量: ", anchor=CENTER)
        self.keyLabel.grid()
        self.keynum = Entry(keyFrame2)
        self.keynum.insert(END, "5")
        self.keynum.grid()

        recFrame1 = Frame(self.frame, padding=(5,4))
        recFrame1.grid(row=2, column=1)
        recFrame2 = Frame(self.frame, padding=(5,4))
        recFrame2.grid(row=2, column=2)
        self.recLabel = Label(recFrame1, text="样本大小: ", anchor=CENTER)
        self.recLabel.grid()
        self.recnum = Entry(recFrame2)
        self.recnum.insert(END, "10000")
        self.recnum.grid()

        resultFrame = Frame(self.frame, padding=(5,4))
        resultFrame.grid(row=3, column=1, columnspan=2)
        self.showResult = Text(resultFrame, width=40, height=20)
        self.showResult.grid()

        buttonFrame = Frame(self.frame, padding=(5,4))
        buttonFrame.grid(row=4, column=1, columnspan=2)
        self.randomButton = Button(buttonFrame, text='随机', command=lambda: self.random(data))
        self.randomButton.grid(row=0, column=0)
        self.analyButton = Button(buttonFrame, text='分析', command=self.analyse)
        self.analyButton.grid(row=0, column=1)
        self.resetButton = Button(buttonFrame, text='重置', command=self.reset)
        self.resetButton.grid(row=0, column=2)

        root.bind('<Return>', lambda: self.random(data))
        self.recnum.focus()

    def random(self, data):
        rec = self.recnum.get()
        key = self.keynum.get()
        cin = makecin(0, key, rec)
        result = run(data.runtime, data.cmd, cin)
        data.runtime += 1
        result = makeResult(0, result)
        self.showResult.insert(END, str(result[3]) + ", " + str(result[4]) + "\n")
        writeToExcel(result[:3], 3)

    def analyse(self):
        result = self.showResult.get("0.0", "end")
        result = analyse(result)
        info = '''Radix Sort Average Time: %.3fs
Merge Sort Average Time: %.3fs
Radix Sort is %.1fx faster than Merge Sort''' % (result[0], result[1], result[2])
        messagebox.showinfo(title='Analyse',message=info)

    def reset(self):
        self.showResult.delete('1.0', END)


class Struct(object): pass
data = Struct()
data.runtime = 0
data.cmd = getFilePath()
root = Tk()
root.title("多关键字排序 Multi-keyword Sorting")
root.iconbitmap('ucas.ico')
w, h = root.winfo_screenwidth(), root.winfo_screenheight()
window = presentation(root, data)
root.focus_set()
root.mainloop()
