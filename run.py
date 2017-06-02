# a python script to interact with exe

import subprocess
from tkinter import *
from tkinter import filedialog
from tkinter import messagebox
from tkinter.ttk import *
import xlwt, time
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

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
        if isinstance(x, list):
            for xx in x:
                result += makecin(xx).decode('UTF-8')
        else:
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
        for col in range(len(data[i][0])):
            sheet.write(0, col, str(col))
        for row in range(len(data[i])):
            for col in range(len(data[i][row])):
                sheet.write(row + 1, col, str(data[i][row][col]))
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

        prioFrame1 = Frame(frame, padding=(5, 4))
        prioFrame1.grid(row=3, column=1)
        prioFrame2 = Frame(frame, padding=(5, 4))
        prioFrame2.grid(row=3, column=2)
        prioLabel = Label(prioFrame1, text="排序优先级: ", anchor=CENTER)
        prioLabel.grid()
        self.priority = Entry(prioFrame2)
        self.priority.insert(END, "0,1,2,3,4")
        self.priority.grid()

        resultLabelFrame = Frame(frame, padding=(5, 4))
        resultLabelFrame.grid(row=4, column=1, columnspan=2)
        resultStr = "radixLSD, radixMSD, mergeLSD, mergeMSD"
        resultLabel = Label(resultLabelFrame, text=resultStr, anchor=CENTER)
        resultLabel.grid()

        resultFrame = Frame(frame, padding=(5, 4))
        resultFrame.grid(row=5, column=1, columnspan=2)
        self.showResult = Text(resultFrame, width=40, height=20)
        self.showResult.grid()
        scrollbar = Scrollbar(frame, command=self.showResult.yview)
        scrollbar.grid(row=5, column=3, sticky='nsew')

        randomFrame = Frame(frame, padding=(5, 4))
        randomFrame.grid(row=6, column=1)
        analyFrame = Frame(frame, padding=(5, 4))
        analyFrame.grid(row=6, column=2)
        resetFrame = Frame(frame, padding=(5, 4))
        resetFrame.grid(row=7, column=1)
        trendFrame = Frame(frame, padding=(5, 4))
        trendFrame.grid(row=7, column=2)
        randomButton = Button(randomFrame, text='随机', command=lambda: self.random(data))
        randomButton.grid()
        analyButton = Button(analyFrame, text='分析', command=self.analyse)
        analyButton.grid()
        resetButton = Button(resetFrame, text='比较', command=self.compare)
        resetButton.grid()
        trendButton = Button(trendFrame, text='趋势', command=self.trend)
        trendButton.grid()

        infoFrame = Frame(frame, padding=(5, 4))
        infoFrame.grid(row=8, column=1, columnspan=2)
        self.var = StringVar()
        info = Label(infoFrame, textvariable=self.var, anchor=CENTER)
        info.grid()

        root.bind('<Return>', lambda: self.random(data))
        self.recnum.focus()

    def random(self, data):
        rec = self.recnum.get()
        key = self.keynum.get()
        priority = self.priority.get()
        priority = priority.split(",")
        self.var.set("Loading...\nrecnum = %s, keynum = %s" % (rec, key))
        self.root.update()
        cin = makecin(0, key, rec, priority)
        result = run(data.cmd, cin)
        data.runtime += 1
        result = makeResult(0, result)
        self.showResult.insert(END, ", ".join(result[5:]) + "\n")
        self.var.set("Finished!")
        self.root.update()
        export = messagebox.askquestion("导出", "是否导出至 Excel？")
        if export == 'yes':
            writeToExcel(result[:5])
            messagebox.showinfo(title="导出", message="导出成功！")

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

    def compare(self):
        '''get from http://pbpython.com/excel-diff-pandas.html'''
        # Define the diff function to show the changes in each field
        def report_diff(x):
            return x[0] if x[0] == x[1] else '{} ---> {}'.format(*x)

        # We want to be able to easily tell which rows have changes
        def has_change(row):
            if "--->" in row.to_string():
                return "Y"
            else:
                return "N"

        file = getFilePath()
        self.var.set("Loading...")
        self.root.update()
        # Read in all excel files
        df1 = pd.read_excel(file, 'radixLSD', na_values=['NA'])
        df2 = pd.read_excel(file, 'mergeLSD', na_values=['NA'])
        df3 = pd.read_excel(file, 'radixMSD', na_values=['NA'])
        df4 = pd.read_excel(file, 'mergeMSD', na_values=['NA'])
        self.var.set("Comparing radixLSD and mergeLSD...")
        self.root.update()
        # Create a panel of the two dataframes
        diff_panel = pd.Panel(dict(df1=df1, df2=df2))
        #Apply the diff function
        diff_output = diff_panel.apply(report_diff, axis=0)
        # Flag all the changes
        diff_output['change'] = diff_output.apply(has_change, axis=1)
        #Save the changes to excel but only include the columns we care about
        diff_output[(diff_output.change == 'Y')].to_excel('1-2.xlsx', index=False)
        self.var.set("Comparing radixLSD and radixMSD...")
        self.root.update()
        diff_panel = pd.Panel(dict(df1=df1, df2=df3))
        diff_output = diff_panel.apply(report_diff, axis=0)
        diff_output['change'] = diff_output.apply(has_change, axis=1)
        diff_output[(diff_output.change == 'Y')].to_excel('1-3.xlsx', index=False)
        self.var.set("Comparing radixLSD and mergeMSD...")
        self.root.update()
        diff_panel = pd.Panel(dict(df1=df1, df2=df4))
        diff_output = diff_panel.apply(report_diff, axis=0)
        diff_output['change'] = diff_output.apply(has_change, axis=1)
        diff_output[(diff_output.change == 'Y')].to_excel('1-4.xlsx', index=False)
        self.var.set("Finished!")
        self.root.update()
        messagebox.showinfo(title="比较", message="比较成功！")

    def trend(self):
        key = [1, 2, 5, 6, 8, 10, 12, 14, 17, 20, 25, 30, 40, 50]
        rec = [2000, 5000, 10000, 12000, 15000, 18000, 20000, 25000, 30000, 50000]
        self.showResult.delete('1.0', END)
        result = []
        for k in key:
            for r in rec:
                self.var.set("Loading...\nkeynum = %s, recnum = %s" % (k, r))
                self.root.update()
                priority = []
                for i in range(k):
                    priority += [i]
                cin = makecin(1, k, r, priority)
                out = run(data.cmd, cin)
                out = makeResult(1, out)
                result.append([k, r] + out)
                self.showResult.insert(END, ", ".join(out) + "\n")
        self.var.set("Finished!")
        self.root.update()
        colors = ['r', 'b', 'g', 'y']
        markers = ['s', '^', 'o', '*']
        plot = [[211, 212, 211, 212], [211, 211, 212, 212]]
        title = ['TIME = TIME(recnum)\nAbove is LSD, below is MSD',
                 'TIME = TIME(recnum)\nAbove is radix sort, below is merge sort',
                 'TIME = TIME(keynum)\nAbove is LSD, below is MSD',
                 'TIME = TIME(keynum)\nAbove is radix sort, below is merge sort']
        length = [len(key), len(rec)]
        factor = [key, rec]
        minSize = [float(rec[0]), float(key[0])]
        maxSize = [float(rec[-1]), float(key[-1])]
        for j in range(4):
            index = j // 2
            plt.figure(j + 1)
            runTime = [[[] for i in range(length[index])] for j in range(4)]
            for item in result:
                for i in range(4):
                    runTime[i][factor[index].index(item[index])].append(item[i + 2])
            for i in range(4):
                plt.subplot(plot[j % 2][i])
                for item in runTime[i]:
                    line = plt.plot(factor[1 - index], item)
                    plt.setp(line, color=colors[i], aa=True, ls='-', marker=markers[i])
            plt.title(title[j])
            plt.tight_layout()
        plt.show()



if __name__ == "__main__":
    class Struct(object): pass
    data = Struct()
    data.runtime = 0
    data.cmd = getFilePath()
    root = Tk()
    root.title("多关键字排序 Multi-key Sort")
    root.iconbitmap('ucas.ico')
    presentation(root, data)
    root.focus_set()
    root.mainloop()
