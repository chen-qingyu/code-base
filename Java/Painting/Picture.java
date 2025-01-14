import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Picture extends JFrame
{
    private final int width;
    private final int height;

    private final ArrayList<Shape> shapes = new ArrayList<>();

    private class ShapesPanel extends JPanel
    {
        @Override
        protected void paintComponent(Graphics g)
        {
            super.paintComponent(g);
            for (Shape s : shapes)
            {
                s.draw(g);
            }
        }
    }

    public void add(Shape s)
    {
        shapes.add(s);
    }

    public Picture(int width, int height)
    {
        add(new ShapesPanel());
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.width = width;
        this.height = height;
    }

    public void draw()
    {
        setLocationRelativeTo(null);
        setSize(width, height);
        setVisible(true);
    }
}
