import requests
import time
import socket
from bs4 import BeautifulSoup

DEBUG = True
DEBUG_REQUEST = True


def inspect(url, deep):
    global DEBUG

    if url[len(url) - 1] == "/":
        url = url[0:len(url) - 1]
    if DEBUG: print("URL: " + url)

    start = time.time()
    if DEBUG: print("Start at: " + str(start))

    visitedCount = []
    allUrlVisited = []
    if DEBUG: print("visitedCount: ".join(visitedCount))
    if DEBUG: print("allUrlVisited: ".join(allUrlVisited))

    listOfUrl = [url]
    profondeur = deep
    while len(listOfUrl) > 0:
        linkToInspect = listOfUrl.pop()
        if DEBUG: print("Request on " + linkToInspect)

        if not linkToInspect in allUrlVisited:
            allUrlVisited.append(linkToInspect)
            visitedCount.append(1)
            if DEBUG: print("The link is not in 'AllUrlVisited'")
        else:
            index = allUrlVisited.index(linkToInspect)
            visitedCount[index] += 1
            if DEBUG: print("The link is in 'AllUrlVisited'")

        if linkToInspect.startswith("/"):
            linkToInspect = url + linkToInspect

        if DEBUG: print("Profondeur : " + str(profondeur) + "\n")
        if profondeur > 0 and (linkToInspect.endswith(".html") or linkToInspect.endswith(".php")):
            returnList = listOfLinksOf(linkToInspect)
            profondeur -= 1

            for x in returnList:
                if not x in allUrlVisited:
                    listOfUrl.append(x)

    end = time.time()
    if DEBUG: print("Ends at: " + str(end))

    file = open("Result.txt", 'w+')
    file.write("Task ended in " + str(end - start) + " \n\n")
    for element in range(0, len(allUrlVisited)):
        amountOfSpace = 100 - len(str(allUrlVisited[element]))
        file.write(
            str(allUrlVisited[element]) + (" " * amountOfSpace) + " : Visited " + str(visitedCount[element]) + "\n")

    return 1


def listOfLinksOf(url):
    global DEBUG_REQUEST

    urlToCrawl = []
    try:
        req = requests.get(url)
        text = req.text
        soup = BeautifulSoup(text, features="html.parser")
        links = soup.find_all('a')

        urls = []
        for tag in links:
            link = tag.get('href', None)
            if link is not None and not link.startswith("#") and not link == "/" and not link.startswith("mailto:"):
                if link.startswith(url):
                    link = link[len(url):len(link)]
                urls.append(link)

        urlToCrawl = list(dict.fromkeys(urls))

        if DEBUG_REQUEST:
            print("    " + url + "\n    ---------------------------------------  \n")
            fileUrls = ""
            for x in urlToCrawl:
                fileUrls += "   " + x + " |"
            print(fileUrls)
            print("    ---------------------------------------  \n\n")

    except Exception as error:
        if DEBUG_REQUEST: print("   " + url + ": Error\n")

    return urlToCrawl


def getIpOf(host):
    ip = ""
    try:
        ip = socket.gethostbyname(host)
        # print("Ip de " + host + " est : " + socket.gethostbyname(host))
    except Exception as e:
        ip = "-1"
        # print("Erreur de récupération de l'ip: ", e)

    return ip


if __name__ == "__main__":
    # url = input("Entrez l'url: ")

    getIpOf("www.lirmm.fr")

    print(inspect("http://www.lirmm.fr/", 50))
    # print(listOfLinksOf("http://www.lirmm.fr/"))
