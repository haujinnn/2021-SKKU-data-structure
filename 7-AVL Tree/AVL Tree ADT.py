#2020313241 하유진
#10주차 AVL Tree ADT Proragm - Python

height = 0
i = 0

class NODE:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)

class AVL:
    def __init__(self):
        self.root = None
        self.OnOff = 0 #create를 할건지 insert를 할건지 구분해주는 속성

    def create(self, data):
        new = NODE(data)
        self.root = new
        self.OnOff = 1

    def print(self, tmp):
        if tmp == None:
            return
        if self.root == tmp:
            print("  (", end='')

        print("{}".format(tmp.data),end='')

        if (tmp.left != None or tmp.right !=None):
            print("(", end='')
            self.print(tmp.left)
            print(",", end='')
            self.print(tmp.right)
            print(")",end='')

        if self.root == tmp:
            print(")")

    def insert_node(self, data):
        tmp = self.root
        p_tmp =None

        while tmp != None:
            if tmp.data == data:
                print("  [Error] Data already exist\n")
                return
            p_tmp = tmp

            if data > tmp.data:
                tmp = tmp.right

            else:
                tmp = tmp.left

        new = NODE(data)

        if data > p_tmp.data:
            p_tmp.right = new
        else:
            p_tmp.left = new

        self.root = self.rebalance(self.root)

    def get_parent(self, search, target): #target이 None이 아니라는 걸 알고 사용하기
        if search == None:
            return None
        if (search.left == target or search.right == target):
            return search

        adress = self.get_parent(search.left, target)
        if adress:
            return adress
        adress = self.get_parent(search.right, target)
        if adress:
            return adress
        return None

    def inorder_traversal(self, traverse):
        if traverse == None:
            return
        if self.root == traverse:
            print("  ", end='')

        self.inorder_traversal(traverse.left)
        print("{} ".format(traverse.data), end='')
        self.inorder_traversal(traverse.right)

        if self.root == traverse:
            print("\n")

    def right_root_left_traversal(self, traverse):
        if traverse == None:
            return
        if self.root == traverse:
            print("  ", end='')

        self.right_root_left_traversal(traverse.right)
        print("{} ".format(traverse.data), end='')
        self.right_root_left_traversal((traverse.left))

        if self.root == traverse:
            print("\n")

    def get_min(self):
        tmp = self.root
        while tmp.left != None:
            tmp = tmp.left
        return tmp.data

    def get_max(self):
        tmp = self.root
        while tmp.right != None:
            tmp = tmp.right

        return tmp.data

    def find_node(self, data):
        tmp = self.root
        while tmp != None:
            if data == tmp.data:
                return tmp
            elif data > tmp.data:
                tmp = tmp.right
            else:
                tmp = tmp.left

        return tmp

    def find_path(self, target):
        print("  Root", end='')
        tmp = self.root

        while tmp.data != target.data:
            if target.data > tmp.data:
                print(" > Right", end='')
                tmp = tmp.right
            else:
                print(" > Left", end='')
                tmp = tmp.left

        print("\n")

    def delete_node(self, data):
        if self.OnOff == 0: #AVL empty
            print("  [Error] Nothing to delete\n")
            return -1
        target = self.find_node(data)
        if target == None:
            print("  [Error] Can't find target\n")
            return -1

        if target.left == None and target.right == None: #자식노드가 아예 없을 때
            if target == self.root:
                item = target.data
                del target
                self.root = None
                self.OnOff = 0

            else:
                p_target = self.get_parent(self.root, target)

                if p_target.right == target:
                    p_target.right = target.left
                    item = target.data
                    del target

                else:
                    p_target.left = target.left
                    item = target.data
                    del target

        elif target.left != None and target.right == None: #왼쪽에만 자식이 있을 때
            if target == self.root:
                self.root = target.left
                item = target.data
                del(target)

            else:
                p_target = self.get_parent(self.root, target)

                if p_target.right == target:
                    p_target.right = target.left
                    item = target.data
                    del target

                else:
                    p_target.left = target.left
                    item = target.data
                    del target

        elif target.left == None and target.right !=None: #오른쪽에만 자식이 있을 때
            if target == self.root:
                self.root = target.right
                item = target.data
                del target

            else:
                p_target = self.get_parent(self.root, target)

                if p_target.right == target:
                    p_target.right = target.right
                    item = target.data
                    del target

                else:
                    p_target.left = target.right
                    item = target.data
                    del target

        else: #자식 노드가 2개일 때, (*) balance factor에 따라 left most / right most 값을 후계자 노드로 지정
            heir = target

            if self.balance_factor(target) >= 0:
                heir = target.left

                while heir.right != None:
                    heir = heir.right

            else:
                heir = target.right
                while heir.left != None:
                    heir = heir.left

            item = target.data
            heir_data = heir.data

            self.delete_node(heir.data)
            target.data = heir_data

        self.root = self.rebalance(self.root)
        return item

    def height_of_node(self, root, target):
        height = 0

        while target != root:
            target = self.get_parent(root, target)
            height += 1

        return height

    def height(self, root, tmp):
        global height

        if tmp == None:
            return

        self.height(root, tmp.left)
        self.height(root, tmp.right)

        if self.height_of_node(root, tmp) > height:
            height = self.height_of_node(root, tmp)

    def get_right_child(self, data):
        target = self.find_node(data)
        if target == None:
            print("  [Error] Can't find target\n")
            return -1
        if target.right == None:
            return -2

        return target.right.data

    def get_left_child(self, data):
        target = self.find_node(data)
        if target == None:
            print("  [Error] Can't find target\n")
            return -1
        if target.left == None:
            return -2

        return target.left.data

    def count_node(self, tmp):
        if tmp == None:
            return 0

        return self.count_node(tmp.left) + self.count_node(tmp.right) + 1

    def clear(self):
        if self.root == None:
            print("  [Error] Already Empty\n")
            return

        while True:
            if self.root == None:
                print("  Clear finished\n")
                break

            self.delete_node(self.root.data)

    def destroy(self):
        if self.root != None:
            print("  [Error] Please clear AVL first\n")
            return 0

        del self
        return 1

    def right_rotate(self, root):
        parent = root
        child = parent.left

        parent.left = child.right
        child.right = parent

        return child

    def left_rotate(self, root):
        parent = root
        child = parent.right

        parent.right = child.left
        child.left = parent

        return child

    def LR_rotate(self, root):
        parent = root
        child = parent.left

        parent.left = self.left_rotate(child)

        return self.right_rotate(parent)

    def RL_rotate(self, root):
        parent = root
        child = parent.right

        parent.right = self.right_rotate(child)

        return self.left_rotate(parent)

    def balance_factor(self, root):
        global height

        height = -1
        self.height(root.left, root.left)
        left_height = height

        height = -1
        self.height(root.right, root.right)
        right_height = height

        return (left_height - right_height)

    def rebalance(self, root):
        if root == None:
            return None
        root.left = self.rebalance(root.left)
        root.right = self.rebalance(root.right)

        bf = self.balance_factor(root)

        if -1 <= bf and bf <= 1:
            return root

        if bf >= 2:
            if self.balance_factor(root.left) >= 1:
                root = self.right_rotate(root)
                print("  Right Rotate is Done\n")

            else:
                root = self.LR_rotate(root)
                print("  LR Rotate is Done\n")

        if bf <= -2:
            if self.balance_factor(root.right) <= -1:
                root = self.left_rotate(root)
                print("  Left Rotate is Done\n")

            else:
                root = self.RL_rotate(root)
                print("  RL Rotate is Done\n")

        return root


