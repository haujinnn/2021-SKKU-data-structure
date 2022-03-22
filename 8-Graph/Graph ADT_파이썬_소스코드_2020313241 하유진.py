#2020313241 하유진
#11주차 Graph ADT Proragm - Python

class VERTEX:
    def __init__(self, data):
        self.next = None
        self.data = data
        self.visited = 0
        self.connect = None
        self.count_edge = 0

class EDGE:
    def __init__(self, vertex):
        self.vertex = vertex
        self.more = None

class GRAPH:
    def __init__(self):
        self.head = None
        self.count_vertex = 0

    def print(self):
        tmp = self.head
        print("  (", end='')

        while tmp:
            print("{}".format(tmp.data), end='')

            tmp2 = tmp.connect
            while tmp2:
                if tmp2 == tmp.connect:
                    print("(", end='')
                print("{}".format(tmp2.vertex.data), end='')

                if tmp2.more != None:
                    print(",", end='')
                tmp2 = tmp2.more
                if tmp2 == None:
                    print(")", end='')

            if tmp.next != None:
                print(", ", end='')
            tmp = tmp.next
        print(")\n")

    def insert_vertex(self, data):
        if self.is_empty() == 0 and self.is_exist_vertex(data):
            print("  [Error] Already Exist Data")
            return

        new = VERTEX(data)

        if self.is_empty() == 1:
            self.head = new
        else:
            target = self.head

            while target.next != None:
                target = target.next
            target.next = new

        self.count_vertex += 1

    def is_exist_vertex(self, data):
        tmp = self.head

        while True:
            if tmp == None:
                return 0
            if tmp.data == data:
                return 1
            tmp = tmp.next

    def is_exist_edge(self, data1, data2):
        tmp = self.search_vertex(data1)
        tmp2 = tmp.connect

        while True:
            if tmp2 == None:
                return 0
            if tmp2.vertex.data == data2:
                return 1
            tmp2 = tmp2.more

    def add_edge(self, data1, data2):
        if self.is_exist_vertex(data1) == 0 or self.is_exist_vertex(data2) == 0:
            print("  [Error] Vertex doesn't Exist\n")
            return
        if self.is_exist_edge(data1, data2) == 1:
            print("  [Error] Edge already Exist\n")
            return

        target1 = self.search_vertex(data1)
        target2 = self.search_vertex(data2)

        new1 = EDGE(target2)

        if target1.connect == None:
            target1.connect = new1
        else:
            target3 = target1.connect

            while target3.more != None:
                target3 = target3.more

            target3.more = new1
        target1.count_edge += 1

        new2 = EDGE(target1)

        if target2.connect == None:
            target2.connect = new2

        else:
            target4 = target2.connect

            while target4.more != None:
                target4 = target4.more

            target4.more = new2
        target2.count_edge += 1

    def search_vertex(self, data):
        if self.is_exist_vertex(data) == 0:
            print("  [Error] Vertex doesn't Exist\n")
            return None
        result = self.head

        while True:
            if result.data == data:
                return result
            result = result.next

    def degree_of_vertex(self, data):
        tmp = self.search_vertex(data)

        if tmp == None:
            return -1
        else:
            return tmp.count_edge

    def is_connected(self):
        tmp = self.head

        while tmp:
            if tmp.count_edge == 0:
                return 0
            tmp = tmp.next

        return 1

    def is_empty(self):
        if self.head == None:
            return 1
        else:
            return 0

    def adjacent(self, data):

        target = self.search_vertex(data)
        if target == None:
            return
        tmp = target.connect

        print("  {", end='')
        while True:
            if tmp == None:
                break
            print("{}".format(tmp.vertex.data), end='')

            if tmp.more != None:
                print(", ",end='')
            tmp = tmp.more

        print("}\n")

    def delete_vertex(self, data):
        target = self.search_vertex(data)
        if target == None:
            return
        if target.connect == None:
            if self.head == target:
                self.head = self.head.next
                del target
            else:
                tmp = self.head
                while tmp.next != target:
                    tmp = tmp.next
                tmp.next = tmp.next.next
                del target
        else:
            A = int(input("  해당 정점이 간선으로 연결되어 있음, 1. 삭제  2. 명령 취소\n  : "))

            if A == 2:
                return
            else:
                dt = target.connect

                e_target = target.connect
                v_target = None
                e_v_target = None

                d_e_v_target = None
                d_e_target = None

                while e_target:
                    v_target = self.search_vertex(e_target.vertex.data)
                    e_v_target = v_target.connect

                    if e_v_target.vertex.data == target.data:
                        d_e_v_target = e_v_target
                        v_target.connect = v_target.connect.more
                    else:
                        while e_v_target.more.vertex.data != target.data:
                            e_v_target = e_v_target.more
                        d_e_v_target = e_v_target.more
                        e_v_target.more = e_v_target.more.more

                    v_target.count_edge -= 1
                    del d_e_v_target

                    d_e_target = e_target
                    target.connect = target.connect.more
                    e_target = target.connect

                    target.count_edge -= 1
                    del d_e_target

                if self.head == target:
                    self.head = self.head.next
                    del target
                else:
                    tmp = self.head
                    while tmp.next != target:
                        tmp = tmp.next
                    tmp.next = tmp.next.next
                    del target

        self.count_vertex -= 1

    def path_exist(self, d1, d2):
        if d1 == d2:
            return 1
        tmp = d1.connect
        d1.visited = 1

        while tmp:
            if tmp.vertex.visited == 0:
                if self.path_exist(tmp.vertex, d2):
                    return 1
            tmp = tmp.more

        return 0

    def visited_initialize(self):
        tmp = self.head

        for i in range(0, self.count_vertex, 1):
            tmp.visited = 0
            tmp = tmp.next

    def find_path_1(self, d1, d2, back):

        if d1 == d2:
            return 1

        tmp = d1.connect
        d1.visited = 1

        while tmp:
            if tmp.vertex.visited == 0:
                back[ord(tmp.vertex.data)-ord('A')] = d1.data
                if self.find_path_1(tmp.vertex, d2, back):
                    return 1
            tmp = tmp.more

        return 0

    def find_path_2(self, d1, d2):
        back = [None]*100
        path = [None]*100

        self.find_path_1(d1, d2, back)

        end = d2.data
        start = d1.data
        i = 0

        while end != start:
            path[i] = back[ord(end)-ord('A')]
            end = back[ord(end)-ord('A')]
            i += 1

        print("  Path: ", end='')
        j = i - 1

        while j > -1:
            print("{} -> ".format(path[j]), end='')
            j -= 1

        print("{}\n".format(d2.data), end='')

    def num_of_vertex(self):
        return self.count_vertex

    def num_of_edge(self):
        count = 0

        tmp = self.head

        for i in range(0, self.num_of_vertex(), 1):
            count += tmp.count_edge
            tmp = tmp.next

        return int(count/2)

    def delete_edge(self, data1, data2):
        target1 = self.search_vertex(data1)
        target2 = self.search_vertex(data2)

        if target1 == None or target2 == None:
            return

        if self.is_exist_edge(data1, data2) == 0:
            print("  [Error] Edge already Not Exist\n")
            return

        tmp1 = target1.connect
        del1 = None

        if tmp1.vertex.data == data2:
            del1 = tmp1
            target1.connect = target1.connect.more
        else:
            while tmp1.more.vertex.data != data2:
                tmp1 = tmp1.more
            del1 = tmp1.more
            tmp1.more = tmp1.more.more

        target1.count_edge -= 1
        del del1

        tmp2 = target2.connect
        del2 = None

        if tmp2.vertex.data == data1:
            del2 = tmp2
            target2.connect = target2.connect.more

        else:
            while tmp2.more.vertex.data != data1:
                tm2 = tmp2.more
            del2 = tmp2.more
            tmp2.more = tmp2.more.more

        target2.count_edge -= 1
        del del2

    def rename_vertex(self, old, new):
        target_v = self.search_vertex(old)
        if target_v == None:
            return
        if self.is_exist_vertex(new):
            print("  [Error] New Data already Exist\n")
            return

        target_v.data = new

        target_e = target_v.connect
        search = None

        while target_e:
            search = target_e.vertex.connect
            while search:
                if search.vertex.data == old:
                    search.vertex.data = new
                search = search.more
            target_e = target_e.more

    def clear(self):
        if self.is_empty() == 1:
            print("  [Error] Already Empty\n")
            return
        while self.is_empty() == 0:
            self.delete_vertex_for_clear(self.head.data)
        print("  Clear Finished\n")

    def delete_vertex_for_clear(self, data):
        target = self.search_vertex(data)
        if target == None:
            return
        if target.connect == None:
            if self.head == target:
                self.head = self.head.next
                del target
            else:
                tmp = self.head
                while tmp.next != target:
                    tmp = tmp.next
                tmp.next = tmp.next.next
                del target
        else:
            e_target = target.connect
            v_target = None
            e_v_target = None

            d_e_v_target = None
            d_e_target = None

            while e_target:
                v_target = self.search_vertex(e_target.vertex.data)
                e_v_target = v_target.connect

                if e_v_target.vertex.data == target.data:
                    d_e_v_target = e_v_target
                    v_target.connect = v_target.connect.more
                else:
                    while e_v_target.more.vertex.data != target.data:
                        e_v_target = e_v_target.more
                    d_e_v_target = e_v_target.more
                    e_v_target.more = e_v_target.more.more

                v_target.count_edge -= 1
                del d_e_v_target

                d_e_target = e_target
                target.connect = target.connect.more
                e_target = target.connect

                target.count_edge -= 1
                del d_e_target

            if self.head == target:
                self.head = self.head.next
                del target
            else:
                tmp = self.head
                while tmp.next != target:
                    tmp = tmp.next
                tmp.next = tmp.next.next
                del target

        self.count_vertex -= 1

    def destroy(self):
        if self.is_empty() == 0:
            print("  [Error] Please clear GRAPH first")
            return 0

        del self
        return 1


