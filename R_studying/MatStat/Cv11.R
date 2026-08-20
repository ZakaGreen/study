#1 Гипотеза о равенстве ген дисперсий 2х норм распр + Гипотеза о равенстве ген ср 2х распр, 
#где малые выборки(<30), ген сов-ти распределены нормально и дисперсии их неизвестны

#Psychologický experiment skúma krátkodobú pamäť dvoch skupín účastníkov, líšiacich sa
#vekom. Testuje sa schopnosť zapamätať si 20 položiek a po 2 minútach rozptýlenia ich
#správne identifikovať. Skupina A je vek 15-30 rokov, skupina B je 40+, vektory a, b
#predstavujú počet správne určených položiek u každého z účastníkov. 
#Testovanou hypotézou bude to, že schopnosti krátkodobej pamäte nie sú závislé od veku.

#H0: σ^2a = σ^2b, alfa = 5% / H1: σ^2a ≠ σ^2b
a <- c(14, 19, 15, 17, 16, 20, 11, 18, 20, 9, 13, 14, 17, 12, 20, 17, 18)
b <- c(12, 14, 9, 11, 16, 11, 7, 7, 5, 8, 14, 15, 8, 19, 17, 10, 12, 9, 11)
boxplot(a,b,horizontal = T)

shapiro.test(a)
shapiro.test(b)

#тест для равенства дисперсий, так как для данного типа доказательства равенства μ, требуется доказать равенство D
var.test(a,b) #тестирует сразу Fнабл между Fкр(a,k1;k2); k1 = m - 1; k2 = n -1;
# 0.2947195 < = 0.77816 < 2.1142712

# H0: μa = μb, tj. μa - μb = 0; alfa = 5% // H1: μa ≠ μb
t.test(a,b,paired=F,var.equal = T)  #paired=F – nechceme párový test
                                    #var.equal = T – overili sme, že disperzie sa môžu považovať za zhodné
#Интерпритация данных 
#p-value ≈ 0.0005 ≪ 0.05 → при любом стандартном уровне значимости (5 %, 1 %, даже 0.1 %) нулевую гипотезу отвергаем.
#95 % доверительный интервал для разности средних μa−μb равен [2.15;6.98], он не содержит 0, значит средние различаются.

#2
#Test krátkodobej pamäte sa zopakoval na ďalších dvoch skupinách účastníkov, ktoré sa okrem veku líšili aj ďalšími okolnosťami (vzdelanie, únava, ...).
p <- c(18, 19, 19, 17, 20, 18, 16, 19, 20, 19)
q <- c(4, 17, 2, 16, 10, 5, 8, 19, 4, 7, 8, 5, 2)

#Проверим, нормально ли разделены векторы? 
#если p-value меньше alfa, то гипотезу нормальности отвергаем
shapiro.test(p)
shapiro.test(q)

var.test(p,q)
#То есть выборочная дисперсия первой группы ≈ 4.9% от дисперсии второй
# Hodnota p-value je extrémne malá, hypotézu o zhode rozptylov zamietame.
#V takomto prípade je možné použiť Welchov test, pri ktorom sa zhoda rozptylov nevyžaduje. 
t.test(p,q,paired=F,var.equal = F)
#Hodnota p-value je takmer nulová. Hypotézu zamietame
#Интерпритация данных 
#p-value ≈ 0.0005 ≪ 0.05 → при любом стандартном уровне значимости (5 %, 1 %, даже 0.1 %) нулевую гипотезу отвергаем.
#95 % доверительный интервал для разности средних μa−μb равен [6.748845; 13.789617], он не содержит 0, значит средние различаются.

#3
#setwd("D:/C/test/STU/R_studying")
getwd()
data <- read_xlsx("data_vyuka.xlsx") #В объекте data теперь лежит полная таблица из файла со всеми строками, включая строки, где какие-то ячейки пустые
new_data <- na.omit(data) #Функция na.omit(data) возвращает новую таблицу, в которой, выкинуты все строки, где хотя бы в одном столбце есть NA

#Z hľadiska testovania nás bude zaujímať stĺpec mprij (príjem) a vzdelanie (hodnoty 1,2,3
#podľa stupňa), budeme skúmať vplyv vzdelania na príjem respondentov.

mprij <- new_data$mprij
vzd <- new_data$vzdelanie

#Množinu respondentov ankety vieme rozdeliť na tri skupiny podľa stupňa vzdelania. V každej
#skupine by hodnoty výšky príjmu mali mať normálne rozdelenie. To si overíme klasickým
#testom, aplikovaným trojmo po skupinách
tapply(mprij,vzd,shapiro.test)

#H0: variancie vo všetkých 3 skupinách sú rovnaké alfa = 5%
#H1: variancia aspoň v jednej skupine sa významne líši od ostatných

bartlett.test(mprij,vzd) #=> h0
boxplot(mprij~vzd,xlab="vzdelanie", ylab="prijem")

#H0: stredné hodnoty vo všetkých 3 skupinách sú rovnaké; alfa = 5%
#H1: stredná hodnota aspoň v jednej skupine sa významne líši od ostatných

#Použijeme príkaz aov, ktorý si vyžaduje faktorizovať vektor vzd, tj. jeho hodnoty pretlmočiť
#ako úrovne/skupiny 1,2,3.

#ANOVA (analysis of variance, анализ дисперсии) — это метод, который отвечает на вопрос:
#одинаковы ли средние в нескольких группах (3 и больше),
#сравнивая межгрупповый разброс с внутригрупповым разбросом.
#То есть это как t-test на равенство средних, но для многих групп сразу.

