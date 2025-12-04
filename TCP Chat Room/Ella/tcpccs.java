
//counterclient in Java
import java.io.*;
import java.net.*;


class countclient{
    private static final Object lock = new Object();
    public static void main(String[] args) throws Exception {
        //defining the client message and the servers response message
        String clientName;
        String serverResponseLogin;
        
        //takes input from user
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader((System.in)));
        //creates socket for client to connect with host 
        Socket clientSocket = new Socket("localhost",9090);

        // creates connection to server based on socket and allows us to send things to server
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        //similar to inFromUser but gets info backfromserver via the port connection
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));


        outToServer.writeBytes(args[1] +'\n');
        
        
        
        clientRecieve info = new clientRecieve(inFromServer,outToServer,clientSocket);
        Thread recieveMsg = new Thread(info);
        recieveMsg.start();
        String send;
       
        while((send = inFromUser.readLine()) != null){
            
            outToServer.writeBytes(send + '\n');
            if(send.equals("/quit")){
                break;
            }
            
        }
       
        clientSocket.close();
    }
    
    static class clientRecieve implements Runnable{
        
        BufferedReader infromServer;
        DataOutputStream outToServer;
        Socket client;
        
        clientRecieve(BufferedReader in, DataOutputStream out, Socket clientSocket) {
            this.infromServer = in;
            this.client = clientSocket;
            this.outToServer = out;
        }
            public void run(){
                try {
                String msg;
                String toClientN = "";
                String fileName = "";
                Long fileSize = 0l;
                while((msg = infromServer.readLine()) != null){
                    
                    if(msg.startsWith("//Info")){
                        String[] sendCommand = msg.trim().split("\\s+", 4);
                        toClientN = sendCommand[1];
                        fileName = sendCommand[2];
                        fileSize = Long.valueOf(sendCommand[3]);
                        continue;
                    }
                    else if (msg.startsWith("/accepted")){
                        int port = 1234;
                        ServerSocket FTSocket = new ServerSocket(port);
                        outToServer.writeBytes("//start " + toClientN + " " + port + " " + '\n');
                        Socket cSocket = FTSocket.accept();
                        Thread fTransfer = new Thread(new fileTransferSend(toClientN,fileName,fileSize,cSocket));
                        fTransfer.start();
                        continue;
                    }
                    else if(msg.startsWith("//startfile")){
                        String[] sendCommand = msg.trim().split("\\s+", 4);
                        String x = sendCommand[1];
                        int port = Integer.parseInt(x);
                        Socket transferSocket = new Socket("localhost", port);
                        Thread fileTransferR = new Thread(new fileTransferRecieve(toClientN,fileSize,transferSocket));
                        fileTransferR.start();
                        continue;
                    }
                    else{
                    System.out.println(msg);
                    }
                    continue;
                    
                }
                } catch (IOException e) {
                System.out.println("Connection closed. CRTL+C to continue");
                }finally {
                    try {
                    client.close();
                    } catch (IOException e) {
                    e.printStackTrace();
                    }
                }   
                
            }
    }

    static class fileTransferSend implements Runnable{
        private String sendingToo;
        private String fileName;
        private long fileSize;
        private Socket clientSocket;
        
        public fileTransferSend(String s, String f,Long size, Socket c) {
            this.sendingToo = s;
            this.fileName = f;
            this.fileSize = size;
            this.clientSocket = c;
        }
            public void run(){
                File directory = new File(fileName);
                
            
                try(
                DataOutputStream out = new DataOutputStream(new BufferedOutputStream(clientSocket.getOutputStream()));
                BufferedInputStream file = new BufferedInputStream(new FileInputStream(directory));
                ){
                    

                    out.writeUTF(fileName);
                    out.writeLong(directory.length());
                    byte[] buffer = new byte[8192];

                    if(!directory.exists()){
                            System.out.println("File Not Found");
                    }
                    else{
                        int n;
                        while((n = file.read(buffer)) != -1){
                            out.write(buffer, 0,n);
                        }
                    }    
                    out.flush();
  
                }catch(IOException e){
                    e.printStackTrace();
                }finally{
                    try{
                        clientSocket.close();
                    } catch(IOException e){
                        e.printStackTrace();
                    }
                }
                
            }
        

    }
    static class fileTransferRecieve implements Runnable{
        private String sendingToo;
        private long fileSize;
        private Socket transferSocket;
        public fileTransferRecieve(String s,Long f, Socket c) {
            this.sendingToo = s;
            this.fileSize = f;
            this.transferSocket = c;
        }
       
        
        public void run(){
            try{
                DataInputStream file = new DataInputStream(new BufferedInputStream(transferSocket.getInputStream()));
                String fileName = file.readUTF();
                long left = file.readLong();
                File output = new File(fileName);
                BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(output));

                

                while(left > 0){
                    byte[] buffer = new byte[8192];
                    int n = file.read(buffer);
                    if (n == -1) throw new EOFException("End");
                    out.write(buffer, 0,n);
                    left -= n;
                }
                out.flush();

            } catch (Exception e) {
                e.printStackTrace();
            }finally{
                    try{
                        transferSocket.close();
                    } catch(IOException e){
                        e.printStackTrace();
                    }
                }
        }
    }
}
