import org.apache.sshd.server.SshServer;
import org.apache.sshd.server.keyprovider.SimpleGeneratorHostKeyProvider;
import org.apache.sshd.server.session.ServerSession;
import org.apache.sshd.server.shell.ProcessShellFactory;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class SimpleSSHChat {

    private static final int SERVER_PORT = 2222;
    private static final String HOST_KEY_PATH = "hostkey.ser";

    private final SshServer sshd;
    private final Map<ServerSession, ChatClient> clients;

    public SimpleSSHChat() {
        clients = new HashMap<>();
        sshd = SshServer.setUpDefaultServer();
        sshd.setPort(SERVER_PORT);
        sshd.setKeyPairProvider(new SimpleGeneratorHostKeyProvider(Paths.get(HOST_KEY_PATH)));
        sshd.setShellFactory(new ProcessShellFactory(new String[]{"bash", "-i"}));
        sshd.setSessionListener(new SimpleChatSessionListener(this));
    }

    public void start() throws IOException {
        sshd.start();
    }

    public void stop() throws IOException {
        sshd.stop();
    }

    public void addClient(ServerSession session, ChatClient client) {
        clients.put(session, client);
    }

    public void removeClient(ServerSession session) {
        clients.remove(session);
    }

    public ChatClient getClient(ServerSession session) {
        return clients.get(session);
    }

    public static void main(String[] args) throws IOException {
        SimpleSSHChat chat = new SimpleSSHChat();
        chat.start();
        System.out.println("SSH Chat server started on port " + SERVER_PORT);
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try {
                chat.stop();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }));
    }
}

import org.apache.sshd.server.session.ServerSession;

public class ChatClient {
    private final ServerSession session;
    private final String remoteAddress;
    private String handle;
    private StringBuilder messageBuffer;

    public ChatClient(ServerSession session, String remoteAddress) {
        this.session = session;
        this.remoteAddress = remoteAddress;
        this.handle = "";
        this.messageBuffer = new StringBuilder();
    }

    public ServerSession getSession() {
        return session;
    }

    public String getRemoteAddress() {
        return remoteAddress;
    }

    public String getHandle() {
        return handle;
    }

    public void setHandle(String handle) {
        this.handle = handle;
    }

    public StringBuilder getMessageBuffer() {
        return messageBuffer;
    }
}