print("\n");
print("===========================================")
print("  Python Graph ADT Program")
print("  Programmed by 2020313241 Ha Yujin")
print("===========================================\n")
print("                         >> M E N U <<               ");
print("─────────────────────────")
print("     G     : Create Graph			")
print("   +@    : Insert Vertex with Data @                          ")
print("  E(A,B) : Add Edge which connects Vertices A and B		")
print("     L     : Print all Data of Graph				    	")
print("   V(@)  : Get Degree of Vertex @	    			")
print("     C     : Check Graph is Connected	    		")
print("     N     : Check Graph is Empty		    		")
print("   A(@)  : Print Adjacent of Vertex @	    		")
print("    -@    : Delete Vertex @					")
print("  P(A,B) : Check Existence of Path from Vertex A to B		")
print("     X     : Get Num of Vertex                                  ")
print("     H     : Get Num of Edge                                    ")
print("  D(A,B) : Delete Edge which connects Vertices A and B  		")
print("  R(A,Z) : Rename Vertex A to Z			    	")
print("    ?@    : * Check Graph has Vertex @                         ")
print("     K     : Clear Graph                                        ")
print("     Q     : * Destroy Graph and Quit			")
print("     X      : Exit program                          \n")
print("===========================================\n")
print("                    ** C O U T I O N **                 ");
print("─────────────────────────")
print("  @ means a data in menu")
print("  The length of command must be shorter than 40	")
print("  Make a space between commands    ")
print("  Create Graph by command 'G' first\n")
print("===========================================\n")  


