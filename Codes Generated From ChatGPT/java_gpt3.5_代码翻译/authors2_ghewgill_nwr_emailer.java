import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;

public class Emailer {
    private static String from = "nwr@hewgill.net";
    private static String notify = "notify";

    public static void main(String[] args) throws IOException {
        if (args.length < 2) {
            System.err.println("Usage: emailer code filename");
            System.exit(1);
        }

        EasMessage message = EasDecode.decode(args[0]);
        if (message == null) {
            System.err.println("emailer: bad code");
            System.exit(1);
        }

        email(message, args[1]);
    }

    public static void email(EasMessage message, String fn) throws IOException {
        Set<String> addresses = new HashSet<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(notify))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (!line.isEmpty() && line.charAt(0) != '#') {
                    addresses.add(line);
                }
            }
        }

        for (String address : addresses) {
            System.out.printf("*** sending %s to %s%n", fn, address);

            // Create a multipart email
            String boundary = String.format("%08x.%d", System.currentTimeMillis(), ProcessHandle.current().pid());
            MimeMultipart multipart = new MimeMultipart("mixed", new ContentType("multipart/mixed").setParameter("boundary", boundary));

            // Add the text/plain part
            MimeBodyPart textPart = new MimeBodyPart();
            textPart.setText(message.toString());
            multipart.addBodyPart(textPart);

            // Add the audio/mp3 part
            MimeBodyPart audioPart = new MimeBodyPart();
            File audioFile = new File(fn);
            audioPart.setDataHandler(new DataHandler(new FileDataSource(audioFile)));
            audioPart.setFileName(audioFile.getName());
            audioPart.setHeader("Content-Type", "audio/mp3");
            audioPart.setHeader("Content-Transfer-Encoding", "base64");
            multipart.addBodyPart(audioPart);

            // Create and send the email
            MimeMessage email = new MimeMessage(Session.getDefaultInstance(new Properties()));
            email.setFrom(new InternetAddress(from));
            email.addRecipient(Message.RecipientType.TO, new InternetAddress(address));
            email.setSubject("[NWR] " + audioFile.getName());
            email.setContent(multipart);
            Transport.send(email);
        }
    }
}
