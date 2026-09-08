package oop.skuska.figure;

public abstract class AbstractFigure implements Figure {

    protected int position = 0;
    protected final int step;

    protected AbstractFigure(int step) {
        this.step = step;
    }

    @Override
    public void move() {
        position += step;
    }

    @Override
    public int getPosition() {
        return position;
    }

    @Override
    public void setPosition(int position) {
        this.position = position;
    }
}