answer = []
signal = 1
MG = GRAPH()

while signal:
    answer = input("  >> ")
    long = len(answer)

    i = 0

    while i < long:
        if answer[i] == 'G':
            MG.head = None
            MG.count_vertex = 0
        elif answer[i] == '+':
            i += 1
            MG.insert_vertex(answer[i])
        elif answer[i] == 'E':
            MG.add_edge(answer[i+2], answer[i+4])
            i += 5
        elif answer[i] == 'L':
            i += 1
            continue
        elif answer[i] == 'V':
            degree = MG.degree_of_vertex(answer[i+2])
            if degree >= 0:
                print("  {}\n".format(degree))
            i += 3

        elif answer[i] == 'C':
            if MG.is_connected() == 1:
                print("  True")
            else:
                print("  False")

        elif answer[i] == 'N':
            if MG.is_empty():
                print("  True")
            else:
                print("  False")

        elif answer[i] == 'A':
            MG.adjacent(answer[i+2])
            i += 3

        elif answer[i] == '-':
            MG.delete_vertex((answer[i+1]))
            i += 1

        elif answer[i] == 'P':
            d1 = MG.search_vertex((answer[i+2]))
            d2 = MG.search_vertex((answer[i+4]))
            if d1 == None or d2 == None:
                i += 6
                continue
            if MG.path_exist(d1, d2):
                print("  Path from {} to {} Exist\n".format(d1.data, d2.data))
                MG.visited_initialize()
                MG.find_path_2(d1, d2)
            else:
                print("  Path from {} to {} Not Exist\n".format(d1.data, d2.data))
            i += 5
            MG.visited_initialize()

        elif answer[i] == 'X':
            print("  Num of Vertex: {}\n".format(MG.num_of_vertex()))

        elif answer[i] == 'H':
            print("  Num of Edge: {}\n".format(MG.num_of_edge()))

        elif answer[i] == 'D':
            MG.delete_edge(answer[i+2], answer[i+4])
            i += 5

        elif answer[i] == 'R':
            MG.rename_vertex(answer[i+2], answer[i+4])
            i += 5

        elif answer[i] == 'K':
            MG.clear()

        elif answer[i] == 'Q':
            if MG.destroy():
                print("  System finished\n")
                signal = 0

        elif answer[i] == '?':
            YN = MG.is_exist_vertex(answer[i+1])
            if YN:
                print("  {} Exist in Graph\n".format(answer[i+1]))
            else:
                print("  {} Not Exist in Graph\n".format(answer[i+1]))
            i += 1

        elif answer[i] == 'X': #프로그램 종료
            break

        else:
            print("  Error (wrong command)")

        i += 1

    if signal:
        MG.print()
