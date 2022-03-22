#2020313241 하유진
#6주차 Queue ADT Proragm - Python

class NODE: #NODE class 정의
    def __init__(self, data): #node를 생성하고 받은 data를 저장하는 스페셜 메서드
        self.data = data
        self.next = None

    def __str__(self): #node의 data 값을 출력하는 스페셜 메서드
        return str(self.data)

class Q: #Q class 정의
    def __init__(self, MAX): #빈 node를 생성하면서, queue를 생성하는 스페셜 메서드
        new = NODE(None) #빈 node를 생성
        self.head = new.next
        self.tail = new.next #tail이 빈 node의 next를 가리키도록
        self.size = 0 #현재 크기를 나타내는 속성은 0으로 초기화 
        self.max = MAX #최대 크기를 나타내는 속성에 받은 값을 대입

    def __str__(self): #queue의 모든 data들을 출력하는 스페셜 메서드
        display = '  '
        sz = self.size
        for i in range (0, sz, 1): #dequeue한 후, 출력할 문자열에 추가하고, 다시 enqueue하는 과정을 반복
            tmp = self.dequeue()
            display += "{0} ".format(tmp)
            self.enqueue(tmp)
        if self.is_empty():
            display += "empty queue\n"

        return display

    def enqueue(self, data): #queue의 tail에 data를 enqueue하는 메서드
        if self.is_full(): #가득 차있어서 enqueue할 수 없을 때
            print("  [Error] Queue is full\n")
            return
        new = NODE(data)

        if self.is_empty(): #첫 enqueue일 때 
            self.tail = new
            self.head = new
        else:
            self.tail.next = new
            self.tail = new

        self.size += 1

    def dequeue(self): #queue의 head에서 dequeue하는 메서드
        dequeue_data = self.head.data #return할 값을 미리 저장

        target = self.head
        self.head = self.head.next

        del target

        self.size += -1

        if self.size == 0: #마지막 dequeue일 때 
            self.tail = None

        return dequeue_data #dequeue한 data를 return

    def is_empty(self): #queue가 비어있는지 확인하는 메서드
        if self.size == 0:
            return 1
        else:
            return 0

    def is_full(self): #queue가 가득 차있는지 확인하는 메서드 (동적할당이므로 tail == Max_Size의 방식으로 확인하는 것과 다르게 속성을 활용해 판단) 
        if self.size == self.max:
            return 1
        else:
            return 0

    def peek(self): #head의 data를 반환하는 메서드
        return self.head.data

    def data_count(self): #queue에 들어있는 data의 개수를 반환하는 메서드 (동적할당이므로 tail-head의 방식으로 확인하는 것이 아닌 속성을 활용)
        return self.size

    def Head(self): #head의 index를 반환하는 메서드 (첫번째 data의 index를 0으로 고정하고, 상대적인 위치로 index 결정)
        return 0

    def Tail(self): #tail의 index를 반환하는 메서드
        return self.size - 1

    def is_member(self, data): #특정 data가 queue의 원소인지 확인하는 메서드
        count = 0 #현재 탐색 중인 위치를 기록할 변수
        position = -1 #만약 찾는 data와 일치하는 data를 발견하면 현재 탐색 중인 위치를 대입할 변수

        sz = self.size 

        for i in range (0, sz, 1): #data의 수만큼 dequeue한 후, 받은 data와 비교한 뒤, 다시 enqueue하는 과정을 반복
            tmp = self.dequeue()
            count += 1
            if tmp == data:
                position = count
            self.enqueue(tmp)

        return position

    def replace(self, data): #tail의 data를 다른 data로 교체하는 메서드 
        self.tail.data = data

    def clear(self): #queue의 모든 data를 dequeue하는 메서드
        sz = self.size
        for i in range (0, sz, 1): #data의 수만큼 dequeue
            self.dequeue()

    def SizeChange(self, new_size): #queue의 최대 크기를 바꾸는 메서드 
        if self.size > new_size: #만약 현재 data의 수가 바꾸려고 하는 최대 크기보다 클 경우 (과도하게 최대 크기를 줄일 경우)
            print("  [Error] Too many elements\n")
            return
        self.max = new_size

    def Twice(self): #queue의 data들을 하나씩 dequeue한 뒤, 두번씩 enqueue하면서 data를 두배로 불리는 메서드
        if self.max < ((self.size)*2): #max size의 한계로 인해 data를 2배로 늘릴 수 없을 때
            print("  [Error] not enough memory\n")
            return
        sz = self.size
        for i in range (0, sz, 1): #data를 하나씩 dequeue하며 다시 두번씩 enqueue해줌
            tmp = self.dequeue()
            self.enqueue(tmp)
            self.enqueue(tmp)

    def MaxEnqueue(self, data): #queue가 full한 상태가 될 때까지 특정 data를 enqueue하는 메서드
        if self.is_full(): #이미 가득 차있으면
            print("  [Error] already full\n")
            return
        count = self.max - self.size
        for i in range (0, count, 1): #가득 찰 때까지
            self.enqueue(data) #받은 data를 enqueue

def is_number(factor): #factor가 숫자인지 확인하는 함수
    try:
        float(factor)
        return 1
    except ValueError:
        return 0

