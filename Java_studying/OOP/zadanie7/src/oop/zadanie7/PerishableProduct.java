package oop.zadanie7;

import java.time.LocalDate;

public class PerishableProduct extends Product {
    private LocalDate expirationDate;

    public PerishableProduct(String id, String name, double price, LocalDate expirationDate) {
        super(id, name, price);
        this.expirationDate = expirationDate;
    }

    public LocalDate getExpirationDate() {
        return expirationDate;
    }

    public void setLocalDate(LocalDate LocalDate) {
        this.expirationDate = LocalDate;
    }

    @Override
    public String toString() {
        return "PerishableProduct{" +
                "id='" + getId() + '\'' +
                ", name='" + getName() + '\'' +
                ", price=" + getPrice() +
                ", expirationDate=" + expirationDate +
                '}';
    }

    public boolean isExpired(){
        return expirationDate.isBefore(LocalDate.now());
    }
}
