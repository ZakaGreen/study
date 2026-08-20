#Náhodná veličina X sa v sérii 30 experimentov prejavila nasledujúcimi hodnotami:
x <- c(51,55,56,57,57,59,61,61,63,64,65,65,68,69,69,71,72,74,76,78,79,79,81,83,85,86,89,93,96,98)

n <- length(x)
xm <- mean(x)
s2 <- var(x)
s1 <- sd(x)

#Overíme si, či získané hodnoty môžu zodpovedať náhodnej veličine s normálnym rozdelením:
qqnorm(x)
qqline(x)
#Vizuálna kontrola ukazuje, že pri troche tolerancie body ležia zhruba na priamke, tj. kvantily
#vektora x a normálneho rozdelenia si zodpovedajú. Ale poďme to presne vyčísliť

#Shapiro-Wilk normality test
shapiro.test(x)
#Hodnota p-value je vysoko nad tradičnou hranicou 0.05 (aj kvôli malému počtu hodnôt
#v dátovom vektore), takže predpoklad o normálnom rozdelení sa nedá zamietnuť.

#1а
#H0: m = 55 alpha = 5%
u <- qt(0.975, n - 1) # 0.975 так как qt() всегда даёт тебе квантиль по левой площади = 0.95 + 5%/2
u
d <- s1*u/sqrt(n)
d
#interval (55 nepatri =>)
c(xm - d, xm + d) #67.18201 76.81799
#H0 sa zamieta => H1: m != 55

#1b 
#Postup cez porovnanie kvantilov. Stanovíme si interval okolo stredu 55 taký, aby sa xm=72
#nachádzalo na jeho hranici, a vypočítame si zodpovedajúcu hodnotu ux.

ux = sqrt(n) * abs(xm-55)/s1
ux #Vidíme, že hodnota 7.2165 sa nachádza ďaleko mimo intervalu (-2.045, 2.045), hypotézu preto zamietame.

#1c
# Postup cez p-hodnotu. Urobíme ešte jeden „krok späť“ a zistíme, akým kvantilom je
#získané ux. Distributívna funkcia je pt (inverznou k nej bola qt).
ph <- 2*(1-pt(ux,29))
ph

#1d
#Systémový postup: #H0: mu = 68 / H1: mu != 68
t.test(x, mu=68)

#1e
#H0: mu <= 68
#H1: mu > 68

t.test(x, mu=68, alternative="g")
t.test(x, mu = 68, alternative="l")

#2
#Vráťme sa k poslednej z overovaných hypotéz. Predpokladajme, že s1=11 presne (nechajme
#bokom otázku, odkiaľ to môžeme vedieť). <= Vieme σ => Norm. rozd.
s1 <- 11
u <- qnorm(0.975)
u
d <- 11*u/sqrt(n)
d
c(xm - d, xm + d)
# 68 !Є c
ux <- sqrt(n)*abs(xm-68)/11
ux

ph <- 2*(1 - pnorm(ux))
ph #0.046 < 0.05

#library(DescTools)
ZTest(x, mu=68, sd_pop=11)


#3
cisla <- read_csv("cisla.csv")
GLC <- cisla$Glucose

#Na hladine významnosti 2% (conf.level = 0.98)
#testujte (všetkými spomenutými cestami založenými na Studentovom rozdelení)
#hypotézy, že pre strednú hodnotu platí mu=121, mu=125, mu<121, mu>121.

# mu = 121 
t.test(GLC, mu = 121, conf.level = 0.98)
# mu є [118.6297, 123.1593]

# mu = 125
t.test(GLC, mu = 125, conf.level = 0.98)
# mu !є [118.6297, 123.1593]

# mu < 121
t.test(GLC, mu = 121, alternative = "g", conf.level = 0.98)
# mu є [118.6297, 123.1593]

# mu > 121
t.test(GLC, mu = 121, alternative = "l", conf.level = 0.98)
# mu є [118.6297, 123.1593]

# mu < 125
t.test(GLC, mu = 125, alternative = "g", conf.level = 0.98)
# mu є [118.6297, 123.1593]



