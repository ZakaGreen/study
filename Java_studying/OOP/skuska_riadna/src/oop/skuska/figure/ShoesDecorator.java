package oop.skuska.figure;

public class ShoesDecorator implements Figure {

    private final Figure figure;

    public ShoesDecorator(Figure figure) {
        this.figure = figure;
    }

    @Override
    public void move() {
        int before = figure.getPosition();
        figure.move();
        int delta = figure.getPosition() - before;
        figure.setPosition(before + delta * 2);
    }

    @Override
    public int getPosition() {
        return figure.getPosition();
    }

    @Override
    public void setPosition(int position) {
        figure.setPosition(position);
    }
}
