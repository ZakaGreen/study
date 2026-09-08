package oop.skuska.figurefactory;

import oop.skuska.figure.Figure;
import oop.skuska.figure.kral_modr;
import oop.skuska.figure.pesiak_modr;
import oop.skuska.figure.strelec_modr;

public class BlueFigureFactory implements FigureFactory {

    @Override
    public Figure createPawn() {
        return new pesiak_modr();
    }

    @Override
    public Figure createBishop() {
        return new strelec_modr();
    }

    @Override
    public Figure createQueen() {
        return new kral_modr();
    }
}
