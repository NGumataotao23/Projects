
//tcpcss.java
//Nathan Gumataotao CSC138 11/2/25

import java.io.*;
import java.net.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.ConcurrentHashMap;

class TCPserver{

    private static final ConcurrentHashMap<String, PrintWriter> clientList = new ConcurrentHashMap<>();
    public static void main(String[] args) throws IOException {
        int port = 9090;  // default port
        if (args.length == 1) {
            port = Integer.parseInt(args[0]);
        }

        ServerSocket serverSocket = new ServerSocket(port);
        System.out.println("Waiting for Connections...");
        
        while (true) {
            Socket clientSocket = serverSocket.accept();
            Thread t = new Thread(new ClientHandler(clientSocket));
            t.start();
        }
    }
    

    static  class ClientHandler implements Runnable {
        
        
        
        private Socket clientSocket;
        
        ClientHandler(Socket socket) {this.clientSocket = socket;}
        
        @SuppressWarnings("ConvertToStringSwitch")
        public void run() {
            try (
                
                BufferedReader in = new BufferedReader( new InputStreamReader(clientSocket.getInputStream()));
                PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            ) {
                System.out.println("New Connection name is " + Thread.currentThread().getName() + " ip is:" + clientSocket.getInetAddress() + ", port:" + clientSocket.getPort());
                
                
                String clientName = in.readLine();
                if(clientName != null){
                    
                    clientList.putIfAbsent(clientName, out);
                    System.out.println(clientName + " has joined");
                    joinLeave(clientName, true);
                    out.println("Welcome " + clientName);

                }
                String clientMsg;
                while((clientMsg = in.readLine()) != null){
                    if(clientMsg.startsWith("/")){
                        if(clientMsg.equals("/quit")){
                            
                            clientList.remove(clientName,out);
                            joinLeave(clientName, false);
                            clientSocket.close();
                            System.out.println("["+ clientName + "]: has left");
                            break;
                        }
                        else if(clientMsg.equals("/who")){
                            out.println("Users:" + clientList);
                        }
                        else if(clientMsg.startsWith("/sendfile")){
                            
                            String[] sendCommand = clientMsg.trim().split("\\s+", 3);
                            String toUser = sendCommand[1];
                            String fileName = sendCommand[2];
                            String filePath = clientName + "/" + fileName;
                            Path path = Paths.get(filePath);
                            Long fileSize = Files.size(path);
                            Long fileSizeDis = fileSize / 1024;
                            if(!clientList.containsKey(toUser)){
                                out.println("User not Found try again");
                                continue;
                            }
                            PrintWriter x = clientList.get(toUser);
                            x.println("File transfer initiated between " + clientName + " and " + toUser + " " + fileName+ " " + fileSizeDis + "(KB)");
                            out.println("//Info " + toUser + " " + fileName + " " + fileSize);
                            continue;
                        }
                        else if(clientMsg.startsWith("/acceptfile")){
                            
                            String[] sendCommand = clientMsg.trim().split("\\s+", 3);
                            String fromUser = sendCommand[1];
                            PrintWriter x = clientList.get(fromUser);
                            x.println("/accepted");
                            x.println("File transfer accepted from " + clientName + " and " + fromUser);
                            out.println("Starting file Transfer between " + fromUser + " and " + clientName);
                            x.println("Starting file Transfer between " + clientName + " and " + fromUser);
                            continue;
                        }
                        else if(clientMsg.startsWith("//start")){
                            String[] sendCommand = clientMsg.trim().split("\\s+", 3);
                            String toUser = sendCommand[1];
                            String port = sendCommand[2];
                            PrintWriter x = clientList.get(toUser);
                            x.println("//startfile " + port);
                            System.out.println("check2");
                        }
                        else if(clientMsg.startsWith("/rejectfile")){
                            String[] sendCommand = clientMsg.trim().split("\\s+", 3);
                            String fromUser = sendCommand[1];
                            PrintWriter x = clientList.get(fromUser);
                            if(!clientList.containsKey(fromUser)){
                                out.println("User not Found try again");
                                continue;
                            }
                            x.println(clientName + " has rejected a file transfer request from " + fromUser);
                            continue;
                        }
                        else{
                            out.println("Error: Expecting Command");
                            continue;
                        }
                    }
                    if(!clientMsg.startsWith("/")){
                        System.out.println("["+ clientName + "]:" + clientMsg);
                        broadcast(clientMsg, clientName);
                    }
                    
                }   
            } catch (IOException e) {
                
                e.printStackTrace();
            } finally {
                try {
                    
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    private static void broadcast(String msg, String name){
        for(PrintWriter x : clientList.values()){
            
            x.println("["+ name + "]:" + msg);
        }
    }
    private static void joinLeave(String name, boolean f){
        for(PrintWriter x : clientList.values()){
            if (f) {
              x.println("["+ name + "]: has Joined");     
            }
            if(!f){
                x.println("["+ name + "]: has left");  
            }
        }
    }
      
}
