#include <ntifs.h>
#include <ndis.h>
#include <fwpmk.h>

extern "C" NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

NTSTATUS classifyFn(
    IN const FWPS_INCOMING_VALUES0* inFixedValues,
    IN const FWPS_INCOMING_METADATA_VALUES0* inMetaValues,
    IN OUT VOID* layerData,
    IN const FWPS_FILTER0* filter,
    IN UINT64 flowContext,
    IN OUT FWPS_CLASSIFY_OUT0* classifyOut
);

NTSTATUS notifyFn(
    IN FWPS_CALLOUT_NOTIFY_TYPE notifyType,
    IN const GUID* filterKey,
    IN const FWPS_FILTER0* filter
);

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {
    NTSTATUS status = STATUS_SUCCESS;
    UNICODE_STRING deviceName, symbolicLinkName;
    PDEVICE_OBJECT deviceObject = nullptr;
    FWPM_FILTER0 filter = {0};
    FWPS_CALLOUT0 callout = {0};
    FWP_BYTE_BLOB* byteBlob = nullptr;
    FWPM_CALLOUT0 mCallout = {0};

    RtlInitUnicodeString(&deviceName, L"\\Device\\MyKernelFilterDriver");
    RtlInitUnicodeString(&symbolicLinkName, L"\\DosDevices\\MyKernelFilterDriver");

    status = IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_NETWORK, 0, FALSE, &deviceObject);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Failed to create device object. Status: 0x%08x\n", status));
        goto Cleanup;
    }

    status = IoCreateSymbolicLink(&symbolicLinkName, &deviceName);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Failed to create symbolic link. Status: 0x%08x\n", status));
        goto Cleanup;
    }

    callout.calloutKey = {0}; // Assign a unique GUID here
    callout.classifyFn = classifyFn;
    callout.notifyFn = notifyFn;

    status = FwpsCalloutRegister0(deviceObject, &callout, nullptr);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Failed to register callout. Status: 0x%08x\n", status));
        goto Cleanup;
    }

    // Unload routine
    DriverObject->DriverUnload = [](PDRIVER_OBJECT driverObject) {
        IoDeleteSymbolicLink(&symbolicLinkName);
        IoDeleteDevice(deviceObject);
        FwpsCalloutUnregisterByKey0(&callout.calloutKey);
    };

Cleanup:
    if (!NT_SUCCESS(status)) {
        if (deviceObject) {
            IoDeleteDevice(deviceObject);
        }
        if (byteBlob) {
            ExFreePoolWithTag(byteBlob, 'bLoB');
        }
    }
    return status;
}
