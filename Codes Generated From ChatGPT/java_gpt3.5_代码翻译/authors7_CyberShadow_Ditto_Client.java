import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class Client {
    private Socket connection;

    public static void main(String[] args) {
        // Test the Client class
        Client client = new Client();
        Clip clip = new Clip();
        clip.setDescription("Test clip");

        ClipFormat cf = new ClipFormat(1, ByteBuffer.wrap("Test data".getBytes()));
        clip.getFormats().add(cf);

        SendToFriendInfo info = new SendToFriendInfo();
        info.setIpAddress("127.0.0.1");
        info.setClipList(List.of(clip));

        System.out.println(sendToFriend(info));
    }

    public static boolean sendToFriend(SendToFriendInfo info) {
        System.out.println("Start of Send To Friend");

        String ipAddress = info.getIpAddress();
        System.out.println("Sending clip to " + ipAddress);

        Client client = new Client();

        if (!client.openConnection(ipAddress)) {
            System.out.println("Error opening connection to " + ipAddress);
            return false;
        }

        List<Clip> clipList = info.getClipList();
        for (int i = 0; i < clipList.size(); i++) {
            Clip clip = clipList.get(i);
            System.out.println(String.format("Sending %d of %d", i + 1, clipList.size()));

            if (!client.sendItem(clip)) {
                System.out.println("Error SendItem Failed");
                return false;
            }
        }

        System.out.println("End of Send To Friend");
        return true;
    }

    public Client() {
        connection = null;
    }

    public boolean openConnection(String serverName) {
        try {
            InetAddress address = InetAddress.getByName(serverName);
            connection = new Socket(address, 12345);
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            connection = null;
            return false;
        }
    }

    public boolean closeConnection() {
        if (connection != null) {
            try {
                connection.close();
                connection = null;
                return true;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return false;
    }

    public boolean sendItem(Clip clip) {
        // Implement the logic for sending a clip item
        // For now, just print the description and return true
        System.out.println("Sending clip: " + clip.getDescription());
        return true;
    }
}

class Clip {
    private String description;
    private List<ClipFormat> formats;

    public Clip() {
        formats = new ArrayList<>();
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public List<ClipFormat> getFormats() {
        return formats;
    }
}

class ClipFormat {
    private int type;
    private ByteBuffer data;

    public ClipFormat(int type, ByteBuffer data) {
        this.type = type;
        this.data = data;
    }

    public int getType() {
        return type;
    }

    public ByteBuffer getData() {
        return data;
    }
}

class SendToFriendInfo {
    private String ipAddress;
    private List<Clip> clipList;

    public String getIpAddress() {
        return ipAddress;
    }

    public void setIpAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public List<Clip> getClipList() {
        return clipList;
    }

    public void setClipList(List<Clip> clipList) {
        this.clipList = clipList
    }
}