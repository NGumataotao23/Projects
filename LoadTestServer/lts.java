//Nathan Gumataotao, Load Test Server, December 1, 2025, CSC138
import java.io.*;
import java.net.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;


//============================================================================
// lts - Load Test Server
//
// A multi-phase HTTP/1.1 server implementation for teaching computer
// networking concepts. Supports basic request/response, persistent
// connections with keep-alive, and virtual thread concurrency.
//
// Phase 1: Basic HTTP server with GET requests and static file serving
// Phase 2: HTTP/1.1 keep-alive with connection persistence
// Phase 3: Virtual threading for high-concurrency workloads
//
// Usage: java lts.java [options] [port]
//   -t            Enable virtual threading (Java 21+)
//   -k [timeout]  Enable keep-alive with optional timeout
//   -q            Quiet mode (disable request logging)
//   -h, --help    Show usage information
//
//============================================================================


public class lts {
    private static final int DEFAULT_PORT = 8080;
    private static final String PUBLIC_DIR = "public";
    private static final int DEFAULT_KEEPALIVE_TIMEOUT = 5;


    private boolean quiet = false;
    private boolean keepAlive = false;
    private int keepAliveTimeout = DEFAULT_KEEPALIVE_TIMEOUT;


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // main
    //
    // Entry point - creates server instance and delegates to appMain.
    // Enables single-source execution via 'java lts.java'.
    //
    public static void main(String[] args) {
        new lts().appMain(args);
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // appMain
    //
    // Configures and runs the HTTP server based on command-line arguments.
    // Parses options for threading mode, keep-alive, and logging, then
    // enters the main server loop to accept and dispatch connections.
    //
    // The server uses a strategy pattern to separate basic single-request
    // handling from keep-alive multi-request handling, allowing students
    // to implement phases incrementally without breaking prior work.
    //
    public void appMain(String[] args) {
        int port = DEFAULT_PORT;
        boolean threaded = false;


        // Parse command-line arguments
        for (int i = 0; i < args.length; i++) {
            if (args[i].equals("-t")) {
                // Enable virtual threading (Phase 3)
                threaded = true;
            } else if (args[i].equals("-q")) {
                // Quiet mode - suppress per-request logging
                quiet = true;
            } else if (args[i].equals("-k")) {
                // Enable keep-alive with optional timeout (Phase 2)
                keepAlive = true;
                if (i + 1 < args.length) {
                    try {
                        int timeout = Integer.parseInt(args[i + 1]);
                        keepAliveTimeout = timeout;
                        i++; // Consume the timeout argument
                    } catch (NumberFormatException e) {
                        // Next arg is not a number, use default timeout
                        keepAliveTimeout = DEFAULT_KEEPALIVE_TIMEOUT;
                    }
                }
            } else if (args[i].equals("-h") || args[i].equals("--help")) {
                // Show help and exit
                printUsage();
                System.exit(0);
            } else {
                // Any other numeric argument is treated as port number
                try {
                    port = Integer.parseInt(args[i]);
                } catch (NumberFormatException e) {
                    System.err.println("Invalid port number, using default: " + DEFAULT_PORT);
                }
            }
        }


        // Create server socket and enter main loop
        try (ServerSocket serverSocket = new ServerSocket(port)) {
            // Display server configuration
            System.out.println("Server started on port " + port);
            System.out.println("Mode: " + (threaded ? "Virtual Threaded" : "Single Threaded"));
            System.out.println("Logging: " + (quiet ? "Quiet" : "Verbose"));
            System.out.println("Keep-Alive: " + (keepAlive ? "Enabled (timeout: " + keepAliveTimeout + "s)" : "Disabled"));
            System.out.println("Static files served from: " + PUBLIC_DIR);


            // Main server loop - accept and dispatch connections
            while (true) {
                try {
                    Socket clientSocket = serverSocket.accept();


                    if (threaded) {
                        // Phase 3: Handle connection in virtual thread
                        handleConnectionThreaded(clientSocket);
                    } else {
                        // Phase 1/2: Handle connection synchronously on main thread
                        handleConnection(clientSocket);
                        clientSocket.close();
                    }
                } catch (IOException e) {
                    System.err.println("Error accepting connection: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            System.err.println("Could not start server: " + e.getMessage());
        }
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // printUsage
    //
    // Displays command-line help with available options and examples.
    //
    private void printUsage() {
        System.out.println("Usage: java lts.java [options] [port]");
        System.out.println("Options:");
        System.out.println("  -t                Enable virtual threading");
        System.out.println("  -q                Quiet mode (disable per-request logging)");
        System.out.println("  -k [timeout]      Enable keep-alive (optional timeout in seconds, default: 5)");
        System.out.println("  -h, --help        Show this help message");
        System.out.println();
        System.out.println("Examples:");
        System.out.println("  java lts.java 8080           Start server on port 8080");
        System.out.println("  java lts.java -t 8080        Start with virtual threading");
        System.out.println("  java lts.java -k 8080        Start with keep-alive (5s timeout)");
        System.out.println("  java lts.java -k 30 8080     Start with keep-alive (30s timeout)");
        System.out.println("  java lts.java -t -k -q 8080  All options combined");
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Request Handling Strategy
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // handleConnection
    //
    // Dispatches to appropriate handler based on keep-alive mode.
    // Strategy pattern: basic handler for single requests, keep-alive
    // handler for persistent connections.
    //
    
    private void handleConnection(Socket socket) throws IOException {
        if(keepAlive){
            handleWithKeepAlive(socket);
        }
        else if(!keepAlive){
            handleBasic(socket);
        }
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // handleBasic
    //
    // Handles a single HTTP request and closes the connection.
    //
    // This is the simpler handler used when keep-alive is disabled. It reads
    // one request, validates it, dispatches to the appropriate endpoint
    // handler, and returns. The connection is closed by the caller after
    // this method returns.
    //
   
    private void handleBasic(Socket socket) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        OutputStream out = socket.getOutputStream();


        String clientRequest = in.readLine();
        if(clientRequest == null || clientRequest.isEmpty()){
            return;
        }
        Map headers = parseHeaders(in);
        String request[] = validateRequest(clientRequest);
        if(!"GET".equals(request[0])){
            sendError(out, 405, "Method not Allowed", false);
        }
        
        dispatchRequest(out, request[1], false);


    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // handleWithKeepAlive
    //
    // Handles multiple HTTP requests on a single connection with timeout.
    //
    // This handler implements HTTP/1.1 persistent connections. It loops to
    // process multiple requests on the same TCP connection, reducing the
    // overhead of connection setup/teardown. The loop exits when:
    //   - Client sends "Connection: close" header
    //   - Socket timeout expires (no request within keepAliveTimeout seconds)
    //   - Client closes connection (readLine returns null)
    //   - An error occurs
    //

    private void handleWithKeepAlive(Socket socket) throws IOException {
       socket.setSoTimeout(keepAliveTimeout * 1000);
       BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
       OutputStream out = socket.getOutputStream();
       boolean clientWantsClose = false;

       String clientRequest;
       while(true){
            try {
                 clientRequest = in.readLine();
            } catch (Exception e) {
                sendError(out, 408, "Request Timeout", false);
                break;
            }
            if(clientRequest == null || clientRequest.isEmpty()){return;}
            Map<String, String> headers = parseHeaders(in);
            String[] request = validateRequest(clientRequest);

            if(headers.getOrDefault("Connection", "").equalsIgnoreCase("close")){
                clientWantsClose = true;
            }
            Boolean shouldKeepAlive = !clientWantsClose;

            dispatchRequest(out, request[1], shouldKeepAlive);


       }
       
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // handleConnectionThreaded
    //
    // Handles a connection in a new virtual thread.
    //
    // This method spawns a virtual thread to handle the connection,
    // allowing the server to process multiple requests concurrently.
    // Virtual threads are lightweight and can scale to thousands of
    // concurrent connections without the overhead of platform threads.
    //
  
    private void handleConnectionThreaded(Socket socket) {
        Thread vThread = Thread.ofVirtual().start(() -> { 
            try {handleConnection(socket);} 
            catch (Exception e){ 
                System.err.println("Could not Handle Connection Thread");
                
            }
            finally{
                try {
                    socket.close();
                } catch (Exception e) {
                    System.err.println("Could not close Socket Properly");
                    
                }
            }
        
        });

    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Request Processing Utilities
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // parseHeaders
    //
    // Reads HTTP headers from input stream and returns them as a map.
    // Header names are normalized to lowercase for case-insensitive lookup.
    //
    // HTTP headers follow the format "Header-Name: value" and are terminated
    // by a blank line. This method reads until it encounters the blank line,
    // building a map of header name -> value pairs.
    //
    private Map<String, String> parseHeaders(BufferedReader in) throws IOException {
        Map<String, String> headers = new HashMap<>();
        String line;


        // Read lines until we hit the blank line separating headers from body
        while ((line = in.readLine()) != null && !line.isEmpty()) {
            int colonIndex = line.indexOf(':');
            if (colonIndex > 0) {
                String headerName = line.substring(0, colonIndex).trim().toLowerCase();
                String headerValue = line.substring(colonIndex + 1).trim();
                headers.put(headerName, headerValue);
            }
        }


        return headers;
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // validateRequest
    //
    // Validates request line format and returns [method, path] array.
    // Returns null if request is malformed.
    //
    // Expected format: "METHOD /path HTTP/version"
    // Example: "GET /index.html HTTP/1.1"
    //
    // We extract only method and path, ignoring the HTTP version since we
    // always respond with HTTP/1.1 regardless of what the client sends.
    //
    private String[] validateRequest(String requestLine) {
        String[] parts = requestLine.split(" ");
        if (parts.length < 2) {
            return null; // Malformed request line
        }
        return new String[] { parts[0], parts[1] };
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // dispatchRequest
    //
    // Routes request to appropriate handler based on path.
    //
    // Routing rules:
    //   /echo/{size} -> handleEcho (dynamic payload generation)
    //   Everything else -> handleStaticFile (serve from public/ directory)
    //
    private void dispatchRequest(OutputStream out, String path, boolean shouldKeepAlive) throws IOException {
        if(path.startsWith("/echo/")){
            handleEcho(out, path, shouldKeepAlive);
        }
        else{
            handleStaticFile(out, path, shouldKeepAlive);
        }
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Endpoint Handlers
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // handleEcho
    //
    // Handles /echo/{size} endpoint - generates deterministic payload of
    // specified size and returns it with SHA-256 hash verification header.
    //
    // This endpoint is used for load testing and verification. It generates
    // a repeating pattern of bytes ("0123456789"...) of the requested size
    // and computes a SHA-256 hash that the client can verify. This ensures
    // data integrity during transmission.
    //
    // Example: GET /echo/100 returns 100 bytes with X-Payload-Hash header

    private void handleEcho(OutputStream out, String path, boolean shouldKeepAlive) throws IOException {
        String[] parts = path.split("/");
        if(!(parts.length >= 3)){
            sendError(out, 400,"Bad Request" , false);
            
        }
        String size = parts[2];
        int sizeP = 0;
        
        try {
            sizeP = Integer.parseInt(size);
            
        } catch (Exception e) {
            sendError(out, 400,"Bad Request" , false);
            return;
        }
        
        if(!(sizeP >= 0)){
            sendError(out, 400, "Bad Request", false);
            return;
        }
        
        byte[] payload = generatePayload(sizeP);

        
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hashByte = digest.digest(payload);
            String hash = bytesToHex(hashByte);

            Map<String, String> extraHeaders = new HashMap<>();
            extraHeaders.put("X-Payload-Hash", hash);

            sendResponse(out, 200, "OK", "text/plain", payload, extraHeaders, shouldKeepAlive);



        } catch (Exception e) {
            sendError(out, 500,"Internal Server Error" , false);
        }

        





    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // handleStaticFile
    //
    // Serves static files from the public directory. Handles default
    // index.html, directory traversal protection, and custom 404 pages.
    //
    // Security considerations:
    //   - Rejects paths containing ".." to prevent directory traversal
    //   - Only serves regular files (not directories or special files)
    //   - All paths are relative to PUBLIC_DIR
    //
    // Special cases:
    //   - "/" is mapped to "/index.html"
    //   - Missing files trigger custom 404.html if it exists
    //
    
    private void handleStaticFile(OutputStream out, String path, boolean shouldKeepAlive) throws IOException {
       
        String defaultPath = "/index.html";
       
        if(path.contains("..")){
            sendError(out, 403, "forbidden", false);
        }
        if(path.equals("/")){
            path = defaultPath;
        }
        Path filePath = Paths.get(PUBLIC_DIR, path);


        if(!Files.exists(filePath) && !Files.isRegularFile(filePath)){
            if(!tryServeCustom404(out, false)){
                sendError(out, 404, "Page Not Found", false);
            }
        }
        else{
            byte[] content = Files.readAllBytes(filePath);
            String MIME = guessContentType(path);
            sendResponse(out, 200, "ok", MIME, content, null, shouldKeepAlive);
        }


       


    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // tryServeCustom404
    //
    // Attempts to serve custom 404.html page if it exists.
    // Returns true if custom 404 was served, false otherwise.
    //
    // This provides a better user experience than the default error page,
    // allowing site-specific branding and helpful navigation on 404 errors.
    //
   
    private boolean tryServeCustom404(OutputStream out, boolean shouldKeepAlive) throws IOException {
        
        Path path404 = Paths.get(PUBLIC_DIR, "404.html");

        if(!Files.exists(path404) && !Files.isRegularFile(path404)){
            return false;
        }
        else{
            byte[] content = Files.readAllBytes(path404);
            sendResponse(out, 404, "Page not Found", "text/html", content, null, shouldKeepAlive);
            return true;
        }

    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Response Utilities
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // sendResponse
    //
    // Unified response writer - sends HTTP response with status, headers,
    // and body. Handles optional extra headers and connection persistence.
    //
    // All responses go through this method, ensuring consistent formatting.
    // HTTP response format:
    //   Status line: "HTTP/1.1 {code} {message}\r\n"
    //   Headers: "Header-Name: value\r\n" ...
    //   Blank line: "\r\n"
    //   Body: raw bytes
    //
    // The Connection header is set based on shouldKeepAlive to inform the
    // client whether the connection will persist after this response.
    //
   
    private void sendResponse(OutputStream out, int code, String message, String contentType,
                             byte[] body, Map<String, String> extraHeaders, boolean shouldKeepAlive)
                             throws IOException
    {
        PrintWriter writer = new PrintWriter(out);
                           
        writer.print("HTTP/1.1 200 ok \r\n");
        writer.print("Content-Type: text/html\r\n");
        writer.print("Content-Length: " + body.length + "\r\n");
        if(extraHeaders != null){
            for(Map.Entry<String,String> entry: extraHeaders.entrySet()){
                writer.print(entry.getKey()+ ": " + entry.getValue() +"\r\n");
            }
        }
        String connectionHeader = (shouldKeepAlive ? "keep-alive" : "close");
        writer.print("Connection: " + connectionHeader + "\r\n");


        writer.print("\r\n");
        writer.flush();


        out.write(body);
        out.flush();


    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // sendError
    //
    // Sends an HTTP error response with a simple HTML body.
    //
    // Convenience wrapper around sendResponse for error cases. Generates a
    // minimal HTML page displaying the error code and message.
    //
   
    private void sendError(OutputStream out, int code, String message, boolean shouldKeepAlive)
                          throws IOException {
        String htmlBS = "<html><body><h1>" + code +" "+ message +"<h1></body></html1>";


        sendResponse(out, code, message, message, htmlBS.getBytes(), null, shouldKeepAlive);
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // guessContentType
    //
    // Maps file extensions to MIME types for Content-Type header.
    //
    // Proper Content-Type headers help browsers render files correctly.
    // This is a simplified version - production servers use more extensive
    // MIME type databases.
    //
    private String guessContentType(String path) {
        if (path.endsWith(".html") || path.endsWith(".htm")) {
            return "text/html";
        } else if (path.endsWith(".css")) {
            return "text/css";
        } else if (path.endsWith(".js")) {
            return "application/javascript";
        } else if (path.endsWith(".json")) {
            return "application/json";
        } else if (path.endsWith(".txt")) {
            return "text/plain";
        }
        return "application/octet-stream"; // Generic binary data
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Data Generation & Hashing
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // generatePayload
    //
    // Generates deterministic byte payload of specified size using a
    // repeating pattern. Same size always produces same payload.
    //
    // The pattern "0123456789" repeats to fill the requested size. This
    // deterministic approach allows clients to verify they received the
    // correct data by computing the hash of the expected pattern.
    //
    // Example: size=25 produces "0123456789012345678901234"
    //
    private byte[] generatePayload(int size) {
        byte[] payload = new byte[size];
        String pattern = "0123456789";
        byte[] patternBytes = pattern.getBytes();


        // Fill payload by repeating pattern
        for (int i = 0; i < size; i++) {
            payload[i] = patternBytes[i % patternBytes.length];
        }


        return payload;
    }


    //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    // bytesToHex
    //
    // Converts byte array to hexadecimal string representation.
    //
    // Used to convert SHA-256 hash bytes to a readable hex string for the
    // X-Payload-Hash header. Each byte becomes two hex digits (00-ff).
    //
    // Example: [0x1a, 0x2b, 0x3c] -> "1a2b3c"
    //
    private String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}
