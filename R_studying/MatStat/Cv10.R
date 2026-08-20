#Pr1
#Senzor na meranie koncentrácie metánu v ovzduší je nastavený tak, aby spustil alarm pri
#úrovni 10 promile. Na základe testovaní sa ešte môže upraviť jeho kalibrácia, je však
#potrebné, aby výsledky meraní boli čo najviac konzistentné. Výrobca v tejto otázke garantuje
#rozptyl hodnôt sigma2 = 0.0169 = 0.13^2. Pri testovaní senzora boli v 15 meraniach zistené
#nasledujúce hodnoty koncentrácií spúšťajúcich alarm:
  
vx <- c(9.9, 9.87, 10.11, 10.08, 10.21, 9.94, 10.04, 10.24, 9.84, 9.79, 10.17, 10.01, 10.13, 9.88, 9.97)
#Testujme na hladine významnosti 5% výrobcom deklarovaný rozptyl konfrontovaný s nameranými údajmi.
(n <- length(vx)) #15
(xm <- mean(vx)) #10.012
(s2 <- var(vx)) #0.02007429

u2 <- qchisq(0.975,n-1)
u1 <- qchisq(0.025,n-1)
#Тут мы ищем 2 крит значения, так как граффик не симетричен => 0.975 = 0.95 + 5%/2
c(u1,u2) #u1 = 5.628726; u2 = 26.118948

(isox <- s2*(n-1)/c(u2,u1)) #0.01076000 0.04992959 #доверительный интервалл для сигмы
#Hypotetické σ2 = 0.0169 sa nachádza v intervale spoľahlivosti (0.01076, 0.05) Hypotézu preto nezamietame.
(ux <- (n-1)*s2/0.0169) #16.62959 #uнабл

(2*(1-pchisq(ux,14))) #0.55291
varTest(vx,sigma.squared = 0.13^2)

plot(function(vx)dchisq(vx,14),from=0, to =50,
     main=("Test pre sigma^2"),ylab="hustota")
abline(v=16.63,col="blue")
abline(v=qchisq(0.975,14),col="red")
abline(v=qchisq(0.025,14),col="red")
legend("topright",legend=c("Hranica krit. oblasti",
                           "Statistika T"),
       col=c("red","blue"),lty=c(1,1),cex=0.5
)

#Domaca uloha
#Nechajte si vygenerovať vektor náhodných čísel s normálnym rozdelením.
#Hodnoty a,b,n si zvoľte podľa dátumu svojho narodenia (a=deň, b=mesiac,n=rok)

x <- 11+4*rnorm(2004)

#Testujte na hladine alfa= 2% hypotézu o strednej hodnote μ = a a o rozptyle σ2 = b^2.
#Testujte* obojstranne aj jednostranne z oboch strán, k „pohľadu II“ nechajte vykresliť obrázky. 

(len <- length(x))
(xe <- mean(x))
(s2new <- var(x))
(snew <- sd(x))
(unew <- qt(0.99,len-1))
uxnew <- sqrt(len) * abs(xe-11)/snew

u2new <- qchisq(0.99,len-1)
u1new <- qchisq(0.01,len-1)
(uxdisnew <- (len-1)*s2new/16)
