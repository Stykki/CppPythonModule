
import msvcrt
import sys
import cpp_module_01

N, S, E, W = 1, 2, 4, 8

PD = {
        "N": ( -1, 0),
        "W": ( 0, -1),
        "S": ( 1, 0),
        "E": ( 0, 1),
        }

VM = {
        "N" : 1,
        "S" : 2,
        "E" : 4,
        "W" : 8
        }


NS = N+S
NE = N+E
NW = N+W

SE = S+E
SW = S+W

EW = E+W

NSW = N+S+W
NSE = N+S+E


SNEW = S+N+E+W


DISPMAP = {

        0: "━━━━━",

        N: "┃   ┃-┃ - ┃-┗━━━┛",

        W: "┏━━━━-┃ -  -┗━━━━",

        S: "┏━━━┓-┃ - ┃-┃   ┃",

        E: "━━━━┓-  - ┃-━━━━┛",

        NS: "┃   ┃-┃ - ┃-┃   ┃",

        NW: "┃    -┃ -  -┗━━━━",

        NE: "    ┃-  - ┃-━━━━┛",

        EW: "━━━━━-  -  -━━━━━",

        SW: "┏━━━━-┃ -  -┃    ",

        NSW: "┃    -┃ -  -┃    ",

        SE: "━━━━┓-  - ┃-    ┃",

        NSE: "    ┃- -  ┃-    ┃",

        
        SNEW:"     -  -  -     ",

        }


class Game():
    
    def __init__(self, grid):
        self.grid = grid
        self.playerX = 0
        self.playerY = 0
        self.goalX = len(grid)-1
        self.goalY = len(grid[0])-1
        self.path =[[0]*4]*4


    def displayGrid(self):
        
        line1 = ""
        line2 = ""
        line3 = ""
        for x in range(len(self.grid)):
            for y in range(len(self.grid[0])):
                line1 += DISPMAP[self.grid[x][y]].split("-")[0]
                line2 += DISPMAP[self.grid[x][y]].split("-")[1]
                if(self.playerY == y and self.playerX == x):
                    line2 += "P"
                elif(self.goalY== y and self.goalX== x):
                    line2 += "G"
                else:
                    line2 += " "
                line2 += DISPMAP[self.grid[x][y]].split("-")[2]
                line3 += DISPMAP[self.grid[x][y]].split("-")[3]
            print(line1)
            print(line2)
            print(line3)
            line1, line2, line3 = "", "", ""

    def makeMove(self):
        nx,ny =-1,-1
        while(not(self.moveIsValid(nx,ny))):
            validMoves = []
            if ( self.grid[self.playerX][self.playerY] & N != 0):
                validMoves.append("N")

            if ( self.grid[self.playerX][self.playerY] & S != 0):
                validMoves.append("S")

            if ( self.grid[self.playerX][self.playerY] & E != 0):
                validMoves.append("W")

            if ( self.grid[self.playerX][self.playerY] & W != 0):
                validMoves.append("E")

            print(validMoves)
            inp = msvcrt.getch().decode("utf-8").upper()
            if (inp.upper() in validMoves):
                nx = self.playerX + PD[inp][0]
                ny = self.playerY + PD[inp][1]


        self.playerX = nx
        self.playerY = ny


    def moveIsValid(self, nx, ny):
        if (nx >= 0 and nx < len(self.grid) and ny >= 0 and ny < len(self.grid[0])):
            return 1
        return 0

    def play(self):
        while(True):
            self.displayGrid()
            self.makeMove()
            if(self.playerX == self.goalX and self.playerY == self.goalY):
                print("============== WINNER =================")
                self.displayGrid()
                break


# print(cpp_module_01.generateKruskals(40, 20, 0))
# print(cpp_module_01.generatePrims(40, 20, 0))
# print(cpp_module_01.generateRecursiveBacktrack(40, 20, 0))

lis = cpp_module_01.generateKruskals(4,4,0)
print(lis)
d = Game(lis)
d.play()



