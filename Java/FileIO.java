import java.io.*;

public class FileIO {
    public static void main(String[] args) {
        writeText();
        readText();

        writeData();
        readData();
    }

    public static void writeText() {
        try (BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("./test.txt")))) {
            bw.write("呀呀呀\n啦啦啦");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void readText() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("./test.txt")))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }


    public static void writeData() {
        try (DataOutputStream dos = new DataOutputStream(new BufferedOutputStream(new FileOutputStream("test.dat")))) {
            dos.writeUTF("二进制文件");
            dos.writeInt(233);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void readData() {
        try (DataInputStream dis = new DataInputStream(new BufferedInputStream(new FileInputStream("./test.dat")))) {
            System.out.println(dis.readUTF() + ", " + dis.readInt());
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
