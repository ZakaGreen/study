setwd("D:/C/test/STU/RStidio")
x <- c(3, 4, 7, 8, 9, 11, 12, 13, 16, 17)
n <- length(x)
xm <- mean(x) #(xm <- sum(x)/n)
s2 <- 22
s1 <- sqrt(22)
u <- qnorm(0.95) #квантильная функция нормального распределения
                #u здесь это просто обозначение критического 
                #значения стандартного нормального распределения.
d <- (u*s1)/sqrt(n) #d — это полуширина доверительного интервала
ISO <- xm + c(-1.1)*d
ISL <- c(-Inf,xm+d)
ISP <- c(xm-d,Inf)
ZTest(x,sd_pop = sqrt(22),conf.level = 0.9)$conf.int
ZTest(x,sd_pop = sqrt(22),alternative = "g")$conf.int
ZTest(x,sd_pop = sqrt(22),alternative = "l")$conf.int

#2
s1 <- sd(x)
u <- qt(0.95,n-1)
d <- u*s1/sqrt(n)
ISO <- xm + c(-1,1)*d
ISL <- c(-Inf,xm+d)
ISP <- c(xm-d,Inf)
t.test(x,conf.level = 0.9)$conf.int

#3
s2 <- var(x)
u2 <- qchisq(0.95,n-1)
u1 <- qchisq(0.05,n-1)
isox <- s2*(n-1)/c(u2,u1)

#pr
cisla <- read_csv("cisla.csv")
age <- cisla$Age
