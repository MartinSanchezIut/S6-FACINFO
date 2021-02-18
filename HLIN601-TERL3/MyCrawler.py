import requests
import time
import socket
from urllib.parse import urlparse
from bs4 import BeautifulSoup

DEBUG = True
DEBUG_REQUEST = True


def inspect(url, deep):
    global DEBUG

    # if url[len(url) - 1] == "/":
    #     url = url[0:len(url) - 1]
    if DEBUG: print("URL: " + url)

    o = urlparse(url)
    domain = o.netloc.removeprefix("www.")
    if DEBUG: print("O : " + str(o) + "\n")

    start = time.time()
    if DEBUG: print("Start at: " + str(start))

    visitedCount = []
    allUrlVisited = []
    if DEBUG: print("visitedCount: " + str(visitedCount))
    if DEBUG: print("allUrlVisited: " + str(allUrlVisited) + "\n")

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
        if profondeur > 0 and urlIsValid(linkToInspect):
            # (linkToInspect.endswith(".html") or linkToInspect.endswith(".php")
            #  or not linkToInspect.endswith(".*")):   Le truc a modifier

            returnList = listOfLinksOf(linkToInspect, domain)
            profondeur -= 1

            for x in returnList:
                if not x in allUrlVisited:
                    listOfUrl.insert(0, x)

    end = time.time()
    if DEBUG: print("Ends at: " + str(end))

    file = open("Result.txt", 'w+')
    file.write("Task ended in " + str(end - start) + " \n\n")
    for element in range(0, len(allUrlVisited)):
        file.write("'" + allUrlVisited[element] + "',\n")
        amountOfSpace = 100 - len(str(allUrlVisited[element]))
        # file.write(
        #    str(allUrlVisited[element]) + (" " * amountOfSpace) + " : Visited " + str(visitedCount[element]) + "\n")

    return 1


def listOfLinksOf(url, domain):
    global DEBUG_REQUEST

    urlToCrawl = []
    try:
        req = requests.get(url)
        text = req.text
        soup = BeautifulSoup(text, features="html.parser")
        links = soup.find_all('a')

        urls = []
        trash = []
        for tag in links:
            link = tag.get('href', None)

            if link.startswith("/") and not link == "/":
                link = url[:-1] + link
            newLinkData = urlparse(link)

            if newLinkData.netloc.__contains__(domain):
                if link is not None and not link.startswith("#") and not link.startswith("mailto:"):
                    # if link.endswith("/"):
                    #    link = link[:-1]
                    urls.append(link)
            else:
                trash.append(link)

        urlToCrawl = list(dict.fromkeys(urls))

        if DEBUG_REQUEST:
            print("    " + url + "\n    ---------------------------------------")
            fileUrls = ""
            for x in urlToCrawl:
                fileUrls += "   " + x + " |"
            print(fileUrls)
            fileUrls = "   Trash : "
            for y in trash:
                fileUrls += "   " + y + " |"
            print(fileUrls)
            print("    ---------------------------------------  \n\n")

    except Exception as error:
        if DEBUG_REQUEST: print("   " + url + ": Error\n")

    return urlToCrawl


def urlIsValid(url):
    tab = url.split("/")
    last = tab[-1]
    lastReversed = tab[-1][::-1]
    for i in range(0, len(lastReversed)):
        if lastReversed[i] == ".":
            # On trouve un point avant un /
            # Verifier les terminaisons
            if not last.endswith(".html") or last.endswith(".php"):
                return False

    return True


def getIpOf(host):
    ip = ""
    try:
        ip = socket.gethostbyname(host)
        # print("Ip de " + host + " est : " + socket.gethostbyname(host))
    except Exception as e:
        ip = "-1"
        # print("Erreur de récupération de l'ip: ", e)

    return ip


