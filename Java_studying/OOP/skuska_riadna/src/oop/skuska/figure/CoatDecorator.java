package oop.skuska.figure;

public class CoatDecorator implements Figure {

    private final Figure figure;

    public CoatDecorator(Figure figure) {
        this.figure = figure;
    }

    @Override
    public void move() {
        figure.move();
        figure.setPosition(figure.getPosition() + 3);
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
