import java.util.ArrayList;
import java.util.List;

public class KernelDebug {
    public static void main(String[] args) {
        Multiboot boot = new Multiboot();
        dump(boot);
    }

    public static void dump(Multiboot boot) {
        System.out.println("Boot dump...");

        System.out.print("Booting from: ");
        if (boot.bootLoader != null) {
            System.out.print(boot.bootLoader);
        } else {
            System.out.print("Unknown");
        }
        System.out.println();

        System.out.println("Boot options: " + boot.command);

        System.out.print("Memory: ");
        if (boot.memory != null) {
            System.out.println("lower=" + boot.memory.lower + "KB; upper=" + boot.memory.upper + "KB;");
        } else {
            System.out.println("Invalid memory bounds.");
        }

        System.out.print("Boot device: ");
        if (boot.device != null) {
            System.out.print("BIOS=" + boot.device.BIOS + "; ");
            System.out.print("Partition=" + boot.device.partition.topLevel);

            if (boot.device.partition.subLevel != 0xFF) {
                System.out.print("," + boot.device.partition.subLevel);

                if (boot.device.partition.subSubLevel != 0xFF) {
                    System.out.print("," + boot.device.partition.subSubLevel);
                }
            }
            System.out.print(";");
        } else {
            System.out.print("Invalid device.");
        }
        System.out.println();

        System.out.print("Drives: ");
        if (boot.drives.size() == 0) {
            System.out.println("None.");
        } else {
            System.out.println();
            for (Multiboot.Drive drive : boot.drives) {
                dumpBootDrives(drive);
            }
        }
        System.out.println();
    }

    public static void dumpBootDrives(Multiboot.Drive drive) {
        System.out.print("    ");
        System.out.print(drive.number);
        System.out.print(" [C=" + drive.cylinders + ", H=" + drive.heads + ", S=" + drive.sectors + "]");
        System.out.print(" {" + (drive.mode == 0 ? "CHS" : "LBA") + "} ");

        if (drive.ports != null && drive.ports.size() > 0) {
            System.out.print("(" + drive.ports.get(0));
            for (int i = 1; i < drive.ports.size(); i++) {
                System.out.print(", " + drive.ports.get(i));
            }
            System.out.print(")");
        } else {
            System.out.print("(N/A)");
        }

        System.out.println();
    }
}

class Multiboot {
    String bootLoader;
    String command;
    Memory memory;
    Device device;
    List<Drive> drives;

    // Add constructors and other class definitions as needed

    static class Memory {
        int lower;
        int upper;
    }

    static class Device {
        int BIOS;
        Partition partition;

        static class Partition {
            int topLevel;
            int subLevel;
            int subSubLevel;
        }
    }

    static class Drive {
        int number;
        int cylinders;
        int heads;
        int sectors;
        int mode;
        List<Integer> ports;
    }
}
