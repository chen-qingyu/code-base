public class Painting
{
    public static void main(String[] args)
    {
        Picture pic = new Picture(420, 300);
        Circle c1 = new Circle(320, 50, 40);
        Rectangle r1 = new Rectangle(100, 100, 100, 100);
        Triangle t1 = new Triangle(100, 100, 200, 100, 150, 50);
        Line l1 = new Line(0, 205, 400, 205);
        pic.add(c1);
        pic.add(r1);
        pic.add(t1);
        pic.add(l1);
        pic.draw();
    }
}
