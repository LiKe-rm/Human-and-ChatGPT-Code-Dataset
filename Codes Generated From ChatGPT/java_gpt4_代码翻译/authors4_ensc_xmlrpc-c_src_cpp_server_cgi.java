import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Optional;

public class ServerCgi {

    private final Registry registry;

    public ServerCgi(Registry registry) {
        this.registry = registry;
    }

    public void processCall() {
        try {
            HttpInfo httpInfo = new HttpInfo();
            if (!httpInfo.requestMethod.equals("POST")) {
                throw new HttpError(405, "Method must be POST");
            }

            if (!httpInfo.contentType.isPresent()) {
                throw new HttpError(400, "Must have content-type header");
            }

            if (!httpInfo.contentType.get().equals("text/xml")) {
                throw new HttpError(400, "ContentType must be 'text/xml', not '" + httpInfo.contentType.get() + "'");
            }

            if (!httpInfo.contentLength.isPresent()) {
                throw new HttpError(411, "Content-length required");
            }

            processCall2(System.in, httpInfo.contentLength.getAsInt(), System.out);
        } catch (HttpError e) {
            sendHttpErrorResp(System.out, e);
        }
    }

    private voidprocessCall2(InputStream callInputStream, int callSize, OutputStream respOutputStream) {
if (callSize > XmlRpcLimit.get(XMLRPC_XML_SIZE_LIMIT_ID)) {
throw new Fault("XML-RPC call is too large", Fault.CODE_LIMIT_EXCEEDED);
} else {
String callXml = getHttpBody(callInputStream, callSize);
        String responseXml;

        try {
            responseXml = registry.processCall(callXml);
        } catch (Exception e) {
            throw new HttpError(500, e.getMessage());
        }

        writeNormalHttpResp(respOutputStream, responseXml);
    }
}

private String getHttpBody(InputStream inputStream, int length) throws IOException {
    byte[] buffer = new byte[length];
    int count = inputStream.read(buffer);
    if (count < length) {
        throw new RuntimeException("Expected " + length + " bytes, received " + count);
    }

    return new String(buffer, StandardCharsets.UTF_8);
}

private void writeNormalHttpResp(OutputStream outputStream, String httpBody) throws IOException {
    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream, StandardCharsets.UTF_8));

    // HTTP headers
    writer.write("Status: 200 OK\n");
    writer.write("Content-type: text/xml; charset=\"utf-8\"\n");
    writer.write("Content-length: " + httpBody.length() + "\n");
    writer.write("\n");

    // HTTP body
    writer.write(httpBody);
    writer.flush();
}

private void sendHttpErrorResp(OutputStream outputStream, HttpError e) throws IOException {
    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream, StandardCharsets.UTF_8));

    // HTTP headers
    writer.write("Status: " + e.code + " " + e.msg + "\n");
    writer.write("Content-type: text/html\n");
    writer.write("\n");

    // HTTP body: HTML error message
    writer.write("<title>" + e.code + " " + e.msg + "</title>\n");
    writer.write("<h1>" + e.code + " " + e.msg + "</h1>\n");
    writer.write("<p>The Xmlrpc-c CGI server was unable to process your request. It could not process it even enough to generate an XML-RPC fault response.</p>\n");

    writer.flush();
}

private static class HttpInfo {
    String requestMethod;
    Optional<String> contentType;
    OptionalInt contentLength;

    HttpInfo() {
        requestMethod = System.getenv("REQUEST_METHOD");
        if (requestMethod == null) {
            throw new RuntimeException("Invalid CGI environment; environment variable REQUEST_METHOD is not set");
        }
        contentType = Optional.ofNullable(System.getenv("CONTENT_TYPE"));
        String contentLengthString = System.getenv("CONTENT_LENGTH");
        if (contentLengthString != null) {
            int length = Integer.parseInt(contentLengthString);
            if (length < 0) {
                throw new RuntimeException("Content-length HTTP header value is negative");
            } else if (length == 0) {
                throw new RuntimeException("Content-length HTTP header value is zero");
            } else {
                contentLength = OptionalInt.of(length);
            }
        } else {
            contentLength = OptionalInt.empty();
        }
    }
}

private static class HttpError extends RuntimeException {
    int code;
    String msg;

    HttpError(int code, String msg) {
        super(msg);
        this.code = code;
        this.msg = msg;
    }
}

public static void main(String[] args) {
    // Replace this with your own implementation of the `Registry` class.
    Registry registry = new Registry();
    ServerCgi serverCgi = new ServerCgi(registry);
    serverCgi.processCall();
}
}
