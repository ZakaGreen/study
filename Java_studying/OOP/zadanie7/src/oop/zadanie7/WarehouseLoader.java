package oop.zadanie7;

import java.io.*;
import java.time.LocalDate;
import java.util.*;

public class WarehouseLoader {

    public List<Product> loadProducts(String filename) throws InvalidProductFormatException {
        List<Product> list = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String row;

            while ((row = br.readLine()) != null) {
                String[] data = row.split(",");

                if (data.length != 5) {
                    throw new InvalidProductFormatException("Bad format");
                }

                String typ = data[0];
                String id = data[1];
                String nazov = data[2];
                double cena = Double.parseDouble(data[3]);

                if (typ.equals("E")) {
                    int zaruka = Integer.parseInt(data[4]);
                    list.add(new ElectronicProduct(id, nazov, cena, zaruka));
                } else if (typ.equals("P")) {
                    LocalDate datum = LocalDate.parse(data[4]);
                    list.add(new PerishableProduct(id, nazov, cena, datum));
                } else {
                    throw new InvalidProductFormatException("Bad type");
                }
            }

        } catch (Exception e) {
            throw new InvalidProductFormatException("Bad format");
        }

        Collections.sort(list);
        return list;
    }

    public void saveProducts(List<Product> products, String filename) {
        try (PrintWriter pw = new PrintWriter(new FileWriter(filename))) {
            for (Product p : products) {
                if (p instanceof ElectronicProduct) {
                    ElectronicProduct ep = (ElectronicProduct) p;
                    pw.println("E," + ep.getId() + "," + ep.getName() + "," + ep.getPrice() + "," + ep.getWarrantyMonths());
                } else if (p instanceof PerishableProduct) {
                    PerishableProduct pp = (PerishableProduct) p;
                    pw.println("P," + pp.getId() + "," + pp.getName() + "," + pp.getPrice() + "," + pp.getExpirationDate());
                }
            }
        } catch (IOException e) {
            System.out.println("Chyba pri zapise suboru");
        }
    }
}