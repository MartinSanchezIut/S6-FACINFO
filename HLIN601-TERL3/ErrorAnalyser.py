def erreursVerifies():
    tab = []
    return tab


if __name__ == "__main__":
    path = input("Chemin vers le fichier a analyser :")
    print("\n")
    file = open(path, 'r', encoding='utf-8')

    readlines = file.readlines()

    lineNbr = 1
    nbrErrors = 0
    for i in readlines:
        if "[ERREUR " in str(i):
            nbrErrors += 1
            print("Line : " + str(lineNbr) + " " + str(i), end="")

        lineNbr += 1

    print("\n" + str(nbrErrors) + " erreurs trouvés")
    file.close()
