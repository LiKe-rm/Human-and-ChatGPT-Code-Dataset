import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class MainFrameThread extends Thread {
    private final BlockingQueue<Runnable> tasks = new LinkedBlockingQueue<>();
    private final DatabaseUtilities databaseUtilities = new DatabaseUtilities();

    public MainFrameThread() {
        start();
    }

    public void addClipToSave(Clip clip) {
        tasks.offer(() -> onSaveClips(clip));
    }

    public void addRemoteClipToSave(ClipList clipList) {
        tasks.offer(() -> onSaveRemoteClips(clipList));
    }

    public void onDeleteEntries() {
        tasks.offer(this::onDeleteEntries);
    }

    public void onRemoveRemoteFiles() {
        tasks.offer(this::onRemoveRemoteFiles);
    }

    @Override
    public void run() {
        while (true) {
            try {
                tasks.take().run();
            } catch (InterruptedException e) {
                break;
            }
        }
    }

    private void onDeleteEntries() {
        databaseUtilities.removeOldEntries();
    }

    private void onRemoveRemoteFiles() {
        String remoteFilesDir = Options.getPath(Options.PathType.REMOTE_FILES);
        Path path = Paths.get(remoteFilesDir);
        if (Files.exists(path)) {
            Misc.deleteReceivedFiles(path);
        }
    }

    private void onSaveClips(Clip clip) {
        ClipList localClips = new ClipList();
        localClips.add(clip);

        int count = localClips.addToDB(true);
        if (count > 0) {
            int id = localClips.getLast().getId();
            CpMain.onCopyCompleted(id, count);

            if (Options.getAutoSendClientCount() > 0) {
                SendToClientThread.sendToClient(localClips);
            }
        }
    }

    private void onSaveRemoteClips(ClipList clipList) {
        ClipList localClips = new ClipList(clipList);
        clipList.clear();

        int count = localClips.addToDB(true);
        Clip lastClip = localClips.getLast();

        if (lastClip != null && lastClip.isParam1()) {
            CpMain.loadClipOnClipboard(lastClip);
            localClips.removeLast();
        }

        CpMain.refreshView();
    }
}

class Clip {
    // Clip implementation.
}

class ClipList extends LinkedList<Clip> {
    // ClipList implementation.

    public ClipList() {
        super();
    }

    public ClipList(ClipList clipList) {
        super(clipList);
    }

    public int addToDB(boolean flag) {
        // Add clips to the database and return the number of clips added.
        return size();
    }
}

class DatabaseUtilities {
    public void removeOldEntries() {
        // Remove old entries from the database.
    }
}

class Options {
    enum PathType {
        REMOTE_FILES
    }

    public static String getPath(PathType type) {
        // Return the path for the given type.
        return "/path/to/remote/files";
    }

    public static int getAutoSendClientCount() {
        // Return the number of auto-send clients.
        return 0;
    }
}

class Misc {
    public static void deleteReceivedFiles(Path path) {
        // Delete received files in the given directory.
    }
}

class CpMain {
    public static void onCopyCompleted(int id,int count) {
    // Perform actions after the copy is completed, given the clip ID and count.
    }
    public static void loadClipOnClipboard(Clip clip) {
        // Set the given clip to the clipboard on the main thread.
    }

    public static void refreshView() {
        // Refresh the view in the application.
    }
}

class SendToClientThread {
    public static void sendToClient(ClipList localClips) {
    // Send the clips to the client.
    }
}
