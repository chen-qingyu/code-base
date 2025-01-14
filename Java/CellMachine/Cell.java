class Cell
{
    private boolean alive = false;

    public boolean isAlive()
    {
        return alive;
    }

    public void setAlive(boolean alive)
    {
        this.alive = alive;
    }

    public void update(int neighbour)
    {
        if (neighbour < 2 || neighbour > 3)
        {
            alive = false;
        }
        else if (neighbour == 3)
        {
            alive = true;
        }
        // else neighbour == 2 keep alive unchanged
    }
}
