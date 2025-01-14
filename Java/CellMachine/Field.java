public class Field
{
    private final int width;
    private final int height;
    private final Cell[][] field;
    private final int[][] neighbours;

    public Field(int width, int height)
    {
        this.width = width;
        this.height = height;
        field = new Cell[height][width];
        neighbours = new int[height][width];

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                field[row][col] = new Cell();
                if (Math.random() < 0.2)
                {
                    field[row][col].setAlive(true);
                }
            }
        }
    }

    public int getWidth()
    {
        return width;
    }

    public int getHeight()
    {
        return height;
    }

    public boolean isAlive(int row, int col)
    {
        if (row < 0 || row >= height || col < 0 || col >= width)
        {
            return false;
        }
        return field[row][col].isAlive();
    }

    public int getNeighbour(int row, int col)
    {
        int cnt = 0;
        for (int r = row - 1; r <= row + 1; r++)
        {
            for (int c = col - 1; c <= col + 1; c++)
            {
                if (!(r == row && c == col) && isAlive(r, c))
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    public void update()
    {
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                neighbours[row][col] = getNeighbour(row, col);
            }
        }

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                field[row][col].update(neighbours[row][col]);
            }
        }
    }
}
