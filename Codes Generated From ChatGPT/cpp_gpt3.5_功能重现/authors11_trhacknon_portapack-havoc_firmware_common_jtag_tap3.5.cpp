#include <vector>
#include <iostream>

using namespace std;

class bits_t {
public:
    bits_t(int size) : m_data(size) {}

    int size() const {
        return m_data.size();
    }

    void set(int index, bool value) {
        m_data[index] = value;
    }

    bool get(int index) const {
        return m_data[index];
    }

    bool operator[](int index) const {
        return get(index);
    }

    void print() const {
        for (int i = 0; i < size(); i++) {
            cout << (get(i) ? "1" : "0");
        }
        cout << endl;
    }

private:
    vector<bool> m_data;
};

class TAPState {
public:
    enum Value {
        TestLogicReset,
        RunTestIdle,
        SelectDRScan,
        CaptureDR,
        ShiftDR,
        Exit1DR,
        PauseDR,
        Exit2DR,
        UpdateDR,
        SelectIRScan,
        CaptureIR,
        ShiftIR,
        Exit1IR,
        PauseIR,
        Exit2IR,
        UpdateIR
    };

    static const char* toString(Value state) {
        switch (state) {
            case TestLogicReset: return "TestLogicReset";
            case RunTestIdle: return "RunTestIdle";
            case SelectDRScan: return "SelectDRScan";
            case CaptureDR: return "CaptureDR";
            case ShiftDR: return "ShiftDR";
            case Exit1DR: return "Exit1DR";
            case PauseDR: return "PauseDR";
            case Exit2DR: return "Exit2DR";
            case UpdateDR: return "UpdateDR";
            case SelectIRScan: return "SelectIRScan";
            case CaptureIR: return "CaptureIR";
            case ShiftIR: return "ShiftIR";
            case Exit1IR: return "Exit1IR";
            case PauseIR: return "PauseIR";
            case Exit2IR: return "Exit2IR";
            case UpdateIR: return "UpdateIR";
        }
        return "Unknown";
    }
};

class TAPMachine {
public:
    TAPMachine() : m_state(TAPState::TestLogicReset) {}

    void setRunTest(bool value) {
        m_runTest = value;
    }

    void setEndDR(bool value) {
        m_endDR = value;
    }

    void setEndIR(bool value) {
        m_endIR = value;
    }

    void setRepeat(int value) {
        m_repeat = value;
    }

    bits_t shiftIR(const bits_t& data) {
        setState(TAPState::ShiftIR);
        bits_t result(data.size());
        for (int i = 0; i < data.size(); i++) {
            result.set(i, shiftBit(data[i]));
        }
        return result;
    }

    bits_t shiftDR(const bits_t& data) {
        setState(TAPState::ShiftDR);
        bits_t result(data.size());
        for (int i = 0; i < data.size(); i++) {
            result.set(i, shiftBit(data[i]));
        }
        return result;
    }

    TAPState::Value getState() const {
        return m_state;
    }

private:
    static const int MAX_REPEAT = 100000;

    bool m_runTest = false;
    bool m_endDR = true;
    bool m_endIR = true;
    int m_repeat = 1;
    int m_repeatCount = 0;
    bits_t m_shift;
    TAPState::Value m_state;

    bool shiftBit(bool bit) {
        bool result = false;

        switch (m_state) {
            case TAPState::TestLogicReset:
                if (m_runTest) {
                    setState(TAPState::RunTestIdle);
                }
                break;

            case TAPState::RunTestIdle:
                if (!m_runTest) {
                    setState(TAPState::TestLogicReset);
                }
                else if (!m_endIR) {
                    setState(TAPState::SelectIRScan);
                }
                else if (!m_endDR) {
                    setState(TAPState::SelectDRScan);
                }
                else {
                    setState(TAPState::RunTestIdle);
                }
                break;

            case TAPState::SelectDRScan:
                if (!m_endIR) {
                    setState(TAPState::SelectIRScan);
                }
                else if (m_repeatCount >= m_repeat) {
                    setState(TAPState::RunTestIdle);
                }
                else {
                    setState(TAPState::CaptureDR);
                }
                break;

            case TAPState::CaptureDR:
                setState(TAPState::ShiftDR);
                break;

            case TAPState::ShiftDR:
                result = m_shift.get(0);
                m_shift.set(0, bit);
                if (m_shift.size() > 1) {
                    m_shift = bits_t(m_shift.size() - 1, [&](int i) { return m_shift.get(i + 1); });
                }
                if (m_repeatCount >= m_repeat) {
                    setState(TAPState::Exit1DR);
                }
                break;

            case TAPState::Exit1DR:
                setState(TAPState::PauseDR);
                break;

            case TAPState::PauseDR:
                if (m_endDR) {
                    if (m_repeatCount >= m_repeat) {
                        setState(TAPState::RunTestIdle);
                    }
                    else {
                        setState(TAPState::SelectDRScan);
                    }
                }
                else {
                    setState(TAPState::Exit2DR);
                }
                break;

            case TAPState::Exit2DR:
                setState(TAPState::UpdateDR);
                break;

            case TAPState::UpdateDR:
                m_repeatCount++;
                if (m_endIR) {
                    setState(TAPState::RunTestIdle);
                }
                else {
                    setState(TAPState::SelectIRScan);
                }
                break;

            case TAPState::SelectIRScan:
                if (m_repeatCount >= m_repeat) {
                    setState(TAPState::RunTestIdle);
                }
                else {
                    setState(TAPState::CaptureIR);
                }
                break;

            case TAPState::CaptureIR:
                setState(TAPState::ShiftIR);
                break;

            case TAPState::ShiftIR:
                result = m_shift.get(0);
                m_shift.set(0, bit);
                if (m_shift.size() > 1) {
                    m_shift = bits_t(m_shift.size() - 1, [&](int i) { return m_shift.get(i + 1); });
                }
                if (m_repeatCount >= m_repeat) {
                    setState(TAPState::Exit1IR);
                }
                break;

            case TAPState::Exit1IR:
                setState(TAPState::PauseIR);
                break;

            case TAPState::PauseIR:
                if (m_endIR) {
                    setState(TAPState::RunTestIdle);
                }
                else {
                    setState(TAPState::Exit2IR);
                }
                break;

            case TAPState::Exit2IR:
                setState(TAPState::UpdateIR);
                break;

            case TAPState::UpdateIR:
                m_repeatCount++;
                setState(TAPState::RunTestIdle);
                break;
        }

        return result;
    }

        void setState(TAPState::Value state) {
            cout << "Transition: " << TAPState::toString(m_state) << " -> " << TAPState::toString(state) << endl;
            m_state = state;
            m_shift = bits_t(1, false);
        }

    bits_t m_shift;
};


