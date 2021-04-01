import re


def howToSort(str):
    regex = '.*  [ERREUR \d+]$'
    match = re.match(regex, str)
    return match


if __name__ == "__main__":
    path = input("Chemin vers le fichier a analyser :")

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
            listErrors.append(text)

        lineNbr += 1

    print(str(nbrErrors) + " erreurs trouvés \n")

    for i in listErrors:
        print(str(i), end="")
    file.close()
