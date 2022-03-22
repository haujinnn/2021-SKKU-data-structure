print('==============❤MENU❤==============')
print("INSERT                                       : +(data)")
print("DELET                                        : -")
print("TRAVERSE_FRONT                     : <")
print("TRAVERSE_REAR                       : >")
print("GET_DATA                                  : @")
print("REPLACE                                    : =(data)")
print("EMPTY                                        : E")
print("MOVE                                         : M(position)")
print("MOVE END                                 : Mn");
print("MOVE PREV                                : MP")
print("MOVE NEXT                                : MN")
print("PRINT                                         : L")
print("LETTER_CHANGE                       : C")
print("FIND                                           : F(data)")
print("BACKWARDS                              : B")
print("PROGRAM_END                         : P")
print("--------------------------------------------")
print("* Don't make space between commands")
print("* Programed by Ha Yujin ❁´◡`❁")
print("====================================")


cp = -1
size=0
my_array = [ ]
arr= [ ]

def insert(arr, data): #arr[]에 data를 순서대로 넣는 함수
    if cp!=size:
        arr.insert(cp+1, data)
    else:
        arr.append(data)

def delete(arr): #current point의 문자 삭제
    global size
    del arr[cp]
    size-=1

def traverse_front(arr, count): #배열의 처음부터 시작해서 N 만큼 오른쪽으로 이동
    global cp
    cp=count

def traverse_rear(arr,count): #배열의 맨 뒤부터 시작해서 P 만큼 왼쪽으로 이동
    global cp
    cp=count

def get_data(arr): #current point의 문자 출력
    global cp
    print("return: ", arr[cp])

def replace(arr,new_data): #current point의 문자를 data로 바꿈
    global cp
    arr[cp] = new_data

def empty(arr): #배열에 있는 원소를 모두 삭제
    del arr[:]

def move(arr, new_position):#current point의 문자를 입력한 new_position 위치로 이동
    global cp
    cnt=arr[cp]
    if new_position > cp:
        for i in range(cp, new_position, 1):
            arr[i]=arr[i+1]
    else:
        for i in range(cp, new_position, -1):
            arr[i]=arr[i-1]
    arr[new_position]=cnt
    cp=new_position

def data_count(arr, data): #current point의 문자를 맨뒤로, 앞으로, 뒤로 이동
    global cp
    global size
    cnt=arr[cp]
    if data == 'n':
        del arr[cp]
        arr.append(cnt)
        cp=size-1
    elif data == 'P':
        arr[cp]=arr[cp-1]
        arr[cp-1]=cnt
        cp-=1
    elif data == 'N':
        arr[cp] = arr[cp+1]
        arr[cp+1] = cnt
        cp+=1

def letter_change(arr): #배열의 문자 대소문자 바꿔주기
    global size
    for i in range(size):
        if (arr[i].isupper()):
            arr[i]=arr[i].lower()
        elif (arr[i].islower()):
            arr[i]=arr[i].upper()
            
def find(arr, data): #배열에 있는 문자 탐색
    global size
    for i in range(size):
        if arr[i]==data:
            print("location: ", i)

def backwards(arr): #배열 순서를 반대로
    arr.reverse()

while True:
    arr=input(">> ")
    l=int(len(arr))

    if arr[0]=='+':
        for i in range(0, l, 1):
            if arr[i] == '+':
                insert(my_array, arr[i+1])
                cp+=1
    elif arr[0] == '-':
        delete(my_array)
        if (size-1<cp):
            cp=0
    elif arr[0]=='<':
        count=0
        for i in range(0, l, 1):
            if arr[i]=='N':
                count+=1
        traverse_front(my_array, count)
    elif arr[0]=='>':
        count=size-1
        for i in range(l):
            if arr[i]=='P':
                count-=1
        traverse_rear(my_array, count)
    elif arr[0] == '@':
        get_data(my_array)
    elif arr[0] == '=':
        replace(my_array,arr[1])
    elif arr[0] == 'E':
        empty(my_array)
        size=0
        cp=-1
    elif arr[0] == 'M':
        if (arr[1]=='n' or arr[1]=='P' or arr[1]=='N'):
            data_count(my_array, arr[1])
        else:
            position = int(arr[1])
            move(my_array, position)
    elif arr[0] == 'L':
        size = int(len(my_array))
        for i in range(0, size, 1):
            if i==cp:
                print("(",my_array[i],")", end=' ')
            else:
                print(my_array[i], end=' ')
        if size==0:
            print("empty array", end=' ')
        print(" ")
    elif arr[0] == 'C':
        letter_change(my_array)
    elif arr[0] == 'F':
        find(my_array, arr[1])
    elif arr[0] == 'B':
        backwards(my_array)
    elif arr[0] == 'P':
        print('프로그램을 종료합니다.\n')
        break
        
    size = int(len(my_array))
    for i in range(0, size, 1):
        if i==cp:
            print("(",my_array[i],")", end=' ')
        else:
            print(my_array[i], end=' ')
    if size==0:
        print("empty array", end=' ')
    print(" ")
