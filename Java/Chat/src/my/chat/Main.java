package my.chat;

public class Main
{
    public static void main(String[] args)
    {
        new Thread(Server::new).start();
        new Thread(Client::new).start();
    }
}
