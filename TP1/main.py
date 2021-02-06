import time


def concat(a, b):
    ret = ""
    for i in a:
        ret += i
    for i in b:
        ret += i
    # print(ret)
    return ret


def reverse(a):
    ret = ""
    for i in a:
        ret = i + ret

    # print(ret)
    return ret


def mixer(a, b):
    ret = ""

    alen = len(a)
    blen = len(b)

    i = 0
    while i < alen + blen:
        if i < alen:
            ret += a[i]
        if i < blen:
            ret += b[i]
        i += 1
    # print(ret)
    return ret


def isPrefix(a, b):
    ret = True

    for i in range(0, len(a) - 1):

        if len(b) - 1 >= i:
            if a[i] != b[i]:
                ret = False

    return ret or isPrefix(b, a)


def isSuffix(a, b):
    ret = True

    a = reverse(a)
    b = reverse(b)

    for i in range(0, len(a) - 1):

        if len(b) - 1 >= i:
            if a[i] != b[i]:
                ret = False

    return ret or isSuffix(b, a)


def lesBords(a):
    bord = []

    b = reverse(a)

    for i in range(1, len(a) - 1):
        if isPrefix(a[0:i], a) and isSuffix(a[0:i], a):
            bord.append(a[0:i])

    print(bord)


def motFibo(n):
    if n == 0:
        return "E"
    if n == 1:
        return "a"
    if n == 2:
        return "b"

    return motFibo(n - 2) + "" + motFibo(n - 1)


def rechercheNaif(mot):
    f = open("La Digue.txt", 'r+')

    ligne = 1

    while True:
        data = f.readline()
        if not data:
            break

        for i in range(0, len(data) - 1):
            if data[i] == mot[0]:
                # Chercher
                found = True
                car = i
                for j in range(0, len(mot) - 1):
                    if i + j < len(data) - 1:
                        if data[i + j] != mot[j]:
                            found = False
                if found:
                    print("Ligne " + str(ligne) + " :  Colone " + str(car))

        ligne += 1

    f.close()


if __name__ == '__main__':
    print("HLIN608 - TP1")

    # Ex 5
    start = time.time()
    rechercheNaif("son")
    end = time.time()
    print(end - start)

    # Ex 4
    print(motFibo(5))

    # Ex 3
    print(isPrefix("Pre", "Pr"))
    print(isSuffix("soubi", "grossoubi"))
    lesBords("aabaabaa")

    # Ex 1
    select = input("File (f) ou ecrire (e) ? :")
    if select == "f":
        f = open("Ex1.txt", 'r+')
        line = f.readline()

        a = line.split(":")[0].replace("\n", "")
        b = line.split(":")[1].replace("\n", "")

        f.write("\n" + concat(a, b))
        f.write("\n" + reverse(a))
        f.write("\n" + reverse(b))
        f.write("\n" + mixer(a, b))
        f.close()
        exit(0)
    if select == "e":
        a = input("Entrez a :")
        b = input("Enteez b :")
        concat(a, b)
        reverse(a)
        reverse(b)
        mixer(a, b)

        exit(0)
