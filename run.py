# a python script to interact with exe
# to be completed for GUI

import subprocess
from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
from tkinter.ttk import *
import xlwt, time
import matplotlib.pyplot as plt

def run(cmd, cin):
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
    '''Analyse the result and return inquired information in a tuple.

    0 means no output result printed
    1 otherwise'''
    splitStr = "Python"
    if func == 0:
        result = result.split(splitStr)
        origin = make2DList(result[0])
        radixLSD = make2DList(result[1])
        radixLSDTime = result[2].strip()
        radixMSD = make2DList(result[3])
        radixMSDTime = result[4].strip()
        mergeLSD = make2DList(result[5])
        mergeLSDTime = result[6].strip()
        mergeMSD = make2DList(result[7])
        mergeMSDTime = result[8].strip()
        return [origin, radixLSD, radixMSD, mergeLSD, mergeMSD, 
                radixLSDTime, radixMSDTime, mergeLSDTime, mergeMSDTime]
    elif func == 1:
        result = result.split(splitStr)
        radixLSDTime = result[0].strip()
        radixMSDTime = result[1].strip()
        mergeLSDTime = result[2].strip()
        mergeMSDTime = result[3].strip()
        return [radixLSDTime, radixMSDTime, mergeLSDTime, mergeMSDTime]

def getCurrentTime():
    return time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(time.time()))

def writeToExcel(data):
    workbook = xlwt.Workbook()
    name = ["init", "radixLSD", "radixMSD", "mergeLSD", "mergeMSD"]
    for i in range(len(data)):
        sheet = workbook.add_sheet(name[i])
        for row in range(len(data[i])):
            for col in range(len(data[i][row])):
                sheet.write(row, col, str(data[i][row][col]))
    now = getCurrentTime().replace(':', '-').replace(' ', '-')
    workbook.save("result-%s.xls" % now)

def analyse(result):
    result = result.strip().split('\n')
    for i in range(len(result)):
        result[i] = result[i].split(", ")
    radixLSD, radixMSD, mergeLSD, mergeMSD = 0, 0, 0, 0
    for record in result:
        radixLSD += float(record[0])
        radixMSD += float(record[1])
        mergeLSD += float(record[2])
        mergeMSD += float(record[3])
    radixLSD /= len(result)
    radixMSD /= len(result)
    mergeLSD /= len(result)
    mergeMSD /= len(result)
    return [radixLSD, radixMSD, mergeLSD, mergeMSD]

############
# GUI part #
############

