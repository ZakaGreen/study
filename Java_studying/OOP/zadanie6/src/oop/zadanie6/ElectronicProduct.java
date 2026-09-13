package oop.zadanie6;

public class ElectronicProduct extends Product implements Discountable{
    int warrantyMonths;

    public ElectronicProduct(String id, String name, double price, int warrantyMonths){

        super(id, name, price);
        this.warrantyMonths = warrantyMonths;

    }

    public int getWarrantyMonths() {
        return warrantyMonths;
    }

    public void setWarrantyMonths(int warrantyMonths) {
        this.warrantyMonths = warrantyMonths;
    }

    @Override
    public void applyDiscount(double percentage) {
        if (percentage > 100 || percentage < 0){
            return;
        }
        double cena = this.getPrice();
        cena *= (100 - percentage) / 100;
        this.setPrice(cena);
    }
}
