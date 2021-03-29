if __name__ == "__main__":
    path = input("Chemin vers le fichier a analyser :")
    print("\n")
    file = open(path, 'r', encoding='utf-8')

    lines = file.readlines()

    listErrors = []
    lineNbr = 1
    nbrErrors = 0
    nbrErrorsSET = 0
    for i in lines:
        if "[ERREUR " in str(i):
            nbrErrors += 1

            text = "Line : " + str(lineNbr) + " " + str(i)
            print(text, end="")

            if not text in listErrors:
                listErrors.append("Line : " + str(lineNbr) + " " + str(i))
                nbrErrorsSET += 1

        lineNbr += 1

    print("\n" + str(nbrErrors) + " erreurs trouvés (" + str(nbrErrorsSET) + ")")
    print("Erreurs sans doublons : ")
    for i in range(0, len(listErrors)):
        print(listErrors[i], end="")

    file.close()
