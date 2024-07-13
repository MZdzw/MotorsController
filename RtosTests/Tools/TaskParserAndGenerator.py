import os
import re

NumOfLoopsUserList = [
    {
        'fileName': "BlinkingLEDTask.cpp",
        'LoopCnt': '10'
    },
    {
        'fileName': "MovementElementTask.cpp",
        'LoopCnt': '1'
    }
]

def GetIndentation(string):
    cnt = 0
    for sign in string:
        if sign != ' ':
            break
        cnt += 1
        
    return cnt

def GetNumOfLoops(filePath):
    fileName = os.path.basename(filePath)
    for x in NumOfLoopsUserList:
        if fileName == x['fileName']:
            return x['LoopCnt']
    return 0

def ReadFileToList(filepath):
    file = open(filepath, 'r')
    contentOfFile = file.readlines()
    contentOfFileWithMetaData = {
        'FilePath': filepath,
        'Content': contentOfFile
    }
    file.close()
    return contentOfFileWithMetaData

def ParseForTesting(filesContent):
    lookForRegexes = [r'for\s*\(;;\)', r'vTaskDelete*\(']
    for fileContent in filesContent:
        i = 0
        while (i < len(fileContent['Content'])):
            for j in range(0, len(lookForRegexes)):
                if re.search(lookForRegexes[j], fileContent['Content'][i]):
                    numOfSpaces = GetIndentation(fileContent['Content'][i])
                    outputString = (" " * numOfSpaces)
                    if j == 0:
                        numOfLoops = GetNumOfLoops(fileContent['FilePath'])
                        outputString += "for (unsigned int i = 0; i < "
                        outputString += str(numOfLoops)
                        outputString += "; ++i)\n"
                        fileContent['Content'][i] = outputString
                    if j == 1:
                        outputString += "vTaskEndScheduler();\n"
                        fileContent['Content'].insert(i, outputString)
                        i += 2
            i += 1



def GenerateFiles(filesContent, outPath):
    for fileContent in filesContent:
        fileName = os.path.basename(fileContent['FilePath'])
        file = open(outPath + fileName, "w")
        for i in range(0, len(fileContent['Content'])):
            file.write(fileContent['Content'][i])

        file.close()

def main():
    # List of Task functions (containing begining and ending of)
    directory = r"C:\Users\Marcin\Desktop\Projects\MotorsController\Src\Tasks"
    taskFilesContent = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".cpp"):
                filePath = os.path.join(root, file)
                taskFilesContent.append(ReadFileToList(filePath))

    ParseForTesting(taskFilesContent)

    outPath = r"C:\Users\Marcin\Desktop\Projects\MotorsController\RtosTests\gen\gen"
    GenerateFiles(taskFilesContent, outPath)
                
    print(taskFilesContent)
    

if __name__ == "__main__":
    main()
