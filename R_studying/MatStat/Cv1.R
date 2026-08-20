uvod <- c(165, 171, 194, 184, 164, 142, 198, 177, 166, 130, 159, 179, 181, 163)
uvod

n<-length(uvod)
min(uvod)
max(uvod)
range(uvod)

(udaje <- sort(uvod))

(xm <- sum(udaje)/n) #to iste
(mean(udaje)) #to iste

(s2 <- var(udaje)) #rozplyn (E(xi - x_)^2/n-1)
(s<-sd(udaje)) #odmocnina s2

median(udaje)
quantile(udaje) #0/25/50/75/100 #9 typov vypoctu

quantile(udaje, type=1) #0/25/50/75/100 #1 typ(budeme ho vzdy pouzivat)
quantile(udaje, 0.15, type=1)

IQR(udaje, type=1) #Medzikvartilové rozpätie

#sikmost #treba psych
skew(udaje)

#spicotost #treba psych
kurtosi(udaje)

hist(udaje, breaks="Sturges", main="HGr", xlab="vyska", ylab = "pocetnost")

#Rozloženie údajov na 1 osi
stripchart(udaje) 

#Krabicový diagram (boxplot)
boxplot(udaje)
boxplot(udaje, horizontal=T)

#Koláčový diagram
pocty <- c(1,1,1,2,2,3,3,3,3,4,5,5,7,8,9,9)
tp <- table(pocty)
pie(tp)

getwd() #Посмотреть, где ты сейчас 
#Поменять её на папку, где лежит cisla.csv
#setwd("D:/C/test/STU/R_studying")
cisla <- read_csv("cisla.csv")
bmi <- cisla$BMI
