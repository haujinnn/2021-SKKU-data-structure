#2020313241 하유진
#9주차 Binary Search Tree ADT Proragm - Python

height = 0
i = 0

print("==============♥MENU♥==============")
print("create				: +(data)")
print("insert_node			: +(data)")
print("print				: P")
print("inorder_traversal			: I")
print("right_root_left_traversal	               : R")
print("get_min				: N(data)")
print("get_max				: X")
print("find_node			: F(data)")
print("delete_node			: -(data)")
print("height				: H")
print("get_right_child			: G(data)")
print("get_left_child			: L(data)")
print("clear				: K")
print("Exit program			: Q")
print("--------------------------------------------")
print("* Don't make space between commands")
print("* Programed by Ha Yujin ")
print("====================================")

class NODE:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)

class BST:
    def __init__(self):
        self.root = None
        self.OnOff = 0 

    def create(self, data):
        new = NODE(data)
        self.root = new
        self.OnOff = 1

    def print(self, tmp):
        if tmp==None:
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
                print("Error!")
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

    def get_parent(self, search, target): 
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
        print("Root", end='')
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
        if self.OnOff == 0: #BST empty
            print("Error!")
            return -1
        target = self.find_node(data)
        if target == None:
            print("Error!")
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

        elif target.left != None and target.right == None:
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

        elif target.left == None and target.right !=None: 
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

        else: 
            heir = target.left

            while heir.right != None:
                heir = heir.right

            item = target.data
            heir_data = heir.data

            self.delete_node(heir.data)
            target.data = heir_data

        return item

    def height_of_node(self, target):
        height = 0

        while target != self.root:
            target = self.get_parent(self.root, target)
            height += 1

        return height

    def height(self, tmp):
        global height

        if tmp == None:
            return

        self.height(tmp.left)
        self.height(tmp.right)

        if self.height_of_node(tmp) > height:
            height = self.height_of_node(tmp)

    def get_right_child(self, data):
        target = self.find_node(data)
        if target == None:
            print("Error!")
            return -1
        if target.right == None:
            return -2

        return target.right.data

    def get_left_child(self, data):
        target = self.find_node(data)
        if target == None:
            print("Error!")
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
            print("Error!")
            return

        while True:
            if self.root == None:
                break

            self.delete_node(self.root.data)

    def destroy(self):
        if self.root != None:
            print("Error!")
            return 0

        del self
        return 1

def is_number(factor): 
    try:
        float(factor)
        return 1
    except ValueError:
        return 0

def StN(answer): 
    global i
    number = 0
    tmp = long - i
    for j in range(tmp):
        if is_number(answer[i]):
            number = number * 10
            number += int(answer[i])
            i += 1
    return number


answer = []
signal = 1
Mbst = BST()

while signal:
    answer = input(">> ")
    long=len(answer)

    if answer[0] == '+' and Mbst.OnOff == 0:
        i=1
        Mbst.create(StN(answer)) 
    elif answer[0] == '+' and Mbst.OnOff == 1:
        i=1
        Mbst.insert_node(StN(answer))
    elif answer[0] == 'P':
        pass
    elif answer[0] == 'I':
        Mbst.inorder_traversal(Mbst.root)
    elif answer[0] == 'R':
        Mbst.right_root_left_traversal(Mbst.root)
    elif answer[0] == 'N':
        print("{}".format(Mbst.get_min()))
    elif answer[0] == 'X':
        print("{}".format(Mbst.get_max()))
    elif answer[0] == 'F':
        i=1
        tmp = Mbst.find_node(StN(answer))
        if tmp == None:
            print("Error!")
        else:
            Mbst.find_path(tmp)
    elif answer[0] == '-':
        i=1
        tmp = Mbst.delete_node(StN(answer))
    elif answer[0] == 'H':
        tmp = StN(answer) 
        target = Mbst.find_node(tmp)
        if target == None:
            print("Error!")
            continue
        print("{}".format(Mbst.height_of_node(target)))

    elif answer[0] == 'G': #수정
        i=2
        tmp = StN(answer) #[2:4]
        rc = Mbst.get_right_child(tmp)

        if rc == -1:
            i += 1
            continue
        elif rc == -2:
            print("NULL")
        else:
            print("{}".format(rc))

    elif answer[0] == 'L': #수정
        i = 2
        tmp = StN(answer)
        lc = Mbst.get_left_child(tmp)

        if lc == -1:
            i += 1
            continue
        elif lc == -2:
            print("NULL")
        else:
            print("{}".format(lc))
    elif answer[0] == '#':
        print("{}".format(Mbst.count_node(Mbst.root)))
    elif answer[0] == 'C':
        Mbst.clear()
    elif answer[0] == 'Q': #프로그램 종료
        print("-Exit program-")
        print(" Have a nice day!")
        break
    else:
        print("Error!")

    if signal and Mbst.OnOff == 1:
        Mbst.print(Mbst.root)
    elif signal and Mbst.OnOff == 0:
        print("Empty BST")