print("\n");
print("─────────────────────────")
print("                   C O M M A  D   M E N U                  ");
print("─────────────────────────\n")
print("  +  : Enqueue                                                               ")
print("  -  : Dequeue                                                                   ")
print("  L  : Print all elements                                                               ")
print("  P  : Peek head data                                                    ")
print("  F  : Stack is full or not                                                ")
print("  E  : Stack is empty of not")
print("  #  : Element count                                      	")
print("  H  : Print index of head")
print("  T  : Print index of tail		")
print(" n- : Pop n elements          	")
print("  ?  : Data is member of stack or not         ")
print("  =  : Replace top data	                                      ")
print("  C  : Clear                                     ")
print("  X  : Exit program                          \n")
print("─────────────────────────")
print("                  N E W   F U N C T I O N S		    ")
print("─────────────────────────\n")
print("  Sn  : Change size of queue to n 			    ")
print(" *@ : Push data until stack is full		    ")
print("  D  : Double the datas			\n")
print("──────────────────────────")
print("  **Countion**                                   ")
print("  n is integer in command")
print("  @ means a data in command")
print("  Max size of queue is 10		")
print("──────────────────────────\n")  
        
answer = []
MAX = 10
my_queue = Q(MAX) #create(my_queue)

while True:
    answer = input("  >> ") #command 입력받음
    long = len(answer) 

    i = 0

    while i < long: #command가 남지 않을 때까지 반복
        if answer[i] == '+': #enqueue할 때
            my_queue.enqueue(answer[i+1])
            i += 1
        elif answer[i] == '-': #dequeue할 때
            if (my_queue.is_empty()): #dequeue할 data가 없으면 
                print("  Error (Nothing to dequeue)")
            else: #있으면 dequeue 실행
                print("  return: {0}".format(my_queue.dequeue()))
                
        elif answer[i] == 'L': #queue을 출력할 때
            break
        
        elif answer[i] == 'P': #queue의 head에 있는 data 값을 알고 싶을 때  
            if (my_queue.is_empty()): #peek할 data가 없으면 
                print("  Error (Nothing to peek)\n")
            else: #있으면 head가 가리키는 data를 출력
                print("  {0}".format(my_queue.peek()))
                
        elif answer[i] == 'F': #queue가 가득 차있는지 알고싶을 때
            if (my_queue.is_full()): #queue가 가득 차있으면 
                print("  TRUE") 
            else: #queue가 가득 차있지 않으면 
                print("  FALSE")

        elif answer[i] == 'E': #queue가 비어있는지 알고싶을 때
            if (my_queue.is_empty()):
                print("  TRUE")
            else:
                print("  FALSE")
                
        elif answer[i] == '#': #queue에 들어있는 data의 개수를 알고싶을 때
            print("  Count data: {0}".format(my_queue.data_count()))

        elif answer[i] == 'H': #head의 index를 알고싶을 때
            if my_queue.Head() == None: #head가 가리키는 곳이 없으면
                print("  Error (Nothing on head)")
            else:
                print("  Head: {0}".format(my_queue.Head()))

        elif answer[i] == 'T':  #tail의 index를 알고싶을 때 
            if my_queue.Tail() == None: #tail이 가리키는 곳이 없으면
                print("  Error (nothing on tail)")
            else:
                print("  Tail: {0}".format(my_queue.Tail()))

        elif is_number(answer[i]): #반복해서 dequeue를 하고 싶을 때
            for j in range (0, int(answer[i]), 1): #입력받은 숫자만큼 반복
                    if (my_queue.is_empty()): #queue가 비어있을 때
                        print("  Error (nothing to dequeue)")
                    else: #queue가 비어있지 않을 때
                        print("  return: {0}".format(my_queue.dequeue()))
                    i += 1
            
        elif answer[i] == '?': #특정 data가 queue의 원소인지 확인하고 싶을 때
            pos = my_queue.is_member(answer[i+1])
            if (pos == -1): #member가 아니면
                print("  -1 (Not in queue)")
            else: #member에 해당하면 
                print("  {0} (Position of member)".format(pos))
            i += 1

        elif answer[i] == '=': #tail의 data를 특정 data로 교체하고 싶을 때
            if (my_queue.is_empty()): #queue가 비어있으면
                print("  Error (No element to replace)")
            else: #queue가 비어있지 않으면
                my_queue.replace(answer[i+1])
                i += 1

        elif answer[i] == 'C': #queue를 비우고 싶을 때
            my_queue.clear()

        elif answer[i] == 'S': #queue의 최대 크기를 바꾸고 싶을 때
            my_queue.SizeChange(int(answer[i+1]))
            i += 1

        elif answer[i] == 'D': #queue의 모든 data들을 두배로 불리고 싶을 때
            my_queue.Twice()
            
        elif answer[i] == '*': #queue가 full해질 때까지 특정 data를 enqueue하고 싶을 때 
            my_queue.MaxEnqueue(answer[i+1])
            i += 1
                         
        elif answer[i] == 'X': #프로그램 종료
            break

        else:
            print("  Error (wrong command)")
                         
        i+= 1

    print(my_queue) #command를 처리할 때마다 결과를 출력
    if answer[0] == 'X': 
            print(" -Exit program-")
            print(" Have a nice day!")
            break

print("──────────────────────────")
print(" Python Queue ADT Program")
print(" Programmed by 2020313241 Ha Yujin")
print("──────────────────────────\n")
