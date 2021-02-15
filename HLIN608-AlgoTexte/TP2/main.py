def calculMatrice(mode, x, m, y, n, dell, ins, sub):
    # T = [[n + 1], [m + 1]]
    T = [0] * (n + 1)
    for z in range(n + 1):
        T[z] = [0] * (m + 1)

    T[0][0] = 0
    T[-1][-1] = -1
    for a in range(1, m + 1):
        T[0][a] = T[0][a - 1] + ins(x)
        # print(str(T[0][a]) + " " + str(a) + " = " + str(T[0][a - 1]) + " + " + str(ins(x[a])))

    for k in range(1, n + 1):
        T[k][0] = T[k - 1][0] + ins(y)

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if mode == "d":
                # print("Pour i=" + str(i) + " et j=" + str(j))
                # print("    " + str(T[i - 1][j - 1]) + " + " + str(sub(x[j-1], y[i-1])))
                # print("    " + str(T[i - 1][j]) + " + " + str(dell(x[j-1])))
                # print("    " + str(T[i][j - 1]) + " + " + str(ins(y[i-1])))

                T[i][j] = min(T[i - 1][j - 1] + sub(x[j - 1], y[i - 1]),
                              T[i - 1][j] + dell(x[j - 1]),
                              T[i][j - 1] + ins(y[i - 1]))
            if mode == "s":
                # print("Pour i=" + str(i) + " et j=" + str(j))
                # print("    " + str(T[i - 1][j - 1]) + " + " + str(sub(x[j-1], y[i-1])))
                # print("    " + str(T[i - 1][j]) + " + " + str(dell(x[j-1])))
                # print("    " + str(T[i][j - 1]) + " + " + str(ins(y[i-1])))

                T[i][j] = max(T[i - 1][j - 1] + sub(x[j - 1], y[i - 1]),
                              T[i - 1][j] + dell(x[j - 1]),
                              T[i][j - 1] + ins(y[i - 1]),
                              0)

    printTab2d(T)
    print("---------------")
    return T


def lesAlignements(x, m, y, n, tab, dell, ins, sub):
    la(n, m, ["", ""], tab, dell, ins, sub, x, y)


def lesAlignementsLocal(x, m, y, n, tab, dell, ins, sub):
    nMax = -1
    mMax = -1
    maxi = -1
    for i in range(1, n+1):
        if tab[i][-1] > maxi:
            nMax = i
            mMax = m
            maxi = tab[i][-1]

    for i in range(1, m + 1):
        if tab[-1][i] > maxi:
            nMax = n
            mMax = i
            maxi = tab[-1][i]

    la(nMax, mMax, ["", ""], tab, dell, ins, sub, x, y)


def la(i, j, z, mat, dell, ins, sub, x, y):
    # print("[I,J]  T[" + str(i) + "," + str(j) + "]:" + str(mat[i][j]))
    # printTab2d(mat)
    # print("    " + str(mat[i - 1][j - 1]) + " + " + str(sub(x[j-1], y[i-1])))
    # print("    " + str(mat[i - 1][j]) + " + " + str(dell(x[j-1])))
    # print("    " + str(mat[i][j - 1]) + " + " + str(ins(y[i-1])))
    # print("---------------------------------------------------------")

    if i != 0 and j != 0 and mat[i][j] == mat[i - 1][j - 1] + sub(x[j - 1], y[i - 1]):
        # print("Sub")
        la(i - 1, j - 1, [str(x[j - 1]) + str(z[0]), str(y[i - 1]) + str(z[1])], mat, dell, ins, sub, x, y)

    if i != 0 and mat[i][j] == mat[i - 1][j] + dell(x[j - 1]):
        # print("del")
        la(i - 1, j, [str(x[i - 1]) + str(z[0]), " " + str(z[1])], mat, dell, ins, sub, x, y)

    if j != 0 and mat[i][j] == mat[i][j - 1] + ins(y[i - 1]):
        # "print("ins")
        la(i, j - 1, [" " + str(z[0]), str(y[i - 1]) + str(z[1])], mat, dell, ins, sub, x, y)

    if i == 0 and j == 0:
        print("Alignement : \n" + str(z[0]) + " \n" + str(z[1]) + "\n")


def printTab2d(tab):
    print(str(len(tab)) + " x " + str(len(tab[0])))
    size = 6
    for a in range(0, len(tab)):
        for j in range(0, len(tab[a])):
            taille = len(str(tab[a][j]))
            print(str(tab[a][j]) + " " * (size - taille), end="")
        print("")


def s(a, b):
    if a == b:
        return 0
    else:
        return 3


def i(x):
    return 3


def d(x):
    return 3


if __name__ == '__main__':
    print("HLIN608 - TP2")
    tab = calculMatrice("d", "GGCTGAC", 7, "GATC", 4, d, i, s)
    lesAlignements("GGCTGAC", 7, "GATC", 4, tab, d, i, s)
