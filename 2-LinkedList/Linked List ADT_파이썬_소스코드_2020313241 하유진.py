start = 0 

class NODE: 
    def __init__(self, data): 
        self.data = data
        self.next = None

    def __str__(self): 
        return str(self.data)

class LinkedList: 
    def __init__(self, data): 
        global start
        new = NODE(data)
        self.head = new
        self.size = 1 
        self.current = 0 
        start = 1

    def __str__(self): 
        display = '  '
        tmp = self.head
        while True: 
            display += str(tmp) 
            if tmp.next == None:
                break
            tmp = tmp.next
            display += ' '
        if (self.size): 
            tmp = self.head
            for i in range (0, self.current, 1):
                tmp = tmp.next
            display += ' (current point: {0})\n'.format(tmp.data) 
        
        return display

    def addFirst(self, data): #linked list의 가장 앞부분에 node를 추가하는 메서드
        new = NODE(data)
        
        new.next = self.head
        self.head = new
        self.size += 1

    def addTail(self, data): #current point 뒤에 값을 추가
        new = NODE(data)
        tmp = self.head

        for i in range (0, self.current, 1):
            tmp = tmp.next
        new.data = data
        new.next = tmp.next
        tmp.next = new
        self.size += 1
        self.current += 1

    def add(self, data): #current point 앞에 값을 추가
        new = NODE(data)
        tmp = self.head

        for i in range (0, self.current-1, 1):
            tmp = tmp.next
        new.data = data
        new.next = tmp.next
        tmp.next = new

        self.size += 1

    def get_data(self): #current point의 data 값을 return하는 메서드
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        return str(tmp.data)

    def traverse_first(self): #current point를 가장 앞으로 옮기는 메서드
        self.current = 0

    def traverse_last(self): #current point를 가장 뒤로 옮기는 메서드
        self.current = self.size -1

    def traverse_next(self): 
        self.current += 1

    def traverse_prev(self): 
        self.current += -1
    
    def delete(self): 
        if (self.size == 0): 
            return

        if (self.current == 0): 
            target = self.head
            self.head = target.next
            del target

        else: 
            cur = self.head
            for i in range (0, self.current-1, 1):
                cur = cur.next
            target = cur.next
            cur.next = cur.next.next
            del target

        self.size += -1

        if (self.current >= self.size): #current point가 linked list에서 벗어났을 때
            self.current = 0

    def replace(self, data): #current point의 data를 다른 data로 replace하는 메서드
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        tmp.data = data

    def data_count(self): #linked list의 data 개수를 세는 메서드
        return str(self.size)

    def is_member(self, data): #입력받은 data가 linked list에 있는지 확인하는 메서드
        tmp = self.head
        self.current = 0
        while (tmp):
            if (tmp.data == data):
                return self.current
            tmp = tmp.next
            self.current += 1
        self.current += -1
        return -1 #해당 원소를 찾지 못했을 때    

    def clear(self): #linked list의 모든 원소를 삭제하는 메서드
        global start
        self.current = 0
        tmp = self.size
        for i in range (0, tmp, 1): #원소의 개수만큼 self.delete()를 실행
            self.delete()
        start = 0

    def is_empty(self): #linked list가 비어 있는지 확인하는 메서드
        if (self.head == None):
            return 1
        else:
            return 0

    def letter_change(self):
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        cap = ord(tmp.data)
        if (cap >= 65 and cap <= 90): #대문자인 경우
            cap = cap + 32
        elif (cap >= 97 and cap <= 122): #소문자인 경우
            cap = cap -32
        tmp.data = chr(cap)


    def move_end(self):
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        data=tmp.data
        self.delete()
        self.current = self.size -1
        self.addTail(data)
        

    def move_first(self):
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        data=tmp.data
        self.delete()
        self.addFirst(data)
        self.current =0
    
def is_number(factor): #factor가 숫자인지 확인하는 함수
    try:
        float(factor)
        return 1
    except ValueError:
        return 0        

answer= []

print("==============♥MENU♥==============");
print("INSERT			: +(data)");
print("DELET			: -");
print("PRINT			: L");
print("GET_DATA		: G");
print("TRAVERSE_FRONT	: <");
print("TRAVERSE_REAR		: >");
print("REPLACE		: =(data)");
print("DATA_COUNT		: #");
print("IS_MEMBER		: ?(data)");
print("CLEAR			: C");
print("IS_EMPTY		: E(data)");
print("IS_NUMBER		: (number)");
print("MOVE_END		: Mn");
print("MOVE_FIRST		: Mf");
print("LETTER_CHANGE		: U");
print("--------------------------------------------");
print("* Don't make space between commands");
print("* Programed by Ha Yujin ❁´◡`❁");
print("====================================");


while True:
    answer = input(">> ") #command 입력받음
    long = len(answer)

    i = 0
    
    while i < long: 

        if answer[i] == '+': 
            if start == 0: 
                mylist = LinkedList(answer[i+1])
            else:
                if i==0:
                    mylist.add(answer[i+1])
                    i += 1
                else:
                    mylist.addTail(answer[i+1])
                    i += 1


        elif answer[i] == '-': #current point의 원소를 삭제하고 싶을 때
            if mylist.current==long-1:
                mylist.current=0
            mylist.delete()

        elif answer[i] == 'L': 
            break

        elif answer[i] == 'G': 
            if (start): 
                print("  return:  {0}".format(mylist.get_data()))
            else: 
                print("  empty list\n")

        elif answer[i] == '<': 
            mylist.traverse_first()
            if long > 2:
                if answer[i+2] == '+': #가장 앞에 원소를 추가할 때
                    mylist.add(answer[i+3])
                    i += 3

        elif answer[i] == '>': #current point를 가장 뒤로 옮기고 싶을 때
            mylist.traverse_last()

        elif answer[i] == 'N': #current point를 한칸 뒤로 옮기고 싶을 때
            mylist.traverse_next()

        elif answer[i] == 'P': #current point를 한칸 앞으로 옮기고 싶을 때
            mylist.traverse_prev()

        elif answer[i] == '=': #current point의 원소를 다른 원소로 replace 하고 싶을 때
            mylist.replace(answer[i+1])
            i += 1

        elif is_number(answer[i]): #입력받은 숫자번째로 current point를 변경하고 싶을 때
            mylist.current =  int(answer[i]) - 1

        elif answer[i] == '#': 
            print("  {0}\n".format(mylist.data_count()))        

        elif answer[i] == '?': #해당 원소가 linked list 안에 있는지 확인하고 싶을 때
            mem = mylist.is_member(answer[i+1])

            if mem == -1: #해당 원소를 찾지 못했을 때
                print("  {0} is not member\n".format(answer[i+1]))

            else: #해당 원소를 찾았을 때
                print("  return: {0}\n".format(mem+1))

            i += 1

        elif answer[i] == 'C': #linked list의 모든 원소들을 삭제하고 싶을 때
            mylist.clear()
            start = 0

        elif answer[i] == 'E': #linked list가 비어 있는지 확인하고 싶을 때
            if mylist.is_empty():
                print("  TRUE\n")

            else:
                print("  FALSE\n")

        elif answer[i] == 'M':
            if answer[i+1] == 'n':
                mylist.move_end()
            elif answer[i+1] == 'f':
                mylist.move_first()


        elif answer[i] == 'U': #current point의 원소를 대문자면 소문자로, 소문자면 대문자로 바꾸고 싶을 때
            mylist.letter_change()

        i += 1

    if (start): 
        print(mylist)
    else:
        print('  empty list\n')
