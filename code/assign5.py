'''
Implement all the functions of a dictionary (ADT) using hashing and handle collisions using chaining with / without replacement.

Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, Keys must be unique. Standard Operations: Insert(key, value), Find(key), Delete(key)
'''

class Node:
    def __init__(self, key, mean):
        self.key = key
        self.meaning = mean

class Dict:
    def __init__(self):

        self.l = []
        self.chain = []
        self.length = 0
        self.size = 13

        for i in range(13):
            self.l.append(Node("", ""))
            self.chain.append(-1)

    def hashFunction(self, key):
        i = 0
        s = 0
        for _ in key:
            s = s+ord(_)*i  # ascii valud of char * position
            i += 1
        return s % self.size


    def insertWithoutReplacement(self, key, value):
        if self.search(key)[1] == False and self.length<self.size:
            self.length += 1
            index = self.hashFunction(key)

            if self.l[index].key == "":
                self.l[index].key = key
                self.l[index].meaning = value
                print("Inserted Successfully ")
                return
            
            temp = index
            while(( self.hashFunction(self.l[index].key) != temp) and 
                    self.l[index].key != ''):
                    index = (index+1)%self.size

            if(self.l[index].key == ''):
                self.l[index].key = key
                self.l[index].meaning = value
                print("Inserted Successfully ")
                return

            while self.chain[index] != -1:
                index = self.chain[index]
                           
            temp2 = index
            while(self.l[index].key != ''):
                index = (index+1 ) %self.size
            self.chain[temp2] = index
            self.l[index].key = key
            self.l[index].meaning = value
            print("Inserted Successfully ")
            return

        else:
            print("Element already exists or no place for entry")


    def insertWithReplacement(self, key, value):
        if self.search(key)[1] == False and self.length < self.size:
            self.length += 1
            index = self.hashFunction(key)
            if self.l[index].key == "":
                self.l[index].key = key
                self.l[index].meaning = value
                print("inserted Successfully")
                return

            if self.hashFunction(self.l[index].key) == index :
                while self.chain[index] != -1:
                    index = self.chain[index]

                x = index
                while self.l[index].key != "":
                   index = (index + 1) %self.size
                self.chain[x] = index
                self.l[index].key = key
                self.l[index].meaning = value
                print("Inserted Successfully")
                return
            else:
                temp = index
                index = (index + 1) % self.size
                while(self.chain[index] != temp):
                    index = (index + 1)%self.size
                preindex = index
                index = temp
                while(self.l[index].key != ''):
                    index = (index + 1)%self.size
                self.chain[preindex] = index
                self.l[index].key = self.l[temp].key
                self.l[index].meaning = self.l[temp].meaning
                self.chain[index] = self.chain[temp]

                self.l[temp].key = key
                self.l[temp].meaning = value
                print("inserted Successfully")

        else:
            print("HashTable Full or key is already present ")


    def comparisons(self, key):
    
        comparisons = 0
        index = self.hashFunction(key)
        if (self.hashFunction(self.l[index].key) == index):
            while self.chain[index] != -1:
                comparisons +=1
                if(self.l[index].key == key):
                    return comparisons
                index = self.chain[index]

            if(self.l[index].key == key):
                comparisons +=1
                return comparisons
                
            else:
                return -1

        temp = index
        while self.hashFunction(self.l[index].key) != temp:
            comparisons +=1
            if self.l[index].key == key:
                return comparisons
            index = (index + 1) %self.size
            if index == temp:
                return -1
        while (self.chain[index] != -1):
            comparisons +=1
            if( self.l[index].key == key):
                return comparisons
            index = self.chain[index]
        if self.l[index].key == key:
            comparisons +=1
            return comparisons
        return -1
      


    def search(self, key):
        index = self.hashFunction(key)
        if (self.hashFunction(self.l[index].key) == index):
            while self.chain[index] != -1:
                if(self.l[index].key == key):
                    return index, True
                index = self.chain[index]
            if(self.l[index].key == key):
                return index, True
            else:
                return -1, False

        temp = index
        while self.hashFunction(self.l[index].key) != temp:
            if self.l[index].key == key:
                return index, True
            index = (index + 1) %self.size
            if index == temp:
                return -1, False
        while (self.chain[index] != -1):
            if( self.l[index].key == key):
                return index, True
            index = self.chain[index]
        if self.l[index].key == key:
            return index, True
        return -1, False




    def delete(self, key):
        if self.search(key)[1] == True:
            count = 0
            index = self.hashFunction(key)
            prev  = -1
            while self.l[index].key != key:
                prev = index
                index = self.chain[index]
            self.l[index].key = ""
            self.l[index].meaning = ""
            x = index
            while self.chain[x]!= -1:
                prev = x
                x = self.chain[x]
            if prev == -1:
                pass
            else:
                self.l[index].key, self.l[index].meaning = self.l[x].key, self.l[x].meaning
                print(x)
                self.l[x].key, self.l[x].meaning = "", ""
                self.chain[prev] = -1
        else:
            print("Key is not present")

    def display(self):
        print("\n\n---------------------------------------------------------------")
        print("\n\t Bucket.No", "\t", "Word", "\t", "meaning", "\t", "chain")
        for i in range(len(self.l)):
            print("\t", i ,"\t", self.l[i].key," "*(8-len(self.l[i].key)),"\t", self.l[i].meaning," "*(8-len(self.l[i].key)), "\t", self.chain[i])




a = Dict()
while True:
    print("1. Insert WR")
    print("2. Insert WOR")
    print("3. print")
    print("4. delete")
    print("5. Search for word")
    print("5. close")
  
    ch =  int(input("enter the choice : "))
    if(ch ==1):
        word = str(input("enter the word "))
        mean = str(input("enter the meaning "))
        a.insertWithReplacement(word, mean)
    elif(ch ==2):
        word = str(input("enter the word "))
        mean = str(input("enter the meaning "))
        a.insertWithoutReplacement(word, mean)
    elif (ch ==3):
        a.display()
    elif (ch ==4):
        word = str(input("enter the word "))
        a.delete(word)
    elif (ch ==5):
        word = str(input("enter the word you want to sear "))
        k = a.comparisons(word)
        if k==-1:
            print("Key is not present")
        print("key is present")
        print("no of comparison",k)
       
    elif(ch == 6):
        break