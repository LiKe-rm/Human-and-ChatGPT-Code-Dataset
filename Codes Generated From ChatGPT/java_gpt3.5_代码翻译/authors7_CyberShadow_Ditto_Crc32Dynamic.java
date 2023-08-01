public class Crc32Dynamic {
    private int[] crc32Table;

    public Crc32Dynamic() {
        init();
    }

    public void init() {
        int polynomial = 0xEDB88320;
        crc32Table = new int[256];

        int crc;
        for (int i = 0; i < 256; i++) {
            crc = i;
            for (int j = 8; j > 0; j--) {
                if ((crc & 1) != 0) {
                    crc = (crc >>> 1) ^ polynomial;
                } else {
                    crc >>>= 1;
                }
            }
            crc32Table[i] = crc;
        }
    }

    public void free() {
        crc32Table = null;
    }

    private void calcCrc32(byte b, int[] crc32) {
        crc32[0] = (crc32[0] >>> 8) ^ crc32Table[(b) ^ (crc32[0] & 0x000000FF)];
    }

    public int generateCrc32(byte[] byteArray, int size, int[] crc32) {
        int errorCode = 0;

        try {
            if (crc32Table == null) {
                throw new IllegalStateException("CRC32 table not initialized");
            }

            for (int i = 0; i < size; i++) {
                calcCrc32(byteArray[i], crc32);
            }
        } catch (Exception e) {
            errorCode = -1; // Set the error code to a non-zero value
        }

        return errorCode;
    }
}
