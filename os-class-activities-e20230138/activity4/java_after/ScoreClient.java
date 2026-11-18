// package os-class-activities-e20230138.activity4.java_after;

import java.io.*;
import java.net.*;

public class ScoreClient {
    private static final int PORT = 9012;

    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.out.println("Usage: java ScoreClient 192.168.71.175 TEAV Encheng");
            return;
        }

        String serverIp = args[0];
        String name = args[1];

        Socket socket = new Socket(serverIp, PORT);
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        out.println(name);
        System.out.println(in.readLine());

        socket.close();
    }
}