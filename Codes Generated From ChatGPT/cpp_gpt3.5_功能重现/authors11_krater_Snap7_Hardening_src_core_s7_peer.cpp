#include "snap7.h"

class TSnap7Peer {
private:
    int Error;
    word NextWord;
    int ReqMaxPDU;
    int RspMaxPDU;

public:
    TSnap7Peer() {
        Error = 0;
        NextWord = 0;
        ReqMaxPDU = Snap7::MaxPDU;
        RspMaxPDU = Snap7::MaxPDU;
    }

    ~TSnap7Peer() {
        Error = Snap7::ErrDisconnect;
    }

    int SetError(int e) {
        Error = e;
        return Error;
    }

    void ClrError() {
        Error = 0;
    }

    word GetNextWord() {
        NextWord++;
        if (NextWord == 0)
            NextWord = 1;
        return NextWord;
    }

    int NegotiatePDULength(S7Object Client, S7Object Server) {
        int Result = Snap7::CliNegotiatePduLength(Client, &ReqMaxPDU, &RspMaxPDU);
        if (Result == 0)
            Result = Snap7::SrvNegotiatePduLength(Server, &RspMaxPDU, &ReqMaxPDU);
        if (Result != 0)
            SetError(Result);
        return Result;
    }

    void PeerDisconnect(S7Object Client) {
        Snap7::CliDisconnect(Client);
        ClrError();
    }

    int PeerConnect(S7Object Client, S7Object Server, const char* Address, int Rack, int Slot) {
        int Result = Snap7::CliConnect(Client, Address, Rack, Slot);
        if (Result == 0)
            Result = NegotiatePDULength(Client, Server);
        if (Result != 0) {
            PeerDisconnect(Client);
            SetError(Result);
        }
        return Result;
    }
};
