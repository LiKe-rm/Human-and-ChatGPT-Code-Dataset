package lulzHTTPd;

public class Exception extends java.lang.Exception {
    private String description;

    public Exception(int code) {
        switch (code) {
            case SERVER_NOT_INITED:
                description = "The server has not been initialized.";
                break;

            case SOCKET_CREATION:
                description = "socket() failed.";
                break;

            case SOCKET_LISTEN:
                description = "listen() failed.";
                break;

            case SOCKET_ACCEPT:
                description = "accept() failed.";
                break;

            case SOCKET_BIND:
                description = "bind() failed.";
                break;

            case SOCKET_READ:
                description = "read() failed.";
                break;

            case SOCKET_WRITE:
                description = "write() failed.";
                break;

            case SOCKET_CLOSE:
                description = "close() failed.";
                break;

            case SOCKET_ERROR_SET_BLOCK:
                description = "Couldn't change the socket's block state.";
                break;

            default:
                description = "Well, you did it wrong.";
                break;
        }
    }

    @Override
    public String getMessage() {
        return description;
    }

    public static final int SERVER_NOT_INITED = 1;
    public static final int SOCKET_CREATION = 2;
    public static final int SOCKET_LISTEN = 3;
    public static final int SOCKET_ACCEPT = 4;
    public static final int SOCKET_BIND = 5;
    public static final int SOCKET_READ = 6;
    public static final int SOCKET_WRITE = 7;
    public static final int SOCKET_CLOSE = 8;
    public static final int SOCKET_ERROR_SET_BLOCK = 9;
}
