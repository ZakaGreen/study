vx <- c(9.9, 9.87, 10.11, 10.08, 10.21, 9.94, 10.04, 10.24, 9.84, 9.79, 10.17, 10.01, 10.13, 9.88, 9.97)
(n <- length(vx)) #15
(xm <- mean(vx)) #10.012
(s2 <- var(vx)) #0.02007429

#I
alfa <- 0.05
#II
u2 <- qchisq(0.975,n-1)
u1 <- qchisq(0.025,n-1)
c(u1,u2) #u1 = 5.628726; u2 = 26.118948
#III
(isox <- s2*(n-1)/c(u2,u1)) #0.01076000 0.04992959
(ux <- (n-1)*s2/0.0169) #16.62959
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

