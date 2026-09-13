package oop.zadanie6;
import java.util.HashSet;
import java.util.Set;

public class Warehouse {
    private Set<Product> warehouse = new HashSet<Product>();

    public void addProduct(Product p) throws ProductAlreadyExistsException{
        if (warehouse.contains(p)){
            throw new ProductAlreadyExistsException(p.getId());
        }
        warehouse.add(p);
    }

    public void removeProduct(String id) throws ProductNotFoundException{
        for (Product p : warehouse){
            if (p.getId().equals(id)){
                warehouse.remove(p);
                return;
            }
        }
        throw new ProductNotFoundException(id);
    }

    public int getProductCount(){
        return warehouse.size();
    }

}
