package oop.zadanie7;

import java.util.*;

public class Warehouse {
    private Map<String, Product> products;

    public Warehouse() {
        this.products = new HashMap<>();
    }

    public void addProduct(Product p) throws ProductAlreadyExistsException {
        String id = p.getId();

        if (products.containsKey(id)) {
            throw new ProductAlreadyExistsException("Product already exists");
        }

        products.put(id, p);
    }

    public void removeProduct(String id) throws ProductNotFoundException {
        if (!products.containsKey(id)) {
            throw new ProductNotFoundException("Product s ID '" + id + "' sa v sklade nenachádza.");
        }

        products.remove(id);
    }

    public Product getProduct(String id) {
        return products.get(id);
    }

    public int getProductCount() {
        return products.size();
    }

    public double calculateTotalValue() {
        double sum = 0;

        for (Product p : products.values()) {
            sum = sum + p.getPrice();
        }

        return sum;
    }

    public List<Product> findProductsByPriceRange(double min, double max) {
        List<Product> list = new ArrayList<>();

        for (Product p : products.values()) {
            double price = p.getPrice();

            if (price >= min && price <= max) {
                list.add(p);
            }
        }

        return list;
    }

    public List<Product> getProductsSortedByPrice() {
        List<Product> lst = new ArrayList<>(products.values());

        lst.sort(Comparator.comparingDouble(Product::getPrice));

        return lst;
    }

    public List<Product> getProductsSortedById() {
        List<Product> lst  = new ArrayList<>(products.values());

        Collections.sort(lst);

        return lst ;
    }

    public Product findProductWithSmallestId() {
        Product min = null;

        for (Product p : products.values()) {
            if (min == null) {
                min = p;
            } else if (p.compareTo(min) < 0) {
                min = p;
            }
        }

        return min;
    }

    public <T extends Product> List<T> getProductsByType(Class<T> type) {
        List<T> lst = new ArrayList<>();

        for (Product p : products.values()) {
            if (type.isInstance(p)) {
                T product = type.cast(p);
                lst.add(product);
            }
        }

        return lst;
    }

}
