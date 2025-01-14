import java.awt.*;

public class Rectangle implements Shape
{
    private final int x;
    private final int y;
    private final int width;
    private final int height;

    public Rectangle(int x, int y, int width, int height)
    {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    @Override
    public void draw(Graphics g)
    {
        g.drawRect(x, y, width, height);
    }
}
