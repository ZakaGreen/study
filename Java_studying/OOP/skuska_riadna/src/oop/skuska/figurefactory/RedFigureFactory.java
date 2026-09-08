package oop.skuska.figurefactory;

import oop.skuska.figure.Figure;
import oop.skuska.figure.kral_cerv;
import oop.skuska.figure.pesiak_cerv;
import oop.skuska.figure.strelec_cerv;

public class RedFigureFactory implements FigureFactory {

    @Override
    public Figure createPawn() {
        return new pesiak_cerv();
    }

    @Override
    public Figure createBishop() {
        return new strelec_cerv();
    }

    @Override
    public Figure createQueen() {
        return new kral_cerv();
    }
}