def is_number(factor):  #factor가 숫자인지 확인하는 함수
    try:
        float(factor)
        return 1
    except ValueError:
        return 0

def StN(answer): #String to Number
    global i
    number = 0
    tmp = long - i
    for j in range(tmp):
        if is_number(answer[i]):
            number = number * 10
            number += int(answer[i])
            i += 1


    return number



print("\n");
print("─────────────────────────")
print("                   C O M M A  D   M E N U                  ");
print("─────────────────────────\n")
print("  +@   : Create AVL (at first), Insert Node with Data @	                        ")
print("    P    : Print all Data of AVL	    				")
print("  B@   : Get Balance Factor of @                                                                       ")
print("    I    : Inorder Traversal (From a small number)		                        ")
print("    R    : Right Root Left Traversal (From a large number)                               ")
print("    N    : Get Minimum			    			")
print("    X    : Get Maximum		    				")
print("  F@   : Find Node with Data @ and Search Path   	                ")
print("  D@   : Delete Node with Data @				        ")
print("    H    : Get Height of AVL (Start from 0)				        ")
print("  H(@) : Get Height of Node with Data @			        ")
print("  G(@) : Get Right Child of Node with Data @ 		                ")
print("  L(@) : Get Left Child of Node with Data @  			        ")
print("    #    : Count Node                                                                                      ")
print("  ^(@)  : Get Parent of Node with Data @				        ")
print("    C    : Clear AVL                                                                                       ")
print("    Q    : Destroy AVL				    		")
print("    X    : Exit program                          \n")
print("─────────────────────────")
print("                    ** C O U T I O N **                 ");
print("─────────────────────────\n")
print("  - @ means a data in command")
print("  - The length of command must be shorter than 30			       ")
print("  - Make a space between command		    \n")
print("──────────────────────────\n")  

