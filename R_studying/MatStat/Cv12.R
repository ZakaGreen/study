#Wald–Wolfowitz runs test
#Pr1
#Waldov-Wolfowitzov test „sledov“ overuje hypotézu náhodnosti dát v postupnosti zloženej z dvoch opakovaných položiek (znakov). Napr. v postupnosti
#0001100001111110100101110 sa opakujú položky/znaky 0,1. Pozostáva z 11 „runs“/sledov (= zoskupení po sebe idúcich
#rovnakých znakov). Počet núl je n0, počet jednotiek je n1.

#Testovanou hypotézou H0 je, že každý znak v postupnosti je výsledkom náhodného výberu.
#Teoreticky sa dá ukázať, že počet sledov je náhodná veličina s normálnym rozdelením
#s konkrétnymi parametrami. Dá sa zistiť ideálny počet sledov pre dané čísla n0, n1 a ten
#v teste konfrontovať s ich skutočným počtom

ve <- c(0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,0,1,0,1,1,1,0)
# treba nainštalovať randtests
runs.test(ve, threshold=0.5, plot=T) #Hodnota p-value je dosť veľká na to, aby sme nespochybňovali náhodnosť dát. 

#Pr2a
#Na určenej trase sa merala priemerná rýchlosť účastníkov podujatia počas 10 po sebe
#nasledujúcich dní. Otázkou je, či postupnosť uvedených časov možno považovať za náhodnú.
#Použijeme opäť nástroj runs.test.
#– Ak neuvedieme hodnotu threshold, podľa základného nastavenia sa bude za ňu považovať
#medián daného vektora dát.
#– Čísla vo vektore sa vyhodnocujú len ako väčšie alebo menšie než medián – vyhodnocuje sa
#nakoniec len vektor s dvoma údajmi. Čísla rovné presne mediánu sa vynechávajú.

ry <- c(7.7,7.8,8.5,7.8,7.9,9,7.5,8.2,9.3,8.1)
runs.test(ry,plot = T)

#Jednostranné testy
#V prípade náhodného vektora možno určiť ideálny počet bodov obratu (lokálne minimá
#a maximá), ktorý v teste konfrontujeme s ich skutočným počtom vo vektore. Príliš veľké
#odchýlky indikujú cyklickosť, ktorá sa ťažko dá obhájiť náhodným generovaním.

runs.test(ry,alternative = "left.sided") #Hypotézu nezamietame, v dátach nie je trend (zoskupovanie hodnôt rovnakého typu).
runs.test(ry,alternative = "right.sided") #Hypotézu nezamietame, v dátach nie je negatívna autokorelácia (trend neopakovať znaky rovnakého typu).

#Turning points test
turning.point.test(ry)

turning.point.test(ry,alternative = "left.sided")
turning.point.test(ry,alternative = "right.sided")

# treba nainštalovať pastecs
plot(ry)
lines(ry)
turnpoints(ry)
#Pri náhodných údajoch môžeme očakávať zhruba 5.33 bodov obratu, prakticky ich je
#v skúmanom vektore 5. Opýtajme sa trochu inak, dozvieme sa ďalšie veci:
tp <- turnpoints(ry)
summary(tp)  
lines(tp)

#Sign test
#Znamienkový test. Testovanie hypotéz o mediáne. Robustný a použiteľný aj pre šikmejšie dáta. 
#Pr3a
#Presným laboratórnym meraním bola stanovená teplota skúmanej kvapaliny na 7.5 stupňa. Pri
#testovaní šarže nového modelu low-cost teplomeru sa očakáva (okrem iného), že medián
#nameraných hodnôt bude zodpovedať presnej hodnote 7.5. Namerané hodnoty získané
#vybranou vzorkou teplomerov sú nasledovné:
#H0: medián nameraných hodnôt v rámci šarže je 7.5
#H1: medián nameraných hodnôt v rámci šarže nie je 7.5
tt <- c(7.5,6.8,7.2,8.1,7,6.5,7.9,8.5,6.9,7.5,7.3,6.6,7.8,6.2,7.4)
#treba nainštalovať BSDA

SIGN.test(tt,md=7.5) #=>7.3

#Wilcoxon signed rank test
#Wilcoxonov test – testovanie hypotéz o mediáne. Technicky presnejšie povedané,
#Wilcoxonov test hodnotí symetriu rozloženia dát okolo určeného centra.
#Na korektné použitie testu je potrebné, aby samotné dáta boli približne symetrické, teda ich
#šikmosť ideálne v rozmedzí (-0.5, 0.5), prinajhoršom (-1,1).
#Príklad 3b
#treba nainštalovať moments

