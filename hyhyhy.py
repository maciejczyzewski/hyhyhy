import configparser, os, string, glob

def num(a):
    b = a.split('.')[-2]
    c = b.split('/')[-1]
    return int(c)

def prf(a):
    b = {}
    b['OK'] = '\033[92m[OK]\033[0m'
    b['FAIL'] = '\033[91m[FAIL]\033[0m'
    b['INFO'] = '\033[95m[INFO]\033[0m'
    b['WARNING'] = '\033[93m[WARNING]\033[0m'
    return b[str(a)]

print( prf('INFO'), "Starting hyhyhyhyhyhyhyhyhy", "..." )

assets, sections, default, index = list(glob.glob("assets/*")), list(glob.glob("sections/*")), 'default.cfg', 'build/index.html'
html = '<html><head>(head)</head><body>(body)</body></html>'

config = configparser.ConfigParser()
config.read(default)

print( prf('OK'), "Reading config file", default, "..." )

def getHead(a = ""):
    global html, assets, sections

    if config['head']['charset']:
        a += "<meta charset='" + str(config['head']['charset']) + "'>"

    if config['head']['title']:
        a += "<title>" + str(config['head']['title']) + "</title>"

    for i in assets:
        print( prf('OK'), "Parsing file", i, "..." )
        if i.split('.')[-1] == "css":
            a += "<style>" + str(open(i, 'r').read()) + "</style>"
        elif i.split('.')[-1] == "js":
            a += "<script>" + str(open(i, 'r').read()) + "</script>"

    return a

def getBody(a = ""):
    global html, assets, sections

    sections.sort(key = num)

    for i in sections:
        print( prf('OK'), "Parsing file", i, "..." )
        a += "<section>" + str(open(i, 'r').read()) + "</section>"

    return a

def getHtml():
    global html

    html = html.replace('(head)', getHead())
    html = html.replace('(body)', getBody())

    return html

build = open(index, 'w')
build.write(getHtml())
build.close()

print( prf('OK'), "Saved in", index, "->", config['head']['title'] )