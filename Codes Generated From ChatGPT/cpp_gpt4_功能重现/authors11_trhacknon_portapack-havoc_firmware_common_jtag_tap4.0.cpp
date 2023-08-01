#include <iostream>
#include <string>
#include <vector>
#include <map>

enum TAPState {
    TEST_LOGIC_RESET,
    RUN_TEST_IDLE,
    SELECT_DR_SCAN,
    CAPTURE_DR,
    SHIFT_DR,
    EXIT1_DR,
    PAUSE_DR,
    EXIT2_DR,
    UPDATE_DR,
    SELECT_IR_SCAN,
    CAPTURE_IR,
    SHIFT_IR,
    EXIT1_IR,
    PAUSE_IR,
    EXIT2_IR,
    UPDATE_IR,
    NUM_STATES
};

const char *TAPStateNames[] = {
    "TEST_LOGIC_RESET",
    "RUN_TEST_IDLE",
    "SELECT_DR_SCAN",
    "CAPTURE_DR",
    "SHIFT_DR",
    "EXIT1_DR",
    "PAUSE_DR",
    "EXIT2_DR",
    "UPDATE_DR",
    "SELECT_IR_SCAN",
    "CAPTURE_IR",
    "SHIFT_IR",
    "EXIT1_IR",
    "PAUSE_IR",
    "EXIT2_IR",
    "UPDATE_IR"
};

enum TAPAction {
    TMS_0,
    TMS_1,
    NUM_ACTIONS
};

TAPState TAPStateMachine[NUM_STATES][NUM_ACTIONS] = {
    {RUN_TEST_IDLE, TEST_LOGIC_RESET},
    {RUN_TEST_IDLE, SELECT_DR_SCAN},
    {CAPTURE_DR, SELECT_IR_SCAN},
    {SHIFT_DR, EXIT1_DR},
    {SHIFT_DR, EXIT1_DR},
    {PAUSE_DR, UPDATE_DR},
    {PAUSE_DR, EXIT2_DR},
    {SHIFT_DR, UPDATE_DR},
    {RUN_TEST_IDLE, SELECT_DR_SCAN},
    {CAPTURE_IR, TEST_LOGIC_RESET},
    {SHIFT_IR, EXIT1_IR},
    {SHIFT_IR, EXIT1_IR},
    {PAUSE_IR, UPDATE_IR},
    {PAUSE_IR, EXIT2_IR},
    {SHIFT_IR, UPDATE_IR},
    {RUN_TEST_IDLE, SELECT_DR_SCAN}
};

class bits_t {
public:
    bits_t(size_t length) : bits(length) {}

    size_t length() const {
        return bits.size();
    }

    bool get(size_t index) const {
        return bits[index];
    }

    void set(size_t index, bool value) {
        bits[index] = value;
    }

private:
    std::vector<bool> bits;
};

class TAPMachine {
public:
    TAPMachine() : state(TEST_LOGIC_RESET) {}

    void set_run_test(size_t run_test_count) {
        this->run_test_count = run_test_count;
    }

    void set_repeat(size_t repeat_count) {
        this->repeat_count = repeat_count;
    }

    void set_end_ir(TAPState end_ir) {
        this->end_ir = end_ir;
    }

    void set_end_dr(TAPState end_dr) {
        this->end_dr = end_dr;
    }

    bits_t shift_ir(const bits_t &in_bits) {
        return shift_register(CAPTURE_IR, SHIFT_IR, in_bits);
    }

    bits_t shift_dr(const bits_t &in_bits) {
        return shift_register(CAPTURE_DR, SHIFT_DR, in_bits);
    }

    TAPState get_state() const {
        return state;
    }

    const char *get_state_name() const {
        return TAPStateNames[state];
    }

    void apply_action(TAPAction action) {
        state = TAPStateMachine[state][action];
    }

private:
    bits_t shift_register(TAPState capture, TAPState shift, const bits_t &in_bits) {
        navigate_to_state(capture);
        apply_action(TMS_0);
        bits_t out_bits(in_bits.length());
        for (size_t i = 0; i< i < in_bits.length(); ++i) {
            out_bits.set(i, in_bits.get(i));
            if (i == in_bits.length() - 1) {
                apply_action(TMS_1);
            } else {
                apply_action(TMS_0);
            }
        }
        apply_action(TMS_0);
        return out_bits;
    }

    void navigate_to_state(TAPState target_state) {
        while (state != target_state) {
            switch (state) {
                case TEST_LOGIC_RESET:
                    apply_action(TMS_0);
                    break;
                case RUN_TEST_IDLE:
                    if (target_state == CAPTURE_IR) {
                        apply_action(TMS_1);
                    } else {
                        apply_action(TMS_0);
                    }
                    break;
                case SELECT_DR_SCAN:
                    if (target_state == CAPTURE_DR) {
                        apply_action(TMS_0);
                    } else {
                        apply_action(TMS_1);
                    }
                    break;
                case SELECT_IR_SCAN:
                    if (target_state == CAPTURE_IR) {
                        apply_action(TMS_0);
                    } else {
                        apply_action(TMS_1);
                    }
                    break;
                case CAPTURE_DR:
                case SHIFT_DR:
                case EXIT1_DR:
                case PAUSE_DR:
                case EXIT2_DR:
                case UPDATE_DR:
                    navigate_to_state(RUN_TEST_IDLE);
                    break;
                case CAPTURE_IR:
                case SHIFT_IR:
                case EXIT1_IR:
                case PAUSE_IR:
                case EXIT2_IR:
                case UPDATE_IR:
                    navigate_to_state(RUN_TEST_IDLE);
                    break;
            }
        }
    }

    TAPState state;
    size_t run_test_count;
    size_t repeat_count;
    TAPState end_ir;
    TAPState end_dr;
};


