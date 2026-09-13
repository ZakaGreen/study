#1 H0: σ^2a = σ^2b, alfa = 5% / H1: σ^2a ≠ σ^2b
a <- c(14, 19, 15, 17, 16, 20, 11, 18, 20, 9, 13, 14, 17, 12, 20, 17, 18)
b <- c(12, 14, 9, 11, 16, 11, 7, 7, 5, 8, 14, 15, 8, 19, 17, 10, 12, 9, 11)
boxplot(a,b,horizontal = T)

shapiro.test(a)
shapiro.test(b)

#тест для равенства дисперсий, так как для данного типа доказательства равенства μ, требуется доказать равенство D
var.test(a,b) #тестирует сразу Fнабл между Fкр(a,k1;k2); k1 = m - 1; k2 = n -1;
# 0.2947195 < 0.6191 < 2.1142712

# H0: μa = μb, tj. μa - μb = 0; alfa = 5% // H1: μa ≠ μb
t.test(a,b,paired=F,var.equal = T)  #paired=F – nechceme párový test
                                    #var.equal = T – overili sme, že disperzie sa môžu považovať za zhodné
#2
p <- c(18, 19, 19, 17, 20, 18, 16, 19, 20, 19)
q <- c(4, 17, 2, 16, 10, 5, 8, 19, 4, 7, 8, 5, 2)

#Проверим, нормально ли разделены векторы? 
#если p-value меньше alfa, то гипотезу нормальности отвергаем
shapiro.test(p)
shapiro.test(q)

var.test(p,q)
# Hodnota p-value je extrémne malá, hypotézu o zhode rozptylov zamietame.
#V takomto prípade je možné použiť Welchov test, pri ktorom sa zhoda rozptylov nevyžaduje. 
t.test(p,q,paired=F,var.equal = F)
#Hodnota p-value je takmer nulová. Hypotézu zamietame

#3
setwd("D:/C/test/STU/R_studying")
getwd()
data <- read_xlsx("data_vyuka.xlsx") #В объекте data теперь лежит полная таблица из файла со всеми строками, включая строки, где какие-то ячейки пустые
new_data <- na.omit(data) #Функция na.omit(data) возвращает новую таблицу, в которой, выкинуты все строки, где хотя бы в одном столбце есть NA

mprij <- new_data$mprij
vzd <- new_data$vzdelanie

tapply(mprij,vzd,shapiro.test)

