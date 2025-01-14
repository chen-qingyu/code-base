import javax.swing.*;
import java.awt.*;

public class View extends JPanel
{
    private static final int GRID_SIZE = 16;
    private final Field field;

    public View(Field field)
    {
        this.field = field;
    }

    @Override
    public void paint(Graphics g)
    {
        super.paint(g);
        for (int row = 0; row < field.getHeight(); row++)
        {
            for (int col = 0; col < field.getWidth(); col++)
            {
                g.drawRect(col * GRID_SIZE, row * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                if (field.isAlive(row, col))
                {
                    g.fillRect(col * GRID_SIZE, row * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                }
            }
        }
    }

    @Override
    public Dimension getPreferredSize()
    {
        return new Dimension(field.getWidth() * GRID_SIZE + 1, field.getHeight() * GRID_SIZE + 1);
    }
}
