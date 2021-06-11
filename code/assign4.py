'''
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number. Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers (use linear probing with replacement and without replacement)
'''
SIZE = 10
class Entry:
    name = ""
    mobileNo = -1

    def __init__(self, _name, _mobileNo):
        self.name = _name
        self.mobileNo = _mobileNo


class HashTable:
    ht = []

    def __init__(self):
        for i in range(SIZE):
            self.ht.append(Entry("", -1))

    def hash(self, number):
        return number % SIZE

    # Without replacement
    def insertEntry(self, name, number):
        index = self.hash(number)
        entry = Entry(name, number)
        if (self.ht[index].mobileNo == -1):
            self.ht[index] = entry
        else:
            count = 1
            while (self.ht[index].mobileNo != -1 and count < SIZE):
                index = (index + 1) % SIZE
                count += 1
            if (count < SIZE):
                self.ht[index] = entry
            else:
                print("Cannot insert!")
                return
        print("Entry successfully inserted")

    # With replacement
    def insertEntry1(self, name, number):
        index = self.hash(number)
        entry = Entry(name, number)
        if (self.ht[index].mobileNo == -1):
            self.ht[index] = entry
        elif (self.hash(self.ht[index].mobileNo) != index):
            name = self.ht[index].name
            mobileNo = self.ht[index].mobileNo
            self.ht[index] = entry
            self.insertEntry1(name, mobileNo)
        else:
            count = 1
            while (self.ht[index].mobileNo != -1 and count < SIZE):
                index = (index + 1) % SIZE
                count += 1
            if (count < SIZE):
                self.ht[index] = entry
            else:
                print("Cannot insert!")
                return
        print("Entry successfully inserted")

    def search(self, number):
        index = self.hash(number)
        flag = False
        for i in range(SIZE):
            if (self.ht[index].mobileNo == number):
                flag = True
                break
            else:
                index = (index + 1) % SIZE
        if (flag == True):
            print("Entry found at index: ", index)
            print("Name: ", self.ht[index].name)
            print("Number: ", self.ht[index].mobileNo)
        else:
            print("Entry not found!")

    def displayAllEntry(self):
        print("Index        Name             Mobile Number")
        for i in range(SIZE):
            if (self.ht[i].mobileNo != -1):
                print(i, "       ", self.ht[i].name, "           ", self.ht[i].mobileNo)


flag = True
h = HashTable()
while (flag):
    print("********MENU*******")
    print(
        " 1.Insert Entry without replacement\n 2.Insert Entry with replacement\n 3.Search Entry\n 4.Show All Entries\n 5.Stop\n")
    choice = int(input("Enter choice: "))
    if (choice == 1):
        name = input("Enter name: ")
        number = int(input("Enter number: "))
        h.insertEntry(name, number)
    elif (choice == 2):
        name = input("Enter name: ")
        number = int(input("Enter number: "))
        h.insertEntry1(name, number)
    elif (choice == 3):
        number = int(input("Enter number: "))
        h.search(number)
    elif (choice == 4):
        h.displayAllEntry()
    elif (choice == 5):
        flag = False
    else:
        print("Enter valid choice!")
