import requests
import time
import socket
from urllib.parse import urlparse
from bs4 import BeautifulSoup
import sys
import csv

DEBUG = True
DEBUG_LOOP = True
DEBUG_REQUEST = True
DEBUG_ADD = True


def inspect(url, deep):
    global DEBUG, DEBUG_ADD, DEBUG_LOOP
    file = open("result.txt", 'w+')

    if DEBUG: print("URL: " + url)

    o = urlparse(url)
    domain = o.netloc  # .removeprefix("www.")
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
        if DEBUG_LOOP: print("Link selected: " + str(linkToInspect))

        if linkToInspect is not None and len(linkToInspect.split(".")) == 2 and (
                linkToInspect.endswith(".php") or linkToInspect.endswith(".html")):
            linkToInspect = str(o.scheme) + "://" + str(o.netloc) + "/" + str(linkToInspect)
            if DEBUG_LOOP: print("   Link after modification: " + str(linkToInspect) + "\n")
        if linkToInspect is not None and linkToInspect.startswith("/") and not linkToInspect == "/":
            linkToInspect = str(o.scheme) + "://" + str(o.netloc) + str(linkToInspect)
            if DEBUG_LOOP: print("   Link after modification: " + str(linkToInspect) + "\n")

        if urlIsValid(linkToInspect, domain):
            req2 = requests.get(linkToInspect)
            if req2.ok:
                if DEBUG_LOOP: print("   Requette vers: " + str(linkToInspect) + "  [VALIDE]")
                theLink = req2.url
                req2.close()
                if not str(theLink).__eq__(str(linkToInspect)):
                    linkToInspect = theLink
                    if DEBUG_LOOP: print("   Redirige vers: " + str(linkToInspect) + "\n")
            else:
                theError = req2.status_code
                if DEBUG_LOOP: print("   Requette vers: " + str(linkToInspect) + "  [ERREUR " + str(theError) + "]")
                req2.close()

        if not linkToInspect in allUrlVisited:
            allUrlVisited.append(linkToInspect)
            file.write(allUrlVisited[-1] + "\n")  # Writte dans le fichier   (Temps réel)
            visitedCount.append(1)
            if DEBUG_LOOP: print("      - Première visite ! (" + linkToInspect + ")")
            hasToVisit = True
        else:
            index = allUrlVisited.index(linkToInspect)
            visitedCount[index] += 1
            if DEBUG_LOOP: print("      -" + str(visitedCount[index]) + "eme visite ! (" + linkToInspect + ")")
            hasToVisit = False

        if DEBUG: print("   - Profondeur : " + str(profondeur) + "\n")
        if (profondeur > 0 or profondeur == -1) and urlIsValid(linkToInspect, domain) and hasToVisit:
            if DEBUG_ADD: print("   Liste des liens de : " + str(linkToInspect))
            returnList = listOfLinksOf(linkToInspect, domain)

            if profondeur != -1:
                profondeur -= 1

            for x in returnList:
                if (not x in allUrlVisited) and urlIsValid(x, domain):  # ICI POUR TRIER LES PDF JPG ETC
                    listOfUrl.insert(0, x)
        if DEBUG_LOOP: print(" -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- \n")

    end = time.time()
    if DEBUG: print("Ends at: " + str(end))
    if DEBUG: print("Time : " + str(end - start))

    # file = open("result.txt", 'w+')
    file2 = open("resultFancy.csv", 'w+', newline='')
    writer = csv.writer(file2)

    writer.writerow(["Task time:", str(end - start)])
    writer.writerow(["Urls", "Visited count"])
    # file2.write("Task ended in " + str(end - start) + " \n\n")
    for element in range(0, len(allUrlVisited)):
        # file.write(allUrlVisited[element] + "\n")
        writer.writerow([str(allUrlVisited[element]), str(visitedCount[element])])

        # amountOfSpace = 140 - len(str(allUrlVisited[element]))
        # file2.write(
        #     str(allUrlVisited[element]) + (" " * amountOfSpace) + " : Visited " + str(visitedCount[element]) + "\n")

    file.close()
    file2.close()
    return 1


def listOfLinksOf(url, domain):
    global DEBUG_REQUEST
    urlData = urlparse(url)
    urlToCrawl = []
    try:
        req = requests.get(url)
        if not req.ok:
            return urlToCrawl

        text = req.text
        req.close()

        soup = BeautifulSoup(text, features="html.parser")
        links = soup.find_all('a')

        urls = []
        trash = []
        for tag in links:
            link = tag.get('href', None)

            if link is not None and len(link.split(".")) == 2 and (link.endswith(".php") or link.endswith(".html")):
                link = str(urlData.scheme) + "://" + str(urlData.netloc) + "/" + str(link)
            if link is not None and link.startswith("/") and not link == "/":
                # link = str(url[:-1]) + str(link)
                link = str(urlData.scheme) + "://" + str(urlData.netloc) + str(link)

            newLinkData = urlparse(link)

            if str(newLinkData.netloc).__contains__(domain):
                if link is not None and not link.startswith("#") and not link.startswith("mailto:"):
                    urls.append(link)
            else:
                trash.append(link)

        urlToCrawl = list(dict.fromkeys(urls))

        if DEBUG_REQUEST:
            print("      -> " + str(url) + "\n")
            fileUrls = "     "
            for x in urlToCrawl:
                fileUrls += " " + str(x) + " |"
            print(fileUrls)
            fileUrls = "      Trash : "
            for y in trash:
                fileUrls += " " + str(y) + " |"
            print(fileUrls)

    except Exception as error:
        if DEBUG_REQUEST: print("      -> " + str(url) + ": Error  ( " + str(error) + ")\n")

    return urlToCrawl


def urlIsValid(url, domain):
    tab = url.split("/")
    last = tab[-1]
    if last.__eq__(domain):
        return True
    for i in range(0, len(last)):
        if last[i] == ".":
            # On trouve un point avant un /
            # Verifier les terminaisons
            if not (last.endswith(".html") or last.endswith(".php")):
                return False
    return True


def verif(domain):
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
        print(str(urlToValid[i]) + "  =   " + str(urlIsValid(urlToValid[i], domain)))


if __name__ == "__main__":
    # Temporaire
    url = "https://www.lirmm.fr/"
    deep = 10

    print("$ ./myCrawler " + url + " " + str(deep) + "\n")
    print(inspect(url, int(deep)))

    exit(1)
    # Fin temporaire

    if len(sys.argv) < 2 or len(sys.argv) > 3:
        print("Usage : myCrawler.py <url> [deep]")
        exit(1)
    else:
        url = ""
        deep = -1
        if len(sys.argv) >= 2:
            url = sys.argv[1]
        if len(sys.argv) == 3:
            deep = sys.argv[2]

        print("$ ./myCrawler " + url + " " + str(deep) + "\n")
        print(inspect(url, int(deep)))
        exit(0)

        # verif()
        # print(inspect("http://www.lirmm.fr/", 3))
        # print(listOfLinksOf("http://www.lirmm.fr/"))
