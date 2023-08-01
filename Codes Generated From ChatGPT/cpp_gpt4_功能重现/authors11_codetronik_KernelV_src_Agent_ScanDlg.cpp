#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "resource.h"
#include "CScan.h"
#include "Communication.h"

CScan::CScan()
    : CDialog(IDD_SCAN_DIALOG)
{
}

BOOL CScan::OnInitDialog()
{
    // Call the base class implementation
    return CDialog::OnInitDialog();
}

void CScan::OnOK()
{
    // Replace "\r\n" with newline character when the user presses Enter
    CString pattern;
    GetDlgItemText(IDC_PATTERN_EDIT, pattern);
    pattern.Replace(_T("\r\n"), _T("\n"));
    SetDlgItemText(IDC_PATTERN_EDIT, pattern);
}

void CScan::SetComm(Communication *comm)
{
    m_Comm = comm;
}

void CScan::OnScan()
{
    CString pattern;
    GetDlgItemText(IDC_PATTERN_EDIT, pattern);

    if (pattern.GetLength() > 4096)
    {
        MessageBox(_T("The pattern is too long. Maximum allowed length is 4096 characters."), _T("Error"), MB_ICONERROR | MB_OK);
        return;
    }

    // Remove spaces from the pattern
    pattern.Remove(' ');

    // Check if the pattern contains only hexadecimal characters and newlines
    for (int i = 0; i < pattern.GetLength(); ++i)
    {
        TCHAR c = pattern[i];
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || c == '\n'))
        {
            MessageBox(_T("Invalid pattern. The pattern should contain only hexadecimal characters and newlines."), _T("Error"), MB_ICONERROR | MB_OK);
            return;
        }
    }

    // Convert the pattern to a vector of bytes
    std::vector<BYTE> bytePattern;
    std::istringstream iss(pattern);
    std::string line;

    while (std::getline(iss, line))
    {
        for (size_t i = 0; i < line.length(); i += 2)
        {
            BYTE b;
            std::stringstream ss;
            ss << std::hex << line.substr(i, 2);
            ss >> b;
            bytePattern.push_back(b);
        }
    }

    // Add start and end markers to the byte pattern
    bytePattern.insert(bytePattern.begin(), 'S');
    bytePattern.insert(bytePattern.begin() + 1, 't');
    bytePattern.insert(bytePattern.begin() + 2, 'a');
    bytePattern.insert(bytePattern.begin() + 3, 'r');
    bytePattern.insert(bytePattern.begin() + 4, 't');
    bytePattern.push_back('E');
    bytePattern.push_back('n');
    bytePattern.push_back('d');

    // Perform the memory scan and display the results
    std::vector<BYTE> scanResults = m_Comm->Scan(bytePattern);
    CString resultText;

    for (size_t i = 0; i < scanResults.size(); ++i)
    {
        resultText.AppendFormat(_T("%02X "), scanResults[i]);
    }

    SetDlgItemText(IDC_RESULTS_EDIT, resultText);
}

BEGIN_MESSAGE_MAP(CScan, CDialog)
    ON_BN_CLICKED(IDC_SCAN_BUTTON, &CScan::OnScan)
END_MESSAGE_MAP()
