public class GlobalDescriptorTable {

    private static final int ENTRY_COUNT = 8;
    private static final int USER_LEVEL = 3;

    private static Entry[] entries = new Entry[ENTRY_COUNT];
    private static TSS tss = new TSS();

    public static void init() {
        set(0, 0, 0, (byte) 0, (byte) 0); // Null segment
        set(1, 0, 0xFFFFFFFF, (byte) 0x9A, (byte) 0xCF); // Kernel code segment
        set(2, 0, 0xFFFFFFFF, (byte) 0x92, (byte) 0xCF); // Kernel data segment
        set(3, 0, 0xFFFFFFFF, (byte) 0xBA, (byte) 0xCF); // God service code segment
        set(4, 0, 0xFFFFFFFF, (byte) 0xB2, (byte) 0xCF); // God service data segment
        set(5, 0, 0xFFFFFFFF, (byte) 0xFA, (byte) 0xCF); // User mode code segment
        set(6, 0, 0xFFFFFFFF, (byte) 0xF2, (byte) 0xCF); // User mode data segment

        initTSS(7, (short) 0x10, 0); // @ 0x38
    }

    private static void initTSS(int index, short ss0, int esp0) {
        tss.ss0 = ss0;
        tss.esp0 = esp0;
        tss.cs = (short) (0x08 | USER_LEVEL);
        tss.ss = tss.ds = tss.es = tss.fs = tss.gs = (short) (0x10 | USER_LEVEL);

        int base = tss.hashCode();
        int limit = base + TSS.size();

        set(index, base, limit, (byte) 0xE9, (byte) 0x00);
    }

    public static void set(int index, int base, int limit, byte access, byte granularity) {
        entries[index] = new Entry(base, limit, access, granularity);
    }

    private static class Entry {
        int baseLow;
        int baseMiddle;
        int baseHigh;
        int limitLow;
        int granularity;
        int access;

        public Entry(int base, int limit, byte access, byte granularity) {
            this.baseLow = base & 0xFFFF;
            this.baseMiddle = (base >> 16) & 0xFF;
            this.baseHigh = (base >> 24) & 0xFF;

            this.limitLow = limit & 0xFFFF;
            this.granularity = (limit >> 16) & 0x0F;

            this.granularity |= granularity & 0xF0;
            this.access = access;
        }
    }

    private static class TSS {
        short ss0;
        int esp0;
        short cs;
        short ss;
        short ds;
        short es;
        short fs;
        short gs;

        public static int size() {
            return 104;
        }
    }
}