def verif():
    urlToValid = ['http://www.lirmm.fr/',
                  'http://www.lirmm.fr/switchlanguage/to/lirmm_eng/65',
                  'http://www.lirmm.fr/rssfeed/news',
                  'http://www.lirmm.fr/annuaire',
                  'https://webmail.lirmm.fr/',
                  'https://intranet.lirmm.fr/xml/in/0100-07.html',
                  'http://www.lirmm.fr/Partenariats-entreprises',
                  'http://www.lirmm.fr/Scientifiques-institutions',
                  'http://www.lirmm.fr/acces-etudiants',
                  'http://www.lirmm.fr/le-lirmm/presentation',
                  'http://www.lirmm.fr/le-lirmm/organisation',
                  'http://www.lirmm.fr/le-lirmm/chiffres-cle',
                  'http://www.lirmm.fr/le-lirmm/historique',
                  'http://www.lirmm.fr/le-lirmm/partenariats',
                  'http://www.lirmm.fr/le-lirmm/emplois',
                  'http://www.lirmm.fr/le-lirmm/les-services',
                  'http://www.lirmm.fr/actualites',
                  'http://www.lirmm.fr/agenda',
                  'http://www.lirmm.fr/recherche/departements',
                  'http://www.lirmm.fr/recherche/equipes',
                  'http://www.lirmm.fr/recherche/plateformes',
                  'http://www.lirmm.fr/recherche/publications',
                  'http://www.lirmm.fr/recherche/doctorants',
                  'http://www.lirmm.fr/recherche/theses-et-hdr-soutenues',
                  'http://www.lirmm.fr/recherche/conferences-et-ecoles-thematiques',
                  'http://www.lirmm.fr/recherche/sujets-de-these-proposes',
                  'http://www.lirmm.fr/innovation/nos-competences',
                  'http://www.lirmm.fr/innovation/partenariats-industriels',
                  'http://www.lirmm.fr/innovation/conseils-et-expertises',
                  'http://www.lirmm.fr/innovation/seminaires',
                  'http://www.lirmm.fr/innovation/creation-d-entreprises',
                  'http://www.lirmm.fr/international/international',
                  'http://www.lirmm.fr/contact-acces',
                  'http://www.lirmm.fr/recherche/departements/info',
                  'http://www.lirmm.fr/recherche/plateformes/plateforme-informatique',
                  'http://www.lirmm.fr/recherche/departements/rob',
                  'http://www.lirmm.fr/recherche/plateformes/plateforme-robotique',
                  'http://www.lirmm.fr/recherche/departements/mic',
                  'http://www.lirmm.fr/recherche/plateformes/plateforme-microelectronique',
                  'http://www.lirmm.fr/actualites/felicitations-a-neocean-pour-le-grand-prix-de-l-innovation-de-l-occitanie-2021',
                  'http://www.lirmm.fr/actualites/news-ninjalab-startup-hebergee-au-lirmm',
                  'http://www.lirmm.fr/actualites/video-euronews-sur-les-robots-paralleles-a-cables-resultat-du-projet-europeen-hephaestus',
                  'http://www.lirmm.fr/le-lirmm/organisation/les-services/dist',
                  'https://seafile.lirmm.fr/',
                  'https://gite.lirmm.fr',
                  'http://www.lirmm.fr/le-lirmm/organisation/les-services/comm',
                  'https://www.lirmm.fr/lirmm_admin',
                  'https://www.lirmm.fr/extranet/manuel-redaction-web-LIRMM.pdf',
                  'http://www.lirmm.fr/content/view/sitemap/2',
                  'http://www.lirmm.fr/informations/informations-legales',
                  'https://intranet.lirmm.fr/xml/in/0309-29.html']

    for i in range(0, len(urlToValid)):
        print(str(urlToValid[i]) + "  =   " + str(urlIsValid(urlToValid[i])))


if __name__ == "__main__":
    # url = input("Entrez l'url: ")

    getIpOf("www.lirmm.fr")
    verif()
    # print(inspect("http://www.lirmm.fr/", 1))
    # print(listOfLinksOf("http://www.lirmm.fr/"))
