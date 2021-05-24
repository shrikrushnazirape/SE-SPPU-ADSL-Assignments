class WordNode:
    def __init__(self):
        self.word = ""
        self.meaning = ""
 

    def setValue(self, word, mean):
        self.word = word
        self.meaning = mean


class HashTable:
  
    def __init__(self):
        self.dictionary = []
        self.isAtRightPosition = []
        self.chainValue = []
        self.maxSize = 17
        self.currLength = 0
        for i in range (self.maxSize):
            self.dictionary.append(WordNode())
            self.isAtRightPosition.append(False)
            self.chainValue.append(-1)



    def hashFunction(self, word):
        k=0
        for i in range (len(word)):
            k+=ord(word[i])
        k = int(k/(len(word)+1) )
        return k%self.maxSize



    def searchForNode(self, key):
        index = self.hashFunction(key)
        count = 0
        while(self.dictionary[index].word != "" and count < self.currLength):
            if(self.dictionary[index].word != "" and count<=self.currLength):
                if(self.dictionary[index].word == key):
                    return True
                index  = self.dictionary[index].isLink
                count +=1
        return False



    def insertWithoutReplacement(self, word, mean):
        if(self.searchForNode(word)==False and self.currLength<self.maxSize):

            index = self.hashFunction(word)
            if(self.dictionary[index].word == ""):
                self.dictionary[index].word = word
                self.dictionary[index].meaning = mean
                self.isAtRightPosition[index] = True
                self.currLength +=1

            else:
                ch = self.chainValue[index]
                preindex = index
                if(ch == -1):
                    while(self.dictionary[index].word != ""):
                        index +=1
                    self.dictionary[index].key = word
                    self.dictionary[index].meaning = mean
                    self.chainValue[preindex] = index               
                else:
                    
                    while(self.chainValue[index] != -1 and
                        self.dictionary[index].word != ""):
                        for i in range (ch+1, self.maxSize):
                            if(self.dictionary[index].word == ""):
                                self.dictionary[index].word = word
                                self.dictionary[index].meaning = mean
                                self.chainValue[preindex] = i


                # if(self.isAtRightPosition[index]):
                #         preindex = index
                #         while(self.dictionary[index].word != ""):
                #             index +=1
                #         self.dictionary[index].key = word
                #         self.dictionary[index].meaning = mean
                #         self.chainValue[preindex] = index

        else:
            print("element alrleady exist")

    
    def insertWithReplacement(self, word, mean):
        if self.searchForNode(word) == False and self.currLength < self.maxSize:
            self.currLength += 1
            index = self.hashFunction(word)
            if self.dictionary[index].word == "":
                self.dictionary[index].word = word
                self.dictionary[index].meaning = mean
            elif self.hashFunction(self.dictionary[index].word) == self.hashFunction(word):
                while self.dictionary[index].link != -1:
                    index = self.dictionary[index].link
                x = index
                while self.dictionary[x].word != "":
                    x += 1
                self.dictionary[index].link = x
                self.dictionary[x].word = word
                self.dictionary[x].meaning = mean
            else:
                kw = self.dictionary[index].word
                mn = self.dictionary[index].meaning
                self.dictionary[index].word = word
                self.dictionary[index].meaning = mean
                self.insertWithReplacement(kw, mn)
        else:
            print("HashTable Full")


    def printHashtable(self):
        for i in self.dictionary:
            print("word : ", i.word, " -> Meanning : ",i.meaning )

    def delete(self, key):
        if self.searchForNode(key) is True:
            count = 0
            index = self.hashFunction(key)
            while self.dictionary[index].word != key:
                index = self.dictionary[index].isLink
            self.dictionary[index].word = ""
            self.dictionary[index].meaning = ""
            x = index-1
            while self.hashFunction(self.dictionary[x].word) != self.hashFunction(key) and count<self.currLength:
                x -= 1
                count += 1
                if x<0:
                    x = self.maxSize
            self.dictionary[index] = self.dictionary[x]
            self.dictionary[x].word = ""
            self.dictionary[x].meaning = ""
            self.dictionary[x].isLink = -1

a = HashTable()
while True:
    print("1. Insert WR")
    print("2. Insert WOR")
    print("3. print")
    print("4. delete")
    print("5. close")
  
    ch =  int(input("enter the choice : "))
    if(ch ==1):
        word = str(input("enter the word "))
        mean = str(input("enter the meaning "))
        a.insertWithoutReplacement(word, mean)
    elif(ch ==2):
        word = str(input("enter the word "))
        mean = str(input("enter the meaning "))
        a.insertWithReplacement(word, mean)
    elif (ch ==3):
        a.printHashtable()
    elif (ch ==4):
        word = str(input("enter the word "))
        a.delete(word)
    elif(ch == 5):
        break
