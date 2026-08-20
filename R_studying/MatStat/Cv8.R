getwd()
#setwd("D:/C/test/STU/RStidio")

#Pr1
#Náhodná veličina má normálne rozdelenie N(mi,22) s neznámym parametrom mi.
#Pri 10 pokusoch dostaneme dátový vektor x = [3 4 7 8 9 11 12 13 16 17]
#Nájdite obojstranný intervalový odhad strednej hodnoty so spoľahlivosťou 0.9
#(alfa = 0.1) a jednostranný odhad so spoľahlivosťou 0.95 (alfa = 0.05).

x <- c(3, 4, 7, 8, 9, 11, 12, 13, 16, 17)
n <- length(x)
xm <- mean(x) #(xm <- sum(x)/n)
s2 <- 22
s1 <- sqrt(22)
u <- qnorm(0.95) #квантильная функция нормального распределения
                #u здесь это просто обозначение критического 
                #значения стандартного нормального распределения.
d <- (u*s1)/sqrt(n) #d — это точность оценки в доверительном интервале(е)
ISO <- xm + c(-1,1)*d #ISO je obojstranný interval spoľahlivosti pre alfa=0.9, c - просто вектор чисел
ISO
ISL <- c(-Inf,xm+d) # ISL a ISP sú jednostranné intervaly spoľahlivosti pre alfa = 0.95.
ISL
ISP <- c(xm-d,Inf)
ISP

#Na výpočet obojstranného intervalu spoľahlivosti vieme použiť aj pokročilejšie nástroje – funkciu ZTest.
#Najprv si treba nainštalovať a načítať knižnicu DescTools
ZTest(x,sd_pop = sqrt(22),conf.level = 0.9)$conf.int
#Jednostranné odhady – default spoľahlivosť 0.95, nastavenie cez parametre g, l (greater/lesser)
ZTest(x,sd_pop = sqrt(22),alternative = "g")$conf.int
ZTest(x,sd_pop = sqrt(22),alternative = "l")$conf.int


#2
#Náhodná veličina má normálne rozdelenie N(μ,σ2) s neznámymi parametrami.
#Pri 10 pokusoch dostaneme dátový vektor x (ten istý ako vyššie spomenutý).
#Nájdite intervalový odhad strednej hodnoty so spoľahlivosťou 0.9. 

s1 <- sd(x)
u <- qt(0.95,n-1) #квантильная функция распределения стьюдента так как не знаем σ
# ищем только правый хвост так как график симметричен => 0.95 = 0.9 + 10%/2
d <- u*s1/sqrt(n)

ISO <- xm + c(-1,1)*d
ISO
ISL <- c(-Inf,xm+d)
ISL
ISP <- c(xm-d,Inf)
ISP
#Na výpočet obojstranného intervalu spoľahlivosti opäť vieme použiť pokročilejšie nástroje – funkciu t.test
#Najprv si treba nainštalovať a načítať knižnicu - stats
t.test(x,conf.level = 0.9)$conf.int
#Jednostranné odhady – default spoľahlivosť 0.95, nastavenie cez parametre g, l (greater/lesser)
t.test(x,alternative = "l")$conf.int
t.test(x,alternative = "g")$conf.int

#Pr3
#Počítajme intervalový odhad rozptylu pre zadanie predošlého príkladu, tj. pri neznámom mi
#a so spoľahlivosťou 0.9 (obojstranne), 0.95 (jednostranne).

s2 <- var(x)
u2 <- qchisq(0.95,n-1) #квантильная функция хи-распределения так как нам нужно оценить дисперсию
u1 <- qchisq(0.05,n-1)
#Тут мы ищем 2 крит значения, так как граффик не симетричен => 0.95 = 0.9 + 10%/2
isox <- s2*(n-1)/c(u2,u1)
isox
#Jednostranné odhady:
c(0,isox[2])
c(isox[1],Inf)

#Na výpočet je možné použiť pokročilejšie nástroje – funkciu varTest
#Najprv si treba nainštalovať a načítať knižnicu - EnvStats 
#Obojstranný odhad:
varTest(x, conf.level = 0.9)$conf.int
#Jednostranné odhady:
varTest(x, alternative = "g", conf.level = 0.95)$conf.int
varTest(x, alternative = "l", conf.level = 0.95)$conf.int

#pr
cisla <- read_csv("cisla.csv")
age <- cisla$Age