moments::skewness(tt) #Šikmosť je akceptovateľná, ale skúsme ešte inú funkciu:
moments::agostino.test(tt) #Okrem samotnej šikmosti dostávame aj vysoké p-value, takže dáta môžeme považovať za nezošikmené.

wilcox.test(tt,mu=7.5) #Hodnota p-value je nad limitom 5%, hypotézu o mediáne 7.5 nezamietame. 


#Jednostranný test

#Obvyklá cukornatosť hrozna z vinohradu ABC je 22°NM. Vzhľadom na priaznivé počasie
#poslednej sezóny sa predpokladá, že cukornatosť posledného zberu bude vyššia.
#Merania muštu z jednotlivých lánov vinohradu priniesli nasledovné výsledky:
  
cc <- c(22.5,21.5,20.5,24.5,23.0,18.0,23.5,25.5,24.0,20.0,18.5,22.0,24.5,24.5,26.0,25.5,23.5,24.5,23.0,24.0)
#Najprv musíme overiť nezošikmenosť dát.
moments::skewness(cc)
moments::agostino.test(cc)
#Šikmosť -0.82 je povážlivá, p-value je len trochu nad hranicou. Hypotézu o nezošikmenosti
#dát nezamietame, ale sme si vedomí, že znamienkový test bude v tomto prípade asi dôveryhodnejší. 

SIGN.test(cc,md=22,alternative="less") #Hodnota p-value je priaznivá, hypotézu nezamietame, úrodu môžeme pochváliť. 
wilcox.test(cc,mu=22,alternative="less") #Aplikujme aj Wilcoxonov test:

#Párový test
#Pr5
#Namerané časy pred a po špecializovanom kurze:
pred <- c(87,61,98,90,93,74,83,72,81,75,83)
po <- c(50,45,79,90,88,65,52,79,84,61,52)
#Nastalo zlepšenie? Použijeme párový znamienkový test:
SIGN.test(pred,po,paired=T,alternative = "less")

#To isté teraz Wilcoxonovým testom.Overme najprv nezošikmenosť dát:
moments::skewness(pred-po)

# treba nainštalovať lawstat
lawstat::symmetry.test(pred-po)
moments::agostino.test(pred-po)
#Všetky pohľady potvrdzujú, že dáta môžeme považovať za symetrické.

#Vlastný Wilcoxonov test:
wilcox.test(pred-po,alternative = "l")
#Párová formulácia (rovnaké výsledky):
wilcox.test(pred,po,paired = T,alternative = "less")
#Hypotézu o zlepšení výsledkov nezamietame.


#Dvojvýberový Wilcoxonov test
#Pr6
#Dlhodobým záťažovým testom bola podrobená špeciálna turistická obuv dvoch uznávaných
#značiek. Od oboch značiek sa vybrali vzorky viacerých kusov a odovzdali turistom
#z miestneho klubu.
#Výsledky sú nasledovné
m1<-c(420,560,600,490,550,570,340,480,510,460)
m2<-c(400,420,580,470,470,500,520,530)
#Otázkou je, ktorá z oboch značiek má dlhšiu životnosť.
#H0: median(m1) = median(m2) H1: median(m1) ≠ median(m2)
boxplot(m1,m2,ylab="body",xlab="značka")
zdr <- data.frame("body"=c(m1,m2),"znacka"=rep(c(1,2),times=c(10,8))) #Disperzie sú v poriadku. Môžeme testovať.
zdr

wilcox.test(m1,m2) #Hodnota p-value je vysoko nad 5%, hypotézu nezamietame, životnosti oboch značiek sa od seba významným spôsobom nelíšia. 

#– test Kolmogorov-Smirnov. Tento test je menej háklivý na väčšie rozdiely medzi vzorkami.
ks.test(m1,m2)

#Test Kruskal-Wallis
#Pr7
#Únava na pracovisku sa meria na vzorke 12 respondentov z 3 oddelení podľa dlhodobého priemerného počtu káv, ktoré denne vypijú. 
data <- data.frame("unava"=c(7,8,5,9,4,3,6,5,4,2,3,1),
                   "prostredie"=c(rep(1,4),rep(2,5),rep(3,3)))
data
boxplot(data$unava~data$prostredie,xlab = "prostredie", ylab = "unava",horizontal=T)
#Testovanie. H0: miera únavy nie je závislá od prostredia/oddelenia H1: a veruže je

kruskal.test(data$unava,data$prostredie) #Hodnota p-value je nízka, pod 5%. Zamietame hypotézu, prostredie významným spôsobom vplýva na veľkosť únavy. 

#Post testy:
#treba nainštalovať dunn.test
dunn.test(data$unava,data$prostredie,altp = T, list = T)

























