import javax.swing.JFrame;

public class CellMachine
{
    public static void main(String[] args) throws InterruptedException
    {
        Field field = new Field(50, 50);

        View view = new View(field);
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setTitle("CellMachine");
        frame.add(view);
        frame.pack();
        frame.setVisible(true);

        int i = 0;
        while (true)
        {
            System.out.println("UPDATE: " + (i++));
            Thread.sleep(100);
            field.update();
            frame.repaint();
        }
    }
}