class presentation(object):
    def __init__(self, master, data):
        self.root = master
        frame = Frame(master)
        frame.pack()

        nameFrame = Frame(frame, padding=(5, 4))
        nameFrame.grid(row=0, column=1, columnspan=2)
        Label(nameFrame, text="多关键字排序", font='微软雅黑 16', anchor=CENTER).grid(row=0)

        Frame(frame, width='3').grid(column=0, rowspan=2)
        Frame(frame, width='3').grid(column=4, rowspan=2)

        keyFrame1 = Frame(frame, padding=(5, 4))
        keyFrame1.grid(row=1, column=1)
        keyFrame2 = Frame(frame, padding=(5, 4))
        keyFrame2.grid(row=1, column=2)
        keyLabel = Label(keyFrame1, text="关键字数量: ", anchor=CENTER)
        keyLabel.grid()
        self.keynum = Entry(keyFrame2)
        self.keynum.insert(END, "5")
        self.keynum.grid()

        recFrame1 = Frame(frame, padding=(5, 4))
        recFrame1.grid(row=2, column=1)
        recFrame2 = Frame(frame, padding=(5, 4))
        recFrame2.grid(row=2, column=2)
        recLabel = Label(recFrame1, text="样本大小: ", anchor=CENTER)
        recLabel.grid()
        self.recnum = Entry(recFrame2)
        self.recnum.insert(END, "10000")
        self.recnum.grid()

        resultLabelFrame = Frame(frame, padding=(5, 4))
        resultLabelFrame.grid(row=3, column=1, columnspan=2)
        resultStr = "radixLSD, radixMSD, mergeLSD, mergeMSD"
        resultLabel = Label(resultLabelFrame, text=resultStr, anchor=CENTER)
        resultLabel.grid()
        resultFrame = Frame(frame, padding=(5, 4))
        resultFrame.grid(row=4, column=1, columnspan=2)
        self.showResult = Text(resultFrame, width=40, height=20)
        self.showResult.grid()
        scrollbar = Scrollbar(frame, command=self.showResult.yview)
        scrollbar.grid(row=4, column=3, sticky='nsew')

        randomFrame = Frame(frame, padding=(5, 4))
        randomFrame.grid(row=5, column=1)
        analyFrame = Frame(frame, padding=(5, 4))
        analyFrame.grid(row=5, column=2)
        resetFrame = Frame(frame, padding=(5, 4))
        resetFrame.grid(row=6, column=1)
        trendFrame = Frame(frame, padding=(5, 4))
        trendFrame.grid(row=6, column=2)
        randomButton = Button(randomFrame, text='随机', command=lambda: self.random(data))
        randomButton.grid()
        analyButton = Button(analyFrame, text='分析', command=self.analyse)
        analyButton.grid()
        resetButton = Button(resetFrame, text='重置', command=self.reset)
        resetButton.grid()
        trendButton = Button(trendFrame, text='趋势', command=self.trend)
        trendButton.grid()

        infoFrame = Frame(frame, padding=(5, 4))
        infoFrame.grid(row=7, column=1, columnspan=2)
        self.var = StringVar()
        self.info = Label(infoFrame, textvariable=self.var, anchor=CENTER)
        self.info.grid()

        root.bind('<Return>', lambda: self.random(data))
        self.recnum.focus()

    def random(self, data):
        rec = self.recnum.get()
        key = self.keynum.get()
        self.var.set("Loading...\nrecnum = %s, keynum = %s" % (rec, key))
        self.root.update()
        cin = makecin(0, key, rec)
        result = run(data.cmd, cin)
        data.runtime += 1
        result = makeResult(0, result)
        self.showResult.insert(END, ", ".join(result[5:]) + "\n")
        export = messagebox.askquestion("导出", "是否导出至 Excel？")
        if export == 'yes':
            writeToExcel(result[:5])

    def analyse(self):
        result = self.showResult.get("0.0", "end")
        result = analyse(result)
        for i in range(len(result)):
            result[i] = max(0.001, result[i])
        ratioLSD = result[2] / result[0]
        ratioMSD = result[3] / result[1]
        info = '''LSD Radix Sort Average Time: %.3fs
MSD Radix Sort Average Time: %.3fs
LSD Merge Sort Average Time: %.3fs
MSD Merge Sort Average Time: %.3fs
LSD Radix Sort is %.1fx faster than LSD Merge Sort
MSD Radix Sort is %.1fx faster than MSD Merge Sort''' % (result[0], result[1], \
                                     result[2], result[3], ratioLSD, ratioMSD)
        messagebox.showinfo(title='Analyse', message=info)

    def reset(self):
        self.showResult.delete('1.0', END)

    def trend(self):
        key = [1, 2, 5, 6, 8, 10, 12, 14, 17, 20]
        rec = [2000, 5000, 10000, 12000, 15000, 18000, 20000, 25000]
        #key = [1, 2, 5, 6, 8]
        #rec = [2000, 5000, 10000, 12000, 15000]
        self.showResult.delete('1.0', END)
        # TIME ~ key, set rec = 10000, 20000
        result = []
        for k in key:
            for r in rec:
                self.var.set("Loading...\nrecnum = %s, keynum = %s" % (k, r))
                self.root.update()
                cin = makecin(1, k, r)
                out = run(data.cmd, cin)
                out = makeResult(1, out)
                result.append([k, r] + out)
                if k == key[-1] and r == rec[-1]:
                    maxTime = float(out[2])
                self.showResult.insert(END, ", ".join(out) + "\n")
        plt.figure(1)
        recTime = [[[] for i in range(len(key))] for j in range(4)]
        for item in result:
            for i in range(4):
                recTime[i][key.index(item[0])].append(item[i + 2])
        colors = ['r', 'b', 'g', 'y']
        markers = ['s', '^', 'o', '*']
        for i in range(len(recTime)):
            plt.subplot(210 + 2 - (i + 1) % 2)
            for item in recTime[i]:
                line = plt.plot(rec, item)
                plt.setp(line, color=colors[i], aa=True, ls='-', marker=markers[i])
        plt.title('TIME = TIME(recnum)\nABove is LSD, below is MSD')
        plt.axis([0.8 * float(rec[0]), float(rec[-1]) * 1.05, 0, maxTime * 1.05])

        plt.figure(2)
        recTime = [[[] for i in range(len(key))] for j in range(4)]
        for item in result:
            for i in range(4):
                recTime[i][key.index(item[0])].append(item[i + 2])
        colors = ['r', 'b', 'g', 'y']
        markers = ['s', '^', 'o', '*']
        for i in range(len(recTime)):
            plt.subplot(210 + 1 + i // 2)
            for item in recTime[i]:
                line = plt.plot(rec, item)
                plt.setp(line, color=colors[i], aa=True, ls='-', marker=markers[i])
        plt.title('TIME = TIME(recnum)\nABove is radix sort, below is merge sort')
        plt.axis([0.8 * float(rec[0]), float(rec[-1]) * 1.05, 0, maxTime * 1.05])

        plt.figure(3)
        keyTime = [[[] for i in range(len(rec))] for j in range(4)]
        for item in result:
            for i in range(4):
                keyTime[i][rec.index(item[1])].append(item[i + 2])
        for i in range(len(keyTime)):
            plt.subplot(210 + 2 - (i + 1) % 2)
            for item in keyTime[i]:
                line = plt.plot(key, item)
                plt.setp(line, color=colors[i], aa=True, ls='-', marker=markers[i])
        plt.title('TIME = TIME(keynum)\nABove is LSD, below is MSD')
        plt.axis([0.8 * float(key[0]), float(key[-1]) * 1.05, 0, maxTime * 1.05])

        plt.figure(4)
        keyTime = [[[] for i in range(len(rec))] for j in range(4)]
        for item in result:
            for i in range(4):
                keyTime[i][rec.index(item[1])].append(item[i + 2])
        for i in range(len(keyTime)):
            plt.subplot(210 + 1 + i // 2)
            for item in keyTime[i]:
                line = plt.plot(key, item)
                plt.setp(line, color=colors[i], aa=True, ls='-', marker=markers[i])
        plt.title('TIME = TIME(keynum)\nABove is radix sort, below is merge sort')
        plt.axis([0.8 * float(key[0]), float(key[-1]) * 1.05, 0, maxTime * 1.05])

        plt.show()



if __name__ == "__main__":
    class Struct(object): pass
    data = Struct()
    data.runtime = 0
    data.cmd = getFilePath()
    root = Tk()
    root.title("多关键字排序 Multi-keyword Sorting")
    root.iconbitmap('ucas.ico')
    presentation(root, data)
    root.focus_set()
    root.mainloop()
