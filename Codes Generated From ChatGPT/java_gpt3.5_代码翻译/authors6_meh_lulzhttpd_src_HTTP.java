package http;

import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HTTP {
    private static final Map<Integer, String> codes = new HashMap<>();

    private boolean done;
    private boolean isOk;
    private int status;
    private float version;

    private String method;
    private String uri;
    private String host;

    private String data;
    private boolean dataIncoming;

    private final Map<String, String> headers = new HashMap<>();

    static {
        // Initialize status codes
        initStatusCodes();
    }

    public HTTP() {
        clear();
    }

    public void request(String text) {
        // ... Implement the request method ...
    }

    // ... Implement other methods ...

    private static void initStatusCodes() {
        if (codes.isEmpty()) {
            // Informational
            codes.put(100, "Continue");
            codes.put(101, "Switching Protocols");

            // Successful
            codes.put(200, "OK");
            codes.put(201, "Created");
            codes.put(202, "Accepted");
            codes.put(203, "Non-Authoritative Information");
            codes.put(204, "No Content");
            codes.put(205, "Reset Content");
            codes.put(206, "Partial Content");

            // Redirection
            codes.put(300, "Multiple Choices");
            codes.put(301, "Moved Permanently");
            codes.put(302, "Found");
            codes.put(303, "See Other");
            codes.put(304, "Not Modified");
            codes.put(305, "Use Proxy");
            codes.put(306, "LOLNO");
            codes.put(307, "Temporary Redirect");

            // Client Error
            codes.put(400, "Bad Request");
            codes.put(401, "Unauthorized");
            codes.put(402, "Payment Required");
            codes.put(403, "Forbidden");
            codes.put(404, "Not Found");
            codes.put(405, "Method Not Allowed");
            codes.put(406, "Not Acceptable");
            codes.put(407, "Proxy Authentication Required");
            codes.put(408, "Request Timeout");
            codes.put(409, "Conflict");
            codes.put(410, "Gone");
            codes.put(411, "Length Required");
            codes.put(412, "Precondition Failed");
            codes.put(413, "Request Entity Too Large");
            codes.put(414, "Request-URI Too Long");
            codes.put(415, "Unsupported Media Type");
            codes.put(416, "Requested Range Not Satisfiable");
            codes.put(417, "Expectation Failed");

            // Server Error
            codes.put(500, "Internal Server Error");
            codes.put(501, "Not Implemented");
            codes.put(502, "Bad Gateway");
            codes.put(503, "Service Unavailable");
            codes.put(504, "Gateway Timeout");
            codes.put(505, "HTTP Version Not Supported");
        }
    }
}
