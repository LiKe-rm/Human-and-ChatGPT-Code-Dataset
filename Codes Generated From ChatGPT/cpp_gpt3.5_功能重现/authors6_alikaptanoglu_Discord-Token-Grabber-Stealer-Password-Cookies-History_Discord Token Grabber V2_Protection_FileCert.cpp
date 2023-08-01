#include <windows.h>
#include <wincrypt.h>
#include <softpub.h>
#include <wintrust.h>
#include <iostream>
#include <string>

#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "wintrust.lib")

bool VerifySignatureIssuer(std::wstring filename, std::wstring issuer_name) {
    HCERTSTORE hStore = NULL;
    HCRYPTMSG hMsg = NULL;
    PCCERT_CONTEXT pCertContext = NULL;
    bool result = false;

    // Get certificate store and message handle for the file
    BOOL success = CryptQueryObject(CERT_QUERY_OBJECT_FILE,
                                    filename.c_str(),
                                    CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
                                    CERT_QUERY_FORMAT_FLAG_BINARY,
                                    0,
                                    NULL,
                                    NULL,
                                    NULL,
                                    &hStore,
                                    &hMsg,
                                    NULL);
    if (!success) {
        std::cerr << "CryptQueryObject failed: " << GetLastError() << std::endl;
        goto cleanup;
    }

    // Find the certificate in the store
    pCertContext = CertFindCertificateInStore(hStore,
                                              X509_ASN_ENCODING,
                                              0,
                                              CERT_FIND_ANY,
                                              NULL,
                                              NULL);
    if (pCertContext == NULL) {
        std::cerr << "CertFindCertificateInStore failed: " << GetLastError() << std::endl;
        goto cleanup;
    }

    // Get the certificate's subject name
    DWORD name_length = CertGetNameString(pCertContext,
                                          CERT_NAME_SIMPLE_DISPLAY_TYPE,
                                          0,
                                          NULL,
                                          NULL,
                                          0);
    std::wstring cert_name(name_length, L'\0');
    CertGetNameString(pCertContext,
                      CERT_NAME_SIMPLE_DISPLAY_TYPE,
                      0,
                      NULL,
                      (LPWSTR)cert_name.c_str(),
                      name_length);

    // Check if the certificate was issued by the specified issuer
    if (cert_name.find(issuer_name) != std::wstring::npos) {
        result = true;
    }

cleanup:
    if (hMsg != NULL) {
        CryptMsgClose(hMsg);
    }
    if (pCertContext != NULL) {
        CertFreeCertificateContext(pCertContext);
    }
    if (hStore != NULL) {
        CertCloseStore(hStore, 0);
    }
    return result;
}

bool VerifyExecutableSignature(std::wstring filename) {
    // Initialize WINTRUST_FILE_INFO structure
    WINTRUST_FILE_INFO file_info = {0};
    file_info.cbStruct = sizeof(WINTRUST_FILE_INFO);
    file_info.pcwszFilePath = filename.c_str();
    file_info.hFile = NULL;
    file_info.pgKnownSubject = NULL;

    // Initialize WINTRUST_DATA structure
    WINTRUST_DATA trust_data = {0};
    trust_data.cbStruct = sizeof(WINTRUST_DATA);
    trust_data.dwUIChoice = WTD_UI_NONE;
    trust_data.fdwRevocationChecks = WTD_REVOKE_NONE;
    trust_data.dwUnionChoice = WTD_CHOICE_FILE;
    trust_data.pFile = &file_info;
    trust_data.dwProvFlags = WTD_USE_DEFAULT_OSVER_CHECK | WTD_SAFER_FLAG;

    // Verify trust
    GUID action_id = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    LONG result = WinVerifyTrust(NULL, &action_id, &trust_data);
    if (result == ERROR_SUCCESS) {
        return true;
    } else {
        std::cerr << "WinVerifyTrust failed: " << result << std::endl;
        return false;
    }
}