answer = []
signal = 1
Mavl = AVL()

while signal:
    answer = input("  >> ")
    long = len(answer)

    i = 0

    while i < long:
        if answer[i] == '+' and Mavl.OnOff == 0:
            i += 1
            Mavl.create(StN(answer))
            i -= 1
        elif answer[i] == '+' and Mavl.OnOff == 1:
            i += 1
            Mavl.insert_node(StN(answer))
            i -= 1
        elif answer[i] == 'D':
            i += 1
            tmp = Mavl.delete_node(StN(answer))
            if tmp != -1:
                print("  Deleted : {}\n".format(tmp))
            i -= 1
        elif answer[i] == 'P':
            i += 1
            continue
        elif answer[i] == 'B':
            i += 1
            num = StN(answer)
            i -= 1
            tmp = Mavl.find_node(num)
            if tmp == None:
                print("  [Error] Can't find target\n")
                i += 1
                continue
            print("  Balance Factor of {} is {}\n".format(num, Mavl.balance_factor(tmp)))
        elif answer[i] == 'I':
            Mavl.inorder_traversal(Mavl.root)
        elif answer[i] == 'R':
            Mavl.right_root_left_traversal(Mavl.root)
        elif answer[i] == 'N':
            if Mavl.OnOff:
                print("  Minimum : {}\n".format(Mavl.get_min()))
            else:
                print("  [Error] Empty AVL\n")
        elif answer[i] == 'X':
            if Mavl.OnOff:
                print("  Maximum : {}\n".format(Mavl.get_max()))
            else:
                print("  [Error] Empty AVL\n")
        elif answer[i] == 'F':
            i += 1
            tmp = Mavl.find_node(StN(answer))
            i -= 1

            if tmp == None:
                print("  [Error] Not Exist!\n")
            else:
                Mavl.find_path(tmp)

        elif answer[i] == 'H':
            if long > 1: #H(@)
                if answer[i+1] == '(':
                    i += 2
                    tmp = StN(answer)

                    target = Mavl.find_node(tmp)
                    if target == None:
                        print("  [Error] Can't find target\n")
                        i += 1
                        continue
                    print("  Height of {} is {}\n".format(tmp, Mavl.height_of_node(Mavl.root, target)))
                else:
                    print("  [Error] Check your command\n")
                    break
            else: #그냥 H
                if Mavl.OnOff == 0:
                    print("  [Error] Empty AVL\n")
                    i += 1
                    continue
                height = 0
                Mavl.height(Mavl.root, Mavl.root)
                print("  Height of AVL is {}\n".format(height))

        elif answer[i] == 'G':
            i += 2
            tmp = StN(answer)
            rc = Mavl.get_right_child(tmp)

            if rc == -1:
                i += 1
                continue
            elif rc == -2:
                print("  Right child of {} is NULL\n".format(tmp))
            else:
                print("  Right child of {} is {}\n".format(tmp, rc))

        elif answer[i] == 'L':
            i += 2
            tmp = StN(answer)
            lc = Mavl.get_left_child(tmp)

            if lc == -1:
                i += 1
                continue
            elif lc == -2:
                print("  Left child of {} is NULL\n".format(tmp))
            else:
                print("  Left child of {} is {}\n".format(tmp, lc))
        elif answer[i] == '#':
            print("  Count of node : {}\n".format(Mavl.count_node(Mavl.root)))
        elif answer[i] == 'C':
            Mavl.clear()
        elif answer[i] == 'Q':
            if(Mavl.destroy()):
                print("  System finished\n")
                signal = 0
        elif answer[i] == '^':
            i += 2
            tmp = StN(answer)
            target = Mavl.find_node(tmp)

            if target == Mavl.root:
                print("  [Error] Root has no parent\n")
            elif target == None:
                print("  [Error] Can't find target\n")
            else:
                p = Mavl.get_parent(Mavl.root, target)
                print("  Parent of {} is {}\n".format(tmp, p.data))
        elif answer[i] == 'X': #프로그램 종료
            break
        else:
            print("  Error (wrong command)")

        i += 1

    if signal and Mavl.OnOff == 1:
        Mavl.print(Mavl.root)
    elif signal and Mavl.OnOff == 0:
        print("  Empty AVL\n")

    if answer[0] == 'X': 
            print(" -Exit program-")
            print(" Have a nice day!")
            break

print("──────────────────────────")
print(" Python AVL Tree ADT Program")
print(" Programmed by 2020313241 Ha Yujin")
print("──────────────────────────\n")
