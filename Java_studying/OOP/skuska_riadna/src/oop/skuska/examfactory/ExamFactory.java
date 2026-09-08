package oop.skuska.examfactory;

import oop.skuska.figure.CoatDecorator;
import oop.skuska.figure.Figure;
import oop.skuska.figure.ShoesDecorator;
import oop.skuska.figurefactory.BlueFigureFactory;
import oop.skuska.figurefactory.FigureFactory;
import oop.skuska.figurefactory.RedFigureFactory;

public class ExamFactory {

    public static FigureFactory createRedFigureFactory() {
        return new RedFigureFactory();
    }

    public static FigureFactory createBlueFigureFactory() {
        return new BlueFigureFactory();
    }

    public static Figure createCoat(Figure figure) {
        return new CoatDecorator(figure);
    }

    public static Figure createShoes(Figure figure) {
        return new ShoesDecorator(figure);
    }
}
