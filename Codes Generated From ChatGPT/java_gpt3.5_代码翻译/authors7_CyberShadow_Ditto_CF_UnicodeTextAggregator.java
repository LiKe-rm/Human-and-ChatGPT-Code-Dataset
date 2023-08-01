import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class UnicodeTextAggregator {
    private String separator;
    private List<String> texts;

    public UnicodeTextAggregator(String separator) {
        this.separator = separator;
        this.texts = new ArrayList<>();
    }

    public boolean addClip(byte[] data, int dataSize, int position, int count) {
        String text = new String(data, 0, dataSize, StandardCharsets.UTF_16LE);
        if (text == null) {
            return false;
        }

        int stringLen = dataSize / Character.BYTES;
        if (text.charAt(stringLen - 1) != '\0') {
            int len = 0;
            for (; len < stringLen && text.charAt(len) != '\0'; len++) {
            }
            if (len >= stringLen)
                return false;
        }

        texts.add(text);

        if (position != count - 1) {
            texts.add(separator);
        }

        return true;
    }

    public ByteBuffer getByteBuffer() {
        StringBuilder sb = new StringBuilder();
        for (String text : texts) {
            sb.append(text);
        }
        byte[] bytes = sb.toString().getBytes(StandardCharsets.UTF_16LE);
        ByteBuffer buffer = ByteBuffer.allocate(bytes.length + Character.BYTES);
        buffer.put(bytes);
        buffer.putChar('\0');
        buffer.flip();
        return buffer;
    }
}