vzdf <- factor(vzd)
anova <- aov(mprij~vzdf)
summary(anova)

#Hodnota p-value v stĺpci Pr(>F) je takmer nulová, hypotézu zamietame.
#Veľkosť vplyvu vzdelania na príjem vyjadríme číselne na škále 0 až 1.
#treba nainštalovať effectsize

eta_squared(anova) #Sila vplyvu vzdelania na príjem je 0.62, štatisticky presnejšie povedané, na 95% je v intervale 0.45 až 1.
TukeyHSD(anova)
#Dôležitý je posledný stĺpec (p-value). Hovorí o tom, že štatisticky významné rozdiely sú
#medzi dvojicami 1-3 a 2-3. Skupiny 1 a 2 nie sú navzájom až tak vzdialené.
plot(TukeyHSD(anova))

#Те же выводы другим тестом
ScheffeTest(anova)
plot(ScheffeTest(anova))

#Poznámka
#Ak sa v Bartlettovom teste ukáže významná nezhoda rozptylov, dá sa pokračovať Welchovou
#modifikáciou testu:
#anova <- oneway.test(DátovýVektor~FaktorováMnožina, var.equal = F)
#print(anova)
# interakcia - взаимодействие

#Pr 4
#V sérii experimentov sa merala utajovaná fyzikálna veličina. Meranie vykonávali traja
#laboranti (a,b,c) na štyroch prístrojoch (A,B,C,D). Kladieme si otázku (stane sa predmetom testovania),
#či výsledky meraní sú závislé od toho, kto meria a na čom sa meria.
#Výsledky meraní sú uložené v súbore anova1 (treba si stiahnuť do pracovného adresára).
#Načítame stiahnutý súbor a preventívne (kvôli príkazu aov) hneď urobíme faktorizáciu:
  
anova1 <- read_xlsx("anova1.xlsx")
laborant <- factor(anova1$laborant)
pristroj <- factor(anova1$pristroj)

par(mfrow=c(1,2)) #– rozdelí plochu na dve časti, aby sa vedľa seba zmestili 2 grafy
boxplot(anova1$deg~anova1$laborant,xlab="laborant",ylab="vysledok")
boxplot(anova1$deg~anova1$pristroj,xlab="pristroj",ylab="vysledok")
#Podľa obrázkov vidíme, že laborant a „vytŕča“ z davu, podobne v prípade pristrojov vidíme
#výrazné rozdiely vo výsledkoch.

#Budeme testovať normalitu výsledkov v 12 podskupinách:
tapply(anova1$deg, list(anova1$laborant, anova1$pristroj), function(x) shapiro.test(x)$p.value ) #Je to v poriadku. 

#Overme aspoň zbežne zhodu disperzií.
bartlett.test(anova1$deg,anova1$laborant)
bartlett.test(anova1$deg,anova1$pristroj) #Je to dosť na tesno... ale teda ok. 

#Prejdeme konečne k testu zhody stredných hodnôt
an1 <- aov(anova1$deg~laborant+pristroj)
summary(an1)
#Hodnoty p-value sú malé, hypotézu o zhode stredných hodnôt naprieč skupinami zamietame.
#To znamená, že laborant aj prístroj sú štatisticky významné faktory ovplyvňujúce výsledky. 

#Skúmajme ešte interakcie medzi faktormi laborant a prístroj (vyjadrené znakom násobenia)
an2 <- aov(anova1$deg~laborant*pristroj)
summary(an2)

#Hypotézu o neinterakcii oboch faktorov nezamietame. Tj. nemáme presvedčivé argumenty o
#tom, že by spolu významným spôsobom interagovali – tj. faktor laborant a faktor prístroj sú
#nezávislé. Preto ďalej s an2 už nebudeme pracovať.

#Sila vplyvu faktorov na výsledky:
eta_squared(an1)
TukeyHSD(an1)
plot(TukeyHSD(an1))


#Pr5
#Testovanie rýchlosti e-shopu. Úlohou je zistiť, ako sa spracovanie užívateľskej požiadavky
#(merané ako čas do dokončenia úlohy v sekundách) mení v závislosti od dvoch kľúčových faktorov: 

#Faktor A: Latencia siete – Nízka (bežné kancelárske pripojenie, Low Latency)
#                           Vysoká (mobilné pripojenie v špičke, High Latency)

#Faktor B: Zložitosť UI – Jednoduché UI (intuitívne, moderné rozhranie)
#                         Zložité UI (zastaralé, preplnené rozhranie)

#Overovanie normálnosti a homogenity variancií ponechávame na samostatnú prácu.
#Pracujeme ďalej s vedomím, že niekto to už overil a je to v poriadku.

anova3 <- read_xlsx("anova_interakcie.xlsx")
an3 <- aov(cas~latencia*uiz,data=anova3)
summary(an3)
#Pri latencii a uiz vidno, že tieto faktory významne ovplyvňujú výsledné časy.

par(mfrow=c(1,1)) 
interaction.plot(
  x.factor = anova3$latencia,
  trace.factor = anova3$uiz,
  response = anova3$cas,
  fun = mean,
  type = "b",
  col = c("blue", "red"), # Farby pre lepšiu vizualizáciu
  pch = c(19, 17), # Typy bodov
  trace.label = "Typ UI",
  xlab = "Latencia siete",
  ylab = "Priemerný čas dokončenia (sek.)",
  main = "Vplyv latencie a UI na čas dokončenia úlohy")
























