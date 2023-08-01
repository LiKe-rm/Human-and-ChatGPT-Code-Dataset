import java.io.File;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.platform.win32.Kernel32;
import com.sun.jna.platform.win32.Psapi;
import com.sun.jna.platform.win32.Win32Exception;
import com.sun.jna.platform.win32.WinDef;
import com.sun.jna.platform.win32.WinNT;

public class WoWInjector {
    private static final String[] LOOKING_PROCESS_NAMES = { "Wow.exe", "WowT.exe", "WowB.exe" };
    private static final String INJECT_DLL_NAME = "Katy.x86.dll";

    public static void main(String[] args) {
        System.out.println("Welcome to WoW injector.");

        Map<Integer, String> processList = getProcessList();
        if (processList.isEmpty()) {
            System.out.println("Looking process: ");
            for (String processName : LOOKING_PROCESS_NAMES) {
                System.out.println("'" + processName + "' ");
            }
            System.out.println("NOT found.");
            return;
        }

        // TODO: Implement the rest of the functionality
    }

    private static Map<Integer, String> getProcessList() {
        Map<Integer, String> processMap = new HashMap<>();

        int[] processIds = new int[1024];
        int[] processCount = new int[1];
        if (!Psapi.INSTANCE.EnumProcesses(processIds, processIds.length, processCount)) {
            throw new Win32Exception(Native.getLastError());
        }

        int processCountInt = processCount[0] / 4;
        for (int i = 0; i < processCountInt; i++) {
            WinNT.HANDLE processHandle = Kernel32.INSTANCE.OpenProcess(WinNT.PROCESS_QUERY_INFORMATION | WinNT.PROCESS_VM_READ, false, processIds[i]);
            if (processHandle != null) {
                try {
                    char[] filename = new char[512];
                    int filenameLength = Psapi.INSTANCE.GetModuleFileNameEx(processHandle, null, filename, filename.length);
                    if (filenameLength > 0) {
                        String processName = Native.toString(filename);
                        for (String lookingProcessName : LOOKING_PROCESS_NAMES) {
                            if (processName.endsWith(lookingProcessName)) {
                                processMap.put(processIds[i], lookingProcessName);
                            }
                        }
                    }
                } finally {
                    Kernel32.INSTANCE.CloseHandle(processHandle);
                }
            }
        }

        return processMap;
    }
}
